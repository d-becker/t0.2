#include "TetrominoO.h"

#include "Block.h"

namespace tetris {

TetrominoO::TetrominoO(std::vector<std::shared_ptr<Block>> blocks)
  : BasicShape(4,
               {Coords(1, 1), Coords(1, 2), Coords(2, 1), Coords(2, 2)},
               blocks)
{
  //ctor
}

TetrominoO::TetrominoO(std::shared_ptr<Block> block)
  : TetrominoO(
      block != nullptr ?
      std::vector<std::shared_ptr<Block>>{block->clone(), block->clone(),
                                          block->clone(), block->clone()}
          : std::vector<std::shared_ptr<Block>>{})
{

}

TetrominoO::~TetrominoO()
{
  //dtor
}

TetrominoO::TetrominoO(const TetrominoO& other) : BasicShape(other)
{
  //copy ctor
}

TetrominoO::TetrominoO(TetrominoO&& other) : BasicShape(other)
{

}

std::shared_ptr<Shape> TetrominoO::clone() const {
  return std::make_shared<TetrominoO>(*this);
}

} // namespace tetris.
