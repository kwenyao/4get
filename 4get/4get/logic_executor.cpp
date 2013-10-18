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
	case commandRedo:
		return redoFunction();
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
	else if(isEqual(commandTypeString, COMMAND_REDO))
		return Command::commandRedo;
	else
		return Command::commandInvalid;
}
list<Task> Executor::getUpdatedList(ListType listType){
	return taskList.obtainList(listType);
}
bool Executor::adderFunction(vector<string> vectorOfInputs){
	long long id;
	string description, location;
	time_t reminderTime, startTime, endTime;
	time_t timeStart, timeEnd;
	RepeatType repeat;
	Priority priority;
	Status status = statusNone;
	TaskType taskTypeToCreate;
	string startDatet, startTimet, endDatet, endTimet; 

	startDatet = vectorOfInputs[SLOT_START_DATE];
	startTimet = vectorOfInputs[SLOT_START_TIME];
	endDatet = vectorOfInputs[SLOT_END_DATE];
	endTimet = vectorOfInputs[SLOT_END_TIME];

	id = taskID;
	description = vectorOfInputs[SLOT_DESCRIPTION];
	location = vectorOfInputs[SLOT_LOCATION];
	priority = convert.convertStringToPriority(vectorOfInputs[SLOT_PRIORITY]);
	repeat = convert.convertStringToRepeatType(vectorOfInputs[SLOT_REPEAT]);
	startTime = convert.convertStringToTime(startDatet, startTimet);
	endTime = convert.convertStringToTime(endDatet, endTimet);
	reminderTime = convert.convertStringToTime(vectorOfInputs[SLOT_REMIND_DATE], vectorOfInputs[SLOT_REMIND_TIME]);
	taskTypeToCreate = convert.convertStringToTime(startDatet, 
		startTimet, 
		endDatet, 
		endTimet, 
		timeStart, 
		timeEnd);

	taskID++;

	if(taskTypeToCreate == floating){
		TaskFloating newTask(id,
			description,
			location,
			reminderTime,
			priority,
			status);

		taskGlobal = new TaskFloating;
		*taskGlobal = newTask;
	}

	else if(taskTypeToCreate == deadline){
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

	else if(taskTypeToCreate == timed){
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
	else{
		throw string(Message::MESSAGE_ERROR_COMMAND_ADD);
	}

	storeTask(*taskGlobal);
	taskList.addToList(*taskGlobal, listType);
	return true;
}
bool Executor::deleteFunction(vector<string> vectorOfInputs){
	int deleteNumber;
	deleteNumber = convert.convertStringToInt(vectorOfInputs[SLOT_SLOT_NUMBER]);
	try{
		storeTask(*taskList.obtainTask(deleteNumber));
		taskList.deleteFromList(deleteNumber);
	} catch (string errorStr){
		throw;
	}
	return true;
}
bool Executor::markFunction(vector<string> vectorOfInputs){
	int markNumber;
	markNumber = convert.convertStringToInt(vectorOfInputs[SLOT_SLOT_NUMBER]);
	try{
		storeTask(*taskList.obtainTask(markNumber));
		taskList.markDone(markNumber);
	}catch (string errorStr){
		throw;
	}
	return true;
}
bool Executor::modifyFunction(vector<string> vectorOfInputs){
	Task* taskTemp;
	Task taskModified;
	string description, 
		location;
	time_t reminderTime, 
		startTime, 
		endTime;
	int modifyNumber;

	modifyNumber = convert.convertStringToInt(vectorOfInputs[SLOT_SLOT_NUMBER]);
	taskTemp = taskList.obtainTask(modifyNumber);
	storeTask(*taskTemp);

	description = vectorOfInputs[SLOT_DESCRIPTION];
	location = vectorOfInputs[SLOT_LOCATION];
	startTime = convert.convertStringToTime(vectorOfInputs[SLOT_START_DATE], vectorOfInputs[SLOT_START_TIME]);
	endTime = convert.convertStringToTime(vectorOfInputs[SLOT_END_DATE], vectorOfInputs[SLOT_END_TIME]);
	reminderTime = convert.convertStringToTime(vectorOfInputs[SLOT_REMIND_DATE], vectorOfInputs[SLOT_REMIND_TIME]);

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
		try{
			taskList.deleteIDFromList(id, listToDo);
			taskList.addToList(taskTemp, listToDo);
		} catch(string error){
			throw;
		}
	} 
	if(!vectorOfInputs[SLOT_REMIND_TIME].empty())
	{
		taskTemp->setTaskReminder(reminderTime);
	}
	redoModifiedTaskStack.push(*taskTemp);
	return true;
}
bool Executor::undoFunction(){
	Task taskTemp;
	Command commandType;

	undoCommandStack.pop();
	if(undoCommandStack.empty()){
		return false;
	}

	commandType = undoCommandStack.top();
	taskTemp = undoTaskStack.top();
	redoCommandStack.push(commandType);
	redoTaskStack.push(taskTemp);

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
	undoCommandStack.pop();
	undoTaskStack.pop();

	return true;
}
bool Executor::redoFunction(){
	Task taskTemp;
	Command commandType;

	if(redoCommandStack.empty()){
		return false;
	}

	commandType = redoCommandStack.top();
	switch(commandType)
	{
	case commandAdd:{
		taskTemp = redoTaskStack.top();
		taskList.addToList(taskTemp, listType);
		break;
					}
	case commandDelete:{
		taskTemp = redoTaskStack.top();
		taskList.deleteIDFromList(taskTemp.getTaskId(), listType);
		break;
					   }
	case commandMark:{
		taskTemp = redoTaskStack.top();
		/*taskList.markDone(taskTemp.getTaskId());*/
		taskList.addToList(taskTemp, listCompleted);
		taskList.deleteIDFromList(taskTemp.getTaskId(), listToDo);
		break;
					 }
	case commandModify:{
		taskTemp = redoModifiedTaskStack.top();
		taskList.addToList(taskTemp, listType);
		taskList.deleteIDFromList(taskTemp.getTaskId(), listType);
		redoModifiedTaskStack.pop();
		break;
					   }
	default:
		throw string("error");
	}
	redoCommandStack.pop();
	redoTaskStack.pop();
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
	undoTaskStack.push(taskTemp);
	return true;
}
bool Executor::storeCommands(Command command){
	undoCommandStack.push(command);
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