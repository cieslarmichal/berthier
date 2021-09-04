#pragma once

#include "TransactionRepository.h"

namespace bank::storage
{
class TransactionDb : public TransactionRepository
{
public:
    explicit TransactionDb();

    void add(const Transaction&) override;
    std::vector<Transaction> getTransactions() const override;
};
}