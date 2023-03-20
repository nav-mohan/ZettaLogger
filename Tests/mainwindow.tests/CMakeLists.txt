cmake_minimum_required(VERSION 3.10)

project(test_mainwindow VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
enable_testing(true)

get_filename_component(PROJECT_BASE_DIR ../../ ABSOLUTE)
include_directories(${PROJECT_BASE_DIR}) # points to mainwindow.h/cpp zettalistenerconnection.h/cpp databaseconnection.h/cpp

set(CMAKE_PREFIX_PATH "/opt/homebrew/Cellar/qt@5/5.15.8_2")
find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets Multimedia Test Network)

add_definitions(-DIS_TESTING=TRUE)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(
    CPP_SOURCE_FILES 
	main.cpp 
    mainwindow.tests.h
    ${PROJECT_BASE_DIR}/mainwindow.cpp
    ${PROJECT_BASE_DIR}/zettalistenerconnection.cpp
    ${PROJECT_BASE_DIR}/databaseconnection.cpp
	)
qt_wrap_ui(
    UI_FILES 
	${PROJECT_BASE_DIR}/mainwindow.ui 
	)
add_executable(
    ${PROJECT_NAME} 
    ${CPP_SOURCE_FILES} 
    ${UI_FILES}
    )

add_test(
    NAME ${PROJECT_NAME} 
    COMMAND ${PROJECT_NAME}
    )

target_include_directories(
    ${PROJECT_NAME} PUBLIC 
    /usr/local/mysql-connector-c++-8.0.32/include
    )
    
target_link_libraries(
    ${PROJECT_NAME} 
    Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Multimedia Qt5::Test Qt5::Network
    /usr/local/mysql-connector-c++-8.0.32/lib64/libmysqlcppconn.dylib
    )
