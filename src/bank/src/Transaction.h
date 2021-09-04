#pragma once

#include <ostream>
#include <string>
#include <vector>

namespace bank
{
struct Transaction
{
    std::string name;
    std::string category;
    unsigned int amount;
    std::string date;
};

inline bool operator==(const Transaction& lhs, const Transaction& rhs)
{
    auto tieStruct = [](const Transaction& transaction)
    { return std::tie(transaction.name, transaction.category, transaction.amount, transaction.date); };
    return tieStruct(lhs) == tieStruct(rhs);
}

inline std::ostream& operator<<(std::ostream& os, const Transaction& transaction)
{
    return os << "name: " << transaction.name << " category: " << transaction.category
              << " amount: " << transaction.amount << " date: " << transaction.date;
}

}