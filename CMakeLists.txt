cmake_minimum_required(VERSION 3.16)
project(GPACalculator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)

add_executable(GPACalculator
    src/main.cpp
    src/mainwindow.cpp
    src/mainwindow.h
    src/course.cpp
    src/course.h
)

target_link_libraries(GPACalculator
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)