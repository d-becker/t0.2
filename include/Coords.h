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


#ifndef COORDS_H
#define COORDS_H


class Coords
{
  public:
    Coords(int vertical = 0, int horizontal = 0);
    virtual ~Coords();
    Coords(const Coords& other);
    Coords(Coords&& other);

    Coords& operator=(const Coords& other);

    Coords& operator+=(const Coords& other);

    Coords& operator-=(const Coords& other);

    int getVertical() const;
    void setVertical(int vertical);

    int getHorizontal() const;
    void setHorizontal(int horizontal);
  protected:
  private:
    int m_vertical;
    int m_horizontal;
};

bool operator==(const Coords& lhs, const Coords& rhs);
Coords operator+(Coords lhs, const Coords& rhs);
Coords operator-(Coords lhs, const Coords& rhs);

#endif // COORDS_H
