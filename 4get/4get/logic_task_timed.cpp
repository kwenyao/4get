#include "logic_task_timed.h"

TaskTimed::TaskTimed() : TaskDeadline(){
	taskType = timed;
}
TaskTimed::TaskTimed(long long id) : TaskDeadline(id)
{
	taskType = timed;
	taskId = id;
}
TaskTimed::TaskTimed(long long id, string description, string location, time_t reminder, Priority priority, RepeatType repeat, time_t startTime, time_t endTime) : TaskDeadline()
{
	TaskType type = timed;
	setupTask(id, type, description, location, reminder, priority, repeat, startTime, endTime);
}
void TaskTimed::setupTask(long long id, TaskType type, string description, string location, time_t reminder, Priority priority, RepeatType repeat, time_t startTime, time_t endTime)
{
	taskId = id;
	taskType = type;
	taskDescription = description;
	taskPriority = priority;
	taskLocation = location;
	//taskStatus = status;
	taskReminder = reminder;
	taskRepeat = repeat;
	taskStart = startTime;
	taskEnd = endTime;
}


void TaskTimed::setTaskStart(time_t startTime)
{
	taskStart = startTime;
}

void TaskTimed::setTaskEnd(time_t endTime)
{
	taskEnd = endTime;
}

time_t TaskTimed::getTaskStart()
{
	return taskStart;
}

time_t TaskTimed::getTaskEnd()
{
	return taskEnd;
}
