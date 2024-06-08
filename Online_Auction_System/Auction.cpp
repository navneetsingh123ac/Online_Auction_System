#include "Auction.h"
#include "Database.h"

#include <iostream>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>

using namespace std;

Auction::Auction(string item_name, double start_price, string start_time, string end_time)
    : item_name(item_name), start_price(start_price), start_time(start_time), end_time(end_time) {}

void Auction::createAuction() {
    sql::Connection *conn = Database::getConnection();
    sql::PreparedStatement *pstmt = conn->prepareStatement("INSERT INTO Auctions(item_name, start_price, start_time, end_time) VALUES (?, ?, ?, ?)");
    pstmt->setString(1, item_name);
    pstmt->setDouble(2, start_price);
    pstmt->setString(3, start_time);
    pstmt->setString(4, end_time);
    pstmt->execute();
    delete pstmt;
    Database::disconnect();
}

void Auction::viewOngoingAuctions() {
    sql::Connection *conn = Database::getConnection();
    sql::Statement *stmt = conn->createStatement();
    sql::ResultSet *res = stmt->executeQuery("SELECT * FROM Auctions WHERE end_time > NOW()");
    while (res->next()) {
        cout << "Auction ID: " << res->getInt("id") << ", Item: " << res->getString("item_name") << ", Start Price: " << res->getDouble("start_price") << std::endl;
    }
    delete res;
    delete stmt;
    Database::disconnect();
}

void Auction::placeBid(int user_id, int auction_id, double bid_amount) {
    try {
        sql::Connection *conn = Database::getConnection();
        sql::PreparedStatement *pstmt = conn->prepareStatement("INSERT INTO Bids(auction_id, user_id, bid_amount) VALUES (?, ?, ?)");
        pstmt->setInt(1, auction_id);
        pstmt->setInt(2, user_id);
        pstmt->setDouble(3, bid_amount);
        pstmt->executeUpdate();
        delete pstmt;
        Database::disconnect();
        cout << "Bid placed successfully!\n";
    } catch (sql::SQLException &e) {
        cerr << "SQL Error: " << e.what() << std::endl;
    }
}

