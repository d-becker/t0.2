#include "TetrominoS.h"

#include "Block.h"

namespace tetris {

TetrominoS::TetrominoS(std::vector<std::shared_ptr<Block>> blocks)
  : BasicShape(3,
               {Coords(0, 1), Coords(0, 2), Coords(1, 0), Coords(1, 1)},
               blocks)
{
  //ctor
}

TetrominoS::TetrominoS(std::shared_ptr<Block> block)
  : TetrominoS(
      block != nullptr ?
      std::vector<std::shared_ptr<Block>>{block->clone(), block->clone(),
                                          block->clone(), block->clone()}
          : std::vector<std::shared_ptr<Block>>{})
{

}

TetrominoS::~TetrominoS()
{
  //dtor
}

TetrominoS::TetrominoS(const TetrominoS& other) : BasicShape(other)
{
  //copy ctor
}

TetrominoS::TetrominoS(TetrominoS&& other) : BasicShape(other)
{

}

std::shared_ptr<Shape> TetrominoS::clone() const {
  return std::make_shared<TetrominoS>(*this);
}

} // namespace tetris.
