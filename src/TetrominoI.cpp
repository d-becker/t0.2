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

#include "TetrominoI.h"

#include "Block.h"

namespace tetris {

TetrominoI::TetrominoI(std::vector<std::shared_ptr<Block>> blocks)
  : BasicShape(4,
               {Coords(0, 1), Coords(1, 1), Coords(2, 1), Coords(3, 1)},
               blocks)
{
  //ctor
}

TetrominoI::TetrominoI(std::shared_ptr<Block> block)
  : TetrominoI(
      block != nullptr ?
      std::vector<std::shared_ptr<Block>>{block->clone(), block->clone(),
                                          block->clone(), block->clone()}
          : std::vector<std::shared_ptr<Block>>{})
{

}

TetrominoI::~TetrominoI()
{
  //dtor
}

TetrominoI::TetrominoI(const TetrominoI& other) : BasicShape(other)
{
  //copy ctor
}

TetrominoI::TetrominoI(TetrominoI&& other) : BasicShape(other)
{

}

std::shared_ptr<Shape> TetrominoI::clone() const {
  return std::make_shared<TetrominoI>(*this);
}

} // namespace tetris.
