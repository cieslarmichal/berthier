#pragma once

#include <string>
#include <vector>

namespace bank::storage
{
class DocumentBasedDb
{
public:
    virtual ~DocumentBasedDb() = default;

    virtual void insertDocument(const std::string& collectionName, const std::string& jsonDocument) = 0;
    virtual std::vector<std::string> getAllDocuments(const std::string& collectionName) const = 0;
    virtual void dropCollection(const std::string& collectionName) = 0;
    virtual void replaceDocument(const std::string& collectionName, const std::string& id,
                                 const std::string& jsonDocument) = 0;
};
}