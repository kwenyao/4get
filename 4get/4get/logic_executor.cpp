#include "logic_executor.h"

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
	
	_task.setTaskDescription(vectorOfInputs[SLOT_DESCRIPTION]);
	_task.setTaskLocation(vectorOfInputs[SLOT_LOCATION]);
	_task.setTaskReminderTime(convertStringToTm());
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
tm* Executor::convertStringToTm()
{
	string date = vectorOfInputs[SLOT_REMIND_TIME];
	string day, month, year;
	int dayInt=0, monthInt=0, yearInt=0;
	struct tm* remindTime;

	remindTime = new struct tm;

	if(date == ""){
		remindTime->tm_mday = dayInt;
		remindTime->tm_mon = monthInt;
		remindTime ->tm_year = yearInt;
		return remindTime;
	}

	day += date[0];			//enter date format as dd/m/yy for now..
	day += date[1];
	month += date[3];
	year += date[5];
	year += date[6];

	stringstream sd(day);
	sd >> dayInt;
	stringstream sm(month);
	sm >> monthInt;
	stringstream sy(year);
	sy >> yearInt;

	remindTime ->tm_mday = dayInt;
	remindTime ->tm_mon = monthInt;
	remindTime ->tm_year = yearInt;

	return remindTime;
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
	tasks.addToList(_task, listToDo);
	return true;
}
list<Task> Executor::getUpdatedList(){
	return tasks.obtainList(listToDo);
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
