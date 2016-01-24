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


#ifndef BASICBLOCK_H
#define BASICBLOCK_H

#include "Block.h"

namespace tetris {

/**
 * Basic (essentially empty) class implementing the \c Block interface.
 */
class BasicBlock : public Block
{
  public:
    BasicBlock() = default;
    virtual ~BasicBlock();
    BasicBlock(const BasicBlock& other) = default;

    virtual std::shared_ptr<Block> clone() const override;
  protected:
  private:
};

} // namespace tetris.

#endif // BASICBLOCK_H
