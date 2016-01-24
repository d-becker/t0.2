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

#ifndef TESTHELPERS_H_INCLUDED
#define TESTHELPERS_H_INCLUDED

#include <algorithm>
#include <vector>

// Helper functions.

// Checks whether a vector contains an element.
template <typename T>
bool contains(const std::vector<T>& vec, const T& elem) {
  return std::find(vec.begin(), vec.end(), elem) != vec.end();
}

// Checks if two vectors contain the same elements.
template <typename T>
bool same_elements(const std::vector<T>& vec1, const std::vector<T>& vec2) {
  if (vec1.size() != vec2.size()) {return false;}
  for (const T& elem : vec1) {
    if (!contains(vec2, elem)) {return false;}
  }
  return true;
}

#endif // TESTHELPERS_H_INCLUDED
