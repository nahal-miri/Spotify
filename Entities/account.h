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

    virtual ~Account() = default;

    std::string getFullName() const;
    std::string getUserName() const;
    std::string getBio() const;
    Role getRole() const;
    std::string getPassword() const;
    int getId() const;

    void setFullName(const std::string& newName);
    void setUserName(const std::string& newName);
    void setBio(const std::string& newBio);
    void setPassword(const std::string& newPass);
    void setUserId(int id);

    void editUserName(const std::string& newUserName);
    void changePassword(const std::string& newPassword);
};

#endif // ACCOUNT_H