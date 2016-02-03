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

#include "BasicBoard.h"

using namespace std;

namespace tetris {

BasicBoard::BasicBoard(int height, int width)
  : Board(),
    m_height(height), m_width(width),
    m_table(height, vector<shared_ptr<Block>>(width, nullptr)) {
  if (m_height < 1) {
    throw invalid_argument("Zero or negative height is not allowed.");
  }
  if (m_width < 1) {
    throw invalid_argument("Zero or negative width is not allowed.");
  }
}

BasicBoard::~BasicBoard() {
//dtor
}

int BasicBoard::getHeight() const {
  return m_height;
}

int BasicBoard::getWidth() const {
  return m_width;
}

shared_ptr<Block> BasicBoard::get(int vertical, int horizontal) {
  return m_const_neutral_get(vertical, horizontal);
}

shared_ptr<const Block> BasicBoard::get(int vertical, int horizontal) const {
  return m_const_neutral_get(vertical, horizontal);
}

void BasicBoard::set(int vertical, int horizontal, shared_ptr<Block> block) {
  if (!isValid(vertical, horizontal)) { return; }

  int vertical_index = getHeight() - vertical - 1;
  int horizontal_index = horizontal;
  m_table.at(vertical_index).at(horizontal_index) = block;
}

void BasicBoard::removeRow(int row) {
  if (row < 0 || row >= getHeight()) {
    return;
  }

  int index = getHeight() - row - 1;
  m_table.erase(m_table.begin() + index);

  m_table.emplace_back(getWidth(), nullptr);
}

void BasicBoard::clear() {
  for (std::vector<std::shared_ptr<Block>>& row : m_table) {
    for (std::shared_ptr<Block>& block : row) {
      block = nullptr;
    }
  }
}

void BasicBoard::draw(DrawingContextInfo& dci) const {
  const std::shared_ptr<DrawingTool<Board>>& dt = getDrawingTool();
  if (dt != nullptr) {
    dt->draw(*this, dci);
  }
}

// Helpers.
shared_ptr<Block> BasicBoard::m_const_neutral_get(int vertical, int horizontal)
const {
  if (!isValid(vertical, horizontal)) {
    return nullptr;
  }

  int vertical_index = getHeight() - vertical - 1;
  int horizontal_index = horizontal;
  return m_table.at(vertical_index).at(horizontal_index);
}

} // namespace tetris.
