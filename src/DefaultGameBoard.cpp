#include "DefaultGameBoard.h"

#include <stdexcept>

#include "Board.h"
#include "Shape.h"

using namespace std;

DefaultGameBoard::DefaultGameBoard(shared_ptr<Board> board)
  : m_board(board)
{
  if (board == nullptr) {
    throw invalid_argument("A null board is not allowed.");
  }
}

DefaultGameBoard::~DefaultGameBoard()
{

}

shared_ptr<const Board> DefaultGameBoard::getBoard() const {
  return m_board;
}

shared_ptr<const Shape> DefaultGameBoard::getCurrentShape() const {
  return m_current_shape;
}

void DefaultGameBoard::setCurrentShape(std::shared_ptr<Shape> shape) {
  m_current_shape = shape;
}

Coords DefaultGameBoard::getCurrentShapePosition() const {
  return m_current_shape_pos;
}

void DefaultGameBoard::setCurrentShapePosition(Coords position) {
  m_current_shape_pos = position;
}

vector<Coords> DefaultGameBoard::getAbsolutePositions() const {
  vector<Coords> res;
  for (const Coords& c : m_current_shape->getBlockPositions()) {
    res.emplace_back(m_current_shape_pos + c);
  }
  return res;
}

bool DefaultGameBoard::isAtValidPos() const {
  vector<Coords> abs_pos = getAbsolutePositions();
  for (const Coords& c : abs_pos) {
    if (!m_board->isValid(c)) { return false; }
    if (m_board->get(c) != nullptr) { return false; }
  }
  return true;
}

bool DefaultGameBoard::hasLanded() const {
  vector<Coords> abs_pos = getAbsolutePositions();
  for (const Coords& c : abs_pos) {
    int vertical_under = c.getVertical() + 1;
    int horizontal = c.getHorizontal();
    if (vertical_under >= m_board->getHeight()
     || m_board->get(vertical_under, horizontal) != nullptr) {
      return true;
    }
  }
  return false;
}

void DefaultGameBoard::lock() {
  for (const Coords& c : m_current_shape->getBlockPositions()) {
    shared_ptr<Block> block = m_current_shape->get(c);
    m_board->set(c + m_current_shape_pos, block);
  }
  m_current_shape = nullptr;
}

void DefaultGameBoard::removeFilledRows() {
  for (int i = 0; i < m_board->getHeight(); ++i) {
    bool contains_empty = false;
    for (int j = 0; j < m_board->getWidth(); ++j) {
      if (m_board->get(i, j) == nullptr) {
        contains_empty = true;
        break;
      }
    }
    if (!contains_empty) {
      m_board->removeRow(i);
    }
  }
}

void DefaultGameBoard::rotateLeft() {
  shared_ptr<Shape> orig_current_shape = m_current_shape->clone();
  m_current_shape->rotateLeft();
  if (!isAtValidPos()) {
    m_current_shape = orig_current_shape;
  }
}

void DefaultGameBoard::rotateRight() {
  shared_ptr<Shape> orig_current_shape = m_current_shape->clone();
  m_current_shape->rotateLeft();
  if (!isAtValidPos()) {
    m_current_shape = orig_current_shape;
  }
}

void DefaultGameBoard::moveUp() {
  move(Coords(-1, 0));
}

void DefaultGameBoard::moveDown() {
  move(Coords(1, 0));
}

void DefaultGameBoard::moveLeft() {
  move(Coords(0, -1));
}

void DefaultGameBoard::moveRight() {
  move(Coords(0, 1));
}

void DefaultGameBoard::move(const Coords& offset) {
  Coords orig_pos = m_current_shape_pos;
  m_current_shape_pos += offset;
  if (!isValid()) {
    m_current_shape_pos = orig_pos;
  }
}
