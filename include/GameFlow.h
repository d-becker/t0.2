#ifndef GAMEFLOW_H
#define GAMEFLOW_H

#include <memory>
#include <string>

#include "Game.h"

namespace tetris {

typedef int InputID;

class GameFlow
{
  public:
    virtual ~GameFlow() {}

    /**
     * Returns a (smart) pointer to the \c Game object associated with
     * this object.
     *
     * \return A (smart) pointer to the \c Game object associated with
     *         this object.
     */
    virtual std::shared_ptr<const Game> getGame() const = 0;

    /**
     * Sets the \c Game object associated with this object to \a game.
     * Null pointers may be prohibited.
     */
    virtual void setGame(std::shared_ptr<Game> game) = 0;

    /**
     * Registers a command binding between a new identifier string \a name
     * and the function object \a func. If another function is already bound
     * to \a name, this method does nothing and returns \c false.
     *
     * \param name The name of the new command.
     * \param func The functin obect that will be bound to
     *        the identifier \a name.
     *
     * \return \c true on success, \c false if identifier is not new.
     */
    virtual bool makeNewCommand(std::string name,
                                std::function<void(void)> func) = 0;

    /**
     * Changes the function object associated with the identifier \a name if
     * it exists. Otherwise, this method does nothing, i.e. a new binding
     * is not created.
     *
     * \param name The identifier of the command binding that will be rebound.
     * \param func The functin obect that will be bound to
     *        the identifier \a name.
     */
    virtual bool rebindCommand(std::string name,
                               std::function<void(void)> func) = 0;

    /**
     * Removes the command binding with identifier \a name if it exists,
     * otherwise does nothing.
     *
     * \param name The identifier of the command binding that will be removed.
     *
     * \return \c true if the command binding with identifier \a name existed;
     *         \c false otherwise.
     */
    virtual bool removeCommand(std::string name) = 0;

    /**
     * Binds an input id to an existing command with name \a name.
     * If the input id is already bound to a command, that binding is deleted
     * and the new binding made. If the command is already bound to another
     * input id, that binding is deleted. If the command binding does not exist,
     * it is not created.
     *
     * \param id The id of the input to bind to \a name.
     * \param command_name The string identifier of an existing command binding.
     *
     * \return \c true if a new binding was made or an input id was rebound;
     *         \c false if the command with identifier \a name did not exist.
     */
    virtual bool bindInput(InputID id, std::string command_name) = 0;

    /**
     * Unbinds the given input id from the command it is bound to.
     * If it is not bound to any command, nothing is done.
     *
     * \param id The id of the input to unbind.
     *
     * \return \c true if the binding with \a id existed;
     *         \c false otherwise.
     */
    virtual bool unbindInput(InputID id) = 0;

    /**
     * If \a id is bound to a command, that command is executed.
     * Otherwise this method does nothing.
     *
     * \param id The id of the input that is to be processed.
     */
    virtual void processInput(InputID id) = 0;

    /**
     * Sets the function that will be called periodically. This is typically
     * a method that advances the game state.
     *
     * \param func The function that will be called periodically.
     */
    virtual void setTimeoutFunction(std::function<void(void)> func) = 0;

    /**
     * Returns the interval in milliseconds with which the timeout function
     * is called or 0 if there is no timeout running.
     *
     * \return The interval in milliseconds with which the timeout function
     *         is called, or 0 if there is no timeout running.
     */
    virtual unsigned int getTimeoutInterval() const = 0;

    /**
     * Sets the interval in milliseconds with which the timeout function
     * is called.
     *
     * \param interval The interval in milliseconds with which the timeout
     *        function is called.
     */
    virtual void setTimeoutInterval(unsigned int interval) = 0;

    /**
     * Starts a new game.
     */
    virtual void newGame() = 0;

    /**
     * Checks if the current game is over.
     *
     * \return \c true if the game is over; \c false otherwise.
     */
    virtual bool isGameOver() const = 0;

    /**
     * Pauses the game.
     */
    virtual void pause() = 0;

    /**
     * Resumes the game.
     */
    virtual void resume() = 0;

    /**
     * Checks if the current game is paused.
     *
     * \return \c true if the game is over; \c false otherwise.
     */
    virtual bool isPaused() const = 0;

    /**
     * Draws the tetris state.
     */
    virtual void draw() = 0;
};

} // namespace tetris.

#endif // GAMEFLOW_H