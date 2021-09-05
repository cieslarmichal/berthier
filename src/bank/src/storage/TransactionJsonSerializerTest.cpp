#include "TransactionJsonSerializer.h"

#include "gtest/gtest.h"

#include "exceptions/InvalidJsonDocumentWithTransaction.h"

using namespace ::testing;
using namespace bank::storage;

namespace
{
const auto transaction = Transaction{"water", "shop", "food", 3, "date"};
const std::string serializedTransaction =
    R"({"amount":3,"category":"food","date":"date","name":"water","recipient":"shop"})";
const std::string serializedTransactionWithoutNameField =
    R"({"recipient":"shop","category":"food","amount":3,"date":"date"})";
const std::string serializedTransactionWithoutRecipientField =
    R"({"name":"water","category":"food","amount":3,"date":"date"})";
const std::string serializedTransactionWithoutCategoryField =
    R"({"name":"water","recipient":"shop","amount":3,"date":"date"})";
const std::string serializedTransactionWithoutAmountField =
    R"({"name":"water","recipient":"shop","category":"food","date":"date"})";
const std::string serializedTransactionWithoutDateField =
    R"({"name":"water","recipient":"shop","category":"food","amount":3})";
const std::string invalidJson{"{."};
}

class TransactionJsonSerializerTest : public Test
{
public:
    TransactionJsonSerializer serializer;
};

TEST_F(TransactionJsonSerializerTest, givenTransaction_shouldReturnSerializedTransaction)
{
    const auto actualSerializedTransaction = serializer.serialize(transaction);

    EXPECT_EQ(actualSerializedTransaction, serializedTransaction);
}

TEST_F(TransactionJsonSerializerTest, givenSerializedTransaction_shouldReturnTransaction)
{
    const auto actualTransaction = serializer.deserialize(serializedTransaction);

    EXPECT_EQ(actualTransaction, transaction);
}

TEST_F(TransactionJsonSerializerTest, givenInvalidJson_shouldThrowInvalidJsonDocumentWithTransaction)
{
    ASSERT_THROW(serializer.deserialize(invalidJson), exceptions::InvalidJsonDocumentWithTransaction);
}

TEST_F(TransactionJsonSerializerTest, givenJsonWithoutNameField_shouldThrowInvalidJsonDocumentWithTransaction)
{
    ASSERT_THROW(serializer.deserialize(serializedTransactionWithoutNameField),
                 exceptions::InvalidJsonDocumentWithTransaction);
}

TEST_F(TransactionJsonSerializerTest,
       givenJsonWithoutRecipientField_shouldThrowInvalidJsonDocumentWithTransaction)
{
    ASSERT_THROW(serializer.deserialize(serializedTransactionWithoutRecipientField),
                 exceptions::InvalidJsonDocumentWithTransaction);
}

TEST_F(TransactionJsonSerializerTest,
       givenJsonWithoutCategoryField_shouldThrowInvalidJsonDocumentWithTransaction)
{
    ASSERT_THROW(serializer.deserialize(serializedTransactionWithoutCategoryField),
                 exceptions::InvalidJsonDocumentWithTransaction);
}

TEST_F(TransactionJsonSerializerTest,
       givenJsonWithoutAmountField_shouldThrowInvalidJsonDocumentWithTransaction)
{
    ASSERT_THROW(serializer.deserialize(serializedTransactionWithoutAmountField),
                 exceptions::InvalidJsonDocumentWithTransaction);
}

TEST_F(TransactionJsonSerializerTest, givenJsonWithoutDateField_shouldThrowInvalidJsonDocumentWithTransaction)
{
    ASSERT_THROW(serializer.deserialize(serializedTransactionWithoutDateField),
                 exceptions::InvalidJsonDocumentWithTransaction);
}