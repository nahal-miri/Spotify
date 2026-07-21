#include "database.h"
#include <QSqlError>
#include <QDebug>
#include <QSqlQuery>


Database::Database() {}

Database& Database::getInstance() {
    static Database instance;
    return instance;
}

bool Database::open() {
    db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName("spotify.db");

    if(!db.open()) {
        qDebug() << db.lastError().text();
        return false;
    }

    if(!createTables()) {
        return false;
    }

    return true;
}

void Database::close() {
    if(db.isOpen())
        db.close();
}

QSqlDatabase& Database::getDatabase() {
    return db;
}

bool Database::createTables() {
    QSqlQuery query;

    query.exec(
        "CREATE TABLE IF NOT EXISTS songs ("
        "songId INTEGER PRIMARY KEY,"
        "songName TEXT NOT NULL,"
        "releaseYear INTEGER,"
        "genre TEXT,"
        "audioFilePath TEXT,"
        "artistId INTEGER NOT NULL,"
        "albumId INTEGER DEFAULT 0"
        ");");

    query.exec(
        "CREATE TABLE IF NOT EXISTS artists ("
        "artistId INTEGER PRIMARY KEY,"
        "fullName TEXT NOT NULL,"
        "userName TEXT UNIQUE NOT NULL,"
        "bio TEXT,"
        "password TEXT NOT NULL"
        ");"
        );

    query.exec(
        "CREATE TABLE IF NOT EXISTS albums ("
        "albumId INTEGER PRIMARY KEY,"
        "albumName TEXT NOT NULL,"
        "artistId INTEGER NOT NULL"
        ");"
        );

    query.exec(
        "CREATE TABLE IF NOT EXISTS listeners ("
        "listenerId INTEGER PRIMARY KEY,"
        "fullName TEXT NOT NULL,"
        "userName TEXT UNIQUE NOT NULL,"
        "bio TEXT,"
        "password TEXT NOT NULL"
        ");"
        );

    query.exec(
        "CREATE TABLE IF NOT EXISTS playlists ("
        "playlistId INTEGER PRIMARY KEY,"
        "playlistName TEXT NOT NULL,"
        "listenerId INTEGER NOT NULL"
        ");"
        );

    query.exec(
        "CREATE TABLE IF NOT EXISTS playlistSongs ("
        "playlistId INTEGER NOT NULL,"
        "songId INTEGER NOT NULL"
        ");"
        );

    return true;
}