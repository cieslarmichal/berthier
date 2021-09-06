#include "MongoDb.h"

#include <gmock/gmock.h>

#include "StlOperators.h"
#include "TransactionJsonSerializer.h"

using namespace bank::storage;
using namespace ::testing;

namespace
{
constexpr auto idField = "_id";
constexpr auto nestedIdField = "$oid";
const auto document1 = R"({"name": "coffee", "amount": "8"})";
const auto document2 = R"({"name": "water", "amount": "3"})";
const auto expectedField1InDocument1 = R"("name" : "coffee")";
const auto expectedField2InDocument1 = R"("amount" : "8")";
const auto expectedField1InDocument2 = R"("name" : "water")";
const auto expectedField2InDocument2 = R"("amount" : "3")";
const auto host{"localhost"};
const unsigned port{27017};
const auto dbName{"testDb"};
}

class MongoDbTest : public Test
{
public:
    MongoDbTest()
    {
        db->dropCollection(collectionName1);
        db->dropCollection(collectionName2);
        db->dropCollection(collectionName3);
        db->dropCollection(collectionName4);
        db->dropCollection(collectionName5);
    }

    ~MongoDbTest()
    {
        db->dropCollection(collectionName1);
        db->dropCollection(collectionName2);
        db->dropCollection(collectionName3);
        db->dropCollection(collectionName4);
        db->dropCollection(collectionName5);
    }

    bool containsField(const std::string& document, const std::string& field)
    {
        return document.find(field) != std::string::npos;
    }

    static std::unique_ptr<MongoDb> db;
    const std::string collectionName1{"collection1"};
    const std::string collectionName2{"collection2"};
    const std::string collectionName3{"collection3"};
    const std::string collectionName4{"collection4"};
    const std::string collectionName5{"collection5"};
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

TEST_F(MongoDbTest, givenNonExisingDocumentToReplace_shouldNoInsertNewElement)
{
    db->replaceDocument(collectionName4, "61366e1b6fd06b68e332f572", document1);

    const auto allDocuments = db->getAllDocuments(collectionName4);
    ASSERT_EQ(allDocuments.size(), 0);
}

TEST_F(MongoDbTest, givenExisingDocumentToReplace_shouldReplaceDocument)
{
    db->insertDocument(collectionName5, document1);
    const auto allDocumentsBeforeReplace = db->getAllDocuments(collectionName5);
    ASSERT_EQ(allDocumentsBeforeReplace.size(), 1);
    const auto documentJson = nlohmann::json::parse(allDocumentsBeforeReplace[0]);
    const auto documentId = documentJson.at(idField).at(nestedIdField).get<std::string>();

    db->replaceDocument(collectionName5, documentId, document2);

    const auto allDocumentsAfterReplace = db->getAllDocuments(collectionName5);
    ASSERT_EQ(allDocumentsAfterReplace.size(), 1);
    ASSERT_TRUE(containsField(allDocumentsAfterReplace[0], expectedField1InDocument2));
    ASSERT_TRUE(containsField(allDocumentsAfterReplace[0], expectedField2InDocument2));
}