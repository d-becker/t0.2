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


#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <memory>
#include <vector>

#include "Coords.h"
#include "Drawing.h"

namespace tetris {

class Board;
class Shape;

class GameBoard : public Drawable<GameBoard>
{
  public:
    GameBoard() : Drawable<GameBoard>() {}
    GameBoard(const GameBoard& other) : Drawable<GameBoard>(other) {}
    GameBoard(GameBoard&& other) : Drawable<GameBoard>(other) {}
    virtual ~GameBoard() {}

    /**
     * Returns a (smart) pointer to the board.
     *
     * \return A (smart) pointer to the board.
     */
    virtual std::shared_ptr<const Board> getBoard() const = 0;

    /**
     * Returns a (smart) pointer to the current shape.
     *
     * \return A (smart) pointer to the current shape.
     */
    virtual std::shared_ptr<const Shape> getCurrentShape() const = 0;

    /**
     * Sets the current shape.
     *
     * \param shape The new current shape.
     */
    virtual void setCurrentShape(std::shared_ptr<Shape> shape) = 0;

    /**
     * Returns the current shape's position.
     *
     * \return The current shape's position.
     */
    virtual Coords getCurrentShapePosition() const = 0;

    /**
     * Sets the current shape's position.
     *
     * \param position The current shape's new position.
     */
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
     * Checks for the position where the current shape would land if it did not
     * move sideways.
     *
     * \return The position where the current shape would land if it did not
     *         move sideways.
     */
    virtual Coords whereWouldLand() const = 0;

    /**
     * Locks the shape on the board, that is, the blocks of the shape are
     * assigned to the positions on the board where they currently are.
     * The current shape is set to \c nullptr.
     */
    virtual void lock() = 0;

    /**
     * Removes the rows that are completely filled from the board and adds
     * empty rows at the top of the board.
     *
     * \return The number of rows that have been removed.
     */
    virtual int removeFilledRows() = 0;

    /**
     * Rotates the current shape left if the resulting state of the shape is
     * valid. If it is not (at least one block of the current shape is outside
     * the board or occupies a non-empty cell), no change is made.
     */
    virtual void rotateLeft() = 0;

    /**
     * Rotates the current shape right if the resulting state of the shape is
     * valid. If it is not (at least one block of the current shape is outside
     * the board or occupies a non-empty cell), no change is made.
     */
    virtual void rotateRight() = 0;

    /**
     * Moves the current shape one block up if the resulting state of the shape
     * is valid. If it is not (at least one block of the current shape is
     * outside the board or occupies a non-empty cell), no change is made.
     */
    virtual void moveUp() = 0;

    /**
     * Moves the current shape one block down if the resulting state of the
     * shape is valid. If it is not (at least one block of the current shape is
     * outside the board or occupies a non-empty cell), no change is made.
     */
    virtual void moveDown() = 0;

    /**
     * Moves the current shape one block left if the resulting state of the
     * shape is valid. If it is not (at least one block of the current shape is
     * outside the board or occupies a non-empty cell), no change is made.
     */
    virtual void moveLeft() = 0;

    /**
     * Moves the current shape one block right if the resulting state of the
     * shape is valid. If it is not (at least one block of the current shape is
     * outside the board or occupies a non-empty cell), no change is made.
     */
    virtual void moveRight() = 0;

    /**
     * Clears the board and sets the current shape to \c nullptr. The current
     * shape's position is not reset.
     */
    virtual void clear() = 0;
};

} // namespace tetris.

#endif // GAMEBOARD_H
