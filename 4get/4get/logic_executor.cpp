#include "logic_executor.h"

const int Executor::CONSTANT_MULTIPLIER_YEAR = 1000000;
const int Executor::CONSTANT_MULTIPLIER_MONTH = 10000;
const int Executor::CONSTANT_MULTIPLIER_DAY = 100;
const int Executor::CONSTANT_MONTH_ONE = 1;

Executor::Executor(){
	vectorOfInputs.reserve(SLOT_SIZE);
	taskID = retrieveCurrentDate();
	tasks.loadFromFile();
	
}


bool Executor::receive(string usercommand)
{
	Command commandType = determineCommandType(usercommand);

	switch(commandType)
	{
	case commandAdd:
		return adderFunction();
	case commandDelete:
		return deleteFunction();
	case commandMark:
		return markFunction();
	default: return false;
	}
}
Enum::Command Executor::determineCommandType (string commandTypeString)
{
	if(isEqual(commandTypeString, COMMAND_ADD))
		return Command::commandAdd;
	else if(isEqual(commandTypeString, COMMAND_DELETE))
		return Command::commandDelete;
	else if(isEqual(commandTypeString, COMMAND_MARK))
		return Command::commandMark;
	else
		return Command::commandInvalid;
}
bool Executor::adderFunction()
{
	long long id;
	string description, location;
	tm *reminderTime, *startTime, *endTime;
	RepeatType repeat;
	Priority priority;
	Status status;

	++taskID = determineTaskId();
	id = taskID;
	description = vectorOfInputs[SLOT_DESCRIPTION];
	location = vectorOfInputs[SLOT_LOCATION];
	cout << vectorOfInputs[SLOT_END_TIME] <<endl;
	priority = convert.convertStringToPriority(vectorOfInputs[SLOT_PRIORITY]);
	status = convert.convertStringToStatus(vectorOfInputs[SLOT_STATUS]);
	startTime = convert.convertStringToTm(vectorOfInputs[SLOT_START_TIME]);
	endTime = convert.convertStringToTm(vectorOfInputs[SLOT_END_TIME]);
	reminderTime = convert.convertStringToTm(vectorOfInputs[SLOT_REMIND_TIME]);
	if(vectorOfInputs[SLOT_END_TIME].empty()){
		TaskFloating newTask(id, description, location, reminderTime, priority, status);
		taskGlobal = new TaskFloating;
		*taskGlobal = newTask;
	}
	else if(vectorOfInputs[SLOT_START_TIME].empty()){
		TaskDeadline newTask(id, description, location, reminderTime, priority, status, repeat, endTime); 
		taskGlobal = new TaskDeadline;
		*taskGlobal = newTask;
	}
	else{
		TaskTimed newTask(id, description, location, reminderTime, priority, status, repeat, startTime, endTime);
		taskGlobal = new TaskTimed;
		*taskGlobal = newTask;
	}

	addToTaskList();
	return true;

}
bool Executor::isEqual(string str1, const string str2)
{
	if(str1 == str2)
		return true;
	return false;
}
void Executor::stringCollector(string task)
{
	vector<string> temp(SLOT_SIZE);
	parser.parseInput(task, (temp));
	vectorOfInputs.clear();
	vectorOfInputs = temp;
	receive(temp[SLOT_COMMAND]);
}
void Executor::loadListOfTasks()
{
	tasks.loadFromFile();	
}
bool Executor::deleteFunction()
{
	int deleteNumber;
	stringstream  slotNumber(vectorOfInputs[SLOT_SLOT_NUMBER]);
	slotNumber >> deleteNumber;
	tasks.deleteFromList(deleteNumber);
	return true;
}
bool Executor::markFunction()
{
	int markNumber;
	stringstream slotNumber(vectorOfInputs[SLOT_SLOT_NUMBER]);
	slotNumber >> markNumber;
	tasks.markDone(markNumber);
	return true;
}
bool Executor::addToTaskList()
{
	tasks.addToList(*taskGlobal, listToDo);
	//tasks.addToList(*taskGlobal, listOverdue);
	return true;
}
list<Task> Executor::getUpdatedList(ListType listType){
	return tasks.obtainList(listType);
}
long long Executor::retrieveCurrentDate(){
	time_t temp;
	long long yearMonthDay;
	tm* currentTime;
	time(&temp);
	currentTime = localtime(&temp);
	long long day = currentTime ->tm_mday;
	long long month = CONSTANT_MONTH_ONE + currentTime ->tm_mon;
	long long year = currentTime ->tm_year + CONSTANT_START_YEAR;
	day = day*CONSTANT_MULTIPLIER_DAY;
	month = month*CONSTANT_MULTIPLIER_MONTH;
	year = year*CONSTANT_MULTIPLIER_YEAR;
	yearMonthDay = (year + month + day);
	return yearMonthDay;
}
//ListType Executor::determineListType(vector<string> &input)
//{
//	if(input[SLOT_END_TIME].empty())
//		return 
//}

long long Executor::determineTaskId()
{
	return retrieveCurrentDate();
}