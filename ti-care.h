#ifndef TI_CARE_H
#define TI_CARE_H

// Namespace TI_CARE for const and types used in the application scope
namespace TI_Care {

    // Type for specifying the scheduling of a task:
    // Periodic indicates the scheduling of a task that repeats itself at regular
    // intervals FixedTime indicates the scheduling of a task that repeats itself at
    // a precise time
    enum class SchedulingType { Periodic, FixedTime };

    // Constant used for the management of the weekly schedule
    const int DaysOfWeek = 7;

    // Type for weekly scheduling of a task
    enum class DayOfWeek {
      EveryWeekDay = 0,
      Monday,
      Tuesday,
      Wednesday,
      Thursday,
      Friday,
      Saturday,
      Sunday = DaysOfWeek,
      First = EveryWeekDay,
      Last = Sunday
    };

    // Increment operator to navigate the days of week enum type
    inline DayOfWeek operator++(DayOfWeek &x) {
      return x = (DayOfWeek)(((int)(x) + 1));
    }
} // namespace TI_Care

#endif
