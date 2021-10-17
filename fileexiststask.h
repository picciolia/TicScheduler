#ifndef FILEEXISTSTASK_H
#define FILEEXISTSTASK_H

#include "fileexiststaskparameters.h"
#include "task.h"

// Derived class for the task that check for the existence of a file
// The filename complete with the path is defined in the
// FileExistsTaskParameters class
class FileExistsTask : public TTask<FileExistsTaskParameters> {
public:
  // Constructor
  FileExistsTask();

  // Overrides the base virtual method to implement this specific task
  void Run();
};

#endif
