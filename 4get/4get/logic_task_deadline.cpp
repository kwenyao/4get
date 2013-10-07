#include "logic_task_deadline.h"


TaskDeadline::TaskDeadline(int id, string description, string location, tm *reminderTime, Priority priority, Status status, RepeatType repeat, tm *endTime)
{
	type = deadline;
	setupTask(id, type, description, location, reminderTime, priority, status);
	taskEnd = endTime;
	if(repeat != none)
		setRepeat(repeat);

}

void TaskDeadline::setTaskEnd(tm* endTime)
{
	taskEnd = endTime;
}

tm* TaskDeadline::getTaskEnd()
{
	return taskEnd;
}
