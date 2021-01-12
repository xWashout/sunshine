find_package(Qt5 COMPONENTS Widgets Charts LinguistTools REQUIRED)

add_executable(app
    src/main.cpp
    src/sunshinedesktop.cpp
    inc/sunshinedesktop.h
    src/sunshinedesktop.ui
    src/sessions_analyzer.ui
    inc/rasp3b_sensor_data.h
    src/rasp3b_sensor_data.cpp
    inc/rasp0_sensor_data.h
    src/rasp0_sensor_data.cpp
    inc/qt_chart_wrapper.h
    src/qt_chart_wrapper.cpp
    inc/sessions_analyzer.h
    src/sessions_analyzer.cpp
    inc/serializator.h
    src/serializator.cpp
    inc/measurements_data.h
    src/measurements_data.cpp
    )

#target_compile_options(app PUBLIC -fsanitize=address)
#set(CMAKE_CXX_FLAGS_DEBUG -fsanitize=address CACHE "" INTERNAL)
#set(CMAKE_EXE_LINKER_FLAGS_DEBUG -fsanitize=address CACHE "" INTERNAL)

target_link_libraries(app PRIVATE mqtt Qt5::Widgets Qt5::Charts paho-mqttpp3)
qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})

target_include_directories(app PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/inc")
