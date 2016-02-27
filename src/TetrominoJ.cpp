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

#include "TetrominoJ.h"

#include "Block.h"

namespace tetris {

TetrominoJ::TetrominoJ(std::vector<std::shared_ptr<Block>> blocks)
  : BasicShape(3,
               {Coords(0, 1), Coords(1, 1), Coords(2, 1), Coords(2, 0)},
               blocks)
{
  //ctor
}

TetrominoJ::TetrominoJ(std::shared_ptr<Block> block)
  : TetrominoJ(
      block != nullptr ?
      std::vector<std::shared_ptr<Block>>{block->clone(), block->clone(),
                                          block->clone(), block->clone()}
          : std::vector<std::shared_ptr<Block>>{})
{

}

TetrominoJ::~TetrominoJ()
{
  //dtor
}

TetrominoJ::TetrominoJ(const TetrominoJ& other) : BasicShape(other)
{
  //copy ctor
}

TetrominoJ::TetrominoJ(TetrominoJ&& other) : BasicShape(other)
{

}

std::shared_ptr<Shape> TetrominoJ::clone() const {
  return std::make_shared<TetrominoJ>(*this);
}

} // namespace tetris.
