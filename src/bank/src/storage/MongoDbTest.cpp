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
const auto document4 = R"({"name": "iphone", "amount": 2000, "date": "2021-09-10"})";
const auto document5 = R"({"name": "chair", "amount": 500, "date": "2021-09-05"})";
const auto expectedField1InDocument1 = R"("name" : "coffee")";
const auto expectedField2InDocument1 = R"("amount" : 8)";
const auto expectedField1InDocument2 = R"("name" : "water")";
const auto expectedField2InDocument2 = R"("amount" : 3)";
const auto expectedField1InDocument3 = R"("name" : "apple")";
const auto expectedField2InDocument3 = R"("amount" : 3)";
const auto expectedField1InDocument4 = R"("name" : "iphone")";
const auto expectedField2InDocument4 = R"("amount" : 2000)";
const auto expectedField3InDocument4 = R"("date" : "2021-09-10")";
const auto expectedField1InDocument5 = R"("name" : "chair")";
const auto expectedField2InDocument5 = R"("amount" : 500)";
const auto expectedField3InDocument5 = R"("date" : "2021-09-05")";
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
    const std::string collectionName12{"collection12"};
    const std::vector<std::string> collections{
        collectionName1, collectionName2, collectionName3, collectionName4,  collectionName5, collectionName6,
        collectionName7, collectionName8, collectionName9, collectionName10, collectionName11, collectionName12};
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

TEST_F(MongoDbTest, givenNoDocumentsMatchingFilter_findDocumentsByStringFieldValue_shouldReturnNoDocuments)
{
    db->insertDocument(collectionName4, document1);
    db->insertDocument(collectionName4, document2);

    const auto allDocuments = db->findDocumentsByFieldValue(collectionName4, "name", "xxx");

    ASSERT_EQ(allDocuments.size(), 0);
}

TEST_F(MongoDbTest, givenDocumentMatchingFilter_findDocumentsByStringFieldValue_shouldReturnMatchinDocument)
{
    db->insertDocument(collectionName5, document1);
    db->insertDocument(collectionName5, document2);

    const auto allDocuments = db->findDocumentsByFieldValue(collectionName5, "name", "coffee");

    ASSERT_EQ(allDocuments.size(), 1);
    ASSERT_TRUE(containsField(allDocuments[0], expectedField1InDocument1));
    ASSERT_TRUE(containsField(allDocuments[0], expectedField2InDocument1));
}

TEST_F(MongoDbTest, givenNoDocumentsMatchingFilter_findDocumentsByIntFieldValue_shouldReturnNoDocuments)
{
    db->insertDocument(collectionName6, document1);
    db->insertDocument(collectionName6, document2);

    const auto allDocuments = db->findDocumentsByFieldValue(collectionName6, "amount", 20);

    ASSERT_EQ(allDocuments.size(), 0);
}

TEST_F(MongoDbTest, givenDocumentsMatchingFilter_findDocumentsByIntFieldValue_shouldReturnDocuments)
{
    db->insertDocument(collectionName7, document2);
    db->insertDocument(collectionName7, document3);

    const auto allDocuments = db->findDocumentsByFieldValue(collectionName7, "amount", 3);

    ASSERT_EQ(allDocuments.size(), 2);
    ASSERT_TRUE(containsField(allDocuments[0], expectedField1InDocument2));
    ASSERT_TRUE(containsField(allDocuments[0], expectedField2InDocument2));
    ASSERT_TRUE(containsField(allDocuments[1], expectedField1InDocument3));
    ASSERT_TRUE(containsField(allDocuments[1], expectedField2InDocument3));
}

TEST_F(MongoDbTest, dropCollection)
{
    db->insertDocument(collectionName8, document1);

    db->dropCollection(collectionName8);

    const auto allDocuments = db->findAllDocuments(collectionName8);
    ASSERT_EQ(allDocuments.size(), 0);
}

TEST_F(MongoDbTest, givenNonExisingDocumentToReplace_shouldNotInsertNewElement)
{
    db->replaceDocument(collectionName9, "61366e1b6fd06b68e332f572", document1);

    const auto allDocuments = db->findAllDocuments(collectionName9);
    ASSERT_EQ(allDocuments.size(), 0);
}

TEST_F(MongoDbTest, givenExisingDocumentToReplace_shouldReplaceDocument)
{
    db->insertDocument(collectionName10, document1);
    const auto allDocumentsBeforeReplace = db->findAllDocuments(collectionName10);
    ASSERT_EQ(allDocumentsBeforeReplace.size(), 1);
    const auto documentJson = nlohmann::json::parse(allDocumentsBeforeReplace[0]);
    const auto documentId = documentJson.at(idField).at(nestedIdField).get<std::string>();

    db->replaceDocument(collectionName10, documentId, document2);

    const auto allDocumentsAfterReplace = db->findAllDocuments(collectionName10);
    ASSERT_EQ(allDocumentsAfterReplace.size(), 1);
    ASSERT_TRUE(containsField(allDocumentsAfterReplace[0], expectedField1InDocument2));
    ASSERT_TRUE(containsField(allDocumentsAfterReplace[0], expectedField2InDocument2));
}

TEST_F(MongoDbTest, givenNoDocumentsMatchingFilterLike_findDocumentsByFieldValueLike_shouldReturnNoDocuments)
{
    db->insertDocument(collectionName11, document2);
    db->insertDocument(collectionName11, document3);

    const auto allDocuments = db->findDocumentsByFieldValueLike(collectionName11, "date", "2021-09");

    ASSERT_EQ(allDocuments.size(), 0);
}


TEST_F(MongoDbTest, givenDocumentsMatchingFilterLike_findDocumentsByFieldValueLike_shouldReturnDocuments)
{
    db->insertDocument(collectionName12, document4);
    db->insertDocument(collectionName12, document5);

    const auto allDocuments = db->findDocumentsByFieldValueLike(collectionName12, "date", "2021-09");

    ASSERT_EQ(allDocuments.size(), 2);
    ASSERT_TRUE(containsField(allDocuments[0], expectedField1InDocument4));
    ASSERT_TRUE(containsField(allDocuments[0], expectedField2InDocument4));
    ASSERT_TRUE(containsField(allDocuments[0], expectedField3InDocument4));
    ASSERT_TRUE(containsField(allDocuments[1], expectedField1InDocument5));
    ASSERT_TRUE(containsField(allDocuments[1], expectedField2InDocument5));
    ASSERT_TRUE(containsField(allDocuments[1], expectedField3InDocument5));
}
