#include "logic_task_deadline.h"

TaskDeadline::TaskDeadline(){
	taskType = deadline;
}
TaskDeadline::TaskDeadline(long long id)
{
	clearAllAttr();
	taskType = deadline;
	taskId = id;
}

TaskDeadline::TaskDeadline(long long id, string description, string location, time_t reminder, Priority priority, RepeatType repeat, time_t endTime) : Task()
{
	TaskType type = deadline;
	setupTask(id, type, description, location, reminder, priority, repeat, endTime);
}


void TaskDeadline::setupTask(long long id, TaskType type, string description, string location, time_t reminder, Priority priority, RepeatType repeat, time_t endTime)
{
	taskId = id;
	taskType = type;
	taskDescription = description;
	taskPriority = priority;
	taskLocation = location;
	taskReminder = reminder;
	taskRepeat = repeat;
	taskEnd = endTime;
}
void TaskDeadline::setTaskEnd(time_t endTime) {	taskEnd = endTime; }

time_t TaskDeadline::getTaskEnd() {	return taskEnd; }

long long TaskDeadline::getTimeLong(TimeType type){
	time_t temp = 0;
	switch (type){
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

long long TaskDeadline::convertToLong(time_t rawTime){
	long long yearMonthDayHourMin;
	tm* time = {0};
	time = localtime(&rawTime);
	long long min = time->tm_min;
	long long hour = time->tm_hour;
	long long day = time->tm_mday;
	long long month = time->tm_mon;
	long long year = time->tm_year + YEAR_CORRECTION;
	hour = hour*CONVERT_MULTIPLIER_HOUR;
	day = day*CONVERT_MULTIPLIER_DAY;
	month = month*CONVERT_MULTIPLIER_MONTH;
	year = year*CONVERT_MULTIPLIER_YEAR;
	yearMonthDayHourMin = (year + month + day + hour + min);
	return yearMonthDayHourMin;
}
