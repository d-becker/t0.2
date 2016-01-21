#ifndef DEFAULTGAMEBOARD_H
#define DEFAULTGAMEBOARD_H

#include "GameBoard.h"

class Board;
class Shape;

class DefaultGameBoard : public GameBoard
{
  public:
    DefaultGameBoard(std::shared_ptr<Board> board);
    DefaultGameBoard(const DefaultGameBoard& other) = delete;
    virtual ~DefaultGameBoard();

    virtual std::shared_ptr<const Board> getBoard() const override;

    virtual std::shared_ptr<const Shape> getCurrentShape() const override;
    virtual void setCurrentShape(std::shared_ptr<Shape> shape) override;


    virtual Coords getCurrentShapePosition() const override;
    virtual void setCurrentShapePosition(Coords position) override;

    virtual std::vector<Coords> getAbsolutePositions() const override;

    virtual bool isAtValidPos() const override;
    virtual bool hasLanded() const override;
    virtual Coords whereWouldLand() const override;

    virtual void lock() override;
    virtual void removeFilledRows() override;


    virtual void rotateLeft() override;
    virtual void rotateRight() override;

    virtual void moveUp() override;
    virtual void moveDown() override;
    virtual void moveLeft() override;
    virtual void moveRight() override;
  private:
    std::vector<Coords> getAbsolutePositions(std::shared_ptr<Shape> shape,
                                             const Coords& coords) const;
    bool isAtValidPos(std::shared_ptr<Shape> shape, const Coords& coords) const;
    bool hasLanded(std::shared_ptr<Shape> shape, const Coords& coords) const;
    void move(const Coords& offset);
  private:
    std::shared_ptr<Board> m_board;
    std::shared_ptr<Shape> m_current_shape;
    Coords m_current_shape_pos = Coords(0, 0);
};

#endif // DEFAULTGAMEBOARD_H
