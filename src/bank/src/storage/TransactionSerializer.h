#pragma once

#include "Transaction.h"

namespace bank::storage
{
class TransactionSerializer
{
public:
    virtual ~TransactionSerializer() = default;

    virtual std::string serialize(const Transaction&) const = 0;
    virtual Transaction deserialize(const std::string&) const = 0;
};
}