#include "MemoryLeaksChecker.h"

MemoryLeaksChecker::MemoryLeaksChecker()
{
  this->_leaksFound = false;
}

void MemoryLeaksChecker::start()
{
  this->_leaksFound = false;
  _CrtMemCheckpoint(&beginMemoryState);
}

void MemoryLeaksChecker::finish()
{
  // only check for memory leaks if the test did not end in a failure
  _CrtMemState endingMemoryState; // holds the current memory state (state during destruction)
  _CrtMemState memoryStateDiff;   // holds the difference between states during construction and destruction

  _CrtMemCheckpoint(&endingMemoryState);

  // if there are differences between the memory state at beginning and end, then there are memory leaks
  if (_CrtMemDifference(&memoryStateDiff, &beginMemoryState, &endingMemoryState))
  {
    _CrtMemDumpAllObjectsSince(&memoryStateDiff);
    _CrtMemDumpStatistics(&memoryStateDiff);

    this->_leaksFound = true;
  }
}

