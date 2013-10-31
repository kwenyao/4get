#include "logic_task_timed.h"

TaskTimed::TaskTimed() : TaskDeadline(){
	taskType = timed;
}
TaskTimed::TaskTimed(long long id) : TaskDeadline(id)
{
	clearAllAttr();
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
	taskReminder = reminder;
	taskRepeat = repeat;
	taskStart = startTime;
	taskEnd = endTime;
}


void TaskTimed::setTaskStart(time_t startTime) { taskStart = startTime; }
time_t TaskTimed::getTaskStart() { return taskStart; }

long long TaskTimed::getTimeLong(TimeType type){
	time_t temp = 0;
	switch (type){
	case Enum::timeStart:
		temp = taskStart;	
		break;
	case Enum::timeEnd:
		temp = taskEnd;
		break;
	case Enum::timeNext:
		temp = taskNextOccurance;
		break;
	case Enum::timeReminder:
		temp = taskReminder;
		break;
	default:
		return 0;
	}
}