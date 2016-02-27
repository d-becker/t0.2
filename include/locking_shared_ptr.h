#ifndef LOCKING_SHARED_PTR_H
#define LOCKING_SHARED_PTR_H

#include <memory>
#include <mutex>

namespace tetris {

/**
 * A smart pointer that during its lifetime provides exclusive access to the
 * object pointed to in a RAII way. This is achieved through a mutex, so any
 * other object that has a pointer or reference to the object pointed to should
 * also use the same mutex for the exclusive access to be possible.
 * The constructor of this class locks the provided mutex and the destructor
 * unlocks it.
 * To facilitate access the the object pointed to, \c operator*
 * and \c operator-> are overridden.
 *
 * \param T The type of the object pointed to.
 * \param Mutex The type of the mutex that will be used.
 *        The default is \c std::mutex.
 */
template<typename T, typename Mutex = std::mutex>
class locking_shared_ptr
{
  public:
    locking_shared_ptr(const std::shared_ptr<T>& ptr, Mutex& mutex)
      : m_shared_ptr(ptr),
        m_lock(mutex)
    {
      m_lock.lock();
    }

    virtual ~locking_shared_ptr()
    {
      m_lock.unlock();
    }

    locking_shared_ptr(const locking_shared_ptr& other) = delete;

    locking_shared_ptr(locking_shared_ptr&& other)
      : m_shared_ptr(other.m_shared_ptr),
        m_lock(other.m_lock)
    {

    }

    T& operator*() const {
      return *m_shared_ptr;
    }

    T* operator->() const {
      return m_shared_ptr.get();
    }

  protected:
  private:
    std::shared_ptr<T> m_shared_ptr;
    Mutex& m_lock;

};

} // namespace tetris.

#endif // LOCKING_SHARED_PTR_H
