#pragma once

#include "BankClient.h"

namespace bank::service
{
class MBankClient : public BankClient
{
public:
    void logIn() const override;
    std::vector<storage::Transaction> getTransactions() const override;
};
}