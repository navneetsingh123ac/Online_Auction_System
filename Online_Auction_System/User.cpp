#include "User.h"
#include "Database.h"

#include <iostream>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
using namespace std;
User::User(string username, string password)
    : username(username), password(password) {}

void User::registerUser() {
    sql::Connection *conn = Database::getConnection();
    sql::PreparedStatement *pstmt = conn->prepareStatement("INSERT INTO Users(username, password) VALUES (?, ?)");
    pstmt->setString(1, username);
    pstmt->setString(2, password);
    pstmt->execute();
    delete pstmt;
    Database::disconnect();
}

bool User::loginUser() {
    sql::Connection *conn = Database::getConnection();
    sql::PreparedStatement *pstmt = conn->prepareStatement("SELECT * FROM Users WHERE username = ? AND password = ?");
    pstmt->setString(1, username);
    pstmt->setString(2, password);
    sql::ResultSet *res = pstmt->executeQuery();
    if (res->next()) {
        id = res->getInt("id"); // Store the user ID upon successful login
        delete res;
        delete pstmt;
        Database::disconnect();
        return true;
    } else {
        delete res;
        delete pstmt;
        Database::disconnect();
        return false;
    }
}

int User::getId() {
    return id;
}

bool User::isConnected() {
    return Database::getConnection() != nullptr;
}

void User::disconnect() {
    Database::disconnect();
}
