#pragma once

#include <stdlib.h>
#include <crtdbg.h>

class MemoryLeaksChecker
{
public:
  MemoryLeaksChecker(void);
  virtual ~MemoryLeaksChecker(void) {};

  void start();
  void finish();
  bool isMemoryLeaks() { return this->_leaksFound; };

private:
  // memory state at the beginning of the test fixture set up
  _CrtMemState beginMemoryState;
  bool _leaksFound;
};
