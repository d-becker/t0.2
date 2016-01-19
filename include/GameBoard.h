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


#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <memory>
#include <vector>

#include "Coords.h"

class Board;
class Shape;

class GameBoard
{
  public:
    virtual ~GameBoard() {}

    virtual std::shared_ptr<const Board> getBoard() = 0;

    virtual std::shared_ptr<const Shape> getCurrentShape() const = 0;
    virtual void setCurrentShape(std::shared_ptr<Shape> shape) = 0;


    virtual Coords getCurrentShapePosition() const = 0;
    virtual void setCurrentShapePosition(Coords position) = 0;

    /**
     * Returns the absolute positions (in the coordinate system of the \c Board)
     * of the blocks of the current shape.
     *
     * \return The absolute positions (in the coordinate system of the \c Board)
     *         of the blocks of the current shape.
     */
    virtual std::vector<Coords> getAbsolutePositions() const = 0;

    /**
     * Checks whether the current \c Shape is at a valid position, that is, all
     * of the blocks of the \c Shape are  inside the board and at positions
     * that are not already filled with a block.
     *
     * \return \c true if the current \c Shape is at a valid position;
     *         \c false otherwise.
     */
    virtual bool isAtValidPos() const = 0;

    /**
     * Checks whether the current \c Shape has "landed", that is, there is a
     * block on the board or the bottom of the board under at least one of the
     * current <tt>Shape</tt>'s blocks.
     *
     * \return \c true if the current \c Shape has landed;
     *         \c false otherwise.
     */
    virtual bool hasLanded() const = 0;

    /**
     * Locks the shape on the board, that is, the blocks of the shape are
     * assigned to the positions on the board where they currently are.
     * The current shape is set to \c nullptr.
     */
    virtual void lock() = 0;

    /**
     * Removes the rows that are completely filled from the board and adds
     * empty rows at the top of the board.
     */
    virtual void removeFilledRows() = 0;

    virtual void rotateLeft() = 0;
    virtual void rotateRight() = 0;

    virtual void moveUp() = 0;
    virtual void moveDown() = 0;
    virtual void moveLeft() = 0;
    virtual void moveRight() = 0;
};

#endif // GAMEBOARD_H
