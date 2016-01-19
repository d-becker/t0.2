/*
 * Copyright (C) 2016 Daniel Becker <beckerdaniel.dani@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as published by
 * the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "BasicShape.h"

#include <algorithm>
#include <stdexcept>

#include "Block.h"

using namespace std;

// PIMPL
class BasicShape::PIMPL
{
public:

  PIMPL(int bbox_size, vector<Coords> coords, vector<shared_ptr<Block>> blocks)
   : m_bbox_size(bbox_size)
  {
    if (bbox_size < 1) {
      throw invalid_argument("An empty bounding box is not allowed.");
    }

    if (coords.size() != blocks.size()) {
      throw invalid_argument(
              "The number of coordinates does not match the number of blocks.");
    }
    checkDuplicates(coords);
    checkDuplicates(blocks);

    for (unsigned int i = 0; i < coords.size(); ++i) {
      m_blocks.emplace_back(coords.at(i), blocks.at(i)->clone());
    }
  }

  PIMPL(const PIMPL& other)
   : m_bbox_size(other.m_bbox_size), m_blocks(other.m_blocks) {}

  PIMPL(PIMPL&& other)
   : m_bbox_size(other.m_bbox_size), m_blocks(other.m_blocks) {}

  struct BlockWithPos {
    BlockWithPos(Coords p_pos, std::shared_ptr<Block> p_block)
     : pos(p_pos), block(p_block) {}

     BlockWithPos(const BlockWithPos& other)
      : pos(other.pos), block(other.block->clone()) {}

     BlockWithPos(BlockWithPos&& other) : pos(other.pos), block(other.block) {}

    Coords pos;
    std::shared_ptr<Block> block;
  };

  int m_bbox_size;
  std::vector<BlockWithPos> m_blocks {};

  template <typename T>
  void checkDuplicates(std::vector<T> vec) {
    for (unsigned int i = 0; i < vec.size(); ++i) {
      if (std::find(vec.begin(), vec.end(), vec.at(i)) != vec.begin() + i) {
        throw invalid_argument("Duplicates in the vector.");
      }
    }
  }

}; // PIMPL


BasicShape::BasicShape(int bbox_size, vector<Coords> coords,
                       vector<shared_ptr<Block>> blocks)
  : m_pimpl(new PIMPL(bbox_size, coords, blocks))
{


}

BasicShape::BasicShape(const BasicShape& other)
 : m_pimpl(new PIMPL(*other.m_pimpl)) {}

BasicShape::BasicShape(BasicShape&& other)
 : m_pimpl(other.m_pimpl)
{
  other.m_pimpl = nullptr;
}

BasicShape::~BasicShape()
{
  //dtor
  delete m_pimpl;
  m_pimpl = nullptr;
}

int BasicShape::getBBoxSize() const {
  return m_pimpl->m_bbox_size;
}

bool BasicShape::isValid(int vertical, int horizontal) const {
  return vertical >= 0 && horizontal >= 0
      && vertical < getBBoxSize() && horizontal < getBBoxSize();
}

shared_ptr<Block> BasicShape::get(int vertical, int horizontal) const {
  for (PIMPL::BlockWithPos b : m_pimpl->m_blocks) {
    if (b.pos.getVertical() == vertical && b.pos.getHorizontal() == horizontal)
    {
      return b.block;
    }
  }
  return nullptr;
}

vector<shared_ptr<Block>> BasicShape::getBlocks() {
  vector<shared_ptr<Block>> res;
  for (PIMPL::BlockWithPos b : m_pimpl->m_blocks) {
    res.push_back(b.block);
  }
  return res;
}

vector<Coords> BasicShape::getBlockPositions() const {
  vector<Coords> res;
  for (PIMPL::BlockWithPos b : m_pimpl->m_blocks) {
    res.push_back(b.pos);
  }
  return res;
}


void BasicShape::rotateRight() {
  int bbox_size = m_pimpl->m_bbox_size;
  for (PIMPL::BlockWithPos b : m_pimpl->m_blocks) {
    Coords& coords = b.pos;
    int vertical = coords.getVertical();
    int horizontal = coords.getHorizontal();
    coords.setVertical(horizontal);
    coords.setHorizontal(bbox_size - 1 - vertical);
  }
}

void BasicShape::rotateLeft() {
  int bbox_size = m_pimpl->m_bbox_size;
  for (PIMPL::BlockWithPos b : m_pimpl->m_blocks) {
    Coords& coords = b.pos;
    int vertical = coords.getVertical();
    int horizontal = coords.getHorizontal();
    coords.setVertical(bbox_size - 1 - horizontal);
    coords.setHorizontal(vertical);
  }
}

shared_ptr<Shape> BasicShape::clone() const {
  return make_shared<BasicShape>(*this);
}
