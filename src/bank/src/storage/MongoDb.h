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
    std::vector<std::string> findAllDocuments(const std::string& collectionName) const override;
    std::vector<std::string> findDocumentsByFieldValue(const std::string& collectionName,
                                                  const std::string& fieldName,
                                                  const std::string& fieldValue) const override;
    std::vector<std::string> findDocumentsByFieldValue(const std::string& collectionName,
                                                  const std::string& fieldName,
                                                  int fieldValue) const override;
    std::vector<std::string> findDocumentsByFieldValueLike(const std::string& collectionName,
                                                                   const std::string& fieldName,
                                                                   const std::string& fieldValueLike) const override;
    void dropCollection(const std::string& collectionName) override;
    void replaceDocument(const std::string& collectionName, const std::string& id,
                         const std::string& jsonDocument) override;
    void removeDocument(const std::string& collectionName, const std::string& id) override;
    unsigned countDocuments(const std::string& collectionName) const override;

private:
    mongocxx::instance instance;
    std::unique_ptr<mongocxx::client> client;
    mongocxx::database db;
};
}