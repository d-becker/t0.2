#include "UnitTest++.h"

#include "BasicBlock.h"

using namespace std;

namespace {

SUITE(BasicBlockTest)
{
  class BasicBlockFixture {
  public:
    shared_ptr<Block> bb = make_shared<BasicBlock>();
  };

  TEST_FIXTURE(BasicBlockFixture, clone)
  {
    shared_ptr<Block> res = bb->clone();
    CHECK_EQUAL(bb == res, false);
  }
}

}
