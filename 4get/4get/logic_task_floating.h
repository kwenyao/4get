#ifndef _LOGIC_TASK_FLOATING_H_
#define _LOGIC_TASK_FLOATING_H_
#include "logic_task.h"

/*
* =====================================================================================
*
*       Filename:  logic_task_floating.h
*
*         Author:  KUAN CHOW LEONG JOHN (A0097592M), johnkuan@nus.edu.sg
*   Organization:  NUS, School of Computing
*
* =====================================================================================
*/

class TaskFloating : public Task
{
public:
	TaskFloating();
	TaskFloating(long long id);
	TaskFloating(long long id, string description, string location, Priority priority);
};
#endif
