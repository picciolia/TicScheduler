#ifndef PRINTDEBUGTASK_H
#define PRINTDEBUGTASK_H

#include "task.h"
#include "printdebugtaskparameters.h"

// Derived class for the task that print a text
// The text to print is defined in the PrintDebugTaskParameters class
class PrintDebugTask : public TTask<PrintDebugTaskParameters> {
public:
  // Constructor
  PrintDebugTask();

  // Overrides the base virtual method to implement this specific task
  void Run();
};

#endif
