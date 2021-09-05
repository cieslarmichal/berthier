#include "TransactionDb.h"

namespace bank::storage
{
TransactionDb::TransactionDb(std::unique_ptr<DocumentBasedDb> db)
    : db{std::move(db)}, collectionName{"transactions"}
{
}

void TransactionDb::add(const Transaction& transaction)
{
    const auto serializedTransaction = "";
    db->insertDocument(collectionName, serializedTransaction);
}

std::vector<Transaction> TransactionDb::getAll() const
{
    const auto allTransactionsSerialized = db->getAllDocuments(collectionName);

    return {};
}
}