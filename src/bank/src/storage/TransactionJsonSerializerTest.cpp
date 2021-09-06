#include "TransactionJsonSerializer.h"

#include "gtest/gtest.h"

#include "exceptions/InvalidJsonDocumentWithTransaction.h"

using namespace ::testing;
using namespace bank::storage;

namespace
{
const auto transactionToSerialize = Transaction{"", "water", "shop", "food", 3, utils::Date{"2021-09-10"}};
const auto deserializedTransaction =
    Transaction{"61366f91c87878186f1d4fe2", "water", "shop", "food", 3, utils::Date{"2021-09-10"}};
const std::string serializedTransaction =
    R"({"amount":3,"category":"food","date":"2021-09-10","name":"water","recipient":"shop"})";
const std::string transactionToDeserialize =
    R"({"_id":{"$oid":"61366f91c87878186f1d4fe2"},"name":"water","recipient":"shop","category":"food","amount":3,"date":"2021-09-10"})";
const std::string transactionWithoutIdFieldToDeserialize =
    R"({"recipient":"shop","category":"food","amount":3,"date":"2021-09-10"})";
const std::string transactionWithoutNameFieldToDeserialize =
    R"({"_id":{"$oid":"61366f91c87878186f1d4fe2"},"recipient":"shop","category":"food","amount":3,"date":"2021-09-10"})";
const std::string transactionWithoutRecipientFieldToDeserialize =
    R"({"_id":{"$oid":"61366f91c87878186f1d4fe2"},"name":"water","category":"food","amount":3,"date":"2021-09-10"})";
const std::string transactionWithoutCategoryFieldToDeserialize =
    R"({"_id":{"$oid":"61366f91c87878186f1d4fe2"},"name":"water","recipient":"shop","amount":3,"date":"2021-09-10"})";
const std::string transactionWithoutAmountFieldToDeserialize =
    R"({"_id":{"$oid":"61366f91c87878186f1d4fe2"},"name":"water","recipient":"shop","category":"food","date":"2021-09-10"})";
const std::string transactionWithoutDateFieldToDeserialize =
    R"({"_id":{"$oid":"61366f91c87878186f1d4fe2"},"name":"water","recipient":"shop","category":"food","amount":3})";
const std::string invalidJson{"{."};
}

class TransactionJsonSerializerTest : public Test
{
public:
    TransactionJsonSerializer serializer;
};

TEST_F(TransactionJsonSerializerTest, givenTransaction_shouldReturnSerializedTransaction)
{
    const auto actualSerializedTransaction = serializer.serialize(transactionToSerialize);

    EXPECT_EQ(actualSerializedTransaction, serializedTransaction);
}

TEST_F(TransactionJsonSerializerTest, givenSerializedTransaction_shouldReturnTransaction)
{
    const auto actualTransaction = serializer.deserialize(transactionToDeserialize);

    EXPECT_EQ(actualTransaction, deserializedTransaction);
}

TEST_F(TransactionJsonSerializerTest, givenInvalidJson_shouldThrowInvalidJsonDocumentWithTransaction)
{
    ASSERT_THROW(serializer.deserialize(invalidJson), exceptions::InvalidJsonDocumentWithTransaction);
}

TEST_F(TransactionJsonSerializerTest, givenJsonWithoutIdField_shouldThrowInvalidJsonDocumentWithTransaction)
{
    ASSERT_THROW(serializer.deserialize(transactionWithoutIdFieldToDeserialize),
                 exceptions::InvalidJsonDocumentWithTransaction);
}

TEST_F(TransactionJsonSerializerTest, givenJsonWithoutNameField_shouldThrowInvalidJsonDocumentWithTransaction)
{
    ASSERT_THROW(serializer.deserialize(transactionWithoutNameFieldToDeserialize),
                 exceptions::InvalidJsonDocumentWithTransaction);
}

TEST_F(TransactionJsonSerializerTest,
       givenJsonWithoutRecipientField_shouldThrowInvalidJsonDocumentWithTransaction)
{
    ASSERT_THROW(serializer.deserialize(transactionWithoutRecipientFieldToDeserialize),
                 exceptions::InvalidJsonDocumentWithTransaction);
}

TEST_F(TransactionJsonSerializerTest,
       givenJsonWithoutCategoryField_shouldThrowInvalidJsonDocumentWithTransaction)
{
    ASSERT_THROW(serializer.deserialize(transactionWithoutCategoryFieldToDeserialize),
                 exceptions::InvalidJsonDocumentWithTransaction);
}

TEST_F(TransactionJsonSerializerTest,
       givenJsonWithoutAmountField_shouldThrowInvalidJsonDocumentWithTransaction)
{
    ASSERT_THROW(serializer.deserialize(transactionWithoutAmountFieldToDeserialize),
                 exceptions::InvalidJsonDocumentWithTransaction);
}

TEST_F(TransactionJsonSerializerTest, givenJsonWithoutDateField_shouldThrowInvalidJsonDocumentWithTransaction)
{
    ASSERT_THROW(serializer.deserialize(transactionWithoutDateFieldToDeserialize),
                 exceptions::InvalidJsonDocumentWithTransaction);
}