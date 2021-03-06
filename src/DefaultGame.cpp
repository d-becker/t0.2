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

#include "DefaultGame.h"

#include <cstdlib>
#include <ctime>
#include <stdexcept>

#include "Board.h"

namespace tetris {

DefaultGame::DefaultGame(std::shared_ptr<GameBoard> gameBoard,
                         std::vector<std::shared_ptr<Shape>> shapes)
  : Game(),
    m_game_board(gameBoard),
    m_shapes(shapes),
    m_next_shape(nullptr),
    m_game_over(false)
{
  if (m_game_board == nullptr) {
    throw std::invalid_argument("A null game board is not allowed.");
  }

  if (m_shapes.empty()) {
    throw std::invalid_argument("At least one shape must be specified.");
  }

  for (std::shared_ptr<Shape>& ptr : m_shapes) {
    if (ptr == nullptr) {
      throw std::invalid_argument("A null shape is not allowed.");
    }
  }

  // Setting the random seed.
  srand(time(nullptr));
}

DefaultGame::~DefaultGame()
{
  //dtor
}

std::shared_ptr<const GameBoard> DefaultGame::getGameBoard() const {
  return m_game_board;
}

bool DefaultGame::isGameOver() const {
  return m_game_over;
}

void DefaultGame::newGame() {
  m_game_board->clear();
  m_game_over = false;

  setNewShape();
}

int DefaultGame::advance() {
  if (m_game_over) {
    return 0;
  }

  int res = 0;
  if (m_game_board->hasLanded()) {
    m_game_board->lock();
    res = m_game_board->removeFilledRows();

    // Checking for game over.
    if (top_row_not_empty()) {
      m_game_over = true;
      return 0;
    }

    // Choosing a new shape.
    setNewShape();
  } else {
    m_game_board->moveDown();
  }
  return res;
}

int DefaultGame::drop() {
  while(!(m_game_board->hasLanded())) {
    advance();
  }
  return advance();
}

void DefaultGame::rotateLeft() {
  m_game_board->rotateLeft();
}

void DefaultGame::rotateRight() {
  m_game_board->rotateRight();
}

void DefaultGame::moveLeft() {
  m_game_board->moveLeft();
}

void DefaultGame::moveRight() {
  m_game_board->moveRight();
}

void DefaultGame::draw(DrawingContextInfo& dci) const {
  const std::shared_ptr<DrawingTool<Game>>& dt = getDrawingTool();
  if (dt != nullptr) {
    dt->draw(*this, dci);
  }
}

void DefaultGame::setNewShape() {
  unsigned int index = rand() % m_shapes.size();
  m_game_board->setCurrentShape(m_shapes.at(index)->clone());

  if (m_next_shape == nullptr) {
    m_next_shape = chooseNewShape();
    m_game_board->setCurrentShape(chooseNewShape());
  } else {
    m_game_board->setCurrentShape(m_next_shape);
    m_next_shape = chooseNewShape();
  }

  int vertical_coord = - std::min(m_game_board->getHiddenRows(),
                                  get_lowest_block_of_current_shape());

  // It would be better in the middle.
  m_game_board->setCurrentShapePosition(Coords(vertical_coord, 0));
}

std::shared_ptr<Shape> DefaultGame::chooseNewShape() const {
  unsigned int index = rand() % m_shapes.size();
  std::shared_ptr<Shape> res = m_shapes.at(index)->clone();

  // Random rotations.
  int  rotate_times = rand() % 4;
  for (int i = 0; i < rotate_times; ++i) { res->rotateRight(); }

  return res;
}

bool DefaultGame::top_row_not_empty() {
  std::shared_ptr<const Board> board = m_game_board->getBoard();
  int width = board->getWidth();
  for (int i = 0; i < width; ++i) {
    if (board->get(0, i) != nullptr) {
      return true;
    }
  }

  return false;
}

int DefaultGame::get_lowest_block_of_current_shape() const {
  std::shared_ptr<const Shape> current_shape = m_game_board->getCurrentShape();
  int res = -1;
  if (current_shape != nullptr) {
    std::vector<Coords> coords = current_shape->getBlockPositions();
    for (const Coords& coord : coords) {
      int vertical = coord.getVertical();
      if (coord.getVertical() > res) {
        res = vertical;
      }
    }
  }

  return res;
}

} // namespace tetris.
