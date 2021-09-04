#pragma once

#include "TransactionRepository.h"
#include <mongocxx/instance.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/uri.hpp>

namespace bank
{
class TransactionDb : public TransactionRepository
{
public:
    explicit TransactionDb();

    void add(const Transaction&) override;
    std::vector<Transaction> getTransactions() const override;

private:
    mongocxx::instance instance{};
    mongocxx::uri uri{"mongodb://localhost:27017"};
    mongocxx::client client{uri};
    mongocxx::database db;
    mongocxx::collection transactions;
};
}