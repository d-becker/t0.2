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

#include "BasicGameFlow.h"

#include <stdexcept>

namespace tetris {

BasicGameFlow::BasicGameFlow(std::shared_ptr<Game> game, unsigned int interval)
  : m_timeout(std::make_shared<Timeout>([&, this]() { on_advance(); },
                                        interval))
{
  //ctor
  setGame(game);

  // Setting up the default command bindings.
  makeNewCommand("advance", [&, this]() { on_advance(); });
  makeNewCommand("move_down", [&, this]() { on_move_down(); });
  makeNewCommand("move_left", [&, this]() { on_move_left(); });
  makeNewCommand("move_right", [&, this]() { on_move_right(); });
  makeNewCommand("rotate_left", [&, this]() { on_rotate_left(); });
  makeNewCommand("rotate_right", [&, this]() { on_rotate_right(); });
  makeNewCommand("drop", [&, this]() { on_drop(); });
  makeNewCommand("pause", [&, this]() { pause(); });
  makeNewCommand("resume", [&, this]() { resume(); });
  makeNewCommand("toggle_paused", [&, this]() { if (isPaused()) resume();
                                                else pause(); });


}

BasicGameFlow::~BasicGameFlow()
{
  //dtor
}

locking_shared_ptr<const Game> BasicGameFlow::getGame() const {
  return locking_shared_ptr<const Game>(m_game, m_game_mutex);
}

void BasicGameFlow::setGame(std::shared_ptr<Game> game) {
  if (game == nullptr) {
    throw std::invalid_argument(
                  "A null pointer for the Game object is not allowed.");
  }

  pause();
  std::lock_guard<std::mutex> game_lock(m_game_mutex);
  m_game = game;
}

bool BasicGameFlow::makeNewCommand(std::string name,
                                   std::function<void(void)> func) {
  unsigned int index = index_of_command_with_name(name);
  if (index != -1u) {
    return false;
  }

  std::lock_guard<std::mutex> lock_command_bindings(m_command_bindings_mutex);
  m_command_bindings.emplace_back(name, func);
  return true;
}

bool BasicGameFlow::rebindCommand(std::string name,
                                  std::function<void(void)> func) {
  unsigned int index = index_of_command_with_name(name);
  if (index == -1u) {
    return false;
  }

  std::lock_guard<std::mutex> lock_command_bindings(m_command_bindings_mutex);
  m_command_bindings[index].function = func;
  return true;
}

bool BasicGameFlow::removeCommand(std::string name) {
  unsigned int index = index_of_command_with_name(name);
  if (index == -1u) {
    return false;
  }

  std::lock_guard<std::mutex> lock_command_bindings(m_command_bindings_mutex);
  m_command_bindings.erase(m_command_bindings.begin() + index);
  return true;
}

bool BasicGameFlow::bindInput(InputID id, std::string command_name) {
  // Checking for existence.
  unsigned int index = index_of_command_with_name(command_name);
  if (index == -1u) {
    return false;
  }

  // Creating the new binding.
  std::lock_guard<std::mutex> lock_input_bindings(m_input_bindings_mutex);
  m_input_bindings[id] = command_name;

  return true;
}

bool BasicGameFlow::unbindInput(InputID id) {
  std::lock_guard<std::mutex> lock_input_bindings(m_input_bindings_mutex);
  return m_input_bindings.erase(id);
}

void BasicGameFlow::processInput(InputID id) {
  std::lock_guard<std::mutex> lock_input_bindings(m_input_bindings_mutex);
  auto it = m_input_bindings.find(id);
  if (it == m_input_bindings.end()) {
    return;
  }

  std::string name = it->second;

  unsigned int index = index_of_command_with_name(name);
  if (index == -1u) {
    return;
  }

  std::lock_guard<std::mutex> lock_command_bindings(m_command_bindings_mutex);
  Command& cmd = m_command_bindings[index];
  cmd.function.operator() ();
}

void BasicGameFlow::setTimeoutFunction(std::function<void(void)> func) {
  if (m_timeout != nullptr) {
    m_timeout->setFunction(func);
  }
}

unsigned int BasicGameFlow::getTimeoutInterval() const {
  if (m_timeout == nullptr) {
    return 0;
  }

  return m_timeout->getInterval();
}

void BasicGameFlow::setTimeoutInterval(unsigned int interval) {
  if (m_timeout != nullptr) {
    m_timeout->setInterval(interval);
  }
}

void BasicGameFlow::newGame() {
  pause();

  {
    std::lock_guard<std::mutex> lock_game(m_game_mutex);
    m_game->newGame();
  }

  resume();
}

bool BasicGameFlow::isGameOver() const {
  std::lock_guard<std::mutex> lock_game(m_game_mutex);
  return m_game->isGameOver();
}

void BasicGameFlow::pause() {
  if (m_timeout != nullptr) {
    m_timeout->stop();
  }
}

void BasicGameFlow::resume() {
  if (m_timeout != nullptr && !isGameOver()) {
    m_timeout->start();
  }
}

bool BasicGameFlow::isPaused() const {
  if (m_timeout != nullptr) {
    return !m_timeout->isRunning();
  }

  return false;
}

// Protected methods.
int BasicGameFlow::on_advance() {
  if (isGameOver()) {
    on_game_over();
    return 0;
  }

  if (isPaused()) {
    return 0;
  }

  int res = 0;
  {
    std::lock_guard<std::mutex> lock_game(m_game_mutex);
    res = m_game->advance();
  }

  draw();
  return res;
}

int BasicGameFlow::on_move_down() {
  return on_advance();
}

void BasicGameFlow::on_move_left() {
  if (!isPaused()) {
    {
      std::lock_guard<std::mutex> lock_game(m_game_mutex);
      m_game->moveLeft();
    }

    draw();
  }
}

void BasicGameFlow::on_move_right() {
  if (!isPaused()) {
    {
      std::lock_guard<std::mutex> lock_game(m_game_mutex);
      m_game->moveRight();
    }

    draw();
  }
}

void BasicGameFlow::on_rotate_left() {
  if (!isPaused()) {
    {
      std::lock_guard<std::mutex> lock_game(m_game_mutex);
      m_game->rotateLeft();
    }

    draw();
  }
}

void BasicGameFlow::on_rotate_right() {
  if (!isPaused()) {
    {
      std::lock_guard<std::mutex> lock_game(m_game_mutex);
      m_game->rotateRight();
    }

    draw();
  }
}

int BasicGameFlow::on_drop() {
  if (isGameOver()) {
    on_game_over();
    return 0;
  }

  if (!isPaused()) {
    int res = 0;
    {
      std::lock_guard<std::mutex> lock_game(m_game_mutex);
      res = m_game->drop();
    }

    draw();
    return res;
  }

  return 0;
}

void BasicGameFlow::on_game_over() {
  pause();
}

// Private methods.
unsigned int BasicGameFlow::index_of_command_with_name(std::string name) const {
  std::lock_guard<std::mutex> lock_command_bindings(m_command_bindings_mutex);
  for (unsigned int i = 0; i < m_command_bindings.size(); ++i) {
    if (m_command_bindings[i].name == name) {
      return i;
    }
  }

  return -1u;
}

bool BasicGameFlow::is_command_bound_to_input_id(std::string name,
                                                 InputID& id) const {
  std::lock_guard<std::mutex> lock_input_bindings(m_input_bindings_mutex);
  for (auto _pair : m_input_bindings) {
    if (_pair.second == name) {
      id = _pair.first;
      return true;
    }
  }

  return false;
}

} // namespace tetris.
