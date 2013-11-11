#ifndef _LOGIC_TASK_H_
#define _LOGIC_TASK_H_
#include <string>
#include <time.h>
#include <ctime>
#include "common_message.h"

/*
* =====================================================================================
*
*       Filename:  logic_task.h
*
*         Author:  KUAN CHOW LEONG JOHN (A0097592M), johnkuan@nus.edu.sg
*   Organization:  NUS, School of Computing
*
* =====================================================================================
*/

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
	RepeatType taskRepeat;
	time_t taskStart;
	time_t taskEnd;

public:
	Task();

	//getter functions
	long long          getTaskId() const;
	TaskType           getTaskType() const;
	string             getTaskDescription() const;
	Priority           getTaskPriority() const;
	string             getTaskLocation() const;
	virtual time_t     getTaskStart() const;
	virtual time_t     getTaskEnd() const;
	virtual RepeatType getTaskRepeat() const;
	virtual long long  getTimeLong(TimeType type);

	//setter functions
	void         setTaskId(long long id);
	void         setTaskType(TaskType type);
	void         setTaskDescription(string description);
	void         setTaskPriority(Priority priority);
	void         setTaskLocation(string location);
	virtual void setTaskStart(time_t startTask);
	virtual void setTaskEnd(time_t endTask);
	virtual void setTaskRepeat(RepeatType repeat); 
	virtual void setNextOccurance();

	void clearTimeAttr();
	void clearAllAttr();

};
#endif
