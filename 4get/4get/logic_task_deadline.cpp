#include "logic_task_deadline.h"

TaskDeadline::TaskDeadline()
{
}

TaskDeadline::TaskDeadline(long long id, string description, string location, tm *reminderTime, Priority priority, Status status, RepeatType repeat, tm *endTime) : Task()
{
	TaskType type = deadline;
	setupTask(id, type, description, location, reminderTime, priority, status, repeat, endTime);
}


void TaskDeadline::setupTask(long long id, TaskType type, string description, string location, tm *reminderTime, Priority priority, Status status, RepeatType repeat, tm *endTime)
{
	taskId = id;
	taskType = type;
	taskDescription = description;
	taskPriority = priority;
	taskLocation = location;
	taskStatus = status;
	taskReminderTime = reminderTime;
	taskRepeat = repeat;
	taskEnd = endTime;
}
void TaskDeadline::setTaskEnd(tm* endTime)
{
	taskEnd = endTime;
}

tm* TaskDeadline::getTaskEnd()
{
	return taskEnd;
}
