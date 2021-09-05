#include "TransactionJsonSerializer.h"

#include "nlohmann/json.hpp"

namespace bank::storage
{


//namespace nlohmann {
//void from_json(const json & j, bank::storage::transaction & x);
//void to_json(json & j, const bank::storage::transaction & x);
//
//inline void from_json(const json & j, bank::storage::transaction& x) {
//    x.setName(j.at("name").get<std::string>());
//    x.setRecipient(j.at("recipient").get<std::string>());
//    x.setCategory(j.at("category").get<std::string>());
//    x.setAmount(j.at("amount").get<int64_t>());
//    x.setDate(j.at("date").get<std::string>());
//}
//
//inline void to_json(json & j, const bank::storage::transaction & x) {
//    j = json::object();
//    j["name"] = x.getName();
//    j["recipient"] = x.getRecipient();
//    j["category"] = x.getCategory();
//    j["amount"] = x.getAmount();
//    j["date"] = x.getDate();
//}

std::string TransactionJsonSerializer::serialize(const Transaction&) const
{
    return std::string();
}

Transaction TransactionJsonSerializer::deserialize(const std::string&) const
{
    return Transaction();
}
}