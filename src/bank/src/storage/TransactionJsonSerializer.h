#pragma once

#include "TransactionSerializer.h"

namespace bank::storage
{
class TransactionJsonSerializer : public TransactionSerializer
{
public:
    std::string serialize(const Transaction&) const override;
    Transaction deserialize(const std::string&) const override;
};
}