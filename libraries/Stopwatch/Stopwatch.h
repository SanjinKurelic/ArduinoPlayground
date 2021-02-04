#ifndef _STOPWATCH_H_
#define _STOPWATCH_H_

#include "Arduino.h"

class Stopwatch {
  private:
    unsigned long time_start;
    bool enabled = true;

  public:
    bool has_elapsed(unsigned long milliseconds);
    void reset();
    void disable();
    void enable();
};

#endif