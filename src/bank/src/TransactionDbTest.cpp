#include "TransactionDb.h"

#include <gmock/gmock.h>

using namespace bank;
using namespace ::testing;

class TransactionDbTest : public Test
{
public:
    TransactionDb db;
};

TEST_F(TransactionDbTest, addTransaction)
{
    db.add(Transaction{});
}