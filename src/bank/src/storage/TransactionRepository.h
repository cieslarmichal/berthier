#pragma once

#include "Transaction.h"
#include <vector>

namespace bank::storage
{
class TransactionRepository
{
public:
    virtual ~TransactionRepository() = default;

    virtual void add(const Transaction&) = 0;
    virtual std::vector<Transaction> getAll() const = 0;
};
}