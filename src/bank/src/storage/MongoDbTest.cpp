#include "MongoDb.h"

#include <gmock/gmock.h>
#include "StlOperators.h"

using namespace bank::storage;
using namespace ::testing;

class MongoDbTest : public Test
{
public:
    MongoDb db{"transactionsDb"};
};

TEST_F(MongoDbTest, insert)
{
    db.insert("transactions", R"({"name": "coffee", "amount": "8"})");
}

TEST_F(MongoDbTest, getAll)
{
    std::cerr << db.getAll("transactions");
}