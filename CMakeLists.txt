cmake_minimum_required(VERSION 3.10)
project(ZettaLogger LANGUAGES CXX)
set (CMAKE_CXX_STANDARD 11)


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(OPENSSL_PREFIX_PATH "/opt/homebrew/Cellar/openssl@1.1/1.1.1t")
set(QT5_PREFIX_PATH "/opt/homebrew/Cellar/qt@5/5.15.8_2")
set(CMAKE_PREFIX_PATH "${OPENSSL_PREFIX_PATH}" "${QT5_PREFIX_PATH}")
set(QT_REQUIRED_PACKAGES Core Multimedia Gui Widgets Network)

find_package(OpenSSL REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS ${QT_REQUIRED_PACKAGES})
find_package(Boost REQUIRED COMPONENTS headers)
find_package(Threads REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CPP_SOURCE_FILES 
    main.cpp 
    mainwindow.cpp 
    databaseconnection.cpp 
    dbcon.cpp 
    zettalistenerconnection.cpp
    httpserver.cpp
    )
qt_wrap_ui(HEADER_FILES mainwindow.ui)

add_subdirectory(
    /Users/nav/Projects_CCPP/boostlib/mySqlClient_boost/mysql-master 
    /Users/nav/Projects_CCPP/boostlib/mySqlClient_boost/mysql-master/build
    )

set(BOOST_MYSQL_INCLUDE_DIR "/Users/nav/Projects_CCPP/boostlib/mySqlClient_boost/mysql-master/include")

add_executable(${PROJECT_NAME} ${CPP_SOURCE_FILES} ${HEADER_FILES})

target_include_directories(
    ${PROJECT_NAME} PUBLIC 
    /usr/local/mysql-connector-c++-8.0.32/include
    ${BOOST_MYSQL_INCLUDE_DIR}
    )

target_link_libraries(
    ${PROJECT_NAME} PUBLIC
    Qt5::Core Qt5::Gui Qt5::Multimedia Qt5::Widgets Qt5::Network
    Boost::headers Threads::Threads OpenSSL::Crypto OpenSSL::SSL
    /usr/local/mysql-connector-c++-8.0.32/lib64/libmysqlcppconn.dylib
    )