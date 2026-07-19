#ifndef ARTISTREPOSITORY_H
#define ARTISTREPOSITORY_H
#include "accountrepository.h"
#include "../Entities/artist.h"
#include <vector>
#include <optional>

class ArtistRepository : public AccountRepository
{
private:
    std::vector<std::shared_ptr<Artist>> artists;
    int nextId;
    static ArtistRepository instance;

    ArtistRepository();
public:
    static ArtistRepository& getInstance();

    const std::vector<std::shared_ptr<Artist>>& getArtists() const;

    int save(const std::shared_ptr<Account>& obj) override;
    bool remove(int id) override;
    std::optional<std::shared_ptr<Account>> search(int id) override;
    std::optional<std::shared_ptr<Account>> searchByUserName(const std::string& userName) override;
};

#endif // ARTISTREPOSITORY_H
