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
const auto document1 = R"({"name": "coffee", "amount": 8})";
const auto document2 = R"({"name": "water", "amount": 3})";
const auto document3 = R"({"name": "apple", "amount": 3})";
const auto expectedField1InDocument1 = R"("name" : "coffee")";
const auto expectedField2InDocument1 = R"("amount" : 8)";
const auto expectedField1InDocument2 = R"("name" : "water")";
const auto expectedField2InDocument2 = R"("amount" : 3)";
const auto expectedField1InDocument3 = R"("name" : "apple")";
const auto expectedField2InDocument3 = R"("amount" : 3)";
const auto host{"localhost"};
const unsigned port{27017};
const auto dbName{"testDb"};
}

class MongoDbTest : public Test
{
public:
    MongoDbTest()
    {
        dropCollections();
    }

    ~MongoDbTest()
    {
        dropCollections();
    }

    bool containsField(const std::string& document, const std::string& field)
    {
        return document.find(field) != std::string::npos;
    }

    void dropCollections()
    {
        for (const auto& collection : collections)
        {
            db->dropCollection(collection);
        }
    }

    static std::unique_ptr<MongoDb> db;
    const std::string collectionName1{"collection1"};
    const std::string collectionName2{"collection2"};
    const std::string collectionName3{"collection3"};
    const std::string collectionName4{"collection4"};
    const std::string collectionName5{"collection5"};
    const std::string collectionName6{"collection6"};
    const std::string collectionName7{"collection7"};
    const std::string collectionName8{"collection8"};
    const std::string collectionName9{"collection9"};
    const std::string collectionName10{"collection10"};
    const std::string collectionName11{"collection11"};
    const std::vector<std::string> collections{
        collectionName1, collectionName2, collectionName3, collectionName4,  collectionName5, collectionName6,
        collectionName7, collectionName8, collectionName9, collectionName10, collectionName11};
};

std::unique_ptr<MongoDb> MongoDbTest::db = std::make_unique<MongoDb>(host, port, dbName);

TEST_F(MongoDbTest, secondInstanceOfMongoDbCreated_shouldThrow)
{
    ASSERT_ANY_THROW(MongoDb(host, port, dbName));
}

TEST_F(MongoDbTest, insertDocument)
{
    db->insertDocument(collectionName1, document1);

    const auto documents = db->findAllDocuments(collectionName1);

    ASSERT_EQ(documents.size(), 1);
    ASSERT_TRUE(containsField(documents[0], expectedField1InDocument1));
    ASSERT_TRUE(containsField(documents[0], expectedField2InDocument1));
}

TEST_F(MongoDbTest, givenNoDocuments_findAllDocuments_shoudlReturnNoDocuments)
{
    const auto allDocuments = db->findAllDocuments(collectionName2);

    ASSERT_EQ(allDocuments.size(), 0);
}

TEST_F(MongoDbTest, givenDocuments_findAllDocuments_shoudlReturnDocuments)
{
    db->insertDocument(collectionName3, document1);
    db->insertDocument(collectionName3, document2);

    const auto allDocuments = db->findAllDocuments(collectionName3);

    ASSERT_EQ(allDocuments.size(), 2);
    ASSERT_TRUE(containsField(allDocuments[0], expectedField1InDocument1));
    ASSERT_TRUE(containsField(allDocuments[0], expectedField2InDocument1));
    ASSERT_TRUE(containsField(allDocuments[1], expectedField1InDocument2));
    ASSERT_TRUE(containsField(allDocuments[1], expectedField2InDocument2));
}

TEST_F(MongoDbTest, givenNoDocumentsMatchingFilter_findDocumentsByStringField_shouldReturnNoDocuments)
{
    db->insertDocument(collectionName4, document1);
    db->insertDocument(collectionName4, document2);

    const auto allDocuments = db->findDocumentsByField(collectionName4, "name", "xxx");

    ASSERT_EQ(allDocuments.size(), 0);
}

