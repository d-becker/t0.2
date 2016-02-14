#include "TetrominoI.h"

#include "Block.h"

namespace tetris {

TetrominoI::TetrominoI(std::vector<std::shared_ptr<Block>> blocks)
  : BasicShape(4,
               {Coords(0, 1), Coords(1, 1), Coords(2, 1), Coords(3, 1)},
               blocks)
{
  //ctor
}

TetrominoI::TetrominoI(std::shared_ptr<Block> block)
  : TetrominoI(
      block != nullptr ?
      std::vector<std::shared_ptr<Block>>{block->clone(), block->clone(),
                                          block->clone(), block->clone()}
          : std::vector<std::shared_ptr<Block>>{})
{

}

TetrominoI::~TetrominoI()
{
  //dtor
}

TetrominoI::TetrominoI(const TetrominoI& other) : BasicShape(other)
{
  //copy ctor
}

TetrominoI::TetrominoI(TetrominoI&& other) : BasicShape(other)
{

}

std::shared_ptr<Shape> TetrominoI::clone() const {
  return std::make_shared<TetrominoI>(*this);
}

} // namespace tetris.
