#include "logic_executor.h"

using namespace std;

Executor::Executor(){}


bool Executor::receive(string usercommand, vector<string> parameter)
{
	Command commandType = determineCommandType(usercommand);

	switch(commandType)
	{
	case commandAdd:
		return adderFunction(vectorOfInputs);
	case commandDelete:
		return deleteFunction(tasks, vectorOfInputs);
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
bool Executor::adderFunction(vector<string>& vectorOfInputs)
{
	_task.setTaskDescription(vectorOfInputs[SLOT_DESCRIPTION]);
	_task.setTaskLocation(vectorOfInputs[SLOT_LOCATION]);
	_task.setTaskReminderTime(convertStringToTm(vectorOfInputs));
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
}
void Executor::loadListOfTasks()
{
	tasks.loadListFromFile();	
}
tm* Executor::convertStringToTm(vector<string> vectorOfInputs)
{
	string date = vectorOfInputs[SLOT_REMIND_TIME];
	string day, month, year;
	int dayInt, monthInt, yearInt;

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

	tm* remindTime;
	remindTime ->tm_mday = dayInt;
	remindTime ->tm_mon = monthInt;
	remindTime ->tm_year = yearInt;

	return remindTime;
}
bool Executor::deleteFunction(TaskList tasks, vector<string> vectorOfInputs)
{
	int deleteNumber;
	stringstream  slotNumber(vectorOfInputs[SLOT_SLOT_NUMBER]);
	slotNumber >> deleteNumber;
	tasks.deleteFromToDo(deleteNumber);
	return true;
}
bool Executor::addToTaskList()
{
	tasks.addToList(_task, listToDo);
	return true;
}
list<Task>* Executor::getUpdatedList(){
	return &tasks.obtainList(listToDo);
}

