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

namespace tetris {

DefaultGame::DefaultGame(std::shared_ptr<GameBoard> gameBoard,
                         std::vector<std::shared_ptr<Shape>> shapes)
  : m_game_board(gameBoard), m_shapes(shapes), m_game_over(false)
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

bool DefaultGame::isGameOver() const {
  return m_game_over;
}

void DefaultGame::newGame() {
  m_game_board->clear();
  m_game_over = false;

  newShape();
}

int DefaultGame::advance() {
  int res = 0;
  if (m_game_board->hasLanded()) {
    m_game_board->lock();
    res = m_game_board->removeFilledRows();

    // Choosing a new shape.
    newShape();

    // Checking for game over.
    if (!m_game_board->isAtValidPos()) {
      m_game_over = true;
    }

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

void DefaultGame::newShape() {
  m_game_board->setCurrentShapePosition(Coords(0, 0)); // It would be better in the middle.

  unsigned int index = rand() % m_shapes.size();
  m_game_board->setCurrentShape(m_shapes.at(index)->clone());

  // Random rotations.
  int  rotate_times = rand() % 4;
  for (int i = 0; i < rotate_times; ++i) { m_game_board->rotateRight(); }

}

} // namespace tetris.
