#include "task.h"
#include "fileexiststaskparameters.h"
#include "printdebugtaskparameters.h"

#include <QDebug>

using namespace TI_Care;

Task::Task() {
  // Initialization
  _active = false;
  _schedulingType = SchedulingType::Periodic;
  _period = 0;

  for (DayOfWeek day = DayOfWeek::First; day != DayOfWeek::Last; ++day) {
    _weekPlan[(int)day] = false;
  }

  // For simplicity, the last execution of the task is set with the date and
  // time the task was created
  _lastRun = QDateTime::currentDateTime();
}

QString Task::GetDescription() { return _description; }

void Task::SetDescription(QString descripiton) { _description = descripiton; }

bool Task::IsActive(void) { return _active; }

void Task::SetActive(bool active) { _active = active; }

int Task::GetPeriod() { return _period; }

void Task::SetPeriod(int period) { _period = period; }

SchedulingType Task::GetSchedulingType() { return _schedulingType; }

void Task::SetSchedulingType(TI_Care::SchedulingType schedulingType) {
  _schedulingType = schedulingType;
}

void Task::SetDayOfWeek(TI_Care::DayOfWeek day, bool active) {
  _weekPlan[(int)day] = active;
}

bool Task::CheckDayOfWeek(TI_Care::DayOfWeek day) {
  return _weekPlan[(int)day];
}

bool Task::IsToBeExecuted() {
  bool result = false;

  // Checks if the task is active
  if (IsActive() == true) {

    QDateTime now = QDateTime::currentDateTime();
    int today = now.date().dayOfWeek();

    // Check if the task is to be executed on the current day
    if (_weekPlan[(int)DayOfWeek::EveryWeekDay] == true ||
        _weekPlan[today] == true) {

      // According to the SchedulingType, checks wheter the task is to be
      // executed
      switch (_schedulingType) {
      case SchedulingType::Periodic:
        result = isToBeExecutedPeriodic(now);
        break;

      case SchedulingType::FixedTime:
        result = isToBeExecutedFixedTime(now);
        break;

      default:
        result = false;
        break;
      }
    }
  }

  return result;
}

// Return true if _period seconds have passed since the last run, false
// otherwise
bool Task::isToBeExecutedPeriodic(QDateTime now) {
  if (now >= _lastRun.addSecs(_period)) {
    // Update the last run value with current datetime
    _lastRun = now;
    return true;
  }

  return false;
}

// Return true if the current time is equal to or greater than the set time,
// false otherwise
bool Task::isToBeExecutedFixedTime(QDateTime now) {
  // In order not to continue repeating the task after the scheduled time, the
  // date is also checked
  if ((now.time() >= _clockTime) && (now.date() != _lastRun.date())) {
    // Update the last run value with current datetime
    _lastRun = now;
    return true;
  }

  return false;
}

// Explicitly instantiate the template class for the linker
template class TTask<FileExistsTaskParameters>;
template class TTask<PrintDebugTaskParameters>;
