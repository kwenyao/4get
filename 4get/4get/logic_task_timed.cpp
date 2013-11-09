#include "logic_task_timed.h"

TaskTimed::TaskTimed() : TaskDeadline(){
	taskType = timed;
}

TaskTimed::TaskTimed(long long id) : TaskDeadline(id){
	clearAllAttr();
	taskType = timed;
	taskId = id;
}

TaskTimed::TaskTimed(long long id, 
					 string description, 
					 string location, 
					 Priority priority, 
					 RepeatType repeat, 
					 time_t startTime, 
					 time_t endTime) : TaskDeadline()
{
	TaskType type = timed;
	taskId = id;
	taskType = type;
	taskDescription = description;
	taskPriority = priority;
	taskLocation = location;
	taskRepeat = repeat;
	taskStart = startTime;
	taskEnd = endTime;
}

void TaskTimed::setTaskStart(time_t startTime) { taskStart = startTime; }

void TaskTimed::setNextOccurance(){
	struct tm endTM = convertToTm(taskEnd);
	struct tm startTM = convertToTm(taskStart);
	switch (taskRepeat){
	case Enum::daily:
		endTM.tm_mday = endTM.tm_mday + 1;
		startTM.tm_mday = startTM.tm_mday + 1;
		break;
	case Enum::weekly:
		endTM.tm_mday = endTM.tm_mday + 7;
		startTM.tm_mday = startTM.tm_mday + 7;
		break;
	case Enum::fortnightly:
		endTM.tm_mday = endTM.tm_mday + 14;
		startTM.tm_mday = startTM.tm_mday + 14;
		break;
	case Enum::monthly:
		endTM.tm_mon = endTM.tm_mon + 1;
		startTM.tm_mon = startTM.tm_mon + 1;
		break;
	case Enum::annually:
		endTM.tm_year = endTM.tm_year + 1;
		startTM.tm_year = startTM.tm_year + 1;
		break;
	default:
		return;
	}
	taskEnd = mktime(&endTM);
	taskStart = mktime(&startTM);
}

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
	default:
		return 0;
	}
	return convertToLong(temp);
}