#include "TetrominoL.h"

#include "Block.h"

namespace tetris {

TetrominoL::TetrominoL(std::vector<std::shared_ptr<Block>> blocks)
  : BasicShape(3,
               {Coords(0, 1), Coords(1, 1), Coords(2, 1), Coords(2, 2)},
               blocks)
{
  //ctor
}

TetrominoL::TetrominoL(std::shared_ptr<Block> block)
  : TetrominoL(
      block != nullptr ?
      std::vector<std::shared_ptr<Block>>{block->clone(), block->clone(),
                                          block->clone(), block->clone()}
          : std::vector<std::shared_ptr<Block>>{})
{

}

TetrominoL::~TetrominoL()
{
  //dtor
}

TetrominoL::TetrominoL(const TetrominoL& other) : BasicShape(other)
{
  //copy ctor
}

TetrominoL::TetrominoL(TetrominoL&& other) : BasicShape(other)
{

}

std::shared_ptr<Shape> TetrominoL::clone() const {
  return std::make_shared<TetrominoL>(*this);
}

} // namespace tetris.
