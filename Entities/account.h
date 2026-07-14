#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <string>
#include "Role.h"

class Account
{
protected:
    std::string fullName;
    std::string userName;
    std::string bio;
    Role role;
    std::string password;
    int userId;
public:
    Account(const std::string& fullName, const std::string& userName, const std::string& bio, Role role, const std::string& password);
    Account(const std::string& fullName, const std::string& userName, const std::string& bio, Role role, const std::string& password, int id);

    std::string getFullName() const;
    std::string getUserName() const;
    std::string getBio() const;
    Role getRole() const;
    std::string getPass() const;
    int getId() const;

    void setUserId(int id);

    void editUserName(const std::string& newUserName);
    void changePassword(const std::string& newPassword);
};

#endif // ACCOUNT_H