#include "user.h"

user::user(bool adminStatus, string userName) {
    isAdmin = adminStatus;
    uName = userName;
}

bool user::updateAdminStatus(bool newStatus) {
    if (newStatus != isAdmin) {
        //if status can be changed, change and return true
        isAdmin = newStatus;
        return true;
    } else
        return false;
}

bool user::updateUserName(string newName) {
    if (newName == uName)
        return false;
    else {
        uName = newName;
        return true;
    }
}

bool user::updatePassWord(string newPass) {
    if (newPass == passWord)
        return false;
    else {
        passWord = newPass;
        return true;
    }
}

bool user::getAdminStatus() {
    return isAdmin;
}

string user::getUserName() {
    return uName;
}

string user::getPassWord() {
    return passWord;
}