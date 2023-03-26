#include "dbcon.h"

void DbCon::setAuth(std::string username, std::string password, std::string databasename, std::string hostname)
{
    m_username = "zettalogger_user";
    m_password = "zettalogger_password";
    m_databasename = "zettalogger";
    m_hostname = "127.0.0.1";
}

void DbCon::openConnection()
{
    boost::asio::io_context ctx;
    boost::mysql::handshake_params params(m_username,m_password,m_databasename);
    boost::asio::ssl::context ssl_ctx(boost::asio::ssl::context::tls_client);
    m_conn = new boost::mysql::tcp_ssl_connection(ctx, ssl_ctx);

    boost::asio::ip::tcp::resolver resolver(ctx.get_executor());
    auto endpoints = resolver.resolve(m_hostname.c_str(), boost::mysql::default_port_string);
    try
    {
        m_conn->connect(*endpoints.begin(),params);
        boost::mysql::error_code ec;
        boost::mysql::diagnostics diag;
        // m_conn->ping(&ec, &diag);
        m_conn->ping();
    }
    catch(const boost::mysql::error_with_diagnostics& err)
    {
        handleSqlException(err);
    }
    catch(const std::exception &err)
    {
        handleStandardException(err);
    }
}

void DbCon::handleSqlException(const boost::mysql::error_with_diagnostics& err)
{
    qDebug() << "ERROR:  " << err.what() << "\n";
    std::cout << err.get_diagnostics().server_message()  << "\n";
    return;
}

void DbCon::handleStandardException(const std::exception &err)
{
    qDebug() << "ERROR: " << err.what() << '\n';
    return;
}

bool DbCon::connectionStatus()
{
    const char *sql = "SELECT 'Hello World!'";
    m_conn->query(sql,m_result);
    
    boost::mysql::rows r = m_result.rows();
    if(r.empty())
        return false;

    boost::mysql::row_view r0 = r.at(0);
    if(r0.empty())
        return false;

    boost::mysql::field_view f00 = r0.at(0);
    std::cout << "Database Response: " << f00 << "\n";
    if(f00.is_null())
        return false;
    if(!f00.is_string())
        return false;

    std::string result_string = f00.as_string();
    if(strcmp(result_string.c_str(),"Hello World!"))
        return false;

    
    m_conn->ping();

    return true;
}

void DbCon::countRecords()
{
    try
    {
    const char *sql = "SELECT count(*) FROM zettalogger";
    m_conn->query(sql,m_result);
    std::cout << "FOUND " << m_result.rows().at(0).at(0) << " ROWS\n";
        /* code */
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}


void DbCon::prepareStatements()
{
    try
    {
    m_recordInserStatement = m_conn->prepare_statement(
        "INSERT INTO zettalogger \
        (logevent_id, logevent_type, air_date, rw_local, artist_name, album_name, title) \
        VALUES \
        (?, ?, ?, ?, ?, ?, ?);"
    );
        /* code */
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}

void DbCon::insertRecord()
{
    try
    {
    m_conn->execute_statement(
        m_recordInserStatement,
        std::make_tuple(1234,"LIVE","2020-10-10",0,"DRAKE","L0V3rBoi","35y/oCreepyMan"),
        m_result
    );        
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    

}
