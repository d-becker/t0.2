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

#ifndef BASICBOARD_H
#define BASICBOARD_H

#include <vector>

#include "Board.h"

namespace tetris {

class BasicBoard : public Board
{
  public:
    BasicBoard(int height, int width);
    BasicBoard(const BasicBoard& other) = delete;
    virtual ~BasicBoard();

    virtual int getHeight() const override;
    virtual int getWidth() const override;

    virtual std::shared_ptr<Block> get(int vertical, int horizontal) override;
    virtual std::shared_ptr<const Block> get(int vertical, int horizontal) const;

    virtual void set(int vertical, int horizontal,
                     std::shared_ptr<Block> block) override;

    virtual void removeRow(int row) override;
    virtual void clear() override;

    virtual void draw(DrawingContextInfo& dci) const override;
  private:
    // This method is declared const so it can be used by the const version of
    // get, but returns a mutable smart pointer so that it can be returned
    // again from the non-const version of get.
    std::shared_ptr<Block> m_const_neutral_get(int vertical, int horizontal)
                                                                          const;
  private:
    int m_height;
    int m_width;

    // The first coordinate is the vertical one, but number 0 is the at the
    // bottom - in this way, adding new rows to the doesn't need to move all
    // the other rows. Because of this, the accessor methods have to "reverse"
    // the table.
    std::vector<std::vector<std::shared_ptr<Block>>> m_table;
};

} // namespace tetris.

#endif // BASICBOARD_H
