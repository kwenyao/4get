#include "logic_task.h"

const int Task::CONVERT_MULTIPLIER_YEAR = 100000000;
const int Task::CONVERT_MULTIPLIER_MONTH = 1000000;
const int Task::CONVERT_MULTIPLIER_DAY = 10000;
const int Task::CONVERT_MULTIPLIER_HOUR = 100;

Task::Task(){
	clearAllAttr();
}


void Task::setupTask(long long id, TaskType type, string description, string location, tm *reminderTime, Priority priority, Status status)
{
	taskId = id;
	taskType = type;
	taskDescription = description;
	taskPriority = priority;
	taskLocation = location;
//	taskStatus = status;
	taskReminderTime = reminderTime;
}

/*
Task::Task(string description, Priority priority, string location, Status status, Repeat_Type repeat, tm *reminderTime)
{
taskDescription = description;
taskPriority = priority;
taskLocation = location;
taskReminderTime = reminderTime;
taskStatus = status;
taskRepeat = repeat;

}
*/

long long Task::getTaskId() const
{
	return taskId;
}
TaskType Task::getTaskType() const
{
	return taskType;
}
string Task::getTaskDescription() const
{
	return taskDescription;
}
Priority Task::getTaskPriority() const
{
	return taskPriority;
}
string Task::getTaskLocation() const
{
	return taskLocation;
}
Status Task::getTaskStatus() const
{
	return taskStatus;
}
tm* Task::getTaskReminderTime() const
{
	return taskReminderTime;
}
tm* Task::getTaskStart() const
{
	return taskStart;
}
tm* Task::getTaskEnd() const
{
	return taskEnd;
}
RepeatType Task::getTaskRepeat() const
{
	return taskRepeat;
}



void Task::setTaskId(long long id)
{
	taskId = id;
}
void Task::setTaskType(TaskType type)
{
	taskType = type;
}
void Task::setTaskDescription(string description)
{
	taskDescription = description;
}
void Task::setTaskPriority(Priority priority)
{
	taskPriority = priority;
}
void Task::setTaskLocation(string location)
{
	taskLocation = location;
}
void Task::setTaskStatus(Status status)
{
	taskStatus = status;
}
void Task::setTaskReminderTime(tm* remindTime)
{
	taskReminderTime = remindTime;
}
void Task::setTaskStart(tm* startTime)
{
	taskStart = startTime;
}
void Task::setTaskEnd(tm* endTime)
{
	taskEnd = endTime;
}
void Task::setTaskRepeat(RepeatType repeat)
{
	taskRepeat = repeat;
}

void Task::updateAllAttr()
{

}

void Task::clearTimeAttr()
{
	tm *initializeTime = NULL;
	taskStart = initializeTime;
	taskEnd = initializeTime;
	taskNextOccurance = initializeTime;
	taskReminderTime = initializeTime;

}

void Task::clearAllAttr()
{
	taskId = INITIALIZE_INT;
	taskType = floating;
	taskDescription = INITIALIZE_STRING_BLANK;
	taskPriority = normal;
	taskLocation = INITIALIZE_STRING_BLANK;
	taskStatus = statusNone;
	clearTimeAttr();
}

long long Task::getTimeInt(TimeType type) const
{
	long long yearMonthDayHourMin;
	tm* time = NULL;

	if(type==timeStart)
		time = taskStart;
	else if(type==timeEnd)
		time = taskEnd;
	else if(type==timeNext)
		time = taskNextOccurance;
	else if(type==timeReminder)
		time = taskReminderTime;

	if(time!=NULL){
		long long min = time->tm_min;
		long long hour = time->tm_hour;
		long long day = time ->tm_mday;
		long long month = time ->tm_mon;
		long long year = time ->tm_year + CONSTANT_START_YEAR;
		hour = hour*CONVERT_MULTIPLIER_HOUR;
		day = day*CONVERT_MULTIPLIER_DAY;
		month = month*CONVERT_MULTIPLIER_MONTH;
		year = year*CONVERT_MULTIPLIER_YEAR;
		yearMonthDayHourMin = (year + month + day + hour + min);
		return yearMonthDayHourMin;
	}
	else
		return 0;

}