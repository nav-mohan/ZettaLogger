cmake_minimum_required(VERSION 3.10)
project(ZettaLogger LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/opt/homebrew/Cellar/qt@5/5.15.8_2")
set(QT_REQUIRED_PACKAGES Core Multimedia Gui Widgets Network)
find_package(Qt5 REQUIRED COMPONENTS ${QT_REQUIRED_PACKAGES})

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CPP_SOURCE_FILES main.cpp mainwindow.cpp databaseconnection.cpp zettalistenerconnection.cpp)
qt_wrap_ui(HEADER_FILES mainwindow.ui)
add_executable(${PROJECT_NAME} 
	${CPP_SOURCE_FILES}
	${HEADER_FILES}
	)

target_include_directories(${PROJECT_NAME} PUBLIC /usr/local/mysql-connector-c++-8.0.32/include)

target_link_libraries(
    ${PROJECT_NAME} PUBLIC
    Qt5::Core Qt5::Gui Qt5::Multimedia Qt5::Widgets Qt5::Network
    /usr/local/mysql-connector-c++-8.0.32/lib64/libmysqlcppconn.dylib)