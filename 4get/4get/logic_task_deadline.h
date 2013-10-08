#ifndef _LOGIC_TASK_DEADLINE_H_
#define _LOGIC_TASK_DEADLINE_H_
#include "logic_task.h"

// handled by John Kuan (A0097592M)

class TaskDeadline : public Task
{
public:
	TaskDeadline(int id, string description, string location, tm *reminderTime, Priority priority, Status status, RepeatType repeat, tm *endTime);
	void setTaskEnd(tm *endTask);
	tm* getTaskEnd();
};

#endif