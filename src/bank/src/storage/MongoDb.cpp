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
    transactions = db[collection];

    auto builder = bsoncxx::builder::stream::document{};
    bsoncxx::document::value doc_value = builder << "name"
                                                 << "desk"
                                                 << "amount"
                                                 << 400 << bsoncxx::builder::stream::finalize;
    //    bsoncxx::document::value bsonObj = bsoncxx::from_json(R"({
    //"name":"aaa",
    //"amount":100
    //})");
    bsoncxx::document::view view = doc_value.view();

    bsoncxx::stdx::optional<mongocxx::result::insert_one> result =
        transactions.insert_one(view);
    if (result)
    {
        std::cerr <<"success";
    }

}

std::vector<std::string> MongoDb::getAll(const std::string& collection) const
{
    return {};
}
}