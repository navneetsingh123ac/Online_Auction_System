#include "User.h"
#include "Auction.h"
#include "Database.h"

#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

void displayMenu()
{
    cout << "\n=== Auction Management System ===\n";
    cout << "1. Register\n";
    cout << "2. Login\n";
    cout << "3. Create Auction\n";
    cout << "4. View Ongoing Auctions\n";
    cout << "5. Place Bid\n";
    cout << "6. Exit\n";
    cout << "===============================\n";
    cout << "Enter your choice: ";
}

void registerUser(User &user)
{
    string username, password;
    cout << "\nEnter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    user = User(username, password);
    user.registerUser();
    cout << "User registered successfully!\n";
}
void clearConsole()
{
    system("clear");
}

void pauseConsole()
{
    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();
}

void loginUser(User &user)
{
    string username, password;
    cout << "\nEnter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    user = User(username, password);
    if (user.loginUser())
    {
        cout << "Login successful!\n";
    }
    else
    {
        cout << "Login failed. Invalid username or password.\n";
    }
}

void createAuction(Auction &auction)
{
    string item_name, start_time, end_time;
    double start_price;
    cout << "\nEnter item name: ";
    cin.ignore();
    getline(cin, item_name);
    cout << "Enter starting price: ";
    cin >> start_price;
    cout << "Enter start time (YYYY-MM-DD HH:MM:SS): ";
    cin.ignore();
    getline(cin, start_time);
    cout << "Enter end time (YYYY-MM-DD HH:MM:SS): ";
    getline(cin, end_time);
    auction = Auction(item_name, start_price, start_time, end_time);
    auction.createAuction();
    cout << "Auction created successfully!\n";
}

void viewOngoingAuctions()
{
    cout << "\n=== Ongoing Auctions ===\n";
    Auction::viewOngoingAuctions();
    cout << "========================\n";
}

void placeBid(Auction &auction, int user_id)
{
    int auction_id;
    double bid_amount;
    cout << "\nEnter auction ID to place bid: ";
    cin >> auction_id;
    cout << "\nEnter bid amount: ";
    cin >> bid_amount;
    cout << "Enter User ID: ";
    cin >> user_id;
    auction = Auction("", 0.0, "", "");
    auction.placeBid(user_id, auction_id, bid_amount);
    cout << "Bid placed successfully!\n";
}

int main()
{
    Database::initialize();
    User currentUser("navneet", "12345");
    Auction currentAuction("", 0.0, "", "");

    int choice;
    do
    {
        displayMenu();
        cin >> choice;
        switch (choice)
        {
        case 1:
            registerUser(currentUser);
            break;
        case 2:
            loginUser(currentUser);
            break;
        case 3:
            if (User::isConnected())
            {
                createAuction(currentAuction);
            }
            else
            {
                cout << "Please login first.\n";
            }
            break;
        case 4:
            if (User::isConnected())
            {
                viewOngoingAuctions();
            }
            else
            {
                cout << "Please login first.\n";
            }
            break;
        case 5:
            if (User::isConnected())
            {
                placeBid(currentAuction, currentUser.getId());
            }
            else
            {
                cout << "Please login first.\n";
            }
            break;
        case 6:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Please enter a number from 1 to 6.\n";
            break;
        }
        pauseConsole();
        clearConsole();
    } while (choice != 6);

    Database::disconnect();
    return 0;
}
