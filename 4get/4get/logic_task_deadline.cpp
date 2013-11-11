#include "logic_task_deadline.h"

/*************************************
           PUBLIC FUNCTIONS            
*************************************/

TaskDeadline::TaskDeadline(){
	taskType = deadline;
}
TaskDeadline::TaskDeadline(long long id)
{
	clearAllAttr();
	taskType = deadline;
	taskId = id;
}

TaskDeadline::TaskDeadline(long long id, 
						   string description, 
						   string location, 
						   Priority priority, 
						   RepeatType repeat, 
						   time_t endTime) : Task()
{
	TaskType type = deadline;
	taskId = id;
	taskType = type;
	taskDescription = description;
	taskPriority = priority;
	taskLocation = location;
	taskRepeat = repeat;
	taskEnd = endTime;
}

void TaskDeadline::setTaskEnd(time_t endTime) {	taskEnd = endTime; }

void TaskDeadline::setNextOccurance(){
	struct tm timeTM = convertToTm(taskEnd);
	switch (taskRepeat){
	case Enum::daily:
		timeTM.tm_mday = timeTM.tm_mday + 1;
		break;
	case Enum::weekly:
		timeTM.tm_mday = timeTM.tm_mday + 7;
		break;
	case Enum::fortnightly:
		timeTM.tm_mday = timeTM.tm_mday + 14;
		break;
	case Enum::monthly:
		timeTM.tm_mon = timeTM.tm_mon + 1;
		break;
	case Enum::annually:
		timeTM.tm_year = timeTM.tm_year + 1;
		break;
	default:
		return;
	}
	taskEnd = mktime(&timeTM);
}

time_t TaskDeadline::getTaskEnd() {	return taskEnd; }

long long TaskDeadline::getTimeLong(TimeType type){
	time_t temp = 0;
	switch (type){
	case Enum::timeEnd:
		temp = taskEnd;
		break;
	default:
		return 0;
	}
	return convertToLong(temp);
}

long long TaskDeadline::convertToLong(time_t rawTime){
	long long yearMonthDayHourMin;
	tm* time = {0};
	localtime_s(time, &rawTime);
	long long min = time->tm_min;
	long long hour = time->tm_hour;
	long long day = time->tm_mday;
	long long month = time->tm_mon;
	long long year = time->tm_year + YEAR_CORRECTION;
	//hour = hour*CONVERT_MULTIPLIER_HOUR;
	day = day*CONVERT_MULTIPLIER_DAY;
	month = month*CONVERT_MULTIPLIER_MONTH;
	year = year*CONVERT_MULTIPLIER_YEAR;
	yearMonthDayHourMin = (year + month + day);
	return yearMonthDayHourMin;
}

tm TaskDeadline::convertToTm(time_t rawTime){
	struct tm returnTime;
	localtime_s(&returnTime,&rawTime);
	return returnTime;
}
