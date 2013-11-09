#include "logic_task_floating.h"

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