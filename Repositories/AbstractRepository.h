#ifndef ABSTRACTREPOSITORY_H
#define ABSTRACTREPOSITORY_H
#include <optional>
#include <memory>

template<class T>
class AbstractRepository
{
public:
    virtual ~AbstractRepository() = default;

    virtual int save(const std::shared_ptr<T>& obj) = 0;
    virtual bool remove(int id) = 0;
    virtual std::optional<std::shared_ptr<T>> search(int id) = 0;
};

#endif // ABSTRACTREPOSITORY_H