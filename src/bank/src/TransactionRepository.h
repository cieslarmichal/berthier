#pragma once

#include "Transaction.h"
#include <vector>

namespace bank
{
class TransactionRepository
{
public:
    virtual ~TransactionRepository() = default;

    virtual void add(const Transaction&) = 0;
    virtual std::vector<Transaction> getTransactions() const = 0;
};
}