#pragma once

#include <string>
#include <vector>

namespace bank::storage
{
class DocumentBasedDb
{
public:
    virtual ~DocumentBasedDb() = default;

    virtual void insert(const std::string& collection, const std::string& jsonDocument) = 0;
    virtual std::vector<std::string> getAll(const std::string& collection) const = 0;
};
}