#if !defined(RECORD_H)
#define RECORD_H
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <string>

struct Record
{
    uint64_t logevent_id;
    std::string logevent_type;
    boost::posix_time::ptime air_start_time;
    boost::posix_time::ptime air_stop_time;
    boost::gregorian::date air_date;
    uint32_t asset_id;
    std::string asset_filename;
    uint32_t asset_type_id;
    std::string asset_type_name;
    std::string asset_participant_name;
    uint32_t asset_participant_id;
    uint32_t asset_sponsor_id;
    std::string asset_sponsor_name;
    uint32_t asset_product_id;
    std::string asset_product_name;
    std::string comment;
    uint8_t rw_local;
    uint8_t rw_cancon;
    uint8_t rw_hit;
    uint8_t rw_female;
    uint8_t rw_indigenous;
    uint8_t rw_explicit;
    boost::gregorian::date rw_release_date;
    std::string rw_genre;
    uint32_t artist_id;
    std::string artist_name;
    uint32_t album_id;
    std::string album_name;
    std::string title;

    Record(QMap<QString,QString> &map)
    {
        qDebug() << map;
        std::string temp;

        logevent_id = map["LogEventID"].toULongLong();
        logevent_type = map["LogEventType"].toStdString();
        
        temp = map["AirStarttimeLocal"].replace("-","").replace(":","").replace(" ","T").replace("Z","").toStdString();
        air_start_time = boost::posix_time::from_iso_string(temp);
        
        temp = map["AirStoptimeLocal"].replace("-","").replace(":","").replace(" ","T").replace("Z","").toStdString();
        air_stop_time = boost::posix_time::from_iso_string(temp);

        temp = map["AirDate"].replace("-","").toStdString();
        air_date = boost::gregorian::from_undelimited_string(temp);

        asset_id= map["AssetID"].toULongLong();
        asset_filename = map["AssetFileName"].toStdString();
        asset_type_id = map["AssetTypeID"].toULongLong();
        asset_type_name  = map["AssetTypeName "].toStdString();
        asset_participant_id = map["ParticipantID"].toULongLong();
        asset_participant_name = map["ParticipantName"].toStdString();
        asset_sponsor_id = map["SponsorID"].toULongLong();
        asset_sponsor_name = map["SponsorName"].toStdString();
        asset_product_id = map["ProductID"].toULongLong();
        asset_product_name = map["ProductName"].toStdString();

        comment = map["Comment"].toStdString();
        
        rw_local = map["RwLocal"].toULongLong();
        rw_cancon = map["RwCanCon"].toULongLong();
        rw_hit = map["RwHit"].toULongLong();
        rw_female = map["RwFemale"].toULongLong();
        rw_indigenous = map["RwIndigenous"].toULongLong();
        rw_explicit = map["RwExplicit"].toULongLong();
        
        if(!map.contains("RwReleaseDate") || map["RwReleaseDate"].isEmpty() || map["RwReleaseDate"].replace(" ","").isEmpty()){
            rw_release_date = boost::gregorian::date(boost::date_time::not_a_date_time);
        }
        else{
            temp = map["RwReleaseDate"].replace("-","").toStdString();
            rw_release_date = boost::gregorian::from_undelimited_string(temp);
        }
        rw_genre = map["RwGenre"].toStdString();
        artist_id = map["ArtistID"].toULongLong();
        artist_name = map["ArtistName"].toStdString();
        album_id = map["AlbumID"].toULongLong();
        album_name = map["AlbumName"].toStdString();
        title = map["Title"].toStdString();

    }
};

#endif//RECORD_H
