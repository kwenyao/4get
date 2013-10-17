#include "logic_executor.h"

const int Executor::CONSTANT_MULTIPLIER_YEAR = 1000000;
const int Executor::CONSTANT_MULTIPLIER_MONTH = 10000;
const int Executor::CONSTANT_MULTIPLIER_DAY = 100;
const int Executor::CONSTANT_MONTH_ONE = 1;

Executor::Executor(){
	taskID = retrieveCurrentDate();
	taskList.loadFromFile();
}
void Executor::stringCollector(string task){
	vector<string> vectorOfInputs(SLOT_SIZE);
	parser.parseInput(task, (vectorOfInputs));
	receive(vectorOfInputs[SLOT_COMMAND], vectorOfInputs);
}
bool Executor::receive(string usercommand, vector<string> vectorOfInputs){
	Command commandType = determineCommandType(usercommand);
	storeCommands(commandType);          
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
Enum::Command Executor::determineCommandType (string commandTypeString){
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
list<Task> Executor::getUpdatedList(ListType listType){
	return taskList.obtainList(listType);
}
bool Executor::adderFunction(vector<string> vectorOfInputs){
	long long id;
	string description, location;
	tm *reminderTime, 
		*startTime, 
		*endTime;
	RepeatType repeat;
	Priority priority;
	Status status = statusNone;

	id = taskID;
	description = vectorOfInputs[SLOT_DESCRIPTION];
	location = vectorOfInputs[SLOT_LOCATION];
	priority = convert.convertStringToPriority(vectorOfInputs[SLOT_PRIORITY]);
	repeat = convert.convertStringToRepeatType(vectorOfInputs[SLOT_REPEAT]);
	startTime = convert.convertStringToTm(vectorOfInputs[SLOT_START_TIME]);
	endTime = convert.convertStringToTm(vectorOfInputs[SLOT_END_TIME]);
	reminderTime = convert.convertStringToTm(vectorOfInputs[SLOT_REMIND_TIME]);

	taskID++;

	if(vectorOfInputs[SLOT_END_TIME].empty()){
		TaskFloating newTask(id,
			description,
			location,
			reminderTime,
			priority,
			status);

		taskGlobal = new TaskFloating;
		*taskGlobal = newTask;
	}

	else if(vectorOfInputs[SLOT_START_TIME].empty()){
		TaskDeadline newTask(id,
			description, 
			location, 
			reminderTime, 
			priority, 
			status, 
			repeat, 
			endTime); 

		taskGlobal = new TaskDeadline;
		*taskGlobal = newTask;
	}

	else{
		TaskTimed newTask(id, 
			description, 
			location, 
			reminderTime, 
			priority, 
			status, 
			repeat, 
			startTime, 
			endTime);

		taskGlobal = new TaskTimed;
		*taskGlobal = newTask;
	}

	storeTask(*taskGlobal);
	taskList.addToList(*taskGlobal, listType);
	return true;
}
bool Executor::deleteFunction(vector<string> vectorOfInputs){
	int deleteNumber;
	deleteNumber = convert.convertStringToInt(vectorOfInputs[SLOT_SLOT_NUMBER]);
	storeTask(*taskList.obtainTask(deleteNumber));
	taskList.deleteFromList(deleteNumber);
	return true;
}
bool Executor::markFunction(vector<string> vectorOfInputs){
	int markNumber;
	markNumber = convert.convertStringToInt(vectorOfInputs[SLOT_SLOT_NUMBER]);
	storeTask(*taskList.obtainTask(markNumber));
	taskList.markDone(markNumber);
	return true;
}
bool Executor::modifyFunction(vector<string> vectorOfInputs){
	Task* taskTemp;
	string description, 
		location;
	tm *reminderTime, 
		*startTime, 
		*endTime;
	int modifyNumber;

	modifyNumber = convert.convertStringToInt(vectorOfInputs[SLOT_SLOT_NUMBER]);
	taskTemp = taskList.obtainTask(modifyNumber);
	storeTask(*taskTemp);

	description = vectorOfInputs[SLOT_DESCRIPTION];
	location = vectorOfInputs[SLOT_LOCATION];
	startTime = convert.convertStringToTm(vectorOfInputs[SLOT_START_TIME]);
	endTime = convert.convertStringToTm(vectorOfInputs[SLOT_END_TIME]);
	reminderTime = convert.convertStringToTm(vectorOfInputs[SLOT_REMIND_TIME]);

	if(!description.empty()){
		taskTemp->setTaskDescription(description);
	}
	if(!location.empty()){
		taskTemp->setTaskLocation(location);
	}
	if(!vectorOfInputs[SLOT_START_TIME].empty()){
		taskTemp->setTaskStart(startTime);
	}
	if(!vectorOfInputs[SLOT_END_TIME].empty()){    //unsure
		taskTemp->setTaskEnd(endTime);
		int id = taskTemp->getTaskId();
		Priority priority = taskTemp->getTaskPriority();
		Status status = taskTemp->getTaskStatus();
		RepeatType repeat = taskTemp->getTaskRepeat();
		TaskDeadline taskTemp(id,
			description, 
			location, 
			reminderTime, 
			priority, 
			status, 
			repeat, 
			endTime);
		taskList.deleteIDFromList(id, listToDo);
		taskList.addToList(taskTemp, listToDo);
	} 
	//if(!vectorOfInputs[SLOT_REMIND_TIME].empty())
	//{
	//taskTemp->setTaskReminderTime(reminderTime);
	//}
	return true;
}
bool Executor::undoFunction(){
	Task taskTemp;
	Command commandType;

	commandStack.pop();
	if(commandStack.empty()){
		return false;
	}

	commandType = commandStack.top();
	taskTemp = taskStack.top();

	switch(commandType)
	{
	case commandAdd: 
		taskList.deleteIDFromList(taskTemp.getTaskId(), listType);
		break;
	case commandDelete:
		taskList.addToList(taskTemp, listType);
		break;
	case commandMark:
		taskList.deleteIDFromList(taskTemp.getTaskId(), listCompleted);
		taskList.addToList(taskTemp, listToDo);
		break;
	case commandModify:
		taskList.deleteIDFromList(taskTemp.getTaskId(), listType);
		taskList.addToList(taskTemp, listType);
		break;
	default:
		return false;
	}
	commandStack.pop();
	taskStack.pop();

	return true;
}
bool Executor::isEqual(string str1, const string str2){
	if(str1 == str2){
		return true;
	}
	return false;
}
long long Executor::retrieveCurrentDate(){
	time_t timeTemp;
	long long yearMonthDay;
	tm* currentTime;

	time(&timeTemp);
	currentTime = localtime(&timeTemp);

	long long day = currentTime ->tm_mday;
	long long month = CONSTANT_MONTH_ONE + currentTime ->tm_mon;
	long long year = currentTime ->tm_year + CONSTANT_START_YEAR;

	day = day*CONSTANT_MULTIPLIER_DAY;
	month = month*CONSTANT_MULTIPLIER_MONTH;
	year = year*CONSTANT_MULTIPLIER_YEAR;
	yearMonthDay = (year + month + day);

	return yearMonthDay;
}
bool Executor::storeTask(Task taskTemp){
	taskStack.push(taskTemp);
	return true;
}
bool Executor::storeCommands(Command command){
	commandStack.push(command);
	return true;
}
bool Executor::setListType(ListType uiListType)
{
	listType = uiListType;
	return true;
}
void Executor::empty_task(){
	assert(taskGlobal != NULL);
}