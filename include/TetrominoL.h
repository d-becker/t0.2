#ifndef TETROMINOL_H
#define TETROMINOL_H

#include "BasicShape.h"

namespace tetris {

class TetrominoL : public BasicShape
{
  public:
    /**
     * Constructs a new L tetromino with the given blocks. The order is given
     * from the top line down, from left to right.
     *
     * \param blocks The blocks of the new tetromino.
     */
    TetrominoL(std::vector<std::shared_ptr<Block>> blocks);

    /**
     * Constructs a new L tetromino. All blocks will be clones of
     * the specified \c Block.
     *
     * \param block The block whose clones will be the blocks
     *        of the new tetromino.
     */
    TetrominoL(std::shared_ptr<Block> block);

    virtual ~TetrominoL();
    TetrominoL(const TetrominoL& other);
    TetrominoL(TetrominoL&& other);

    virtual std::shared_ptr<Shape> clone() const override;
  protected:
  private:
};

} // namespace tetris.

#endif // TETROMINOL_H
