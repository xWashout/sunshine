add_library(mqtt
            src/mqtt_wrapper.cpp
            inc/mqtt_wrapper.h
            )

target_include_directories(mqtt PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/inc")
