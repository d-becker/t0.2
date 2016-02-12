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

#include "Timeout.h"

namespace tetris {

class Timeout::ThreadSafeState {
public:
  ThreadSafeState(std::function<void(void)> func, unsigned int interval)
   : m_func(func),
     m_interval(interval),
     m_running(true),
     m_mutex()
  {

  }

  bool isRunning() const {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_running;
  }

  void stop() {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_running = false;
  }

  unsigned int getInterval() const {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_interval;
  }

  void setInterval(unsigned int interval) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_interval = interval;
  }

  const std::function<void(void)>& getFunction() const {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_func;
  }

  void setFunction(std::function<void(void)> function) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_func = function;
  }

private:
  std::function<void(void)> m_func;
  unsigned int m_interval;
  bool m_running;
  mutable std::mutex m_mutex; // Protects all members.
};


Timeout::Timeout(std::function<void(void)> func, unsigned int interval)
  : m_state(std::make_shared<ThreadSafeState>(func, interval))
{

}

Timeout::Timeout(Timeout&& other)
  : m_state(other.m_state)
{
  other.m_state = nullptr;
}

Timeout::~Timeout() {
  if (m_state != nullptr) {
    m_state->stop();
  }
}

bool Timeout::isRunning() const {
  return m_state->isRunning();
}

void Timeout::start() {
  if (!isRunning()) {
    std::shared_ptr<ThreadSafeState> state_ptr = m_state;
    std::thread([state_ptr]() {
      while (state_ptr->isRunning()) {
        state_ptr->getFunction()();
        unsigned int interval = state_ptr->getInterval();
        std::this_thread::sleep_for(std::chrono::milliseconds(interval));
      }
    }).detach();
  }
}

void Timeout::stop() {
  m_state->stop();
}

unsigned int Timeout::getInterval() const {
  return m_state->getInterval();
}

void Timeout::setInterval(unsigned int interval) {
  m_state->setInterval(interval);
}

std::function<void(void)> Timeout::getFunction() const {
  return std::function<void(void)>(m_state->getFunction());
}

void Timeout::setFunction(std::function<void(void)> function) {
  m_state->setFunction(function);
}

} // namespace tetris-
