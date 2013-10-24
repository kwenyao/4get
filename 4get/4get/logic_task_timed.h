#ifndef _LOGIC_TASK_TIMED_H_
#define _LOGIC_TASK_TIMED_H_
#include "logic_task_deadline.h"

// handled by John Kuan (A0097592M)

class TaskTimed : public TaskDeadline
{
public:
	TaskTimed();
	TaskTimed(long long id);
	TaskTimed(long long id, string description, string location, time_t reminderTime, Priority priority, RepeatType repeat, time_t startTime, time_t endTime);
	void setupTask(long long id, TaskType type, string description, string location, time_t reminderTime, Priority priority, RepeatType repeat, time_t startTime, time_t endTime);

	void setTaskStart(time_t startTask);

	time_t getTaskStart();
	long long getTimeLong(TimeType type);
};
#endif