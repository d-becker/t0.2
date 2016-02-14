#ifndef TETROMINOI_H
#define TETROMINOI_H

#include "BasicShape.h"

namespace tetris {

class TetrominoI : public BasicShape
{
  public:
    /**
     * Constructs a new I tetromino with the given blocks. The order is given
     * from the top line down, from left to right.
     *
     * \param blocks The blocks of the new tetromino.
     */
    TetrominoI(std::vector<std::shared_ptr<Block>> blocks);

    /**
     * Constructs a new I tetromino. All blocks will be clones of
     * the specified \c Block.
     *
     * \param block The block whose clones will be the blocks
     *        of the new tetromino.
     */
    TetrominoI(std::shared_ptr<Block> block);

    virtual ~TetrominoI();
    TetrominoI(const TetrominoI& other);
    TetrominoI(TetrominoI&& other);

    virtual std::shared_ptr<Shape> clone() const override;
  protected:
  private:
};

} // namespace tetris.

#endif // TETROMINOI_H
