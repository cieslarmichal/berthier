#pragma once

#include "gmock/gmock.h"

#include "DocumentBasedDb.h"

namespace bank::storage
{
class DocumentBasedDbMock : public DocumentBasedDb
{
public:
    MOCK_METHOD(void, insertDocument, (const std::string& collectionName, const std::string& jsonDocument),
                (override));
    MOCK_METHOD(std::vector<std::string>, findAllDocuments, (const std::string& collectionName),
                (const override));
    MOCK_METHOD(std::vector<std::string>, findDocumentsByFieldValue,
                (const std::string& collectionName, const std::string& fieldName,
                 const std::string& fieldValue),
                (const override));
    MOCK_METHOD(std::vector<std::string>, findDocumentsByFieldValue,
                (const std::string& collectionName, const std::string& fieldName, int fieldValue),
                (const override));
    MOCK_METHOD(std::vector<std::string>, findDocumentsByFieldValueLike,
                (const std::string& collectionName, const std::string& fieldName,
                 const std::string& fieldValueLike),
                (const override));
    MOCK_METHOD(void, dropCollection, (const std::string& collectionName), (override));
    MOCK_METHOD(void, replaceDocument,
                (const std::string& collectionName, const std::string& id, const std::string& jsonDocument),
                (override));
    MOCK_METHOD(void, removeDocument, (const std::string& collectionName, const std::string& id), (override));
};
}