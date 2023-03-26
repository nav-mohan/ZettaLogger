#include "databaseconnection.h"

void DatabaseConnection::setAuthentication(std::string url,std::string user, std::string password, std::string database)
{
    if(m_connectionStatus)
    {
        signalMessage("MySQL connection error","#ERR: You need to close the existing connection...");
        return;
    }
    m_url = url;
    m_user = user;
    m_password = password;
    m_database = database;
    openConnection();
}

void DatabaseConnection::openConnection() {
    try {
        m_con.reset(m_driver->connect(m_url,m_user,m_password));
        m_con->setSchema(m_database);//this is the same as executeQuery("USE m_database");
        m_stmt.reset(m_con->createStatement());
        emit signalMessage("MySQL Database connection","Succesfully connected to MySQL Database!");
        m_connectionStatus = 1;
    }
    catch(sql::SQLException &e) {
        handleSqlException(e,"openConnection",__FILE__,__LINE__);
    }
    resetResults();
}

void DatabaseConnection::welcomeMessage() {
    try {
        m_res.reset(m_stmt->executeQuery("SELECT 'Welcome to MySQL/C++' AS _message"));
        parseResults("_message");
    }
    catch(sql::SQLException &e) {
        handleSqlException(e,"welcomeMessage",__FILE__,__LINE__);
    }
    resetResults();
}

void DatabaseConnection::showTables() {
    try {
        m_res.reset(m_stmt->executeQuery("SHOW TABLES"));
        parseResults(1);
    }
    catch(sql::SQLException &e) {
        handleSqlException(e,"showTables",__FILE__,__LINE__);
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


void DatabaseConnection::handleSqlException(sql::SQLException &e, std::string functionName, std::string fileName, int lineNumber) {
    QString errorInfo = QString ("#ERR: SQLException in %1 (%2) on line %3\n#ERR: %4 (MySQL error code: %5, SQLState: %6)")
    .arg(fileName.c_str())
    .arg(functionName.c_str())
    .arg(lineNumber)
    .arg(e.what())
    .arg(e.getErrorCode())
    .arg(e.getSQLState().c_str());

    emit signalMessage("MySQL Connection Error",errorInfo);
    
    m_con.reset();
    m_stmt.reset();
    m_res.reset();
    m_connectionStatus=0;
}