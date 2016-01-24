#include <algorithm>
#include <iostream>

#include "UnitTest++.h"
#include "TestHelpers.h"

#include "BasicBlock.h"
#include "BasicShape.h"

using namespace std;
using namespace tetris;

namespace {

// Tests.
SUITE(getBBoxSize)
{
  const int bbox_size = 4;

  class BasicShapeFixture {
  public:
    shared_ptr<Shape> bsh = make_shared<BasicShape>(
                                                  bbox_size,
                                                  vector<Coords>{},
                                                  vector<shared_ptr<Block>>{});
  };

  TEST_FIXTURE(BasicShapeFixture, getBBoxSize)
  {
    int exp_res = bbox_size;
    int res = bsh->getBBoxSize();
    CHECK_EQUAL(exp_res, res);
  }
}

SUITE(isValid)
{
  const int bbox_size = 4;
  const shared_ptr<Block> bblock = make_shared<BasicBlock>();

  class BasicShapeFixture {
  public:
    shared_ptr<Shape> bsh = make_shared<BasicShape>(
            bbox_size,
            vector<Coords>{Coords(0, 0), Coords(0, 1),
                           Coords(1, 1), Coords(2, 1)},
            vector<shared_ptr<Block>>{bblock->clone(), bblock->clone(),
                                      bblock->clone(), bblock->clone(), }
                                                   );
  };

  TEST_FIXTURE(BasicShapeFixture, isValid0)
  {
    Coords c(-1, 2);
    bool exp_res = false;
    bool res = bsh->isValid(c);
    CHECK_EQUAL(exp_res, res);
  }

  TEST_FIXTURE(BasicShapeFixture, isValid1)
  {
    Coords c(bbox_size, 2);
    bool exp_res = false;
    bool res = bsh->isValid(c);
    CHECK_EQUAL(exp_res, res);
  }

  TEST_FIXTURE(BasicShapeFixture, isValid2)
  {
    Coords c(bbox_size-1, -2);
    bool exp_res = false;
    bool res = bsh->isValid(c);
    CHECK_EQUAL(exp_res, res);
  }

  TEST_FIXTURE(BasicShapeFixture, isValid3)
  {
    Coords c(bbox_size-1, bbox_size);
    bool exp_res = false;
    bool res = bsh->isValid(c);
    CHECK_EQUAL(exp_res, res);
  }

  TEST_FIXTURE(BasicShapeFixture, isValid4)
  {
    Coords c(bbox_size-1, bbox_size-2);
    bool exp_res = true;
    bool res = bsh->isValid(c);
    CHECK_EQUAL(exp_res, res);
  }
}

SUITE(get)
{
  const int bbox_size = 4;
  const shared_ptr<Block> bblock = make_shared<BasicBlock>();

  class BasicShapeFixture {
  public:
    shared_ptr<Shape> bsh = make_shared<BasicShape>(
            bbox_size,
            vector<Coords>{Coords(0, 0), Coords(0, 1),
                           Coords(1, 1), Coords(2, 1)},
            vector<shared_ptr<Block>>{bblock->clone(), bblock->clone(),
                                      bblock->clone(), bblock->clone(), }
                                                   );
  };

  TEST_FIXTURE(BasicShapeFixture, get0)
  {
    // Outside the bounding box.
    Coords c(-1, 1);
    bool exp_res = true;
    bool res = bsh->get(c) == nullptr;
    CHECK_EQUAL(exp_res, res);
  }

  TEST_FIXTURE(BasicShapeFixture, get1)
  {
    // Outside the bounding box.
    Coords c(bbox_size, 1);
    bool exp_res = true;
    bool res = bsh->get(c) == nullptr;
    CHECK_EQUAL(exp_res, res);
  }

  TEST_FIXTURE(BasicShapeFixture, get2)
  {
    // Inside the bounding box.
    Coords c(bbox_size-1, 1);
    bool exp_res = false;
    bool not_null = bsh->get(c) == nullptr;
    bool correct_class = dynamic_cast<BasicShape*>(bsh->get(c).get());
    bool res = not_null && correct_class;
    CHECK_EQUAL(exp_res, res);
  }
}

SUITE(getBlocks)
{
  const int bbox_size = 3;
  const shared_ptr<Block> bblock = make_shared<BasicBlock>();
  vector<shared_ptr<Block>> blocks{bblock->clone(), bblock->clone(),
                                   bblock->clone(), bblock->clone()};

  class BasicShapeFixture {
  public:
    shared_ptr<Shape> bsh = make_shared<BasicShape>(
            bbox_size,
            vector<Coords>{Coords(0, 0), Coords(0, 1),
                           Coords(1, 1), Coords(2, 1)},
                           blocks
                                                   );
  };

  TEST_FIXTURE(BasicShapeFixture, getBlocks0)
  {
    vector<shared_ptr<Block>>& exp_blocks = blocks;
    vector<shared_ptr<Block>> blocks = bsh->getBlocks();
    CHECK_EQUAL(true, exp_blocks.size() == blocks.size());
  }
}

SUITE(getBlockPositions)
{
  const int bbox_size = 3;
  vector<Coords> coords {Coords(0, 0), Coords(0, 1),
                         Coords(1, 1), Coords(2, 1)};
  const shared_ptr<Block> bblock = make_shared<BasicBlock>();
  vector<shared_ptr<Block>> blocks{bblock->clone(), bblock->clone(),
                                   bblock->clone(), bblock->clone()};

  class BasicShapeFixture {
  public:
    shared_ptr<Shape> bsh = make_shared<BasicShape>(bbox_size, coords, blocks);
  };

  TEST_FIXTURE(BasicShapeFixture, getBlockPositions0)
  {
    vector<Coords>& exp_coords = coords;
    const vector<Coords>& res_coords = bsh->getBlockPositions();
    bool exp_res = true;
    bool res = same_elements(exp_coords, res_coords);
    CHECK_EQUAL(exp_res, res);
  }
}

SUITE(rotateRight)
{
  const int bbox_size = 3;
  vector<Coords> coords {Coords(0, 0), Coords(0, 1),
                         Coords(1, 0), Coords(2, 0)};
  const shared_ptr<Block> bblock = make_shared<BasicBlock>();
  vector<shared_ptr<Block>> blocks{bblock->clone(), bblock->clone(),
                                   bblock->clone(), bblock->clone()};

  class BasicShapeFixture {
  public:
    shared_ptr<Shape> bsh = make_shared<BasicShape>(bbox_size, coords, blocks);
  };

  TEST_FIXTURE(BasicShapeFixture, rotateRight0)
  {
    bsh->rotateRight();
    vector<Coords> exp_coords {Coords(0, 0), Coords(0, 1),
                               Coords(0, 2), Coords(1, 2)};
    vector<Coords> res_coords = bsh->getBlockPositions();

    bool exp_res = true;
    bool res = same_elements(exp_coords, res_coords);
    CHECK_EQUAL(exp_res, res);
  }
}

SUITE(rotateLeft)
{
  const int bbox_size = 3;
  vector<Coords> coords {Coords(0, 0), Coords(0, 1),
                         Coords(1, 0), Coords(2, 0)};
  const shared_ptr<Block> bblock = make_shared<BasicBlock>();
  vector<shared_ptr<Block>> blocks{bblock->clone(), bblock->clone(),
                                   bblock->clone(), bblock->clone()};

  class BasicShapeFixture {
  public:
    shared_ptr<Shape> bsh = make_shared<BasicShape>(bbox_size, coords, blocks);
  };

  TEST_FIXTURE(BasicShapeFixture, rotateLeftt0)
  {
    bsh->rotateLeft();
    vector<Coords> exp_coords {Coords(1, 0), Coords(2, 0),
                               Coords(2, 1), Coords(2, 2)};
    vector<Coords> res_coords = bsh->getBlockPositions();

    bool exp_res = true;
    bool res = same_elements(exp_coords, res_coords);
    CHECK_EQUAL(exp_res, res);
  }
}

// Checking whether two rotations in the opposite direction give back
// the original state.
SUITE(rotateBack)
{
  const int bbox_size = 3;
  vector<Coords> coords {Coords(0, 0), Coords(0, 1),
                         Coords(1, 0), Coords(2, 0)};
  const shared_ptr<Block> bblock = make_shared<BasicBlock>();
  vector<shared_ptr<Block>> blocks{bblock->clone(), bblock->clone(),
                                   bblock->clone(), bblock->clone()};

  class BasicShapeFixture {
  public:
    shared_ptr<Shape> bsh = make_shared<BasicShape>(bbox_size, coords, blocks);
  };

  TEST_FIXTURE(BasicShapeFixture, rotateBackfromRight0)
  {
    bsh->rotateRight();
    bsh->rotateLeft();
    vector<Coords> exp_coords {Coords(0, 0), Coords(0, 1),
                               Coords(1, 0), Coords(2, 0)};
    vector<Coords> res_coords = bsh->getBlockPositions();

    bool exp_res = true;
    bool res = same_elements(exp_coords, res_coords);
    CHECK_EQUAL(exp_res, res);
  }

  TEST_FIXTURE(BasicShapeFixture, rotateBackfromLeft0)
  {
    bsh->rotateLeft();
    bsh->rotateRight();
    vector<Coords> exp_coords {Coords(0, 0), Coords(0, 1),
                               Coords(1, 0), Coords(2, 0)};
    vector<Coords> res_coords = bsh->getBlockPositions();

    bool exp_res = true;
    bool res = same_elements(exp_coords, res_coords);
    CHECK_EQUAL(exp_res, res);
  }
}

}
