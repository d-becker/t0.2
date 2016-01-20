#include "BasicBoard.h"

using namespace std;

BasicBoard::BasicBoard(int height, int width)
  : m_height(height), m_width(width),
    m_table(height, vector<shared_ptr<Block>>(width, nullptr)) {
  if (m_height < 1) {
    throw invalid_argument("Zero or negative height is not allowed.");
  }
  if (m_width < 1) {
    throw invalid_argument("Zero or negative width is not allowed.");
  }
}

BasicBoard::~BasicBoard() {
//dtor
}

int BasicBoard::getHeight() const {
  return m_height;
}

/**
 * Returns the width of this \c Board.
 *
 * \return The width of this \c Board.
 */
int BasicBoard::getWidth() const {
  return m_width;
}

/**
 * Returns a pointer to the \c Block at the given position.
 *
 * \param vertical The vertical position of the block to query.
 * \param horizontal The horizontal position of the block to query.
 *
 * \return A pointer to the \c Block at the given position.
 */
shared_ptr<Block> BasicBoard::get(int vertical, int horizontal) {
  return m_const_neutral_get(vertical, horizontal);
}

shared_ptr<const Block> BasicBoard::get(int vertical, int horizontal) const {
  return m_const_neutral_get(vertical, horizontal);
}

/**
 * Sets the \c Block pointer at the given position to point to the object
 * pointed to by \a block.
 *
 * \param vertical The vertical position of the block to set.
 * \param horizontal The horizontal position of the block to set.
 * \param A pointer to the \c Block that will be the new value of the \c
 *        Block pointer at the given position.
 */
void BasicBoard::set(int vertical, int horizontal, shared_ptr<Block> block) {
  if (!isValid(vertical, horizontal)) { return; }

  int vertical_index = getHeight() - vertical - 1;
  int horizontal_index = horizontal;
  m_table.at(vertical_index).at(horizontal_index) = block;
}



/**
 * Removes the row with vertical coordinate \a row and adds a new empty row
 * to the top of the board.
 *
 * \param row The vertical coordinate of the row to be removed.
 */
void BasicBoard::removeRow(int row) {
  if (row < 0 || row >= getHeight()) {
    return;
  }

  int index = getHeight() - row - 1;
  m_table.erase(m_table.begin() + index);

  m_table.emplace_back(getWidth(), nullptr);
}

// Helpers.
shared_ptr<Block> BasicBoard::m_const_neutral_get(int vertical, int horizontal)
const {
  if (!isValid(vertical, horizontal)) {
    return nullptr;
  }

  int vertical_index = getHeight() - vertical - 1;
  int horizontal_index = horizontal;
  return m_table.at(vertical_index).at(horizontal_index);
}

