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
    MongoDb(const std::string& host, unsigned port, const std::string& dbName);

    void insertDocument(const std::string& collectionName, const std::string& jsonDocument) override;
    std::vector<std::string> getAllDocuments(const std::string& collectionName) const override;
    void dropCollection(const std::string& collectionName) override;

private:
    mongocxx::instance instance;
    std::unique_ptr<mongocxx::client> client;
    mongocxx::database db;
};
}