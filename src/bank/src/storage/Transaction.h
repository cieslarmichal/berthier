#pragma once

#include <ostream>
#include <string>
#include <tuple>

namespace bank::storage
{
struct Transaction
{
    std::string name;
    std::string recipient;
    std::string category;
    unsigned int amount;
    std::string date;
};

inline bool operator==(const Transaction& lhs, const Transaction& rhs)
{
    auto tieStruct = [](const Transaction& transaction)
    {
        return std::tie(transaction.name, transaction.recipient, transaction.category, transaction.amount,
                        transaction.date);
    };
    return tieStruct(lhs) == tieStruct(rhs);
}

inline std::ostream& operator<<(std::ostream& os, const Transaction& transaction)
{
    return os << "name: " << transaction.name << " category: " << transaction.category
              << "recipient: " << transaction.recipient << " amount: " << transaction.amount
              << " date: " << transaction.date;
}

}