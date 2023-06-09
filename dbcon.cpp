#include "dbcon.h"

DbCon::DbCon()
{
    m_ctx = new boost::asio::io_context();
    boost::asio::ssl::context ssl_ctx(boost::asio::ssl::context::tls_client);
    m_conn = new boost::mysql::tcp_ssl_connection(*m_ctx, ssl_ctx);
}

DbCon::~DbCon()
{
    if(m_conn != nullptr && connectionStatus())
        m_conn->close();
    delete m_ctx;
    delete m_conn;
}
void DbCon::setAuth(std::string username, std::string password, std::string databasename, std::string hostname)
{
    m_username = "zettalogger_user";
    m_password = "zettalogger_password";
    m_databasename = "zettalogger";
    m_hostname = "127.0.0.1";
}

void DbCon::openConnection()
{
    boost::mysql::handshake_params params(m_username,m_password,m_databasename);

    boost::asio::ip::tcp::resolver resolver(m_ctx->get_executor());
    auto endpoints = resolver.resolve(m_hostname.c_str(), boost::mysql::default_port_string);
    try
    {
        m_conn->connect(*endpoints.begin(),params);
        prepareStatements();
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
    if(m_conn == nullptr) return false;

    boost::mysql::error_code ec;
    boost::mysql::diagnostics diag;
    m_conn->ping(ec, diag);
    if(ec.value() != boost::system::errc::success)
    {
        std::cout << "ERROR CODE: " << ec << ":" << ec.what() << "\nSERVER MESSAGE : " <<diag.server_message() << "\n";
        return false;
    }

    std::cout << "ALL GOOD!" << ec.value() << "|" << ec.what() << "\nSERVER MESSAGE : " <<diag.server_message() << "\n";
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

    return true;
}

void DbCon::countRecords()
{
    try
    {
        const char *sql = "SELECT count(*) FROM zettalogger";
        m_conn->query(sql,m_result);
        std::cout << "FOUND " << m_result.rows().at(0).at(0) << " ROWS\n";
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


void DbCon::prepareStatements()
{
    m_recordInsertStatement = m_conn->prepare_statement("INSERT INTO zettalogger \
(logevent_id,logevent_type,air_start_time,air_stop_time,air_date,asset_id,asset_type_id,asset_type_name,\
asset_filename,asset_participant_name,asset_participant_id,asset_sponsor_id,asset_sponsor_name,\
asset_product_id,asset_product_name,comment,rw_local,rw_cancon,rw_hit,rw_female,rw_indigenous,rw_explicit,rw_release_date,rw_genre,\
artist_id,artist_name,album_id,album_name,title) \
VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?);");

    // m_recordReadStatement = m_conn->prepare_statement("SELECT * FROM zettalogger WHERE air_date = '?';");
    m_recordReadStatement = m_conn->prepare_statement("SELECT * FROM zettalogger;");
}

void DbCon::readRecord(QTcpSocket *socket, QString air_date)
{
    qDebug() << "Db::Con readRecord()" << socket << air_date;
    
    if(m_conn == nullptr || !connectionStatus()) {
        qDebug("NO CONNECTION TO DATABASE YOU IDIOT!");
        emit deliverRecord(socket,"Could not establish connection to database");
        return;
    }

    try
    {
        boost::mysql::results result;
        // m_conn->execute_statement(m_recordReadStatement, std::make_tuple(air_date.toStdString()), result);
        const char* sql = "SELECT artist_name,album_name,title FROM zettalogger";
        m_conn->query(sql, result);
        qDebug() << "Records ready for deliver" << air_date;
        std::string resString("[");
        for (boost::mysql::row_view zettalogs : result.rows())
        {
            resString += "{";
            resString += "\"artist\":";
            resString += "\"";
            resString += zettalogs.at(0).as_string();
            resString += "\"";
            resString += ",";
            resString += "\"album\":";
            resString += "\"";
            resString += zettalogs.at(1).as_string();
            resString += "\"";
            resString += ",";
            resString += "\"title\":";
            resString += "\"";
            resString += zettalogs.at(2).as_string();
            resString += "\"";
            resString += "},";
        }
        resString += "{}]";

        emit deliverRecord(socket,QString::fromStdString(resString));
    }
    catch(boost::wrapexcept<boost::bad_lexical_cast> &e)
    {
        std::cerr << e.what() << '\n';
    }
    catch(const boost::mysql::error_with_diagnostics& err)
    {
        handleSqlException(err);
    }
    catch(const std::exception &err)
    {
        qDebug("std::exception ");
        handleStandardException(err);
    }
}

void DbCon::insertRecord(QMap<QString,QString> &map)
{
    try
    {
        Record rec(map);
        qDebug("Begin Executing Statement");
        qDebug() << map;
        boost::mysql::results result;
        m_conn->execute_statement(
            m_recordInsertStatement,
            std::make_tuple(
                rec.logevent_id,
                rec.logevent_type,
                boost::posix_time::to_iso_extended_string(rec.air_start_time),
                boost::posix_time::to_iso_extended_string(rec.air_stop_time),
                boost::gregorian::to_iso_extended_string(rec.air_date),
                rec.asset_id,
                rec.asset_type_id,
                rec.asset_type_name,
                rec.asset_filename,
                rec.asset_participant_name,
                rec.asset_participant_id,
                rec.asset_sponsor_id,
                rec.asset_sponsor_name,
                rec.asset_product_id,
                rec.asset_product_name,
                rec.comment,
                rec.rw_local,
                rec.rw_cancon,
                rec.rw_hit,
                rec.rw_female,
                rec.rw_indigenous,
                rec.rw_explicit,
                boost::gregorian::to_iso_extended_string(rec.rw_release_date),
                rec.rw_genre,
                rec.artist_id,
                rec.artist_name,
                rec.album_id,
                rec.album_name,
                rec.title
                ),
            result
        );        
    qDebug("Done Executing Statement");
    
    }
    catch(boost::wrapexcept<boost::bad_lexical_cast> &e)
    {
        std::cerr << e.what() << '\n';
    }
    catch(const boost::mysql::error_with_diagnostics& err)
    {
        handleSqlException(err);
    }
    catch(const std::exception &err)
    {
        qDebug("std::exception ");
        handleStandardException(err);
    }
}
