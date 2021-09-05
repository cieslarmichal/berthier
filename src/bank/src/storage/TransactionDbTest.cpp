#include "TransactionDb.h"

#include <gmock/gmock.h>

#include "DocumentBasedDbMock.h"

using namespace bank::storage;
using namespace ::testing;

namespace
{
const auto transaction1 = Transaction{"water", "shop", "food", 3, "date"};
const auto transaction1Serialized =
    R"({"name":"water","recipient":"shop","category":"food","amount":3,"date":"date"})";
const std::vector<std::string> transactionsSerialized{transaction1Serialized};
const std::string collectionName{"transactions"};
}

class TransactionDbTest : public Test
{
public:
    std::unique_ptr<DocumentBasedDbMock> documentsDbInit{std::make_unique<StrictMock<DocumentBasedDbMock>>()};
    DocumentBasedDbMock* documentsDb{documentsDbInit.get()};
    TransactionDb db{std::move(documentsDbInit)};
};

TEST_F(TransactionDbTest, addTransaction)
{
    EXPECT_CALL(*documentsDb, insertDocument(collectionName, transaction1Serialized));
    EXPECT_CALL(*documentsDb, getAllDocuments(collectionName)).WillOnce(Return(transactionsSerialized));
    db.add(transaction1);

    const auto allTransactions = db.getAll();

    ASSERT_EQ(allTransactions.size(), 1);
    ASSERT_EQ(allTransactions[0], transaction1);
}