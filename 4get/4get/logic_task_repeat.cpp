#include "logic_task_repeat.h"

TaskRepeat::TaskRepeat() : Task()
{

}

void TaskRepeat::setTaskRepeat(RepeatType repeat)
{
	switch(repeat)
	{
	case daily:
		{
			break;
		}
	case weekly:
		{
			break;
		}
	case fortnightly:
		{
			break;
		}
	case monthly:
		{
			break;
		}
	case annually:
		{
			break;
		}
	}

}
RepeatType TaskRepeat::getTaskRepeat()
{
	return taskRepeat;
}

