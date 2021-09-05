#include "MongoDb.h"

#include <gmock/gmock.h>

#include "StlOperators.h"

using namespace bank::storage;
using namespace ::testing;

namespace
{
const auto document1 = R"({"name": "coffee", "amount": "8"})";
const auto document2 = R"({"name": "water", "amount": "3"})";
const auto expectedField1InDocument1 = R"("name" : "coffee")";
const auto expectedField2InDocument1 = R"("amount" : "8")";
const auto expectedField1InDocument2 = R"("name" : "water")";
const auto expectedField2InDocument2 = R"("amount" : "3")";
const auto host{"localhost"};
const unsigned port{27017};
const auto dbName{"testTransactionsDb"};
}

class MongoDbTest : public Test
{
public:
    ~MongoDbTest()
    {
        db->dropCollection(collectionName1);
        db->dropCollection(collectionName2);
        db->dropCollection(collectionName3);
    }

    bool containsField(const std::string& document, const std::string& field)
    {
        return document.find(field) != std::string::npos;
    }

    static std::unique_ptr<MongoDb> db;
    const std::string collectionName1{"transactions1"};
    const std::string collectionName2{"transactions2"};
    const std::string collectionName3{"transactions3"};
};

std::unique_ptr<MongoDb> MongoDbTest::db = std::make_unique<MongoDb>(host, port, dbName);

TEST_F(MongoDbTest, secondInstanceOfMongoDbCreated_shouldThrow)
{
    ASSERT_ANY_THROW(MongoDb(host, port, dbName));
}

TEST_F(MongoDbTest, insert)
{
    db->insertDocument(collectionName1, document1);

    const auto documents = db->getAllDocuments(collectionName1);

    ASSERT_EQ(documents.size(), 1);
    ASSERT_TRUE(containsField(documents[0], expectedField1InDocument1));
    ASSERT_TRUE(containsField(documents[0], expectedField2InDocument1));
}

TEST_F(MongoDbTest, getAll)
{
    db->insertDocument(collectionName2, document1);
    db->insertDocument(collectionName2, document2);

    const auto allDocuments = db->getAllDocuments(collectionName2);

    ASSERT_EQ(allDocuments.size(), 2);
    ASSERT_TRUE(containsField(allDocuments[0], expectedField1InDocument1));
    ASSERT_TRUE(containsField(allDocuments[0], expectedField2InDocument1));
    ASSERT_TRUE(containsField(allDocuments[1], expectedField1InDocument2));
    ASSERT_TRUE(containsField(allDocuments[1], expectedField2InDocument2));
}

TEST_F(MongoDbTest, drop)
{
    db->insertDocument(collectionName3, document1);

    db->dropCollection(collectionName3);

    const auto allDocuments = db->getAllDocuments(collectionName3);
    ASSERT_EQ(allDocuments.size(), 0);
}