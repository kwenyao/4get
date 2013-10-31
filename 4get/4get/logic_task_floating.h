#ifndef _LOGIC_TASK_FLOATING_H_
#define _LOGIC_TASK_FLOATING_H_
#include "logic_task.h"

// handled by John Kuan (A0097592M)

class TaskFloating : public Task
{
public:
	TaskFloating();
	TaskFloating(long long id);
	TaskFloating(long long id, string description, string location, time_t reminderTime, Priority priority);
};
#endif
