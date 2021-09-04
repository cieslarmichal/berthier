#pragma once

#include <string>
#include <vector>

namespace bank
{
class DocumentDb
{
public:
    virtual ~DocumentDb() = default;

    virtual void add(const std::string& collection, const std::string& jsonDocument) = 0;
    virtual std::vector<std::string> getAll(const std::string& collection) const = 0;
};
}