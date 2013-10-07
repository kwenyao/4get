#include "logic_task_floating.h"


TaskFloating::TaskFloating(int id, string description, string location, tm *reminderTime, Priority priority, Status status)
{
	setupTask(id, type, description, location,reminderTime, priority, status);
}
