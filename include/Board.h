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


#ifndef BOARD_H
#define BOARD_H

#include <memory>

#include "Coords.h"

class Block;

/**
 * A low-level abstraction interface that provides means to manipulate the
 * tetris board. The coordinate system of the board has (0, 0) at the top left
 * corner, the first coordinate is for the vertical, the second coordinate is
 * for the horizontal direction.
 */
class Board
{
  public:
    virtual ~Board() {}

    /**
     * Returns the height of this \c Board.
     *
     * \return The height of this \c Board.
     */
    virtual int getHeight() const = 0;

    /**
     * Returns the width of this \c Board.
     *
     * \return The width of this \c Board.
     */
    virtual int getWidth() const = 0;

    /**
     * Returns a pointer to the \c Block at the given position.
     *
     * \param vertical The vertical position of the block to query.
     * \param horizontal The horizontal position of the block to query.
     *
     * \return A pointer to the \c Block at the given position.
     */
    virtual std::shared_ptr<Block> get(int vertical, int horizontal) = 0;

    /**
     * The same as calling get(coords.getVertical(), coords.getHorizontal()).
     */
    virtual std::shared_ptr<Block> get(const Coords& coords) {
      return get(coords.getVertical(), coords.getHorizontal());
    }

    /**
     * Const version of \c get.
     */
    virtual std::shared_ptr<const Block> get(int vertical, int horizontal) const
                                                                            = 0;

    /**
     * The same as calling the const version of
     * get(coords.getVertical(), coords.getHorizontal()).
     */
    virtual std::shared_ptr<const Block> get(const Coords& coords) const {
      return get(coords.getVertical(), coords.getHorizontal());
    }

    /**
     * Sets the \c Block pointer at the given position to point to the object
     * pointed to by \a block.
     *
     * \param vertical The vertical position of the block to set.
     * \param horizontal The horizontal position of the block to set.
     * \param A pointer to the \c Block that will be the new value of the \c
     *        Block pointer at the given position.
     */
    virtual void set(int vertical, int horizontal,
                     std::shared_ptr<Block> block) = 0;

    /**
     * The same as calling
     * set(coords.getVertical(), coords.getHorizontal(), block).
     */
    virtual void set(const Coords& coords, std::shared_ptr<Block> block) {
      set(coords.getVertical(), coords.getHorizontal(), block);
    }

    /**
     * Checks whether the given position is valid on this \c Board.
     *
     * \param vertical The vertical coordinate of the position to check.
     * \param horizontal The horizontal coordinate of the position to check.
     * \return \c true if the given position is valid on this \c Board;
     *         \c false otherwise.
     */
    virtual bool isValid(int vertical, int horizontal) const {
      return vertical >= 0 && horizontal >= 0
          && vertical < getHeight() && horizontal < getWidth();
    }

    /**
     * The same as calling
     * isValid(coords.getVertical(), coords.getHorizontal()).
     */
    virtual bool isValid(const Coords& coords) const {
      return isValid(coords.getVertical(), coords.getHorizontal());
    }

    /**
     * Removes the row with vertical coordinate \a row and adds a new empty row
     * to the top of the board.
     *
     * \param row The vertical coordinate of the row to be removed.
     */
    virtual void removeRow(int row) = 0;
};

#endif // BOARD_H
