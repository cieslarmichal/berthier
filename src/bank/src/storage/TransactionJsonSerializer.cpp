#include "TransactionJsonSerializer.h"

namespace bank::storage
{


std::string TransactionJsonSerializer::serialize(const Transaction&) const
{
    return std::string();
}

Transaction TransactionJsonSerializer::deserialize(const std::string&) const
{
    return Transaction();
}
}