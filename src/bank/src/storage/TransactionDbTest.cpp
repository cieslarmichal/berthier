#include "TransactionDb.h"

#include <gmock/gmock.h>

#include "DocumentBasedDbMock.h"
#include "TransactionSerializerMock.h"

using namespace bank::storage;
using namespace ::testing;

namespace
{
const auto transaction1 = Transaction{"id", "water", "shop", "food", 3, utils::Date{"2021-09-10"}};
const auto transaction2 = Transaction{"id", "orange", "fruit shop", "food", 1, utils::Date{"2021-09-11"}};
const auto transaction1Serialized =
    R"({"name":"water","recipient":"shop","category":"food","amount":3,"date":"2021-09-10"})";
const auto transaction2Serialized =
    R"({"name":"orange","recipient":"fruit shop","category":"food","amount":1,"date":"2021-09-11"})";
const std::vector<std::string> transactionsSerializedWithOneTransaction{transaction1Serialized};
const std::vector<std::string> transactionsSerializedWithTwoTransactions{transaction1Serialized,
                                                                         transaction2Serialized};
const std::vector<std::string> emptyTransactionsSerialized{};
const std::string collectionName{"transactions"};
const auto transactionId{"id"};
}

class TransactionDbTest : public Test
{
public:
    std::unique_ptr<DocumentBasedDbMock> documentsDbInit{std::make_unique<StrictMock<DocumentBasedDbMock>>()};
    DocumentBasedDbMock* documentsDb{documentsDbInit.get()};
    std::unique_ptr<TransactionSerializerMock> transactionSerializerInit{
        std::make_unique<StrictMock<TransactionSerializerMock>>()};
    TransactionSerializerMock* transactionSerializer{transactionSerializerInit.get()};
    TransactionDb db{std::move(documentsDbInit), std::move(transactionSerializerInit)};
};

TEST_F(TransactionDbTest, addTransaction)
{
    EXPECT_CALL(*transactionSerializer, serialize(transaction1)).WillOnce(Return(transaction1Serialized));
    EXPECT_CALL(*documentsDb, insertDocument(collectionName, transaction1Serialized));

    db.add(transaction1);
}

TEST_F(TransactionDbTest, givenNoTransactions_shouldReturnEmptyTransactions)
{
    EXPECT_CALL(*documentsDb, getAllDocuments(collectionName)).WillOnce(Return(emptyTransactionsSerialized));

    const auto allTransactions = db.getAll();

    ASSERT_TRUE(allTransactions.empty());
}

TEST_F(TransactionDbTest, givenTwoTransactionsInserted_shouldReturnTwoTransactions)
{
    EXPECT_CALL(*transactionSerializer, serialize(transaction1)).WillOnce(Return(transaction1Serialized));
    EXPECT_CALL(*documentsDb, insertDocument(collectionName, transaction1Serialized));
    EXPECT_CALL(*transactionSerializer, serialize(transaction2)).WillOnce(Return(transaction2Serialized));
    EXPECT_CALL(*documentsDb, insertDocument(collectionName, transaction2Serialized));
    EXPECT_CALL(*transactionSerializer, deserialize(transaction1Serialized)).WillOnce(Return(transaction1));
    EXPECT_CALL(*transactionSerializer, deserialize(transaction2Serialized)).WillOnce(Return(transaction2));
    EXPECT_CALL(*documentsDb, getAllDocuments(collectionName))
        .WillOnce(Return(transactionsSerializedWithTwoTransactions));
    db.add(transaction1);
    db.add(transaction2);

    const auto allTransactions = db.getAll();

    ASSERT_EQ(allTransactions.size(), 2);
    ASSERT_EQ(allTransactions[0], transaction1);
    ASSERT_EQ(allTransactions[1], transaction2);
}

TEST_F(TransactionDbTest, updateTransaction)
{
    EXPECT_CALL(*transactionSerializer, serialize(transaction1)).WillOnce(Return(transaction1Serialized));
    EXPECT_CALL(*documentsDb, replaceDocument(collectionName, transactionId, transaction1Serialized));

    db.update(transactionId, transaction1);
}
