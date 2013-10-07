#ifndef _LOGIC_TASK_H_
#define _LOGIC_TASK_H_
#include <string>
#include <time.h>
#include <ctime>
#include "common_message.h"

// handled by John Kuan (A0097592M)

using namespace std;
using namespace Enum;

class Task 
{	
protected:

	//attributes
	int taskId;
	TaskType taskType;
	string taskDescription;
	Priority taskPriority;
	string taskLocation;
	tm *taskReminderTime;
	Status taskStatus;

public:
	Task();
	void setupTask(int id, TaskType type, string description, string location, tm *reminderTime, Priority priority, Status status);
	//Task(string description, Priority priority, string location, Status status, Repeat_Type repeat, tm *reminder);

	//getter functions
	int getTaskId();
	string getTaskDescription();
	Priority getTaskPriority();
	string getTaskLocation();
	Status getTaskStatus();
	tm* getTaskReminderTime();

	//setter functions
	void setTaskId(int id);
	void setTaskDescription(string description);
	void setTaskPriority(Priority priority);
	void setTaskLocation(string location);
	void setTaskStatus(Status status);
	void setTaskReminderTime(tm* remindTime);
	
	//update function
	void updateAllAttr();

};
#endif
