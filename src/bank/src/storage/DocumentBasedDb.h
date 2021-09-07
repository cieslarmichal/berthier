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
    virtual std::vector<std::string> findAllDocuments(const std::string& collectionName) const = 0;
    virtual std::vector<std::string> findDocumentsByFieldValue(const std::string& collectionName,
                                                          const std::string& fieldName,
                                                          const std::string& fieldValue) const = 0;
    virtual std::vector<std::string> findDocumentsByFieldValue(const std::string& collectionName,
                                                          const std::string& fieldName,
                                                          int fieldValue) const = 0;
    virtual std::vector<std::string> findDocumentsByFieldValueLike(const std::string& collectionName,
                                                               const std::string& fieldName,
                                                               const std::string& fieldValueLike) const = 0;
    virtual void dropCollection(const std::string& collectionName) = 0;
    virtual void replaceDocument(const std::string& collectionName, const std::string& id,
                                 const std::string& jsonDocument) = 0;
    virtual void removeDocument(const std::string& collectionName, const std::string& id) = 0;
    virtual unsigned countDocuments(const std::string& collectionName) const = 0;
};
}