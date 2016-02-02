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

#include "Drawing.h"

#include <iostream> ///////////////////////////////////////////////////////////////////////

namespace tetris {

Drawable::Drawable()
  : m_dt(nullptr)
{

}

Drawable::~Drawable() {
  // Destructor.
}

Drawable::Drawable(const Drawable& other)
{
  if (other.m_dt != nullptr) {
    m_dt = other.m_dt->copy(*this);
    std::cerr << "Copy constructor of Drawable.\n";
  }
}

Drawable::Drawable(Drawable&& other)
{
  if (other.m_dt != nullptr) {
    m_dt = other.m_dt->copy(*this);
    std::cerr << "Move constructor of Drawable.\n";
  }
}


std::shared_ptr<DrawingTool> Drawable::getDrawingTool() {
  return m_dt;
}

void Drawable::setDrawingTool(std::shared_ptr<DrawingTool> dt) {
  m_dt = dt;
}

void Drawable::draw(DrawingContextInfo& dci) const {
  if (m_dt != nullptr) {
    m_dt->draw(dci);
  }
}

} // namespace tetris.
