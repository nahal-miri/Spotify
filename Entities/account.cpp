#include "account.h"

Account::Account(const std::string& fullName, const std::string& userName, const std::string& bio, Role role, const std::string& password)
    : fullName(fullName),
    userName(userName),
    bio(bio),
    role(role),
    password(password),
    userId(0) {}

Account::Account(const std::string& fullName, const std::string& userName, const std::string& bio, Role role, const std::string& password, int id)
    : fullName(fullName),
    userName(userName),
    bio(bio),
    role(role),
    password(password),
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

void Account::setUserId(int id) {
    this->userId = id;
}

void Account::editUserName(const std::string& newUserName) {
    this->userName = newUserName;
}

void Account::changePassword(const std::string& newPassword) {
    this->password = newPassword;
}