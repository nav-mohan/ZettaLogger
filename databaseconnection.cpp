#include "databaseconnection.h"

void DatabaseConnection::setAuthentication(char *url,std::string user, std::string password, std::string database)
{
    if(m_connectionStatus)
    {
        displayError("#ERR: You need to close the existing connection...");
        return;
    }
    m_url = url;
    m_user = user;
    m_password = password;
    m_database = database;

}

void DatabaseConnection::openConnection() {
    try {
        m_con.reset(m_driver->connect(m_url,m_user,m_password));
        m_con->setSchema(m_database);//this is the same as executeQuery("USE m_database");
        m_stmt.reset(m_con->createStatement());
        std::cout << "CLASS CONNECTED!\n";
        m_connectionStatus = 1;
    }
    catch(sql::SQLException &e) {
        displaySqlException(e,"openConnection",__FILE__,__LINE__);
    }
    resetResults();
}

void DatabaseConnection::welcomeMessage() {
    try {
        m_res.reset(m_stmt->executeQuery("SELECT 'Welcome to MySQL/C++' AS _message"));
        parseResults("_message");
    }
    catch(sql::SQLException &e) {
        displaySqlException(e,"welcomeMessage",__FILE__,__LINE__);
    }
    resetResults();
}

void DatabaseConnection::showTables() {
    try {
        m_res.reset(m_stmt->executeQuery("SHOW TABLES"));
        parseResults(1);
    }
    catch(sql::SQLException &e) {
        displaySqlException(e,"showTables",__FILE__,__LINE__);
    }
    resetResults();
}

void DatabaseConnection::parseResults(int columnIndex) {
    while(m_res->next())
        qDebug() << m_res->getString(columnIndex).c_str();
}

void DatabaseConnection::parseResults(std::string columnName) {
    while(m_res->next())
        qDebug() << m_res->getString(columnName).c_str();
}



void DatabaseConnection::displaySqlException(sql::SQLException &e, std::string functionName, std::string fileName, int lineNumber) {
    qDebug("#ERR: SQLException in %s (%s) on line %d",fileName.c_str(),functionName.c_str(),lineNumber);
    qDebug(
        "#ERR: %s (MySQL error code: %d, SQLState: %s)",
        e.what(),
        e.getErrorCode(),
        e.getSQLState().c_str()
        );
}

void DatabaseConnection::displayError(std::string error)
{
    qDebug("%s",error.c_str());
}