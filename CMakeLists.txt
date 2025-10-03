cmake_minimum_required(VERSION 3.16)
project(owloApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)   # Active la génération automatique des moc_*.cpp
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(owloApp
    main.cpp
    HeatmapWidget.cpp
    FrameProvider.cpp
    HeatmapWidget.h
    FrameProvider.h
)

target_link_libraries(owloApp PRIVATE Qt6::Widgets)
