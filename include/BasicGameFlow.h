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

#ifndef BASICGAMEFLOW_H
#define BASICGAMEFLOW_H

#include "GameFlow.h"

#include <mutex>
#include <unordered_map>

#include "Timeout.h"

namespace tetris {

class BasicGameFlow : public GameFlow
{
  public:
    BasicGameFlow(std::shared_ptr<Game> game, unsigned int interval = 800u);
    BasicGameFlow(const BasicGameFlow& other) = delete;
    virtual ~BasicGameFlow();

    virtual std::shared_ptr<const Game> getGame() const override;
    virtual void setGame(std::shared_ptr<Game> game) override;

    virtual bool makeNewCommand(std::string name,
                                std::function<void(void)> func) override;
    virtual bool rebindCommand(std::string name,
                               std::function<void(void)> func) override;
    virtual bool removeCommand(std::string name);

    virtual bool bindInput(InputID id, std::string command_name) override;
    virtual bool unbindInput(InputID id) override;

    virtual void processInput(InputID id) override;

    virtual void setTimeoutFunction(std::function<void(void)> func) override;
    virtual unsigned int getTimeoutInterval() const override;
    virtual void setTimeoutInterval(unsigned int interval) override;

    virtual void newGame() override;
    virtual bool isGameOver() const override;
    virtual void pause() override;
    virtual void resume() override;
    virtual bool isPaused() const override;

  protected:
    virtual void on_advance();
    virtual void on_move_down();
    virtual void on_move_left();
    virtual void on_move_right();
    virtual void on_rotate_left();
    virtual void on_rotate_right();
    virtual void on_drop();

    virtual void on_game_over();
  private:
    // Returns -1 if name is not contained in m_command_bindings.
    unsigned int index_of_command_with_name(std::string name) const;
    bool is_command_bound_to_input_id(std::string name, InputID& id) const;
  private:
    struct Command {
      Command(std::string p_name, std::function<void(void)> p_function)
       : name(p_name), function(p_function) {}

      std::string name;
      std::function<void(void)> function;
    };

    std::shared_ptr<Game> m_game = nullptr;
    mutable std::mutex m_game_mutex {};

    std::unordered_map<InputID, std::string> m_input_bindings {};
    mutable std::mutex m_input_bindings_mutex {};

    std::vector<Command> m_command_bindings {};
    mutable std::mutex m_command_bindings_mutex {};

    // Timeout doesn't need a mutex because it is thread-safe.
    std::shared_ptr<Timeout> m_timeout = nullptr;

    bool m_paused = false;
    std::mutex m_paused_mutex {};
};

} // namespace tetris.

#endif // BASICGAMEFLOW_H
