#ifndef TASKLIST_H
#define TASKLIST_H

#include "task.h"
#include <QList>
#include <QString>

// Singleton class to manage the task list. The main purpose of this class is to
// serialize or deserialize all tasks in a file or database. For simplicity this
// part has not been fully implemented
class TaskList {
public:
  // Return the instance of the singleton class
  static TaskList *getInstance();

  // Return a QList containing the task list
  static QList<Task *> List;

  // Static method for serialize the task list
  static void Serialize(void);
  // Static method for deserialize the task list
  static void Deserialize(void);

public slots:
  void updatePrintDebugTask(QString text);

private:
  TaskList();
  static TaskList *instance;
};

#endif
