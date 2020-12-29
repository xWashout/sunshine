find_package(Qt5 COMPONENTS Widgets LinguistTools REQUIRED)

add_executable(app
    src/main.cpp
    src/sunshinedesktop.cpp
    inc/sunshinedesktop.h
    src/sunshinedesktop.ui
    inc/rasp3b_sensor_data.h
    src/rasp3b_sensor_data.cpp
    inc/rasp0_sensor_data.h
    src/rasp0_sensor_data.cpp
    )

target_link_libraries(app PRIVATE mqtt Qt5::Widgets paho-mqttpp3)
qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})

target_include_directories(app PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/inc")

