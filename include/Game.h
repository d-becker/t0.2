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

#ifndef GAME_H
#define GAME_H

#include "Drawing.h"
#include "GameBoard.h"

namespace tetris {

/**
 * An interface for the class that provides the high-level functionality for
 * updating the game. The GUI event handlers should normally call the methods
 * of this class through commands registered with the \c GameFlow interface.
 */
class Game : public Drawable<Game>
{
  public:
    Game() : Drawable<Game>() {}
    Game(const Game& other) : Drawable<Game>(other) {}
    Game(Game&& other) : Drawable<Game>(other) {}
    virtual ~Game() {}

    /**
     * Returns the game board that is associated with this game.
     *
     * \return The game board that is associated with this game.
     */
    virtual std::shared_ptr<const GameBoard> getGameBoard() const = 0;

    /**
     * Checks whether the game is over.
     *
     * \return \c true if the game is over; \c false otherwise.
     */
    virtual bool isGameOver() const = 0;

    /**
     * Starts a new game.
     */
    virtual void newGame() = 0;

    /**
     * Advances the game, that is, the current shape moves down one line, and
     * the game board is checked for landing and completely filled lines, and
     * creates a new current shape if the previous was locked.
     *
     * \return The number of rows that have been removed.
     */
    virtual int advance() = 0;

    /**
     * Advances the game to the point where the current shape lands.
     *
     * \return The number of rows that have been removed (if any).
     */
    virtual int drop() = 0;

    /**
     * Rotates the current shape left if it is possible.
     */
    virtual void rotateLeft() = 0;

    /**
     * Rotates the current shape right if it is possible.
     */
    virtual void rotateRight() = 0;

    /**
     * Moves the current shape one column to the left if it is possible.
     */
    virtual void moveLeft() = 0;

    /**
     * Moves the current shape one column to the right if it is possible.
     */
    virtual void moveRight() = 0;
};

} // namespace tetris.

#endif // GAME_H
