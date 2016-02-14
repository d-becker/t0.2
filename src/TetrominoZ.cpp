#include "TetrominoZ.h"

#include "Block.h"

namespace tetris {

TetrominoZ::TetrominoZ(std::vector<std::shared_ptr<Block>> blocks)
  : BasicShape(3,
               {Coords(0, 0), Coords(0, 1), Coords(1, 1), Coords(1, 2)},
               blocks)
{
  //ctor
}

TetrominoZ::TetrominoZ(std::shared_ptr<Block> block)
  : TetrominoZ(
      block != nullptr ?
      std::vector<std::shared_ptr<Block>>{block->clone(), block->clone(),
                                          block->clone(), block->clone()}
          : std::vector<std::shared_ptr<Block>>{})
{

}

TetrominoZ::~TetrominoZ()
{
  //dtor
}

TetrominoZ::TetrominoZ(const TetrominoZ& other) : BasicShape(other)
{
  //copy ctor
}

TetrominoZ::TetrominoZ(TetrominoZ&& other) : BasicShape(other)
{

}

std::shared_ptr<Shape> TetrominoZ::clone() const {
  return std::make_shared<TetrominoZ>(*this);
}

} // namespace tetris.
