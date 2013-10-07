#ifndef _LOGIC_TASK_FLOATING_H_
#define _LOGIC_TASK_FLOATING_H_
#include "logic_task.h"

// handled by John Kuan (A0097592M)

class TaskFloating : Task
{
private:
	TaskType type;

public:
	TaskFloating(int id, string description, string location, tm *reminderTime, Priority priority, Status status);
};
#endif
