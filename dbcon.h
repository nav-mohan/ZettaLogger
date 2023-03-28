#if !defined(DBCON_H)
#define DBCON_H

#include <QDebug>
#include <iostream>

#include <string>
#include <stdlib.h>
#include <memory>
#include <QObject>
#include <QMessageBox>
#include <QTcpSocket>
#include <boost/mysql.hpp>

#include "record.h"

class DbCon : public QObject {
Q_OBJECT
public:
    DbCon();
    ~DbCon();
    void setAuth(std::string username, std::string password, std::string databasename, std::string hostname);
    void prepareStatements();
    void openConnection();
    bool connectionStatus();
    void countRecords();
    void insertRecord(QMap<QString,QString> &map);
    void readRecord(QTcpSocket *socket, QString air_date);

    void handleSqlException(const boost::mysql::error_with_diagnostics& err);
    void handleStandardException(const std::exception &err);
    std::string m_username;
    std::string m_password;
    std::string m_databasename;
    std::string m_hostname;

    boost::asio::io_context *m_ctx = nullptr;
    boost::mysql::tcp_ssl_connection *m_conn = nullptr; // a single tcp connection
    boost::mysql::results m_result;
    boost::mysql::statement m_recordInsertStatement;
    boost::mysql::statement m_recordReadStatement;
    boost::mysql::statement ps;

signals:
    void alert(const QString &windowTitle, const QString &windowInfo);
    void appendLog(const QString &str);
    void connectionChanged(int);
    void deliverRecord(QTcpSocket *socket, QString record);
};

#endif // DBCON_H
