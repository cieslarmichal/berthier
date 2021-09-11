#pragma once

#include "gmock/gmock.h"

#include "BankClient.h"

namespace bank::service
{
class BankClientMock : public BankClient
{
public:
    MOCK_METHOD(void, logIn, (), (const override));
    MOCK_METHOD(std::vector<storage::Transaction>, getTransactions, (), (const override));
};
}