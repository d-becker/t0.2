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


#ifndef BASICSHAPE_H
#define BASICSHAPE_H

#include "Shape.h"

namespace tetris {

class BasicShape : public Shape
{
public:
  BasicShape(int bbox_size, std::vector<Coords> coords,
             std::vector<std::shared_ptr<Block>> blocks);
  BasicShape(const BasicShape& other);
  BasicShape(BasicShape&& other);
  virtual ~BasicShape();


  virtual int getBBoxSize() const override;
  virtual bool isValid(int vertical, int horizontal) const override;

  virtual std::shared_ptr<Block> get(int vertical, int horizontal) const override;
  virtual std::vector<std::shared_ptr<Block>> getBlocks()  override;
  virtual std::vector<Coords> getBlockPositions() const override;


  virtual void rotateRight() override;
  virtual void rotateLeft() override;

  virtual std::shared_ptr<Shape> clone() const override;
protected:
private:
  class PIMPL;
  PIMPL* m_pimpl;

};

} // namespace tetris.

#endif // BASICSHAPE_H
