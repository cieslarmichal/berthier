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
MongoDb::MongoDb(const std::string& dbName)
{
    //    db = client["transactionsDb"];
    db = client[dbName];
}

void MongoDb::insert(const std::string& collection, const std::string& jsonDocument)
{
    //    transactions = db["transactions"];
    auto transactions = db[collection];

    const auto bsonObj = bsoncxx::from_json(jsonDocument);
    const auto view = bsonObj.view();

    transactions.insert_one(view);
}

std::vector<std::string> MongoDb::getAll(const std::string& collection) const
{
    auto transactions = db[collection];

    mongocxx::cursor cursor = transactions.find(document{} << finalize);

    std::vector<std::string> documents;

    for (auto doc : cursor)
    {
        documents.push_back(bsoncxx::to_json(doc));
    }

    return documents;
}
}