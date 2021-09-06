#pragma once

#include <memory>

#include "DocumentBasedDb.h"
#include "TransactionRepository.h"
#include "TransactionSerializer.h"

namespace bank::storage
{
class TransactionDb : public TransactionRepository
{
public:
    TransactionDb(std::unique_ptr<DocumentBasedDb>, std::unique_ptr<TransactionSerializer>);

    void add(const Transaction&) override;
    std::vector<Transaction> getAll() const override;
    void update(const std::string& id, const Transaction&) override;

private:
    std::unique_ptr<DocumentBasedDb> db;
    std::unique_ptr<TransactionSerializer> serializer;
    const std::string collectionName;
};
}