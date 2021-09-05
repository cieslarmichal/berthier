#pragma once

#include "TransactionRepository.h"
#include "DocumentBasedDb.h"
#include "TransactionSerializer.h"
#include <memory>

namespace bank::storage
{
class TransactionDb : public TransactionRepository
{
public:
    TransactionDb(std::unique_ptr<DocumentBasedDb>, std::unique_ptr<TransactionSerializer>);

    void add(const Transaction&) override;
    std::vector<Transaction> getAll() const override;

private:
    std::unique_ptr<DocumentBasedDb> db;
    std::unique_ptr<TransactionSerializer> serializer;
    const std::string collectionName;
};
}