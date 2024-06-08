#include "Database.h"
using namespace std;
sql::mysql::MySQL_Driver *Database::driver = nullptr;
sql::Connection *Database::conn = nullptr;

void Database::initialize() {
    try {
        driver = sql::mysql::get_mysql_driver_instance();
        conn = driver->connect("tcp://127.0.0.1:3306", "navneet123ac", "Nav123neet@");
        conn->setSchema("auction_db");
    } catch (sql::SQLException &e) {
        cerr << "SQL Error: " << e.what() << std::endl;
    }
}

sql::Connection* Database::getConnection() {
    if (conn == nullptr) {
        initialize();
    }
    return conn;
}

void Database::disconnect() {
    if (conn != nullptr) {
        delete conn;
        conn = nullptr;
    }
}
