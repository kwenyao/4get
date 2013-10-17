#ifndef _LOGIC_TASK_DEADLINE_H_
#define _LOGIC_TASK_DEADLINE_H_
#include "logic_task.h"

// handled by John Kuan (A0097592M)

class TaskDeadline : public Task
{
public:
	TaskDeadline();
	TaskDeadline(long long id, string description, string location, time_t reminder, Priority priority, Status status, RepeatType repeat, time_t endTime);
	virtual void setupTask(long long id, TaskType type, string description, string location, time_t reminder, Priority priority, Status status, RepeatType repeat, time_t endTime);
	void setTaskEnd(time_t endTask);
	time_t getTaskEnd();
	long long getTimeLong(TimeType type);
};

#endif