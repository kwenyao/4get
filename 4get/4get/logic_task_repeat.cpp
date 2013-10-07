#include "logic_task_repeat.h"

TaskRepeat::TaskRepeat() : Task()
{

}

void TaskRepeat::setRepeat(RepeatType repeat)
{
	switch(repeat)
	{
	case DAILY:
		{
			break;
		}
	case WEEKLY:
		{
			break;
		}
	case FORTNIGHTLY:
		{
			break;
		}
	case MONTHLY:
		{
			break;
		}
	case ANNUALLY:
		{
			break;
		}
	}

}
RepeatType TaskRepeat::getTaskRepeat()
{
	return taskRepeat;
}

