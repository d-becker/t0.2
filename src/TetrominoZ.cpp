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

#include "TetrominoZ.h"

#include "Block.h"

namespace tetris {

TetrominoZ::TetrominoZ(std::vector<std::shared_ptr<Block>> blocks)
  : BasicShape(3,
               {Coords(0, 0), Coords(0, 1), Coords(1, 1), Coords(1, 2)},
               blocks)
{
  //ctor
}

TetrominoZ::TetrominoZ(std::shared_ptr<Block> block)
  : TetrominoZ(
      block != nullptr ?
      std::vector<std::shared_ptr<Block>>{block->clone(), block->clone(),
                                          block->clone(), block->clone()}
          : std::vector<std::shared_ptr<Block>>{})
{

}

TetrominoZ::~TetrominoZ()
{
  //dtor
}

TetrominoZ::TetrominoZ(const TetrominoZ& other) : BasicShape(other)
{
  //copy ctor
}

TetrominoZ::TetrominoZ(TetrominoZ&& other) : BasicShape(other)
{

}

std::shared_ptr<Shape> TetrominoZ::clone() const {
  return std::make_shared<TetrominoZ>(*this);
}

} // namespace tetris.
