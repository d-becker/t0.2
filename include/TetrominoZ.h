#ifndef TETROMINOZ_H
#define TETROMINOZ_H

#include "BasicShape.h"

namespace tetris {

class TetrominoZ : public BasicShape
{
  public:
    /**
     * Constructs a new Z tetromino with the given blocks. The order is given
     * from the top line down, from left to right.
     *
     * \param blocks The blocks of the new tetromino.
     */
    TetrominoZ(std::vector<std::shared_ptr<Block>> blocks);

    /**
     * Constructs a new Z tetromino. All blocks will be clones of
     * the specified \c Block.
     *
     * \param block The block whose clones will be the blocks
     *        of the new tetromino.
     */
    TetrominoZ(std::shared_ptr<Block> block);

    virtual ~TetrominoZ();
    TetrominoZ(const TetrominoZ& other);
    TetrominoZ(TetrominoZ&& other);

    virtual std::shared_ptr<Shape> clone() const override;
  protected:
  private:
};

} // namespace tetris.

#endif // TETROMINOZ_H
