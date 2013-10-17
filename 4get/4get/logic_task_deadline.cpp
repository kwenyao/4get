#include "logic_task_deadline.h"

TaskDeadline::TaskDeadline()
{
}
TaskDeadline::TaskDeadline(long long id)
{
	clearAllAttr();
	taskId = id;
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

long long TaskDeadline::getTimeLong(TimeType type)
{
	long long yearMonthDayHourMin;
	//tm* time = NULL;
	tm* time = {0};
	time_t temp = 0;
	if(type==timeStart){
		temp = taskStart;	
		//time = taskStart;

	}
	else if(type==timeEnd){
		temp = taskEnd;
		//time = taskEnd;
	}
	else if(type==timeNext){
		temp = taskNextOccurance;
		//time = taskNextOccurance;
	}
	else if(type==timeReminder){
		temp = taskReminder;
		//time = taskReminder;
	}

	else
		return 0;

	time = localtime(&temp);
	long long min = time->tm_min;
	long long hour = time->tm_hour;
	long long day = time->tm_mday;
	long long month = time->tm_mon;
	long long year = time->tm_year + CONSTANT_START_YEAR;
	/*
	long long min = time->tm_min;
	long long hour = time->tm_hour;
	long long day = time ->tm_mday;
	long long month = time ->tm_mon;
	long long year = time ->tm_year + CONSTANT_START_YEAR;
	*/
	hour = hour*CONVERT_MULTIPLIER_HOUR;
	day = day*CONVERT_MULTIPLIER_DAY;
	month = month*CONVERT_MULTIPLIER_MONTH;
	year = year*CONVERT_MULTIPLIER_YEAR;
	yearMonthDayHourMin = (year + month + day + hour + min);
	return yearMonthDayHourMin;
}
