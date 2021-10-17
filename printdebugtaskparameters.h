#ifndef PRINTDEBUGTASKPARAMETERS_H
#define PRINTDEBUGTASKPARAMETERS_H

#include "taskparameters.h"
#include <QString>

// Class for the PrintDebugTask task parametes. It contains only a text
// attribute that rapresents the text to be printed by the task
class PrintDebugTaskParameters : public TaskParameters {
public:
  // Return a QString containing the text to be printed
  QString GetText() { return _text; }

  // Set the text to be printed
  void SetText(QString text) { _text = text; }

private:
  QString _text;
};

#endif
