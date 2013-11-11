//@author A0097592M
#ifndef _LOGIC_TASK_DEADLINE_H_
#define _LOGIC_TASK_DEADLINE_H_
#include "logic_task.h"

/*
* =====================================================================================
*
*       Filename:  logic_task_deadline.h
*
*         Author:  KUAN CHOW LEONG JOHN (A0097592M), johnkuan@nus.edu.sg
*   Organization:  NUS, School of Computing
*
* =====================================================================================
*/

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