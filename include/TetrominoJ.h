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

#ifndef TETROMINOJ_H
#define TETROMINOJ_H

#include "BasicShape.h"

namespace tetris {

class TetrominoJ : public BasicShape
{
  public:
    /**
     * Constructs a new J tetromino with the given blocks. The order is given
     * from the top line down, from left to right.
     *
     * \param blocks The blocks of the new tetromino.
     */
    TetrominoJ(std::vector<std::shared_ptr<Block>> blocks);

    /**
     * Constructs a new J tetromino. All blocks will be clones of
     * the specified \c Block.
     *
     * \param block The block whose clones will be the blocks
     *        of the new tetromino.
     */
    TetrominoJ(std::shared_ptr<Block> block);

    virtual ~TetrominoJ();
    TetrominoJ(const TetrominoJ& other);
    TetrominoJ(TetrominoJ&& other);

    virtual std::shared_ptr<Shape> clone() const override;
  protected:
  private:
};

} // namespace tetris.

#endif // TETROMINOJ_H
