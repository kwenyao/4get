#include "logic_task_floating.h"


TaskFloating::TaskFloating(int id, string description, string location, tm *reminderTime, Priority priority, Status status) : Task()
{
	//TaskType type = floating;
	setupTask(id, description, location, reminderTime, priority, status);
}
