#ifndef BASICGAMEFLOW_H
#define BASICGAMEFLOW_H

#include "GameFlow.h"

namespace tetris {

class BasicGameFlow : public GameFlow
{
  public:
    BasicGameFlow();
    BasicGameFlow(const BasicGameFlow& other) = delete;
    virtual ~BasicGameFlow();
  protected:
  private:
};

} // namespace tetris.

#endif // BASICGAMEFLOW_H
