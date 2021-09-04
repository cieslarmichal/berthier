#pragma once

#include "gmock/gmock.h"

#include "DocumentDb.h"

namespace bank
{
class DocumentDbMock : public DocumentDb
{
public:
    MOCK_METHOD(void, add, (const std::string& collection, const std::string& jsonDocument), (override));
    MOCK_METHOD(std::vector<std::string>, getAll, (const std::string& collection), (const override));
};
}