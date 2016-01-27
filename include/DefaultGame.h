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
