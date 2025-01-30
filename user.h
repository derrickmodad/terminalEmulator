#pragma once
#include <string>
#include <vector>
using namespace std;

class user {
    private:
        bool isAdmin;
        string uName;
        string passWord;
    public:
        user(bool adminStatus, string userName);
        bool updateAdminStatus(bool newStatus);
        bool updateUserName(string newName);
        bool updatePassWord(string newPass);
        bool getAdminStatus();
        string getUserName();
        string getPassWord();
};

/*
user needs:
    admin status - bool
    username - string
    password ?

also a way to read and write to a file of usernames/passwords
*/