#if !defined(DBCON_H)
#define DBCON_H

#include <QDebug>
#include <iostream>

#include <string>
#include <stdlib.h>
#include <memory>
#include <QObject>
#include <QMessageBox>
#include <boost/mysql.hpp>


class DbCon : public QObject {
Q_OBJECT
public:
    DbCon(){};
    ~DbCon(){};
    void setAuth(std::string username, std::string password, std::string databasename, std::string hostname);
    void prepareStatements();
    void openConnection();
    bool connectionStatus();
    void countRecords();
    void insertRecord();

    void handleSqlException(const boost::mysql::error_with_diagnostics& err);
    void handleStandardException(const std::exception &err);
    std::string m_username;
    std::string m_password;
    std::string m_databasename;
    std::string m_hostname;

    boost::mysql::tcp_ssl_connection *m_conn; // a single tcp connection
    boost::mysql::results m_result;
    boost::mysql::statement m_recordInserStatement;
};

#endif // DBCON_H
