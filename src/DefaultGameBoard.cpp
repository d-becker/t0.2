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

#include "DefaultGameBoard.h"

#include <stdexcept>

#include "Board.h"
#include "Shape.h"

using namespace std;

namespace tetris {

DefaultGameBoard::DefaultGameBoard(shared_ptr<Board> board, int hidden_rows)
  : GameBoard(),
    m_board(board),
    m_hidden_rows(hidden_rows)
{
  if (board == nullptr) {
    throw invalid_argument("A null board is not allowed.");
  }
}

DefaultGameBoard::~DefaultGameBoard()
{

}

shared_ptr<const Board> DefaultGameBoard::getBoard() const {
  return m_board;
}

shared_ptr<const Shape> DefaultGameBoard::getCurrentShape() const {
  return m_current_shape;
}

void DefaultGameBoard::setCurrentShape(std::shared_ptr<Shape> shape) {
  m_current_shape = shape;
}

int DefaultGameBoard::getHiddenRows() const {
  return m_hidden_rows;
}

Coords DefaultGameBoard::getCurrentShapePosition() const {
  return m_current_shape_pos;
}

void DefaultGameBoard::setCurrentShapePosition(Coords position) {
  m_current_shape_pos = position;
}

vector<Coords> DefaultGameBoard::getAbsolutePositions() const {
  return getAbsolutePositions(m_current_shape, m_current_shape_pos);
}

bool DefaultGameBoard::isAtValidPos() const {
  return isAtValidPos(m_current_shape, m_current_shape_pos);
}

bool DefaultGameBoard::hasLanded() const {
  return hasLanded(m_current_shape, m_current_shape_pos);
}

Coords DefaultGameBoard::whereWouldLand() const {
  Coords res = m_current_shape_pos;
  for (; !hasLanded(m_current_shape, res); res += Coords(1, 0))
  {}
  return res;
}

void DefaultGameBoard::lock() {
  if (m_current_shape == nullptr) { return; }

  for (const Coords& c : m_current_shape->getBlockPositions()) {
    shared_ptr<Block> block = m_current_shape->get(c);
    m_board->set(c + m_current_shape_pos, block);
  }
  m_current_shape = nullptr;
}

int DefaultGameBoard::removeFilledRows() {
  int res = 0;
  for (int i = 0; i < m_board->getHeight(); ++i) {
    bool contains_empty = false;
    for (int j = 0; j < m_board->getWidth(); ++j) {
      if (m_board->get(i, j) == nullptr) {
        contains_empty = true;
        break;
      }
    }
    if (!contains_empty) {
      m_board->removeRow(i);
      res++;
    }
  }
  return res;
}

void DefaultGameBoard::rotateLeft() {
  if (m_current_shape == nullptr) { return; }

  shared_ptr<Shape> orig_current_shape = m_current_shape->clone();
  m_current_shape->rotateLeft();
  if (!isAtValidPos()) {
    m_current_shape = orig_current_shape;
  }
}

void DefaultGameBoard::rotateRight() {
  if (m_current_shape == nullptr) { return; }

  shared_ptr<Shape> orig_current_shape = m_current_shape->clone();
  m_current_shape->rotateRight();
  if (!isAtValidPos()) {
    m_current_shape = orig_current_shape;
  }
}

void DefaultGameBoard::moveUp() {
  move(Coords(-1, 0));
}

void DefaultGameBoard::moveDown() {
  move(Coords(1, 0));
}

void DefaultGameBoard::moveLeft() {
  move(Coords(0, -1));
}

void DefaultGameBoard::moveRight() {
  move(Coords(0, 1));
}

void DefaultGameBoard::clear() {
  m_board->clear();
  m_current_shape = nullptr;
}

void DefaultGameBoard::draw(DrawingContextInfo& dci) const {
  const std::shared_ptr<DrawingTool<GameBoard>>& dt = getDrawingTool();
  if (dt != nullptr) {
    dt->draw(*this, dci);
  }
}


// Private methods.

vector<Coords> DefaultGameBoard::getAbsolutePositions(
                                             shared_ptr<const Shape> shape,
                                             const Coords& coords) const {
  vector<Coords> res;
  if (shape != nullptr) {
    for (const Coords& c : shape->getBlockPositions()) {
      res.emplace_back(coords + c);
    }
  }
  return res;
 }

bool DefaultGameBoard::isAtValidPos(shared_ptr<Shape> shape,
                                    const Coords& coords) const {
  vector<Coords> abs_pos = getAbsolutePositions(shape, coords);
  for (const Coords& c : abs_pos) {
    // The current shape is not within the board.
    if (!m_board->isValid(c)
        // The current shape is not in the hidden rows either.
        && !m_board->isValid(c + Coords(getHiddenRows(), 0))) {
          return false;
    }
    if (m_board->get(c) != nullptr) { return false; }
  }
  return true;
}

bool DefaultGameBoard::hasLanded(shared_ptr<Shape> shape,
                                 const Coords& coords) const {
  vector<Coords> abs_pos = getAbsolutePositions(shape, coords);
  for (const Coords& c : abs_pos) {
    int vertical_under = c.getVertical() + 1;
    int horizontal = c.getHorizontal();
    if (vertical_under >= m_board->getHeight()
     || m_board->get(vertical_under, horizontal) != nullptr) {
      return true;
    }
  }
  return false;
}

void DefaultGameBoard::move(const Coords& offset) {
  Coords orig_pos = m_current_shape_pos;
  m_current_shape_pos += offset;
  if (!isAtValidPos()) {
    m_current_shape_pos = orig_pos;
  }
}

} // namespace tetris.
