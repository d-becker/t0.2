#ifndef TETROMINOO_H
#define TETROMINOO_H

#include "BasicShape.h"

namespace tetris {

class TetrominoO : public BasicShape
{
  public:
    /**
     * Constructs a new O tetromino with the given blocks. The order is given
     * from the top line down, from left to right.
     *
     * \param blocks The blocks of the new tetromino.
     */
    TetrominoO(std::vector<std::shared_ptr<Block>> blocks);

    /**
     * Constructs a new O tetromino. All blocks will be clones of
     * the specified \c Block.
     *
     * \param block The block whose clones will be the blocks
     *        of the new tetromino.
     */
    TetrominoO(std::shared_ptr<Block> block);

    virtual ~TetrominoO();

    TetrominoO(const TetrominoO& other);
    TetrominoO(TetrominoO&& other);

    virtual std::shared_ptr<Shape> clone() const override;
  protected:
  private:
};

} // namespace tetris.

#endif // TETROMINOO_H
