#include "UnitTest++.h"

#include "Coords.h"

using namespace std;

namespace {

SUITE(getters)
{
  class CoordsFixture {
  public:
    Coords c = Coords(2, -4);
  };

  TEST_FIXTURE(CoordsFixture, getVertical0)
  {
    int exp_res = 2;
    int res = c.getVertical();
    CHECK_EQUAL(exp_res, res);
  }

  TEST_FIXTURE(CoordsFixture, getHorizontal0)
  {
    int exp_res = -4;
    int res = c.getHorizontal();
    CHECK_EQUAL(exp_res, res);
  }
}

SUITE(setters)
{
  class CoordsFixture {
  public:
    Coords c = Coords(2, -4);
  };

  TEST_FIXTURE(CoordsFixture, setVertical0)
  {
    int new_vertical = -5;
    c.setVertical(new_vertical);
    int exp_res = new_vertical;
    int res = c.getVertical();
    CHECK_EQUAL(exp_res, res);
  }

  TEST_FIXTURE(CoordsFixture, getHorizontal0)
  {
    int new_horizontal = 6;
    c.setHorizontal(new_horizontal);
    int exp_res = new_horizontal;
    int res = c.getHorizontal();
    CHECK_EQUAL(exp_res, res);
  }
}

SUITE(operators)
{
  class CoordsFixture {
  public:
    Coords c = Coords(2, -4);
  };

  TEST_FIXTURE(CoordsFixture, operator_equals0)
  {
    Coords new_coords = Coords(c);
    bool exp_res = true;
    bool res = (c == new_coords);
    CHECK_EQUAL(exp_res, res);
  }

  TEST_FIXTURE(CoordsFixture, operator_assignment0)
  {
    Coords new_coords = Coords(4, -5);
    c = new_coords;
    bool exp_res = true;
    bool res = (c == new_coords);
    CHECK_EQUAL(exp_res, res);
  }

  TEST_FIXTURE(CoordsFixture, operator_assignment_plus0)
  {
    Coords orig_c = c;
    Coords new_coords = Coords(4, -5);
    c += new_coords;
    bool exp_res = true;
    bool res = (c == Coords(orig_c.getVertical() + new_coords.getVertical(),
                      orig_c.getHorizontal() + new_coords.getHorizontal()));
    CHECK_EQUAL(exp_res, res);
  }

  TEST_FIXTURE(CoordsFixture, operator_assignment_minus0)
  {
    Coords orig_c = c;
    Coords new_coords = Coords(4, -5);
    c -= new_coords;
    bool exp_res = true;
    bool res = (c == Coords(orig_c.getVertical() - new_coords.getVertical(),
                      orig_c.getHorizontal() - new_coords.getHorizontal()));
    CHECK_EQUAL(exp_res, res);
  }

  TEST_FIXTURE(CoordsFixture, operator_plus0)
  {
    Coords other(6, 4);
    Coords res_coords = c + other;
    int exp_vertical = c.getVertical() + other.getVertical();
    int exp_horizontal = c.getHorizontal() + other.getHorizontal();
    bool exp_res = true;
    bool res = (res_coords == Coords(exp_vertical, exp_horizontal));
    CHECK_EQUAL(exp_res, res);
  }

  TEST_FIXTURE(CoordsFixture, operator_minus0)
  {
    Coords other(6, 14);
    Coords res_coords = c - other;
    int exp_vertical = c.getVertical() - other.getVertical();
    int exp_horizontal = c.getHorizontal() - other.getHorizontal();
    bool exp_res = true;
    bool res = (res_coords == Coords(exp_vertical, exp_horizontal));
    CHECK_EQUAL(exp_res, res);
  }
}


}
