#include <inc/mqtt_wrapper.h>
#include <inc/mqtt_conf_data.h>

#include <stdio.h>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cctype>
#include <thread>
#include <chrono>
#include "mqtt/async_client.h"
#include <mutex>
#include <iostream>
#include <atomic>

std::mutex n;

namespace mqtt_wrapper {

int MqttWrapper::Receiver()
{
    mqtt::connect_options connOpts;
    connOpts.set_keep_alive_interval(20);
    connOpts.set_clean_session(true);

    mqtt::async_client cli(mqttConfData.serverAddress, mqttConfData.clientId);
    mqtt::const_string_collection_ptr stringCollectionPtr(&mqttConfData.topics);
    try {
        std::cerr << "Connecting to the MQTT server...\n";
        cli.connect(connOpts)->wait();
        cli.start_consuming();
        cli.subscribe(stringCollectionPtr, mqttConfData.qualityOfServices)->wait();
        std::cerr << "Subscribe Ok!\n";

        // Consume messages
        while (true) {
            auto msg = cli.consume_message();
            if (!msg) {
                std::cerr << "Error during consume message!\n";
                break;
            }
            std::cerr << "Topic:" << msg->get_topic() << " \nData:" << msg->to_string() << std::endl;
        }

        // Disconnect
        std::cerr << "Shutting down and disconnecting from the MQTT server...\n";
        cli.unsubscribe(stringCollectionPtr)->wait();
        cli.stop_consuming();
        cli.disconnect()->wait();
        std::cerr << "OK";
    }
    catch (const mqtt::exception& exc) {
        std::cerr << "MQTT Exception =%s\n";
        return 1;
    }
    return 0;
}

class callback : public virtual mqtt::callback
{
public:
    void connection_lost(const std::string& cause) override {
        std::cerr << "\nConnection lost" << std::endl;
        if (!cause.empty())
            std::cerr << "\tcause: " << cause << std::endl;
    }

    void delivery_complete(mqtt::delivery_token_ptr tok) override {
        std::cerr << "\tDelivery complete for token: "
            << (tok ? tok->get_message_id() : -1) << std::endl;
    }
};

class action_listener : public virtual mqtt::iaction_listener
{
protected:
    void on_failure(const mqtt::token& tok) override {
        std::cerr << "\tListener failure for token: "
            << tok.get_message_id() << std::endl;
    }

    void on_success(const mqtt::token& tok) override {
        std::cerr << "\tListener success for token: "
            << tok.get_message_id() << std::endl;
    }
};

class delivery_action_listener : public action_listener
{
    std::atomic<bool> done_;

    void on_failure(const mqtt::token& tok) override {
        action_listener::on_failure(tok);
        done_ = true;
    }

    void on_success(const mqtt::token& tok) override {
        action_listener::on_success(tok);
        done_ = true;
    }

public:
    delivery_action_listener() : done_(false) {}
    bool is_done() const { return done_; }
};

int MqttWrapper::Publisher(const char* data, const std::string topic)
{
    std::string	address  = mqttConfData.serverAddress,
                clientID = mqttConfData.clientId;

    std::cerr << "Initializing for server '" << address << "'..." << std::endl;
    mqtt::async_client client(address, clientID);

    callback cb;
    client.set_callback(cb);

    mqtt::connect_options conopts;
    mqtt::message willmsg(topic, mqttConfData.lastWillAndStatement, 1, true);
    mqtt::will_options will(willmsg);
    conopts.set_will(will);

    std::cerr << "  ...OK" << std::endl;

    try {
        std::cerr << "\nConnecting..." << std::endl;
        mqtt::token_ptr conntok = client.connect(conopts);
        std::cerr << "Waiting for the connection..." << std::endl;
        conntok->wait();
        std::cerr << "  ...OK" << std::endl;

        mqtt::message_ptr pubmsg; // to delete supressing compile error!!!
        std::cerr << "\nSending final message..." << std::endl;
        delivery_action_listener deliveryListener;
        pubmsg = mqtt::make_message(topic, data);
        client.publish(pubmsg, nullptr, deliveryListener);

        while (!deliveryListener.is_done()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        std::cerr << "OK" << std::endl;


        // Disconnect
        std::cerr << "\nDisconnecting..." << std::endl;
        conntok = client.disconnect();
        conntok->wait();
        std::cerr << "  ...OK" << std::endl;
    }
    catch (const mqtt::exception& exc) {
        std::cerr << exc.what() << std::endl;
        return 1;
    }
    return 0;
}

} // namespace mqtt_wrapper
