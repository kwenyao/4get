#include "logic_task.h"
Task::Task(){}


void Task::setupTask(int id, TaskType type, string description, string location, tm *reminderTime, Priority priority, Status status)
{
	taskId = id;
	taskType = type;
	taskDescription = description;
	taskPriority = priority;
	taskLocation = location;
	taskStatus = status;
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

int Task::getTaskId()
{
	return taskId;
}
string Task::getTaskDescription()
{
	return taskDescription;
}
Priority Task::getTaskPriority()
{
	return taskPriority;
}
string Task::getTaskLocation()
{
	return taskLocation;
}
Status Task::getTaskStatus()
{
	return taskStatus;
}
tm* Task::getTaskReminderTime()
{
	return taskReminderTime;
}

void Task::setTaskId(int id)
{
	taskId = id;
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

void Task::updateAllAttr()
{

}

