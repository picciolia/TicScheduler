#ifndef TASK_H
#define TASK_H

#include "ti-care.h"
#include <QDateTime>
#include <QString>
#include <QTime>

using namespace TI_Care;

// Base class for managing tasks. It contains the management of the basic
// attributes of the tasks and a virutal RUN method to be overwritten in the
// derived classes to implement a specific task. It is not supposed to be
// instantiated directly.

// A task can be run every day of the week or by defining a weekly schedule
// using the SetDayOfWeek method. In addition, a task can be executed
// periodically or at a specific time. Use the SetSchedulingType(SchedulingType
// schedulingType) method to set this behaviour. In the first case
// (SchedulingType::Periodic), use the SetPeriod(int period) method to set the
// period in seconds. In the latter case (SchedulingType::FixedTime), use the
// SetClockTime(QTime clockTime) to set the specific clock time. To simplify the
// execution of the task, there is the method IsToBeExecuted() for checking the
// scheduling of the task

// No checks are made to verify the correctness of the planning. These checks
// could be part of a business logic to be implemented as improvemnts
class Task {

public:
  // Base class constructor
  Task();

  // Return a QString containing the task description
  QString GetDescription(void);
  // Set the task description using the QString parameter
  void SetDescription(QString descripiton);

  // Return true if the task is active, false otherwise
  bool IsActive(void);
  // Set if the task is active or not. A task can be temporarily disabled
  void SetActive(bool active);

  // Return true if the task must be executed in the specific day of week
  bool CheckDayOfWeek(DayOfWeek day);
  // Set if the task must be executed for a specific day of the week. Use
  // DayOfWeek::EveryWeekDay to execute the task every day
  void SetDayOfWeek(DayOfWeek day, bool active);

  // Return the specific SchedulingType for the task
  SchedulingType GetSchedulingType(void);
  // Set the specific SchedulingType for the task
  void SetSchedulingType(SchedulingType schedulingType);

  // Return the task period in seconds. Used only if the scheduling type is set
  // to SchedulingType::Periodic
  int GetPeriod(void);
  // Set the task period in seconds. Used only if the scheduling type is set to
  // SchedulingType::Periodic
  void SetPeriod(int period);

  // Return a QTime containing the clock time at which the task must be
  // executed. Used only if the scheduling type is set to
  // SchedulingType::FixedTime
  QTime GetClockTime(void);
  // Set the clock time at which the task must be executed. . Used only if the
  // scheduling type is set to SchedulingType::FixedTime
  void SetClockTime(QTime clockTime);

  // Return true if according the scheduling the task is to be executed, false
  // otherwise
  bool IsToBeExecuted(void);

  // virutal RUN method to be overwritten in the derived classes to implement a
  // specific task
  virtual void Run() = 0;

protected:
  QString _description;
  bool _active;
  SchedulingType _schedulingType;
  bool _weekPlan[DaysOfWeek];
  int _period;
  QTime _clockTime;
  QDateTime _lastRun;

private:
  bool isToBeExecutedPeriodic(QDateTime now);
  bool isToBeExecutedFixedTime(QDateTime now);
};

// Template class used to manage the parameters of the variuos task. To define a
// new task it is necessary to derive from this class by specifying the class to
// be used as Parameters and by implementing the virtual Run () method
template <class T> class TTask : public Task {
public:
  T Parameters;
  TTask() : Task() {}

  virtual void Run() = 0;
};

#endif
