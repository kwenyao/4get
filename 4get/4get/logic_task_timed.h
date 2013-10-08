#ifndef _LOGIC_TASK_TIMED_H_
#define _LOGIC_TASK_TIMED_H_
#include "logic_task.h"

// handled by John Kuan (A0097592M)

class TaskTimed : public Task
{
public:
	TaskTimed(int id, string description, string location, tm *reminderTime, Priority priority, Status status, RepeatType repeat, tm *startTime, tm *endTime);

	void setTaskStart(tm *startTask);
	void setTaskEnd(tm *endTask);

	tm* getTaskStart();
	tm* getTaskEnd();
};
#endif