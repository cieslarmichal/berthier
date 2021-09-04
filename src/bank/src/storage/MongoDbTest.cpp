#include "MongoDb.h"

#include <gmock/gmock.h>

using namespace bank::storage;
using namespace ::testing;

class MongoDbTest : public Test
{
public:
    MongoDb db{"transactionsDb"};
};

TEST_F(MongoDbTest, insert)
{
    std::cerr << db.getAll("transactions")[0];
}