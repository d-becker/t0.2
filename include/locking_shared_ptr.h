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

#ifndef LOCKING_SHARED_PTR_H
#define LOCKING_SHARED_PTR_H

#include <memory>
#include <mutex>

namespace tetris {

/**
 * A smart pointer that during its lifetime provides exclusive access to the
 * object pointed to in RAII style. This is achieved through a mutex, so any
 * other object that has a pointer or reference to the object pointed to should
 * also use the same mutex for the exclusive access to be possible.
 * The constructor of this class locks the provided mutex and the destructor
 * unlocks it.
 * To facilitate access the the object pointed to, \c operator*
 * and \c operator-> are overridden.
 *
 * Note that \c locking_shared_ptr is not copy-constructible
 * but it is move-constructible.
 *
 * The behaviour is undefined if the thread that destructs
 * the \c locking_shared_ptr is not the same as the one that created it,
 * therefore objects of this class should always be allocated on the stack
 * and never dynamically on the heap.
 *
 * \param T The type of the object pointed to.
 * \param Mutex The type of the mutex that will be used.
 *        The default is \c std::mutex.
 */
template<typename T, typename Mutex = std::mutex>
class locking_shared_ptr
{
  public:
    /**
     * Constructs a new \c locking_shared_ptr from
     * the provided \c std::shared_ptr and locks the provided mutex.
     *
     * The behaviour is undefined if the thread that destructs
     * the \c locking_shared_ptr is not the same that created it.
     *
     * \param ptr A shared pointer to the object that
     *        this \c locking _shared_ptr is going to point to.
     * \param mutex The mutex that is locked and will be held
     *        by this \c locking_shared_ptr during its lifetime.
     */
    locking_shared_ptr(const std::shared_ptr<T>& ptr, Mutex& mutex)
      : m_shared_ptr(ptr),
        m_lock(mutex)
    {
      m_lock.lock();
    }

    /**
     * Destructs the \c locking_shared_ptr and unlocks the mutex that it held.
     * The behaviour is undefined if the thread that destructs
     * the \c locking_shared_ptr is not the same as the one that created it.
     */
    virtual ~locking_shared_ptr()
    {
      m_lock.unlock();
    }

    locking_shared_ptr(const locking_shared_ptr& other) = delete;

    /**
     * Move-constructs a \c locking_shared_ptr.
     */
    locking_shared_ptr(locking_shared_ptr&& other)
      : m_shared_ptr(other.m_shared_ptr),
        m_lock(other.m_lock)
    {

    }

    /**
     * Accesses the object pointed to. The behaviour is undefined if the
     * underlying pointer is null.
     *
     * \return A reference to the object pointed to.
     */
    T& operator*() const {
      return *m_shared_ptr;
    }

    /**
     * Accesses the object pointed to. The behaviour is undefined if the
     * underlying pointer is null.
     *
     * \return A pointer to the object pointed to.
     */
    T* operator->() const {
      return m_shared_ptr.get();
    }

  private:
    std::shared_ptr<T> m_shared_ptr;
    Mutex& m_lock;

};

} // namespace tetris.

#endif // LOCKING_SHARED_PTR_H
