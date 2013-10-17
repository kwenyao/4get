#include "logic_task_deadline.h"

TaskDeadline::TaskDeadline()
{
}

TaskDeadline::TaskDeadline(long long id, string description, string location, time_t reminder, Priority priority, Status status, RepeatType repeat, time_t endTime) : Task()
{
	TaskType type = deadline;
	setupTask(id, type, description, location, reminder, priority, status, repeat, endTime);
}


void TaskDeadline::setupTask(long long id, TaskType type, string description, string location, time_t reminder, Priority priority, Status status, RepeatType repeat, time_t endTime)
{
	taskId = id;
	taskType = type;
	taskDescription = description;
	taskPriority = priority;
	taskLocation = location;
	taskStatus = status;
	taskReminder = reminder;
	taskRepeat = repeat;
	taskEnd = endTime;
}
void TaskDeadline::setTaskEnd(time_t endTime)
{
	taskEnd = endTime;
}

time_t TaskDeadline::getTaskEnd()
{
	return taskEnd;
}
