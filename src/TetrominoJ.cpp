#include "TetrominoJ.h"

#include "Block.h"

namespace tetris {

TetrominoJ::TetrominoJ(std::vector<std::shared_ptr<Block>> blocks)
  : BasicShape(3,
               {Coords(0, 1), Coords(1, 1), Coords(2, 1), Coords(2, 0)},
               blocks)
{
  //ctor
}

TetrominoJ::TetrominoJ(std::shared_ptr<Block> block)
  : TetrominoJ(
      block != nullptr ?
      std::vector<std::shared_ptr<Block>>{block->clone(), block->clone(),
                                          block->clone(), block->clone()}
          : std::vector<std::shared_ptr<Block>>{})
{

}

TetrominoJ::~TetrominoJ()
{
  //dtor
}

TetrominoJ::TetrominoJ(const TetrominoJ& other) : BasicShape(other)
{
  //copy ctor
}

TetrominoJ::TetrominoJ(TetrominoJ&& other) : BasicShape(other)
{

}

std::shared_ptr<Shape> TetrominoJ::clone() const {
  return std::make_shared<TetrominoJ>(*this);
}

} // namespace tetris.
