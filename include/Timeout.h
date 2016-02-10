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

#ifndef TIMEOUT_H
#define TIMEOUT_H

#include <chrono>
#include <functional>
#include <memory>
#include <mutex>
#include <thread>

namespace tetris {

/**
 * A class that causes a function or any other callable object to be called
 * periodically. The calls are from a separate thread, so synchronization
 * may be necessary. The constructor takes a \c std::function<void(void)>
 * object and the interval in milliseconds. Only zero-argument functions
 * are accepted as functions with arguments can easily be wrapped in
 * a lambda expression.
 * When the destructor of a \c Timeout object is called, that \c Timeout object
 * is stopped.
 */
class Timeout
{
  public:
    /**
     * Constructs a new \c Timeout object and starts it immediately.
     *
     * \param function The function object to call periodically.
     * \param interval The interval in milliseconds.
     */
    Timeout(std::function<void(void)> function, unsigned int interval);

    Timeout(const Timeout& other) = delete;

    /**
     * Move-constructs a \c Timeout object. After the call, the state of the
     * original \c Timeout object is owned by the new object. If the original
     * object was running, the new one will continue to run.
     *
     * \param other The \c Timeout object to move from.
     */
    Timeout(Timeout&& other);

    /**
     * Stops this \c Timeout object and destructs it.
     */
    virtual ~Timeout();

    /**
     * Checks whether this \c Timeout object is still active.
     *
     * \return \c true if this \c Timeout object is still active;
     *         \c false otherwise.
     */
    bool isRunning() const;

    /**
     * Stops this \c Timeout object.
     */
    void stop();

    /**
     * Returns the interval of this \c Timeout object in milliseconds.
     *
     * \return The interval of this \c Timeout object in milliseconds.
     */
    unsigned int getInterval() const;

    /**
     * Sets the interval of this \c Timeout object to \a interval milliseconds.
     *
     * \param interval The new interval (in milliseconds)
     *        of this \c Timeout object-
     */
    void setInterval(unsigned int interval);
  protected:
  private:
    class ThreadSafeState;

    // Having the state in a separate, smart pointer owned object makes it
    // possible for the thread that calls the function object to exit safely.
    // That thread also has a smart pointer to this state. That thread exits
    // when this state indicates in a boolean variable that it should stop.
    // With this solution, that state variable can be reached without
    // undefined behaviour even after the destruction of this Timeout object.
    // After the other thread has exited, the destructor of the smart pointer
    // destructs the state.
    std::shared_ptr<ThreadSafeState> m_state;
};

} // namespace tetris.

#endif // TIMEOUT_H
