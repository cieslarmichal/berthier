#include "TransactionJsonSerializer.h"

#include "nlohmann/json.hpp"

#include "exceptions/InvalidJsonDocumentWithTransaction.h"

namespace bank::storage
{
namespace
{
constexpr auto idField = "_id";
constexpr auto nestedIdField = "$oid";
constexpr auto nameField = "name";
constexpr auto recipientField = "recipient";
constexpr auto categoryField = "category";
constexpr auto amountField = "amount";
constexpr auto dateField = "date";
const std::vector<std::string> requiredFields{idField,       nameField,   recipientField,
                                              categoryField, amountField, dateField};
}

std::string TransactionJsonSerializer::serialize(const Transaction& transaction) const
{
    nlohmann::json val = nlohmann::json::object();
    // not serializing id because it will be added in db
    val[nameField] = transaction.name;
    val[recipientField] = transaction.recipient;
    val[categoryField] = transaction.category;
    val[amountField] = transaction.amount;
    val[dateField] = transaction.date.toString();
    return val.dump();
}

Transaction TransactionJsonSerializer::deserialize(const std::string& jsonText) const
{
    try
    {
        const auto json = nlohmann::json::parse(jsonText);
        return parseTransaction(json);
    }
    catch (const std::exception& e)
    {
        throw exceptions::InvalidJsonDocumentWithTransaction{"Unable to parse transaction json document"};
    }
}

Transaction TransactionJsonSerializer::parseTransaction(const nlohmann::json& transactionJson) const
{
    if (not transactionJsonHasAllRequiredFields(transactionJson))
    {
        throw exceptions::InvalidJsonDocumentWithTransaction{"Transaction json missing required fields"};
    }

    const auto id = transactionJson.at(idField).at(nestedIdField).get<std::string>();
    const auto name = transactionJson.at(nameField).get<std::string>();
    const auto recipient = transactionJson.at(recipientField).get<std::string>();
    const auto category = transactionJson.at(categoryField).get<std::string>();
    const unsigned amount = transactionJson.at(amountField).get<std::int64_t>();
    const auto date = transactionJson.at(dateField).get<std::string>();
    return Transaction{id, name, recipient, category, amount, utils::Date{date}};
}

bool TransactionJsonSerializer::transactionJsonHasAllRequiredFields(
    const nlohmann::json& transactionJson) const
{
    auto transactionIsValid = std::all_of(
        requiredFields.begin(), requiredFields.end(),
        [&](const auto& fieldName) { return transactionJson.find(fieldName) != transactionJson.end(); });
    return transactionIsValid;
}
}