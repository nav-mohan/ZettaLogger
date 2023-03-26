-- To run this script inside mysql CLI.
-- source /path/to/db_setup.sql

-- Connection system variables
SET NAMES utf8;

-- Database
DROP DATABASE IF EXISTS zettalogger;
CREATE DATABASE zettalogger;
USE zettalogger;

-- Tables
CREATE TABLE zettalogger (
    rw_event_id INTEGER NOT NULL AUTO_INCREMENT,
    creation_ts TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
    modification_ts TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
    logevent_id BIGINT NOT NULL UNIQUE,
    logevent_type VARCHAR(255) NOT NULL,
    air_start_time TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
    air_stop_time TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
    air_date DATE NOT NULL,
    asset_id INTEGER,
    asset_filename VARCHAR(255),
    asset_participant_name VARCHAR(255),
    asset_participant_id INTEGER,
    asset_sponsor_id INTEGER,
    asset_sponsor_name VARCHAR(255),
    asset_product_id INTEGER,
    asset_product_name VARCHAR(255),
    comment TEXT,
    rw_local INTEGER,
    rw_cancon INTEGER,
    rw_hit INTEGER,
    rw_female INTEGER,
    rw_indigenous INTEGER,
    rw_explicit INTEGER,
    rw_release_date VARCHAR(64),
    rw_genre VARCHAR(255),
    artist_id INTEGER,
    artist_name VARCHAR(255),
    album_id INTEGER,
    album_name VARCHAR(255),
    title VARCHAR(255),
    PRIMARY KEY (rw_event_id)
);

-- CREATE TABLE employee(
--     id INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
--     first_name VARCHAR(100) NOT NULL,
--     last_name VARCHAR(100) NOT NULL,
--     salary DOUBLE,
--     company_id CHAR(10) NOT NULL,
--     FOREIGN KEY (company_id) REFERENCES company(id)
-- );
    
-- INSERT INTO company (name, id) VALUES
--     ("Award Winning Company, Inc.", "AWC"),
--     ("Sector Global Leader Plc", "SGL"),
--     ("High Growth Startup, Ltd", "HGS")
-- ;
-- INSERT INTO employee (first_name, last_name, salary, company_id) VALUES
--     ("Efficient", "Developer", 30000, "AWC"),
--     ("Lazy", "Manager", 80000, "AWC"),
--     ("Good", "Team Player", 35000, "HGS"),
--     ("Enormous", "Slacker", 45000, "SGL"),
--     ("Coffee", "Drinker", 30000, "HGS"),
--     ("Underpaid", "Intern", 15000, "AWC")
-- ;

-- User
DROP USER IF EXISTS 'zettalogger_user'@'%';
CREATE USER 'zettalogger_user'@'%' IDENTIFIED WITH 'mysql_native_password';
ALTER USER 'zettalogger_user'@'%' IDENTIFIED BY 'zettalogger_password';
GRANT ALL PRIVILEGES ON zettalogger.* TO 'zettalogger_user'@'%';
FLUSH PRIVILEGES;
