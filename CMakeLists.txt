cmake_minimum_required(VERSION 3.5)

project(sunshine LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(mqtt)
add_subdirectory(app)
#add_executable(sunshine
#               app/src/main.cpp)





#if(ANDROID)
#  add_library(sunshine SHARED
#    app/main.cpp
#    app/sunshinedesktop.cpp
#    app/sunshinedesktop.h
#    app/sunshinedesktop.ui
#    ${TS_FILES}
#  )
#else()
#  add_executable(sunshine
#    app/main.cpp
#    app/sunshinedesktop.cpp
#    app/sunshinedesktop.h
#    app/sunshinedesktop.ui
#    ${TS_FILES}
#  )
#endif()

#target_link_libraries(sunshine PRIVATE Qt5::Widgets)

#qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
