#include "UnitTest++.h"
#include "TestHelpers.h"

#include "DefaultGameBoard.h"
#include "BasicBlock.h"
#include "BasicBoard.h"
#include "BasicShape.h"

using namespace std;

namespace {

SUITE(getBoard)
{
  TEST(getBoard0)
  {
    shared_ptr<Board> board = make_shared<BasicBoard>(18, 10);
    shared_ptr<DefaultGameBoard>  dgb = make_shared<DefaultGameBoard>(board);

    shared_ptr<Board> exp_board = board;
    shared_ptr<const Board> board_retrieved = dgb->getBoard();

    bool equals = (board == board_retrieved);
    CHECK_EQUAL(true, equals);
  }
}

SUITE(currentShape)
{
  class DefaultGameBoardFixture {
  public:
    shared_ptr<Board> board = make_shared<BasicBoard>(18, 10);
    shared_ptr<DefaultGameBoard>  dgb = make_shared<DefaultGameBoard>(board);
  };

  TEST_FIXTURE(DefaultGameBoardFixture, get0)
  {
    shared_ptr<const Shape> sh = dgb->getCurrentShape();
    bool res = (sh == nullptr);
    CHECK_EQUAL(true, res);
  }

  TEST_FIXTURE(DefaultGameBoardFixture, get_set0)
  {
    BasicShape s = BasicShape(3, {}, {});
    shared_ptr<Shape> shape = make_shared<BasicShape>(s);
    dgb->setCurrentShape(shape);
    shared_ptr<const Shape> sh = dgb->getCurrentShape();
    bool res = (sh == shape);
    CHECK_EQUAL(true, res);
  }
}

SUITE(shape_pos)
{
  class DefaultGameBoardFixture {
  public:
    shared_ptr<Board> board = make_shared<BasicBoard>(18, 10);
    shared_ptr<DefaultGameBoard>  dgb = make_shared<DefaultGameBoard>(board);
  };

  TEST_FIXTURE(DefaultGameBoardFixture, get_set0)
  {
    Coords new_pos = Coords(1, 4);
    dgb->setCurrentShapePosition(new_pos);

    Coords position_retrieved = dgb->getCurrentShapePosition();

    bool res = (new_pos == position_retrieved);
    CHECK_EQUAL(true, res);
  }
}

SUITE(getAbsolutePositions)
{
  vector<Coords> coords {Coords(0, 0), Coords(0, 1),
                             Coords(1, 0), Coords(2, 0)};
  class DefaultGameBoardFixture {
  public:
    DefaultGameBoardFixture() {
      const int bbox_size = 3;
      const shared_ptr<Block> bblock = make_shared<BasicBlock>();
      vector<shared_ptr<Block>> blocks{bblock->clone(), bblock->clone(),
                                       bblock->clone(), bblock->clone()};

      BasicShape s = BasicShape(bbox_size, coords, blocks);
      shared_ptr<Shape> shape = make_shared<BasicShape>(s);

      dgb->setCurrentShape(shape);
      dgb->setCurrentShapePosition(Coords(5, 2));
    }

    shared_ptr<Board> board = make_shared<BasicBoard>(18, 10);
    shared_ptr<DefaultGameBoard>  dgb = make_shared<DefaultGameBoard>(board);
  };

  TEST_FIXTURE(DefaultGameBoardFixture, getAbsolutePositions)
  {
    vector<Coords> absPos = dgb->getAbsolutePositions();

    vector<Coords> exp_abs_pos {Coords(5, 2), Coords(5, 3),
                                Coords(6, 2), Coords(7, 2)};
    bool exp_res = true;
    bool res = same_elements(exp_abs_pos, absPos);

    CHECK_EQUAL(exp_res, res);
  }
}

SUITE(isAtValidPos)
{
  vector<Coords> coords {Coords(0, 0), Coords(0, 1),
                             Coords(1, 0), Coords(2, 0)};
  const shared_ptr<Block> bblock = make_shared<BasicBlock>();
  class DefaultGameBoardFixture {
  public:
    DefaultGameBoardFixture() {
      const int bbox_size = 3;
      vector<shared_ptr<Block>> blocks{bblock->clone(), bblock->clone(),
                                       bblock->clone(), bblock->clone()};

      BasicShape s = BasicShape(bbox_size, coords, blocks);
      shared_ptr<Shape> shape = make_shared<BasicShape>(s);

      dgb->setCurrentShape(shape);
    }

    shared_ptr<Board> board = make_shared<BasicBoard>(18, 10);
    shared_ptr<DefaultGameBoard>  dgb = make_shared<DefaultGameBoard>(board);
  };

  TEST_FIXTURE(DefaultGameBoardFixture, isAtValidPos_Outside)
  {
    dgb->setCurrentShapePosition(Coords(board->getHeight(), 0));

    bool exp_res = false;
    bool res = dgb->isAtValidPos();

    CHECK_EQUAL(exp_res, res);
  }

  TEST_FIXTURE(DefaultGameBoardFixture, isAtValidPos_Filled)
  {
    dgb->setCurrentShapePosition(Coords(0, 0));
    board->set(0, 0, bblock);

    bool exp_res = false;
    bool res = dgb->isAtValidPos();

    CHECK_EQUAL(exp_res, res);
  }

  TEST_FIXTURE(DefaultGameBoardFixture, isAtValidPos_Pass)
  {
    dgb->setCurrentShapePosition(Coords(0, 0));

    bool exp_res = true;
    bool res = dgb->isAtValidPos();

    CHECK_EQUAL(exp_res, res);
  }
}

SUITE(hasLanded)
{
  vector<Coords> coords {Coords(0, 0), Coords(0, 1),
                         Coords(1, 0), Coords(2, 0)};
  const shared_ptr<Block> bblock = make_shared<BasicBlock>();
  class DefaultGameBoardFixture {
  public:
    DefaultGameBoardFixture() {
      const int bbox_size = 3;
      vector<shared_ptr<Block>> blocks{bblock->clone(), bblock->clone(),
                                       bblock->clone(), bblock->clone()};

      BasicShape s = BasicShape(bbox_size, coords, blocks);
      shared_ptr<Shape> shape = make_shared<BasicShape>(s);

      dgb->setCurrentShape(shape);
    }

    shared_ptr<Board> board = make_shared<BasicBoard>(18, 10);
    shared_ptr<DefaultGameBoard>  dgb = make_shared<DefaultGameBoard>(board);
  };

  TEST_FIXTURE(DefaultGameBoardFixture, hasLanded_Floating)
  {
    dgb->setCurrentShapePosition(Coords(0, 0));

    bool exp_res = false;
    bool res = dgb->hasLanded();
    CHECK_EQUAL(exp_res, res);
  }

  TEST_FIXTURE(DefaultGameBoardFixture, hasLanded_Down)
  {
    dgb->setCurrentShapePosition(Coords(board->getHeight() - 3, 0));

    bool exp_res = true;
    bool res = dgb->hasLanded();
    CHECK_EQUAL(exp_res, res);
  }

  TEST_FIXTURE(DefaultGameBoardFixture, hasLanded_OnBlock)
  {
    dgb->setCurrentShapePosition(Coords(board->getHeight() - 4, 0));
    board->set(board->getHeight()-1, 0, bblock);

    bool exp_res = true;
    bool res = dgb->hasLanded();
    CHECK_EQUAL(exp_res, res);
  }



}

}
