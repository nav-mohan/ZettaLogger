#if !defined(DATABASECONNECTION_H)
#define DATABASECONNECTION_H
#include <QDebug>

#include <string>
#include <stdlib.h>
#include <memory>
#include <mysql/jdbc.h>
#include <QObject>

class DatabaseConnection : public QObject {
Q_OBJECT
public:
    explicit DatabaseConnection() : m_connectionStatus(0),m_driver(sql::mysql::get_driver_instance()){;}
    ~DatabaseConnection(){m_res.reset();m_stmt.reset();m_con.reset(); delete m_url;};
    void setAuthentication(char *url,std::string user, std::string password, std::string database);
    void openConnection();
    void welcomeMessage();
    void showTables();
    void displaySqlException(sql::SQLException &e, std::string functionName, std::string fileName, int lineNumber);
    void displayError(std::string);
    bool status(){return m_connectionStatus;}
    void parseResults(int columnIndex);
    void parseResults(std::string columnName);
    inline void resetResults(){m_res.reset();}
    void closeConnection(){m_res.reset();m_stmt.reset();m_con.reset();}

private:
    char *m_url;
    std::string m_user;
    std::string m_password;
    std::string m_database;
    sql::Driver *m_driver;
    std::unique_ptr<sql::Connection> m_con;
    std::unique_ptr<sql::Statement> m_stmt;
    std::unique_ptr<sql::ResultSet> m_res;
    bool m_connectionStatus;
};

#endif // DATABASECONNECTION_H
