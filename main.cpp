/*
 * Copyright (C) 2016 Daniel Becker <beckerdaniel.dani@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as published
 * by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include <iostream>
#include <cstdlib>

#include "UnitTest++.h"

#include "BasicBoard.h"
#include "BasicBlock.h"
#include "BasicShape.h"
#include "GameBoard.h"
#include "Shape.h"
#include "DefaultGame.h"
#include "Drawable.h"
#include "Game.h"

#include "GameBoardConsole.h"

using namespace std;
using namespace tetris;



int main()
{

  //return UnitTest::RunAllTests();
  int bbox_size = 3;
  shared_ptr<Block> block = make_shared<BasicBlock>();
  vector<Coords> coords {Coords(0, 0), Coords(1, 0), Coords(2, 0), Coords(1, 1)};

  vector<shared_ptr<Block>> blocks(coords.size());
  for (unsigned int i = 0; i < coords.size(); ++i) {
    blocks.at(i) = block->clone();
  }


  shared_ptr<Shape> shape = make_shared<BasicShape>(bbox_size, coords, blocks);
  vector<shared_ptr<Shape>> shapes(1, shape);

  shared_ptr<Board> board = make_shared<BasicBoard>(20, 15);

  shared_ptr<GameBoardConsole> gbc = make_shared<GameBoardConsole>(board);

  shared_ptr<Game> game = make_shared<DefaultGame>(gbc, shapes);

  //
  while (true) {
    system("clear");
    cout << gbc->toString() << ".\n" << "Command: ";

    string input;
    getline(cin, input);

    if (input == "exit") {
      break;
    } else if (input == "a") {
      game->advance();
    } else if (input == "l") {
      game->moveLeft();
    } else if (input == "r") {
      game->moveRight();
    } else if (input == "rl") {
      game->rotateLeft();
    } else if (input == "rr") {
      game->rotateRight();
    } else {
    }
  }

}
