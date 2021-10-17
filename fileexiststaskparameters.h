#ifndef FILEEXISTSTASKPARAMETERS_H
#define FILEEXISTSTASKPARAMETERS_H

#include "taskparameters.h"
#include <QString>

// Class derived from TaskParameters that manages the necessary
// parameters for FileExistsTask type tasks
class FileExistsTaskParameters : public TaskParameters {
public:
  // Return a QString containing the filename with the complete path to verify
  QString GetFilename() { return _filename; }
  // Set the filename with the complete path to verify
  void SetFilename(QString filename) { _filename = filename; }

private:
  QString _filename;
};

#endif
