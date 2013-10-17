#include "logic_task_floating.h"

TaskFloating::TaskFloating(): Task()
{
}

TaskFloating::TaskFloating(long long id): Task()
{
	clearAllAttr();
	taskId = id;
}
TaskFloating::TaskFloating(long long id, string description, string location, time_t reminderTime, Priority priority, Status status) : Task()
{
	TaskType type = floating;
	setupTask(id, type, description, location, reminderTime, priority, status);
}