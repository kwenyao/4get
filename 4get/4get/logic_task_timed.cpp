#include "logic_task_timed.h"

TaskTimed::TaskTimed(int id, string description, string location, tm *reminderTime, Priority priority, Status status, RepeatType repeat, tm *startTime, tm *endTime)
{
	type = timed;
	setupTask(id, type, description, location, reminderTime, priority, status);
	taskStart = startTime;
	taskEnd = endTime;
	if(repeat != none)
		setRepeat(repeat);

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
