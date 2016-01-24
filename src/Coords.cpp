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


#include "Coords.h"

using namespace std;

namespace tetris {

Coords::Coords(int vertical, int horizontal)
  : m_vertical(vertical), m_horizontal(horizontal)
{
  //ctor
}

Coords::~Coords()
{
  //dtor
}

Coords::Coords(const Coords& other)
  : m_vertical(other.m_vertical), m_horizontal(other.m_horizontal)
{
  //copy ctor
}

Coords::Coords(Coords&& other)
  : m_vertical(other.m_vertical), m_horizontal(other.m_horizontal)
{
  // Move constructor.
}

Coords& Coords::operator=(const Coords& rhs)
{
  this->m_vertical = rhs.m_vertical;
  this->m_horizontal = rhs.m_horizontal;
  return *this;
}

Coords& Coords::operator+=(const Coords& other) {
  this->m_vertical += other.m_vertical;
  this->m_horizontal += other.m_horizontal;
  return *this;
}

Coords& Coords::operator-=(const Coords& other) {
  this->m_vertical -= other.m_vertical;
  this->m_horizontal -= other.m_horizontal;
  return *this;
}

int Coords::getVertical() const {
  return m_vertical;
}

void Coords::setVertical(int vertical) {
  m_vertical = vertical;
}

int Coords::getHorizontal() const {
  return m_horizontal;
}

void Coords::setHorizontal(int horizontal) {
  m_horizontal = horizontal;
}

bool operator==(const Coords& lhs, const Coords& rhs) {
  return lhs.getVertical() == rhs.getVertical()
      && lhs.getHorizontal() == rhs.getHorizontal();
}

Coords operator+(Coords lhs, const Coords& rhs) {
  return lhs+=rhs;
}

Coords operator-(Coords lhs, const Coords& rhs) {
  return lhs-=rhs;
}

ostream& operator<<(ostream& os, const Coords& coords) {
  os << "Coords(" << coords.getVertical() << ", "
     << coords.getHorizontal() << ")";
  return os;
}

} // namespace tetris.
