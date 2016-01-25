#ifndef GAME_H
#define GAME_H

#include "Drawable.h"

namespace tetris {

/**
 * An interface for the class that provides the high-level functionality for
 * updating the game. The GUI event handlers should normally call the methods
 * of this class.
 */
class Game : public Drawable
{
  public:
    virtual ~Game() {}

    /**
     * Advances the game, that is, the current shape moves down one line, and
     * the game board is checked for landing and completely filled lines, and
     * creates a new current shape if the previous was locked.
     */
    virtual void advance() = 0;

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
