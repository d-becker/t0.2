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
    void on_advance();
    void on_move_down();
    void on_move_left();
    void on_move_right();
    void on_rotate_left();
    void on_rotate_right();
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
