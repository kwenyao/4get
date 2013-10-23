#include "logic_task.h"

const long long Task::CONVERT_MULTIPLIER_YEAR = 100000000;
const long long Task::CONVERT_MULTIPLIER_MONTH = 1000000;
const long long Task::CONVERT_MULTIPLIER_DAY = 10000;
const long long Task::CONVERT_MULTIPLIER_HOUR = 100;

Task::Task(){
	clearAllAttr();
}
void Task::setupTask(long long id, TaskType type, string description, string location, time_t reminder, Priority priority)
{
	taskId = id;
	taskType = type;
	taskDescription = description;
	taskPriority = priority;
	taskLocation = location;
	//	taskStatus = status;
	taskReminder = reminder;
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
/*
Status Task::getTaskStatus() const
{
	return taskStatus;
}
*/
time_t Task::getTaskReminder() const
{
	return taskReminder;
}
time_t Task::getTaskNextOccurance() const
{
	return taskNextOccurance;
}
time_t Task::getTaskStart() const
{
	return taskStart;
}
time_t Task::getTaskEnd() const
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
/*
void Task::setTaskStatus(Status status)
{
	taskStatus = status;
}*/
void Task::setTaskReminder(time_t reminder)
{
	taskReminder = reminder;
}
void Task::setTaskNextOccurance(time_t next)
{
	taskNextOccurance = next;
}
void Task::setTaskStart(time_t startTime)
{
	taskStart = startTime;
}
void Task::setTaskEnd(time_t endTime)
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
	time_t initializeTime = 0;
	taskStart = initializeTime;
	taskEnd = initializeTime;
	taskNextOccurance = initializeTime;
	taskReminder = initializeTime;
}
void Task::clearAllAttr()
{
	taskId = INITIALIZE_INT;
	taskType = floating;
	taskDescription = INITIALIZE_STRING_BLANK;
	taskPriority = normal;
	taskLocation = INITIALIZE_STRING_BLANK;
	//taskStatus = statusNone;
	clearTimeAttr();
}
long long Task::getTimeLong(TimeType type)
{
	cout << "in parent class long long" <<endl;
	return 0;
}