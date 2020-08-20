find_package(Qt5 COMPONENTS Widgets LinguistTools REQUIRED)

add_executable(app
    src/main.cpp
    src/sunshinedesktop.cpp
    inc/sunshinedesktop.h
    src/sunshinedesktop.ui
    )

target_link_libraries(app PRIVATE Qt5::Widgets)
qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})

target_include_directories(app PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/inc")
