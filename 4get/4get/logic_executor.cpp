#include "logic_executor.h"

const int Executor::CONSTANT_MULTIPLIER_YEAR = 1000000;
const int Executor::CONSTANT_MULTIPLIER_MONTH = 10000;
const int Executor::CONSTANT_MULTIPLIER_DAY = 100;
const int Executor::CONSTANT_MONTH_ONE = 1;

Executor::Executor(){

	taskID = retrieveCurrentDate();
	tasks.loadFromFile();

}
bool Executor::receive(string usercommand, vector<string> vectorOfInputs)
{

	//storeCommands(usercommand);
	Command commandType = determineCommandType(usercommand);
	storeCommands(commandType);          //to store the commands into the stack of commands
	switch(commandType)
	{
	case commandAdd:
		return adderFunction(vectorOfInputs);
	case commandDelete:
		return deleteFunction(vectorOfInputs);
	case commandMark:
		return markFunction(vectorOfInputs);
	case commandModify:
		return modifyFunction(vectorOfInputs);
	case commandUndo:
		return undoFunction();
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
	else if(isEqual(commandTypeString, COMMAND_MODIFY))
		return Command::commandModify;
	else if(isEqual(commandTypeString, COMMAND_UNDO))
		return Command::commandUndo;
	else
		return Command::commandInvalid;
}
bool Executor::adderFunction(vector<string> vectorOfInputs)
{
	long long id;
	string description, location;
	tm *reminderTime, *startTime, *endTime;
	RepeatType repeat;
	Priority priority;
	Status status;

	id = taskID;
	taskID++;
	description = vectorOfInputs[SLOT_DESCRIPTION];
	location = vectorOfInputs[SLOT_LOCATION];
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
	storeTask(*taskGlobal);
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
	vector<string> vectorOfInputs(SLOT_SIZE);
	parser.parseInput(task, (vectorOfInputs));
	receive(vectorOfInputs[SLOT_COMMAND], vectorOfInputs);
}
void Executor::loadListOfTasks()
{
	tasks.loadFromFile();	
}
bool Executor::deleteFunction(vector<string> vectorOfInputs)
{
	int deleteNumber;
	deleteNumber = convert.convertStringToInt(vectorOfInputs[SLOT_SLOT_NUMBER]);
	storeTask(*tasks.obtainTask(deleteNumber));
	tasks.deleteFromList(deleteNumber);
	return true;
}
bool Executor::markFunction(vector<string> vectorOfInputs){
	int markNumber;
	markNumber = convert.convertStringToInt(vectorOfInputs[SLOT_SLOT_NUMBER]);
	storeTask(*tasks.obtainTask(markNumber));
	tasks.markDone(markNumber);
	return true;
}
bool Executor::modifyFunction(vector<string> vectorOfInputs){
	Task* taskTemp;

	string description, location;
	tm *reminderTime, *startTime, *endTime;

	int modifyNumber;
	modifyNumber = convert.convertStringToInt(vectorOfInputs[SLOT_SLOT_NUMBER]);
	taskTemp = tasks.obtainTask(modifyNumber);

	description = vectorOfInputs[SLOT_DESCRIPTION];
	location = vectorOfInputs[SLOT_LOCATION];
	startTime = convert.convertStringToTm(vectorOfInputs[SLOT_START_TIME]);
	endTime = convert.convertStringToTm(vectorOfInputs[SLOT_END_TIME]);
	reminderTime = convert.convertStringToTm(vectorOfInputs[SLOT_REMIND_TIME]);
	if(!description.empty())
	{
		taskTemp->setTaskDescription(description);
	}
	if(!location.empty())
	{
		taskTemp->setTaskLocation(location);
	}
	if(!vectorOfInputs[SLOT_START_TIME].empty())
	{
		taskTemp->setTaskStart(startTime);
	}
	if(!vectorOfInputs[SLOT_END_TIME].empty())
	{
		taskTemp->setTaskEnd(endTime);
	} // need to change the tasktype if the user add endtime. eg. from floating to todo
	/*if(!vectorOfInputs[SLOT_REMIND_TIME].empty())
	{
	taskTemp->setTaskReminderTime(reminderTime);
	}*/
	return true;
}
bool Executor::addToTaskList(){
	tasks.addToList(*taskGlobal, listToDo);
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
bool Executor::storeTask(Task taskTemp)
{
	taskStack.push(taskTemp);
	return true;
}
bool Executor::storeCommands(Command command)
{
	commandStack.push(command);
	return true;
}
bool Executor::undoFunction(){

	Task taskTemp;
	Command commandType;
	bool flag = true;

	commandStack.pop();
	if(commandStack.empty())
		return false;
	commandType = commandStack.top();
	taskTemp = taskStack.top();

	switch(commandType)
	{
	case commandAdd: 
		tasks.deleteIDFromList(taskTemp.getTaskId());
		break;
	case commandDelete:
		tasks.addToList(taskTemp, listToDo);
		break;
	default:
		return false;
	}
	commandStack.pop();
	taskStack.pop();

	return true;
}
bool Executor::setListType(ListType uiListType)
{
	listType = uiListType;
	return true;
}





















