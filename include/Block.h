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


#ifndef BLOCK_H
#define BLOCK_H

#include <memory>

#include "Drawable.h"

namespace tetris {

/**
 * A common interface for blocks that constitute <tt>Shape</tt>s.
 */

class Block : public Drawable
{
  public:
    virtual ~Block() {}

    /**
     * Returns a polymorphic copy of this \c Block.
     *
     * \return A polymorphic copy of this \c Block.
     */
    virtual std::shared_ptr<Block> clone() const = 0;
};

} // namespace tetris.

#endif // BLOCK_H
