#include "logic_task.h"

const long long Task::CONVERT_MULTIPLIER_YEAR = 10000;
const long long Task::CONVERT_MULTIPLIER_MONTH = 100;
const long long Task::CONVERT_MULTIPLIER_DAY = 1;
const long long Task::CONVERT_MULTIPLIER_HOUR = 100;

Task::Task(){
	clearAllAttr();
}

long long Task::getTaskId() const {	return taskId;}
TaskType Task::getTaskType() const { return taskType; }
string Task::getTaskDescription() const { return taskDescription; }
Priority Task::getTaskPriority() const { return taskPriority; }
string Task::getTaskLocation() const { return taskLocation; }
time_t Task::getTaskStart() const {	return taskStart; }
time_t Task::getTaskEnd() const { return taskEnd; }
RepeatType Task::getTaskRepeat() const { return taskRepeat; }

void Task::setTaskId(long long id) { taskId = id; }
void Task::setTaskType(TaskType type) {	taskType = type; }
void Task::setTaskDescription(string description) {	taskDescription = description; }
void Task::setTaskPriority(Priority priority) { taskPriority = priority; }
void Task::setTaskLocation(string location) { taskLocation = location; }
void Task::setTaskStart(time_t startTime) {	taskStart = startTime; }
void Task::setTaskEnd(time_t endTime) {	taskEnd = endTime; }
void Task::setTaskRepeat(RepeatType repeat) { taskRepeat = repeat; }
void Task::setNextOccurance(){ return ; }

void Task::updateAllAttr()
{

}

void Task::clearTimeAttr()
{
	time_t initializeTime = 0;
	taskStart = initializeTime;
	taskEnd = initializeTime;
}

void Task::clearAllAttr()
{
	taskId = INITIALIZE_INT;
	taskType = floating;
	taskDescription = INITIALIZE_STRING_BLANK;
	taskPriority = normal;
	taskLocation = INITIALIZE_STRING_BLANK;
	clearTimeAttr();
}

long long Task::getTimeLong(TimeType type) { return 0; }