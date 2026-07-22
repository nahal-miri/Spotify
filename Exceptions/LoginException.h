#ifndef LOGINEXCEPTION_H
#define LOGINEXCEPTION_H
#include <stdexcept>
#include <string>

class LoginException : public std::runtime_error
{
public:
    explicit LoginException(const std::string& message) : std::runtime_error(message) {}
};

#endif // LOGINEXCEPTION_H
