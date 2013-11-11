//@author A0097592M
#ifndef _LOGIC_TASK_TIMED_H_
#define _LOGIC_TASK_TIMED_H_
#include "logic_task_deadline.h"

// handled by John Kuan (A0097592M)

class TaskTimed : public TaskDeadline {
public:
	TaskTimed();
	TaskTimed(long long id);
	TaskTimed(long long id, 
			  string description, 
			  string location, 
			  Priority priority, 
			  RepeatType repeat, 
			  time_t startTime, 
			  time_t endTime);

	void setTaskStart(time_t startTask);
	void setNextOccurance();

	time_t getTaskStart();
	long long getTimeLong(TimeType type);
};
#endif