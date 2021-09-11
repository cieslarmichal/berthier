#pragma once

#include "storage/Transaction.h"

namespace bank::service
{
class BankClient
{
public:
    virtual ~BankClient() = default;

    virtual void logIn() const = 0;
    virtual std::vector<storage::Transaction> getTransactions() const = 0;
};
}