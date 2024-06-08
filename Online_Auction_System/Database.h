#ifndef DATABASE_H
#define DATABASE_H

#include <mysql_driver.h>
#include <mysql_connection.h>

class Database {
public:
    static void initialize();
    static sql::Connection* getConnection();
    static void disconnect();
    
private:
    static sql::mysql::MySQL_Driver *driver;
    static sql::Connection *conn;
};

#endif // DATABASE_H
