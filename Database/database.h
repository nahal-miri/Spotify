#ifndef DATABASE_H
#define DATABASE_H
#include <QSqlDatabase>

class Database
{
private:
    QSqlDatabase db;
    Database();
public:
    static Database& getInstance();

    bool open();
    void close();
    QSqlDatabase& getDatabase();
    bool createTables();
};

#endif // DATABASE_H
