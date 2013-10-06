#ifndef _LOGIC_TASK_REPEAT_H_
#define _LOGIC_TASK_REPEAT_H_
#include "logic_task.h"

// handled by John Kuan (A0097592M)

class TaskRepeat : public Task
{
protected:
	RepeatType taskRepeat;
	tm *taskNextOccurance;
public:
	void setRepeat(RepeatType repeat); 
	RepeatType getTaskRepeat();
};

#endif

