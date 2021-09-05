#pragma once

#include "gmock/gmock.h"

#include "DocumentBasedDb.h"

namespace bank::storage
{
class DocumentBasedDbMock : public DocumentBasedDb
{
public:
    MOCK_METHOD(void, insertDocument, (const std::string& collectionName, const std::string& jsonDocument), (override));
    MOCK_METHOD(std::vector<std::string>, getAllDocuments, (const std::string& collectionName), (const override));
    MOCK_METHOD(void, dropCollection, (const std::string& collectionName), (override));
};
}