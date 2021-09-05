#pragma once

#include "TransactionRepository.h"
#include "DocumentBasedDb.h"
#include <memory>

namespace bank::storage
{
class TransactionDb : public TransactionRepository
{
public:
    explicit TransactionDb(std::unique_ptr<DocumentBasedDb>);

    void add(const Transaction&) override;
    std::vector<Transaction> getAll() const override;

private:
    std::unique_ptr<DocumentBasedDb> db;
    const std::string collectionName;
};
}