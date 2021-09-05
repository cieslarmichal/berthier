#include "MongoDb.h"

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/stream/helpers.hpp>
#include <bsoncxx/json.hpp>
#include <iostream>

using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;

namespace bank::storage
{
MongoDb::MongoDb(const std::string& host, unsigned port, const std::string& dbName)
{
    mongocxx::uri uri{"mongodb://" + host + ":" + std::to_string(port)};
    client = std::make_unique<mongocxx::client>(uri);
    db = (*client)[dbName];
}

void MongoDb::insertDocument(const std::string& collectionName, const std::string& jsonDocument)
{
    const auto bsonObj = bsoncxx::from_json(jsonDocument);
    const auto view = bsonObj.view();
    auto collection = db[collectionName];
    collection.insert_one(view);
}

std::vector<std::string> MongoDb::getAllDocuments(const std::string& collectionName) const
{
    auto collection = db[collectionName];
    mongocxx::cursor cursor = collection.find(document{} << finalize);

    std::vector<std::string> documents;

    for (const auto& doc : cursor)
    {
        documents.push_back(bsoncxx::to_json(doc));
    }

    return documents;
}

void MongoDb::dropCollection(const std::string& collectionName)
{
    auto collection = db[collectionName];
    collection.drop();
}

}