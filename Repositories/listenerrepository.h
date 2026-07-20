#ifndef LISTENERREPOSITORY_H
#define LISTENERREPOSITORY_H
#include "accountrepository.h"
#include "../Entities/listener.h"
#include <vector>
#include <optional>
#include <memory>
#include <string>

class ListenerRepository : public AccountRepository
{
private:
    std::vector<std::shared_ptr<Listener>> listeners;
    int nextId;
    static ListenerRepository instance;

    ListenerRepository();
public:
    static ListenerRepository& getInstance();

    int save(const std::shared_ptr<Account>& obj) override;
    bool remove(int id) override;
    std::optional<std::shared_ptr<Account>> search(int id) override;
    std::optional<std::shared_ptr<Account>> searchByUserName(const std::string& userName) override;
    bool updateLiked(int listenerId, int songId, bool value);
    bool isLiked(int listenerId, int songId);

    bool removeLikedSong(int songId);
};

#endif // LISTENERREPOSITORY_H
