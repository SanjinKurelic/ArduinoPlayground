#include "Arduino.h"
#include "Stopwatch.h"

bool Stopwatch::has_elapsed(unsigned long milliseconds) {
  return enabled && (millis() - time_start >= milliseconds);
}

void Stopwatch::reset() {
  time_start = millis();
}

void Stopwatch::disable() {
  enabled = false;
}

void Stopwatch::enable() {
  enabled = true;
}
