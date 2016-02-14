#ifndef TETROMINOS_H
#define TETROMINOS_H

#include "BasicShape.h"

namespace tetris {

class TetrominoS : public BasicShape
{
  public:
    /**
     * Constructs a new S tetromino with the given blocks. The order is given
     * from the top line down, from left to right.
     *
     * \param blocks The blocks of the new tetromino.
     */
    TetrominoS(std::vector<std::shared_ptr<Block>> blocks);

    /**
     * Constructs a new S tetromino. All blocks will be clones of
     * the specified \c Block.
     *
     * \param block The block whose clones will be the blocks
     *        of the new tetromino.
     */
    TetrominoS(std::shared_ptr<Block> block);

    virtual ~TetrominoS();
    TetrominoS(const TetrominoS& other);
    TetrominoS(TetrominoS&& other);

    virtual std::shared_ptr<Shape> clone() const override;
  protected:
  private:
};

} // namespace tetris.

#endif // TETROMINOS_H
