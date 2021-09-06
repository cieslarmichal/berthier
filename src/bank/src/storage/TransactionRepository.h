#pragma once

#include <vector>

#include "Transaction.h"

namespace bank::storage
{
class TransactionRepository
{
public:
    virtual ~TransactionRepository() = default;

    virtual void add(const Transaction&) = 0;
    virtual std::vector<Transaction> getAll() const = 0;
    virtual void update(const std::string& id, const Transaction&) = 0;
};
}