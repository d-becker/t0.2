#include "TetrominoT.h"

#include "Block.h"

namespace tetris {

TetrominoT::TetrominoT(std::vector<std::shared_ptr<Block>> blocks)
  : BasicShape(3,
               {Coords(0, 0), Coords(0, 1), Coords(0, 2), Coords(1, 1)},
               blocks)
{
  //ctor
}

TetrominoT::TetrominoT(std::shared_ptr<Block> block)
  : TetrominoT(
      block != nullptr ?
      std::vector<std::shared_ptr<Block>>{block->clone(), block->clone(),
                                          block->clone(), block->clone()}
          : std::vector<std::shared_ptr<Block>>{})
{

}

TetrominoT::~TetrominoT()
{
  //dtor
}

TetrominoT::TetrominoT(const TetrominoT& other) : BasicShape(other)
{
  //copy ctor
}

TetrominoT::TetrominoT(TetrominoT&& other) : BasicShape(other)
{

}

std::shared_ptr<Shape> TetrominoT::clone() const {
  return std::make_shared<TetrominoT>(*this);
}

} // namespace tetris.
