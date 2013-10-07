#ifndef _LOGIC_TASK_TIMED_H_
#define _LOGIC_TASK_TIMED_H_
#include "logic_task_repeat.h"

// handled by John Kuan (A0097592M)

class TaskTimed : public TaskRepeat
{
private:
	TaskType type;
	tm *taskStart;
	tm *taskEnd;


public:
	TaskTimed(int id, string description, string location, tm *reminderTime, Enum::Priority priority, Enum::Status status, Enum::RepeatType repeat, tm *startTime, tm *endTime);

	void setTaskStart(tm *startTask);
	void setTaskEnd(tm *endTask);

	tm* getTaskStart();
	tm* getTaskEnd();
};
#endif