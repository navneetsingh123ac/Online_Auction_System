#ifndef USER_H
#define USER_H

#include <string>

class User {
public:
    User(std::string username, std::string password);
    void registerUser();
    bool loginUser();
    int getId(); // Method to retrieve user ID
    static bool isConnected();
    static void disconnect();
    
private:
    int id; // Store the user's ID after login
    std::string username;
    std::string password;
};

#endif // USER_H
