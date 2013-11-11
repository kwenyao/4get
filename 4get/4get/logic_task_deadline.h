#ifndef _LOGIC_TASK_DEADLINE_H_
#define _LOGIC_TASK_DEADLINE_H_
#include "logic_task.h"

// handled by John Kuan (A0097592M)

class TaskDeadline : public Task
{
protected:
	long long convertToLong(time_t rawTime);
	tm convertToTm(time_t rawTime);

public:
	TaskDeadline();
	TaskDeadline(long long id);
	TaskDeadline(long long id, 
				 string description, 
				 string location, 
				 Priority priority, 
				 RepeatType repeat, 
				 time_t endTime);
	
	void setTaskEnd(time_t endTask);
	virtual void setNextOccurance();
	time_t getTaskEnd();
	virtual long long getTimeLong(TimeType type);
};

#endif