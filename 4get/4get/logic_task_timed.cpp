#include "logic_task_timed.h"

TaskTimed::TaskTimed()
{
}
TaskTimed::TaskTimed(long long id, string description, string location, tm *reminderTime, Priority priority, Status status, RepeatType repeat, tm *startTime, tm *endTime) : TaskDeadline()
{
	TaskType type = timed;
	setupTask(id, type, description, location, reminderTime, priority, status, repeat, startTime, endTime);
}
void TaskTimed::setupTask(long long id, TaskType type, string description, string location, tm *reminderTime, Priority priority, Status status, RepeatType repeat, tm *startTime, tm *endTime)
{
	taskId = id;
	taskType = type;
	taskDescription = description;
	taskPriority = priority;
	taskLocation = location;
	taskStatus = status;
	taskReminderTime = reminderTime;
	taskRepeat = repeat;
	taskStart = startTime;
	taskEnd = endTime;
}


void TaskTimed::setTaskStart(tm* startTime)
{
	taskStart = startTime;
}

void TaskTimed::setTaskEnd(tm* endTime)
{
	taskEnd = endTime;
}

tm* TaskTimed::getTaskStart()
{
	return taskStart;
}

tm* TaskTimed::getTaskEnd()
{
	return taskEnd;
}
