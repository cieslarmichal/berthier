#pragma once

#include "gmock/gmock.h"

#include "TransactionRepository.h"

namespace bank
{
class TransactionRepositoryMock : public TransactionRepository
{
public:
    MOCK_METHOD(void, add, (const Transaction&), (override));
    MOCK_METHOD(std::vector<Transaction>, getTransactions, (), (const override));
};
}