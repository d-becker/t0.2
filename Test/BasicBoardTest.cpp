#include "UnitTest++.h"

#include "BasicBlock.h"
#include "BasicBoard.h"

using namespace std;

namespace {

SUITE(getHeight)
{
  TEST(getHeight0)
  {
    const int height = 15;
    const int width = 8;
    shared_ptr<BasicBoard> bb = make_shared<BasicBoard>(height, width);

    int exp_res = height;
    int res = bb->getHeight();
    CHECK_EQUAL(exp_res, res);
  }

  TEST(getHeight1)
  {
    const int height = 18;
    const int width = 8;
    shared_ptr<BasicBoard> bb = make_shared<BasicBoard>(height, width);

    int exp_res = height;
    int res = bb->getHeight();
    CHECK_EQUAL(exp_res, res);
  }
}

SUITE(getWidth)
{
  TEST(getWidth0)
  {
    const int height = 15;
    const int width = 8;
    shared_ptr<BasicBoard> bb = make_shared<BasicBoard>(height, width);

    int exp_res = width;
    int res = bb->getWidth();
    CHECK_EQUAL(exp_res, res);
  }

  TEST(getWidth1)
  {
    const int height = 18;
    const int width = 10;
    shared_ptr<BasicBoard> bb = make_shared<BasicBoard>(height, width);

    int exp_res = width;
    int res = bb->getWidth();
    CHECK_EQUAL(exp_res, res);
  }
}

SUITE(get)
{
  TEST(get0)
  {
    // Valid position.
    const int height = 18;
    const int width = 10;
    shared_ptr<BasicBoard> bb = make_shared<BasicBoard>(height, width);

    int vertical = 4;
    int horizontal = 8;
    shared_ptr<Block> block = make_shared<BasicBlock>();
    bb->set(vertical, horizontal, block);

    shared_ptr<Block> res = bb->get(vertical, horizontal);
    CHECK_EQUAL(true, res != nullptr);
  }

  TEST(get1)
  {
    // Invalid position.
    const int height = 18;
    const int width = 10;
    shared_ptr<BasicBoard> bb = make_shared<BasicBoard>(height, width);

    shared_ptr<Block> exp_res = nullptr;
    shared_ptr<Block> res = bb->get(-10, 0);
    CHECK_EQUAL(exp_res, res);
  }
}

SUITE(set)
{
  TEST(set0)
  {
    const int height = 18;
    const int width = 10;
    shared_ptr<BasicBoard> bb = make_shared<BasicBoard>(height, width);
    shared_ptr<Block> block = make_shared<BasicBlock>();
    int vertical = 4;
    int horizontal = 6;
    bb->set(vertical, horizontal, block);

    shared_ptr<Block> res = bb->get(vertical, horizontal);
    CHECK_EQUAL(true, (res != nullptr));
  }

  TEST(set1)
  {
    const int height = 18;
    const int width = 10;
    shared_ptr<BasicBoard> bb = make_shared<BasicBoard>(height, width);
    shared_ptr<Block> block = make_shared<BasicBlock>();
    int vertical = 4;
    int horizontal = 60;
    bb->set(vertical, horizontal, block);

    shared_ptr<Block> res = bb->get(vertical, horizontal);
    CHECK_EQUAL(true, (res == nullptr));
  }
}

SUITE(removeRow)
{
  TEST(removeRow0)
  {
    const int height = 18;
    const int width = 10;
    shared_ptr<BasicBoard> bb = make_shared<BasicBoard>(height, width);
    shared_ptr<Block> block = make_shared<BasicBlock>();
    int vertical = 4;
    int horizontal = 6;
    bb->set(vertical, horizontal, block);

    shared_ptr<Block> block_retrieved = bb->get(vertical, horizontal);
    bool is_null = (block_retrieved == nullptr);
    CHECK_EQUAL(false, is_null);

    bb->removeRow(vertical);

    block_retrieved = bb->get(vertical, horizontal);
    is_null = (block_retrieved == nullptr);
    CHECK_EQUAL(true, is_null);
  }

}

}
