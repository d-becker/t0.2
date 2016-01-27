#ifndef TETROMINOT_H
#define TETROMINOT_H

#include "BasicShape.h"

namespace tetris {

class TetrominoT : public BasicShape
{
  public:
    /**
     * Constructs a new T tetromino with the given blocks. The order is given
     * from the top line down, from left to right.
     *
     * \param blocks The blocks of the new tetromino.
     */
    TetrominoT(std::vector<std::shared_ptr<Block>> blocks);

    /**
     * Constructs a new T tetromino. All blocks will be clones of
     * the specified \c Block.
     *
     * \param block The block whose clones will be the blocks
     *        of the new tetromino.
     */
    TetrominoT(std::shared_ptr<Block> block);

    virtual ~TetrominoT();

    TetrominoT(const TetrominoT& other);
    TetrominoT(TetrominoT&& other);

    virtual std::shared_ptr<Shape> clone() const override;
  protected:
  private:
};

} // namespace tetris.

#endif // TETROMINOT_H
