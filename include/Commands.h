#ifndef COMMAND_H_INCLUDED
#define COMMAND_H_INCLUDED
namespace tetris {

/**
 * This enum contains identifiers for the signals/events the game receives.
 */
enum class Command : int
{
  MOVE_DOWN,
  MOVE_LEFT,
  MOVE_RIGHT,
  ROTATE_LEFT,
  ROTATE_RIGHT,
  PAUSE,
  RESUME,
  TOGGLE_PAUSED
};

} // namespace tetris.

namespace std {
  template <> struct hash<tetris::Command>
  {
    size_t operator() (const tetris::Command& command) const {
      return hash<int>()(static_cast<int>(command));
    }
  };
}

#endif // COMMAND_H_INCLUDED
