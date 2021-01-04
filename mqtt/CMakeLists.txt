find_package(Qt5 COMPONENTS Widgets REQUIRED)
add_library(mqtt
            src/mqtt_wrapper.cpp
            inc/mqtt_wrapper.h
            inc/mqtt_conf_data.h
            )

target_include_directories(mqtt PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../mqtt/inc")
target_include_directories(mqtt PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../app/inc/")
target_link_libraries(mqtt PRIVATE Qt5::Widgets)

add_subdirectory ("${CMAKE_CURRENT_SOURCE_DIR}/mqtt_lib/paho.mqtt.cpp")