TEST_F(MongoDbTest, givenDocumentMatchingFilter_findDocumentsByStringField_shouldReturnMatchinDocument)
{
    db->insertDocument(collectionName5, document1);
    db->insertDocument(collectionName5, document2);

    const auto allDocuments = db->findDocumentsByField(collectionName5, "name", "coffee");

    ASSERT_EQ(allDocuments.size(), 1);
    ASSERT_TRUE(containsField(allDocuments[0], expectedField1InDocument1));
    ASSERT_TRUE(containsField(allDocuments[0], expectedField2InDocument1));
}

TEST_F(MongoDbTest, givenNoDocumentsMatchingFilter_findDocumentsByIntField_shouldReturnNoDocuments)
{
    db->insertDocument(collectionName6, document1);
    db->insertDocument(collectionName6, document2);

    const auto allDocuments = db->findDocumentsByField(collectionName6, "amount", 20);

    ASSERT_EQ(allDocuments.size(), 0);
}

TEST_F(MongoDbTest, givenDocumentsMatchingFilter_findDocumentsByIntField_shouldReturnDocuments)
{
    db->insertDocument(collectionName7, document2);
    db->insertDocument(collectionName7, document3);

    const auto allDocuments = db->findDocumentsByField(collectionName7, "amount", 3);

    ASSERT_EQ(allDocuments.size(), 2);
    ASSERT_TRUE(containsField(allDocuments[0], expectedField1InDocument2));
    ASSERT_TRUE(containsField(allDocuments[0], expectedField2InDocument2));
    ASSERT_TRUE(containsField(allDocuments[1], expectedField1InDocument3));
    ASSERT_TRUE(containsField(allDocuments[1], expectedField2InDocument3));
}

TEST_F(MongoDbTest, givenDocumentsMatchingFilter_findDocumentsByIntField_shouldReturnMatchingDocuments)
{
    db->insertDocument(collectionName8, document2);
    db->insertDocument(collectionName8, document3);

    const auto allDocuments = db->findDocumentsByField(collectionName8, "amount", 3);

    ASSERT_EQ(allDocuments.size(), 2);
    ASSERT_TRUE(containsField(allDocuments[0], expectedField1InDocument2));
    ASSERT_TRUE(containsField(allDocuments[0], expectedField2InDocument2));
    ASSERT_TRUE(containsField(allDocuments[1], expectedField2InDocument3));
    ASSERT_TRUE(containsField(allDocuments[1], expectedField2InDocument3));
}

TEST_F(MongoDbTest, dropCollection)
{
    db->insertDocument(collectionName9, document1);

    db->dropCollection(collectionName9);

    const auto allDocuments = db->findAllDocuments(collectionName9);
    ASSERT_EQ(allDocuments.size(), 0);
}

TEST_F(MongoDbTest, givenNonExisingDocumentToReplace_shouldNotInsertNewElement)
{
    db->replaceDocument(collectionName10, "61366e1b6fd06b68e332f572", document1);

    const auto allDocuments = db->findAllDocuments(collectionName10);
    ASSERT_EQ(allDocuments.size(), 0);
}

TEST_F(MongoDbTest, givenExisingDocumentToReplace_shouldReplaceDocument)
{
    db->insertDocument(collectionName11, document1);
    const auto allDocumentsBeforeReplace = db->findAllDocuments(collectionName11);
    ASSERT_EQ(allDocumentsBeforeReplace.size(), 1);
    const auto documentJson = nlohmann::json::parse(allDocumentsBeforeReplace[0]);
    const auto documentId = documentJson.at(idField).at(nestedIdField).get<std::string>();

    db->replaceDocument(collectionName11, documentId, document2);

    const auto allDocumentsAfterReplace = db->findAllDocuments(collectionName11);
    ASSERT_EQ(allDocumentsAfterReplace.size(), 1);
    ASSERT_TRUE(containsField(allDocumentsAfterReplace[0], expectedField1InDocument2));
    ASSERT_TRUE(containsField(allDocumentsAfterReplace[0], expectedField2InDocument2));
}