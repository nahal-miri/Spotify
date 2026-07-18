#ifndef ACCOUNTREPOSITORY_H
#define ACCOUNTREPOSITORY_H
#include "AbstractRepository.h"
#include "../Entities/account.h"
#include <optional>

class AccountRepository : public AbstractRepository<Account>
{
public:
    virtual ~AccountRepository() = default;

    virtual std::optional<std::shared_ptr<Account>> searchByUserName(const std::string& userName) = 0;
};

#endif // ACCOUNTREPOSITORY_H
