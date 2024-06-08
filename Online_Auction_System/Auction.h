#ifndef AUCTION_H
#define AUCTION_H

#include <string>
using namespace std;
class Auction {
public:
    Auction(string item_name, double start_price, string start_time, string end_time);
    void createAuction();
    static void viewOngoingAuctions();
    void placeBid(int user_id, int auction_id, double bid_amount);
    
private:
    string item_name;
    double start_price;
    string start_time;
    string end_time;
};

#endif // AUCTION_H
