cmake_minimum_required(VERSION 3.16)
project(owloApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)   # Active la génération automatique des moc_*.cpp
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets PrintSupport)

add_executable(owloApp
    FrameProvider.cpp
    HeatmapWidget.cpp
    main.cpp
    ProfileWidget.cpp
    qcustomplot.cpp
    FrameProvider.h
    HeatmapWidget.h
    ProfileWidget.cpp
    qcustomplot.h
)

target_link_libraries(owloApp PRIVATE Qt6::Widgets Qt6::PrintSupport)
