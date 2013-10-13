#include "logic_executor.h"

const int Executor::CONSTANT_MULTIPLIER_YEAR = 10000000;
const int Executor::CONSTANT_MULTIPLIER_MONTH = 100000;
const int Executor::CONSTANT_MULTIPLIER_DAY = 1000;

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
	default: return false;
	}
}
Enum::Command Executor::determineCommandType (string commandTypeString)
{
	if(isEqual(commandTypeString, COMMAND_ADD))
		return Command::commandAdd;
	else if(isEqual(commandTypeString, COMMAND_DELETE))
		return Command::commandDelete;
	else
		return Command::commandInvalid;
}
bool Executor::adderFunction()
{
	Task _task;
	int id;
	string description, location;
	tm* reminderTime;
	Priority priority;
	Status status;

	++taskID = determineTaskId();
	id = taskID;
	description = vectorOfInputs[SLOT_DESCRIPTION];
	location = vectorOfInputs[SLOT_LOCATION];
	cout << "hello" << endl;
	cout << vectorOfInputs[SLOT_END_TIME] <<endl;
	priority = convert.convertStringToPriority(vectorOfInputs[SLOT_PRIORITY]);
	status = convert.convertStringToStatus(vectorOfInputs[SLOT_STATUS]);
	cout << "bye" << endl;
	reminderTime = convert.convertStringToTm(vectorOfInputs[SLOT_END_TIME]);
	_task.setupTask(id, description, location, reminderTime, priority, status);
	taskGlobal = _task;

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
bool Executor::addToTaskList()
{
	tasks.addToList(taskGlobal, listToDo);
	return true;
}
list<Task> Executor::getUpdatedList(ListType listType){
	return tasks.obtainList(listType);
}
int Executor::retrieveCurrentDate(){
	time_t temp = time(NULL);
	int yearMonthDay;
	tm* currentTime; 
	currentTime = localtime(&temp);
	int day = currentTime ->tm_mday;
	int month = currentTime ->tm_mon;
	int year = currentTime ->tm_year + CONSTANT_START_YEAR;
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

int Executor::determineTaskId()
{
	return retrieveCurrentDate();
}