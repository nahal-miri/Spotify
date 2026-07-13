#include "account.h"

Account::Account(std::string full, std::string user, std::string b, Role r, std::string pass, int id)
    : fullName(full),
    userName(user),
    bio(b),
    role(r),
    password(pass),
    userId(id) {}

std::string Account::getFullName() const {
    return this->fullName;
}

std::string Account::getUserName() const {
    return this->userName;
}

std::string Account::getBio() const {
    return this->bio;
}

Role Account::getRole() const {
    return this->role;
}

std::string Account::getPass() const {
    return this->password;
}

int Account::getId() const {
    return this->userId;
}

void Account::editUserName(const std::string& newUserName) {
    this->userName = newUserName;
}

void Account::changePassword(const std::string& newPassword) {
    this->password = newPassword;
}