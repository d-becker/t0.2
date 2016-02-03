/*
 * Copyright (C) 2016 Daniel Becker <beckerdaniel.dani@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as published
 * by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "BasicBlock.h"

using namespace std;

namespace tetris {

BasicBlock::BasicBlock()
  : Block()
{

}

BasicBlock::BasicBlock(const BasicBlock& other)
  : Block(other)
{

}

BasicBlock::~BasicBlock()
{
  //dtor
}

shared_ptr<Block> BasicBlock::clone() const {
  return make_shared<BasicBlock>(*this);
}

void BasicBlock::draw(DrawingContextInfo& dci) const {
  const std::shared_ptr<DrawingTool<Block>>& dt = getDrawingTool();
  if (dt != nullptr) {
    dt->draw(*this, dci);
  }
}

} // namespace tetris.
