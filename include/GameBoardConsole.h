#ifndef GAMEBOARDCONSOLE_H
#define GAMEBOARDCONSOLE_H

#include "DefaultGameBoard.h"
#include "Board.h"
#include <algorithm>
#include <string>

namespace tetris {

class GameBoardConsole : public DefaultGameBoard
{
  public:
    GameBoardConsole(std::shared_ptr<Board> board) : DefaultGameBoard(board) {}
    virtual ~GameBoardConsole() {}

    // Only for debugging.
    std::string toString() const {

      return toString(getCurrentShape(), getCurrentShapePosition());
    }

    std::string toString(std::shared_ptr<const Shape> t,
                                      const Coords& pos) const {
      using namespace std;
      static const string sep = " ";
      static const string newline_sep = "\n";
      static const string filled = "F";
      static const string unfilled = "0";
      static const string t_block = "X";
      static const string t_block_and_filled = "Y";

      vector<Coords> blocks = getAbsolutePositions(t, pos);
      stringstream s;

      shared_ptr<const Board> board = getBoard();

      for (int v = 0; v < board->getHeight(); ++v) {
        for (int h = 0; h < board->getWidth(); ++h) {
          Coords blockPos(v, h);
          if (board->get(blockPos) != nullptr
              && find(blocks.begin(), blocks.end(), blockPos) != blocks.end()) {
            s << t_block_and_filled << sep;
          } else if (board->get(blockPos) != nullptr) {
            s << filled << sep;
          } else if (find(blocks.begin(), blocks.end(), blockPos) != blocks.end()) {
            s << t_block << sep;
          } else {
            s << unfilled << sep;
          }
        }
        s << newline_sep;
      }
      return s.str();
    }
  protected:
  private:
};

} // namespace tetris.

#endif // GAMEBOARDCONSOLE_H
