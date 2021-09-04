#pragma once

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>

#include "DocumentBasedDb.h"

namespace bank::storage
{
class MongoDb : public DocumentBasedDb
{
public:
    explicit MongoDb(const std::string& dbName);

    void insert(const std::string& collection, const std::string& jsonDocument) override;
    std::vector<std::string> getAll(const std::string& collection) const override;

private:
    mongocxx::instance instance{};
    mongocxx::uri uri{"mongodb://localhost:27017"};
    mongocxx::client client{uri};
    mongocxx::database db;
    mongocxx::collection transactions;
};
}