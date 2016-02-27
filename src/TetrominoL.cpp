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

#include "TetrominoL.h"

#include "Block.h"

namespace tetris {

TetrominoL::TetrominoL(std::vector<std::shared_ptr<Block>> blocks)
  : BasicShape(3,
               {Coords(0, 1), Coords(1, 1), Coords(2, 1), Coords(2, 2)},
               blocks)
{
  //ctor
}

TetrominoL::TetrominoL(std::shared_ptr<Block> block)
  : TetrominoL(
      block != nullptr ?
      std::vector<std::shared_ptr<Block>>{block->clone(), block->clone(),
                                          block->clone(), block->clone()}
          : std::vector<std::shared_ptr<Block>>{})
{

}

TetrominoL::~TetrominoL()
{
  //dtor
}

TetrominoL::TetrominoL(const TetrominoL& other) : BasicShape(other)
{
  //copy ctor
}

TetrominoL::TetrominoL(TetrominoL&& other) : BasicShape(other)
{

}

std::shared_ptr<Shape> TetrominoL::clone() const {
  return std::make_shared<TetrominoL>(*this);
}

} // namespace tetris.
