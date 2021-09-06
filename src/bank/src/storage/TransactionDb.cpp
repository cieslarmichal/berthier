#include "TransactionDb.h"

namespace bank::storage
{
TransactionDb::TransactionDb(std::unique_ptr<DocumentBasedDb> db,
                             std::unique_ptr<TransactionSerializer> serializer)
    : db{std::move(db)}, serializer{std::move(serializer)}, collectionName{"transactions"}
{
}

void TransactionDb::add(const Transaction& transaction)
{
    const auto serializedTransaction = serializer->serialize(transaction);
    db->insertDocument(collectionName, serializedTransaction);
}

std::vector<Transaction> TransactionDb::getAll() const
{
    const auto allTransactionsSerialized = db->findAllDocuments(collectionName);

    std::vector<Transaction> transactions;

    for (const auto& serializedTransaction : allTransactionsSerialized)
    {
        const auto deserializedTransaction = serializer->deserialize(serializedTransaction);
        transactions.push_back(deserializedTransaction);
    }

    return transactions;
}

void TransactionDb::update(const std::string& id, const Transaction& transaction)
{
    const auto serializedTransaction = serializer->serialize(transaction);
    db->replaceDocument(collectionName, id, serializedTransaction);
}
}