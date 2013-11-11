//@author A0097592M
#include "logic_task_floating.h"

/*
* =====================================================================================
*
*       Filename:  logic_task_floating.cpp
*
*         Author:  KUAN CHOW LEONG JOHN (A0097592M), johnkuan@nus.edu.sg
*   Organization:  NUS, School of Computing
*
* =====================================================================================
*/

/*************************************
           PUBLIC FUNCTIONS            
*************************************/

TaskFloating::TaskFloating(): Task(){
	taskType = floating;
}

TaskFloating::TaskFloating(long long id): Task()
{
	clearAllAttr();
	taskId = id;
	taskType = floating;
}
TaskFloating::TaskFloating(long long id, 
						   string description, 
						   string location, 
						   Priority priority) : Task()
{
	TaskType type = floating;
	taskId = id;
	taskDescription = description;
	taskLocation = location;
	taskPriority = priority;
}