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


#ifndef SHAPE_H
#define SHAPE_H

#include <memory>
#include <vector>

#include "Coords.h"
#include "Drawing.h"

namespace tetris {

class Block;

class Shape : public Drawable
{
  public:
    virtual ~Shape() {}

    /**
     * Returns the size of the side of the bounding box of the \c Shape.
     *
     * \return The size of the side of the bounding box of the \c Shape.
     */
    virtual int getBBoxSize() const = 0;

    /**
     * Checks whether the given position is valid, i.e. it is inside the
     * bounding box of the shape.
     *
     * \param vertical The vertical coordinate of the position.
     * \param horizontal The horizontal coordinate of the position.
     *
     * \return \c true if the given position is valid; \c false otherwise.
     */
    virtual bool isValid(int vertical, int horizontal) const = 0;

    /**
     * The same as calling
     * isValid(coords.getVertical(), coords.getHorizontal()).
     */
    virtual bool isValid(const Coords& coords) const {
      return isValid(coords.getVertical(), coords.getHorizontal());
    }

    /**
     * Returns a pointer to the \c Block object that is at the given position.
     *
     * \param vertical The vertical position of the \c Block object.
     * \param horizontal The horizontal position of the \c Block object.
     *
     * \return A pointer to the \c Block object that is at the given position.
     */
    virtual std::shared_ptr<Block> get(int vertical, int horizontal) const = 0;

    /**
     * The same as calling get(coords.getVertical(), coords.getHorizontal()).
     */
    virtual std::shared_ptr<Block> get(const Coords& coords) const {
      return get(coords.getVertical(), coords.getHorizontal());
    }

    /**
     * Returns a container of pointers to the blocks contained by this \c Shape.
     * There are no guarantees as to the order of the blocks.
     *
     * \return A container of pointers to the blocks contained by this \c Shape.
     */
    virtual std::vector<std::shared_ptr<Block>> getBlocks() = 0;

    /**
     * Returns a container of the relative positions that the blocks in this
     * \c Shape occupy.
     * There are no guarantees as to the order of the positions.
     *
     * \return A container of the relative positions that the blocks in this
     *         \c Shape occupy.
     */
    virtual std::vector<Coords> getBlockPositions() const = 0;

    /**
     * Rotates the \c Shape to the right with 90 degrees.
     */
    virtual void rotateRight() = 0;

    /**
     * Rotates the \c Shape to the left with 90 degrees.
     */
    virtual void rotateLeft() = 0;

    /**
     * Returns a polymorphic copy of this \c Shape.
     *
     * \return A polymorphic copy of this \c Shape.
     */
    virtual std::shared_ptr<Shape> clone() const = 0;
};

} // namespace tetris.

#endif // SHAPE_H
