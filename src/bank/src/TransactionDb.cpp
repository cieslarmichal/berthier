#include "TransactionDb.h"

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/stream/helpers.hpp>
#include <bsoncxx/json.hpp>

using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;

namespace bank
{
TransactionDb::TransactionDb()
{
    db = client["transactionsDb"];
    transactions = db["transactions"];
}

void TransactionDb::add(const Transaction&)
{
    auto builder = bsoncxx::builder::stream::document{};
    bsoncxx::document::value doc_value = builder << "name"
                                                 << "desk"
                                                 << "amount"
                                                 << 400 << bsoncxx::builder::stream::finalize;
    bsoncxx::document::view view = doc_value.view();
    bsoncxx::stdx::optional<mongocxx::result::insert_one> result =
        transactions.insert_one(view);
}

std::vector<Transaction> TransactionDb::getTransactions() const
{
    return {};
}
}