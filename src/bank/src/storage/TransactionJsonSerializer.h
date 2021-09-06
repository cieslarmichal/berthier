#pragma once

#include "nlohmann/json.hpp"

#include "TransactionSerializer.h"

namespace bank::storage
{
class TransactionJsonSerializer : public TransactionSerializer
{
public:
    std::string serialize(const Transaction&) const override;
    Transaction deserialize(const std::string&) const override;

private:
    Transaction parseTransaction(const nlohmann::json& transactionJson) const;
    bool transactionJsonHasAllRequiredFields(const nlohmann::json& transactionJson) const;
};
}