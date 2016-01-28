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

#ifndef DEFAULTGAME_H
#define DEFAULTGAME_H

#include <memory>
#include <vector>

#include "Game.h"
#include "GameBoard.h"
#include "Shape.h"

namespace tetris {

class DefaultGame : public Game
{
  public:
    DefaultGame(std::shared_ptr<GameBoard> gameBoard,
                std::vector<std::shared_ptr<Shape>> shapes);
    virtual ~DefaultGame();

    virtual bool isGameOver() const override;
    virtual void newGame() override;
    virtual int advance() override;
    virtual int drop() override;
    virtual void rotateLeft() override;
    virtual void rotateRight() override;
    virtual void moveLeft() override;
    virtual void moveRight() override;
  protected:
  private:
    void newShape();

    std::shared_ptr<GameBoard> m_game_board;
    std::vector<std::shared_ptr<Shape>> m_shapes;
    bool m_game_over;
};

} // namespace tetris.

#endif // DEFAULTGAME_H
