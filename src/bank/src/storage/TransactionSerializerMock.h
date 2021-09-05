#pragma once

#include "gmock/gmock.h"

#include "TransactionSerializer.h"

namespace bank::storage
{
class TransactionSerializerMock : public TransactionSerializer
{
public:
    MOCK_METHOD(std::string, serialize, (const Transaction&), (const override));
    MOCK_METHOD(Transaction, deserialize, (const std::string&), (const override));
};
}