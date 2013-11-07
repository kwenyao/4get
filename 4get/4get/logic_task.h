#ifndef _LOGIC_TASK_H_
#define _LOGIC_TASK_H_
#include <string>
#include <time.h>
#include <ctime>
#include "common_message.h"

// handled by John Kuan (A0097592M)

using namespace std;
using namespace Enum;
using namespace Constants;


class Task 
{	
protected:

	//multipliers for time conversion in Task
	static const long long CONVERT_MULTIPLIER_YEAR;
	static const long long CONVERT_MULTIPLIER_MONTH;
	static const long long CONVERT_MULTIPLIER_DAY;
	static const long long CONVERT_MULTIPLIER_HOUR;

	//attributes
	long long taskId;
	TaskType taskType;
	string taskDescription;
	Priority taskPriority;
	string taskLocation;
	time_t taskReminder;
	//Status taskStatus;
	RepeatType taskRepeat;
	time_t taskNextOccurance;
	time_t taskStart;
	time_t taskEnd;

public:
	Task();
	virtual void setupTask(long long id, TaskType type, string description, string location, time_t reminder, Priority priority);
	//Task(string description, Priority priority, string location, Status status, Repeat_Type repeat, tm *reminder);

	//getter functions
	long long getTaskId() const;
	TaskType getTaskType() const;
	string getTaskDescription() const;
	Priority getTaskPriority() const;
	string getTaskLocation() const;
	//Status getTaskStatus() const;
	time_t getTaskReminder() const;
	time_t getTaskNextOccurance() const;
	virtual time_t getTaskStart() const;
	virtual time_t getTaskEnd() const;
	virtual RepeatType getTaskRepeat() const;
	virtual long long getTimeLong(TimeType type);

	//setter functions
	void setTaskId(long long id);
	void setTaskType(TaskType type);
	void setTaskDescription(string description);
	void setTaskPriority(Priority priority);
	void setTaskLocation(string location);
	//void setTaskStatus(Status status);
	void setTaskReminder(time_t reminder);
	void setTaskNextOccurance(time_t next);
	virtual void setTaskStart(time_t startTask);
	virtual void setTaskEnd(time_t endTask);
	virtual void setTaskRepeat(RepeatType repeat); 

	//update function
	void updateAllAttr();

	void clearTimeAttr();
	void clearAllAttr();

};
#endif
