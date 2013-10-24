#include "logic_executor.h"

const int Executor::CONSTANT_MULTIPLIER_YEAR = 1000000;
const int Executor::CONSTANT_MULTIPLIER_MONTH = 10000;
const int Executor::CONSTANT_MULTIPLIER_DAY = 100;
const int Executor::CONSTANT_MONTH_ONE = 1;

Executor::Executor(){}
bool Executor::stringCollector(string task){
	try{
		vector<string> vectorOfInputs(SLOT_SIZE);
		parser.parseInput(task, (vectorOfInputs));
		if(receive(vectorOfInputs[SLOT_COMMAND], vectorOfInputs)){
			logging("Number of times UI call stringCollector", Info, Pass);
			return true;
		}
		else{ 
			return false;
		}
	}catch(string Error){
		throw;
	}
}
bool Executor::receive(string usercommand, vector<string> vectorOfInputs){
	Command commandType = determineCommandType(usercommand);
	if(!(commandType == commandRedo || commandType == commandUndo)){
		storeIntoUndoCommandStack(commandType); 
	}
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
	default: throw string(MESSAGE_ERROR_WRONG_KEYWORD);
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
		throw string(MESSAGE_ERROR_WRONG_KEYWORD);
}
list<Task*> Executor::getUpdatedList(ListType listType){
	return taskList.obtainList(listType);
}
bool Executor::adderFunction(vector<string> vectorOfInputs){
	long long id;
	string description, location;
	time_t reminderTime, startTime, endTime;
	RepeatType repeat;
	Priority priority;
	TaskType taskTypeToCreate;

	id = retrieveID();
	setParameters(description,
		location,
		priority,
		repeat,
		startTime,
		endTime,
		reminderTime,
		taskTypeToCreate,
		vectorOfInputs);

	if(taskTypeToCreate == floating){
		TaskFloating newTask(id,
			description,
			location,
			reminderTime,
			priority);

		taskGlobal = new TaskFloating;
		*taskGlobal = newTask;
	}

	else if(taskTypeToCreate == deadline){
		TaskDeadline newTask(id,
			description, 
			location, 
			reminderTime, 
			priority,  
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
			repeat, 
			startTime, 
			endTime);

		taskGlobal = new TaskTimed;
		*taskGlobal = newTask;
	}
	else{
		throw string(Message::MESSAGE_ERROR_COMMAND_ADD);
	}

	storeIntoUndoTaskStack(*taskGlobal);
	taskList.addToList(taskGlobal, listType);
	return true;
}
bool Executor::deleteFunction(vector<string> vectorOfInputs){
	int deleteNumber;
	deleteNumber = convert.convertStringToInt(vectorOfInputs[SLOT_SLOT_NUMBER]);
	if(deleteNumber < 1){
		throw string(MESSAGE_ERROR_COMMAND_DELETE);
	}

	try{
		storeIntoUndoTaskStack(*taskList.obtainTask(deleteNumber));
		taskList.deleteFromList(deleteNumber, true);
	} catch (string errorStr){
		throw;
	}
	return true;
}
bool Executor::markFunction(vector<string> vectorOfInputs){
	int markNumber;
	markNumber = convert.convertStringToInt(vectorOfInputs[SLOT_SLOT_NUMBER]);
	if(markNumber < 1){
		throw string(MESSAGE_ERROR_COMMAND_MARK);
	}
	try{
		storeIntoUndoTaskStack(*taskList.obtainTask(markNumber));
		taskList.markDone(markNumber);
	}catch (string errorStr){
		throw;
	}
	return true;
}
bool Executor::modifyFunction(vector<string> vectorOfInputs){
	Task* taskTemp;
	Task* taskNew;
	Task taskModified;
	long long id;
	int modifyNumber;
	string description, 
		location;
	time_t reminderTime, 
		startTime, 
		endTime;
	Priority priority;
	RepeatType repeat;
	TaskType typeOfTask, typeOfOldTask;

	modifyNumber = convert.convertStringToInt(vectorOfInputs[SLOT_SLOT_NUMBER]);
	if(modifyNumber < 1){
		throw string(MESSAGE_ERROR_COMMAND_MODIFY);
	}
	taskTemp = taskList.obtainTask(modifyNumber);
	typeOfOldTask = taskTemp->getTaskType();
	storeIntoUndoTaskStack(*taskTemp);
	setParameters(description,
		location,
		priority,
		repeat,
		startTime,
		endTime,
		reminderTime,
		typeOfTask,
		vectorOfInputs);
	bool isNoEndTime = (endTime == 0);
	bool isNoStartTime = (startTime == 0);
	if(!description.empty()){
		taskTemp->setTaskDescription(description);
	}
	if(!location.empty()){
		taskTemp->setTaskLocation(location);
	}
	if(!vectorOfInputs[SLOT_REMIND_TIME].empty())
	{
		taskTemp->setTaskReminder(reminderTime);
	}
	if(!vectorOfInputs[SLOT_START_TIME].empty() || !vectorOfInputs[SLOT_START_DATE].empty()){
		taskTemp->setTaskStart(startTime);
	}
	//change floating to deadline task
	if(typeOfOldTask == floating && !isNoEndTime && isNoStartTime){
		id = taskTemp->getTaskId();									//set another task
		taskTemp->setTaskEnd(endTime);
		string description = taskTemp->getTaskDescription();
		string location = taskTemp->getTaskLocation();
		Priority priority = taskTemp->getTaskPriority();
		RepeatType repeat = taskTemp->getTaskRepeat();
		time_t reminderTime = taskTemp->getTaskReminder();
		taskNew = new TaskDeadline(id,
			description, 
			location, 
			reminderTime, 
			priority,
			repeat, 
			endTime);
		try{
			taskList.deleteIDFromList(id, listType,true);
			taskList.addToList(taskNew, listType);
		} catch(string error){
			throw;
		}
	}
	//change floating to timed task
	if(typeOfOldTask == floating && !isNoEndTime && !isNoStartTime){
		taskTemp->setTaskEnd(endTime);
		taskTemp->setTaskStart(startTime);
		id = taskTemp->getTaskId();
		string description = taskTemp->getTaskDescription();
		string location = taskTemp->getTaskLocation();
		Priority priority = taskTemp->getTaskPriority();
		RepeatType repeat = taskTemp->getTaskRepeat();
		time_t reminderTime = taskTemp->getTaskReminder();
		taskNew = new TaskTimed(id, 
			description, 
			location, 
			reminderTime, 
			priority,  
			repeat, 
			startTime, 
			endTime);
		try{
			taskList.deleteIDFromList(id, listType, true);
			taskList.addToList(taskNew, listType);
		} catch(string error){
			throw;
		}
	}
	//change deadline task to timed
	if(typeOfOldTask == deadline && !isNoStartTime){
		taskTemp->setTaskStart(startTime);
		id = taskTemp->getTaskId();
		string description = taskTemp->getTaskDescription();
		string location = taskTemp->getTaskLocation();
		Priority priority = taskTemp->getTaskPriority();
		RepeatType repeat = taskTemp->getTaskRepeat();
		time_t reminderTime = taskTemp->getTaskReminder();		
		taskNew = new TaskTimed(id, 
			description, 
			location, 
			reminderTime, 
			priority,  
			repeat, 
			startTime, 
			endTime);
		try{
			taskList.deleteIDFromList(id, listType, true);
			taskList.addToList(taskNew, listType);
		} catch(string error){
			throw;
		}
	}
	return true;
}
bool Executor::undoFunction(){
	Task taskTemp;
	Command commandType;
	Task* taskPtrToAdd;

	if(undoCommandStack.empty()){
		throw string(MESSAGE_ERROR_COMMAND_UNDO);
	}

	commandType = undoCommandStack.top();

	taskTemp = undoTaskStack.top();
	taskPtrToAdd = createTaskPtr(taskTemp);

	storeIntoRedoCommandStack(commandType);
	if(!(commandType == commandModify)){
		storeIntoRedoTaskStack(taskTemp);
	}

	switch(commandType)
	{
	case commandAdd:
		try{
			taskList.deleteIDFromList(taskTemp.getTaskId(), listType, true);
		}catch(string Error){
			throw;
		}
		break;
	case commandDelete:
		try{
			taskList.addToList(taskPtrToAdd, listType);
		}catch(string Error){
			throw;
		}
		break;
	case commandMark:
		try{
			taskList.deleteIDFromList(taskTemp.getTaskId(), listCompleted, true);
			taskList.addToList(taskPtrToAdd, listToDo);
		}catch(string Error){
			throw;
		}
		break;
	case commandModify:
		storeIntoRedoTaskStack(*taskList.obtainTask(taskTemp.getTaskId(), listType));  //get the task currently in the list
		try{
			taskList.deleteIDFromList(taskTemp.getTaskId(), listType, true);     //delete away the task current in the list
			taskList.addToList(taskPtrToAdd, listType);								//add the task.
		}catch(string Error){
			throw;
		}
		break;
	default:
		throw string(MESSAGE_ERROR_COMMAND_UNDO);
	}
	undoCommandStack.pop();
	undoTaskStack.pop();

	return true;
}
bool Executor::redoFunction(){
	Task taskTemp;
	Task taskUndo;
	Command commandType;
	Task* taskPtrToAdd;

	if(redoCommandStack.empty()){
		throw string(MESSAGE_ERROR_COMMAND_REDO);
	}
	commandType = redoCommandStack.top();
	taskTemp = redoTaskStack.top();
	switch(commandType)
	{
	case commandAdd:{
		taskPtrToAdd = createTaskPtr(taskTemp);
		try{	
			taskList.addToList(taskPtrToAdd, listType);
		}catch(string Error){
			throw;
		}
		storeIntoUndoTaskStack(taskTemp);
		break;
					}
	case commandDelete:{
		taskPtrToAdd = createTaskPtr(taskTemp);
		try{
			taskList.deleteIDFromList(taskTemp.getTaskId(), listType, true);
		}catch(string Error){
			throw;
		}
		storeIntoUndoTaskStack(taskTemp);
		break;
					   }
	case commandMark:{
		taskPtrToAdd = createTaskPtr(taskTemp);
		try{
			taskList.addToList(taskPtrToAdd, listCompleted);
			taskList.deleteIDFromList(taskTemp.getTaskId(), listToDo, true);
		}catch(string Error){
			throw;
		}
		storeIntoUndoTaskStack(taskTemp);
		break;
					 }
	case commandModify:{
		taskPtrToAdd = createTaskPtr(taskTemp);
		storeIntoUndoTaskStack(*taskList.obtainTask(taskTemp.getTaskId(), listType));
		try{
			taskList.deleteIDFromList(taskTemp.getTaskId(), listType, true);
			taskList.addToList(taskPtrToAdd, listType);
		}catch(string Error){
			throw;
		}
		break;
					   }
	default:
		throw string(MESSAGE_ERROR_NOTHING_TO_REDO);
	}
	storeIntoUndoCommandStack(commandType);
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
long long Executor::retrieveID(){
	time_t msec = time(NULL) * 1000;
	long long ID;

	return ID = time(&msec);
}
bool Executor::storeIntoUndoTaskStack(Task taskTemp){
	undoTaskStack.push(taskTemp);
	return true;
}
bool Executor::storeIntoUndoCommandStack(Command command){
	undoCommandStack.push(command);
	return true;
}
bool Executor::storeIntoRedoTaskStack(Task taskTemp){
	redoTaskStack.push(taskTemp);
	return true;
}
bool Executor::storeIntoRedoCommandStack(Command command){
	redoCommandStack.push(command);
	return true;
}
bool Executor::setListType(ListType uiListType)
{
	listType = uiListType;
	return true;
}
bool Executor::setParameters(string &description,
							 string &location,
							 Priority &priority,
							 RepeatType &repeat,
							 time_t &startTime,
							 time_t &endTime,
							 time_t &reminderTime,
							 TaskType &typeOfTask,
							 vector<string> &vectorOfInputs){
	string descriptionSlot,
		   locationSlot,
		   prioritySlot,
	       repeatSlot,
		   startDateSlot,
		   startTimeSlot, 
		   endDateSlot, 
		   endTimeSlot, 
		   reminderDateSlot, 
		   reminderTimeSlot;

		   descriptionSlot = vectorOfInputs[SLOT_DESCRIPTION];
		   locationSlot = vectorOfInputs[SLOT_LOCATION];
		   prioritySlot = vectorOfInputs[SLOT_PRIORITY];
		   repeatSlot = vectorOfInputs[SLOT_REPEAT];
		   startDateSlot = vectorOfInputs[SLOT_START_DATE];
		   startTimeSlot = vectorOfInputs[SLOT_START_TIME];
		   endDateSlot = vectorOfInputs[SLOT_END_DATE];
		   endTimeSlot = vectorOfInputs[SLOT_END_TIME];
		   reminderDateSlot = vectorOfInputs[SLOT_REMIND_DATE];
		   reminderTimeSlot = vectorOfInputs[SLOT_REMIND_TIME];
								 
		   description = descriptionSlot;
		   location = locationSlot;
		   priority = convert.convertStringToPriority(prioritySlot);
		   repeat = convert.convertStringToRepeatType(repeatSlot);
		   reminderTime = convert.convertStringToTime(reminderDateSlot, reminderTimeSlot);
		   typeOfTask = convert.convertStringToTime(startDateSlot, 
			                                        startTimeSlot, 
									                endDateSlot, 
									                endTimeSlot, 
									                startTime, 
									                endTime);
		   return true;
}
void Executor::assertNotEmptyTask(){
	assert(taskGlobal != NULL);
}

Task Executor::tempTaskCreator(Task* task)
{
	long long id;
	string description, location;
	time_t reminderTime, startTime, endTime;
	RepeatType repeat;
	Priority priority;
	TaskType taskType;

	id = task -> getTaskId();
	description = task -> getTaskDescription();
	location = task -> getTaskLocation();
	reminderTime = task -> getTaskReminder();
	startTime = task -> getTaskStart();
	endTime = task -> getTaskEnd();
	repeat = task -> getTaskRepeat();
	priority = task -> getTaskPriority();
	taskType = task -> getTaskType();

	if(taskType == floating){
		TaskFloating newTask(id,
			description,
			location,
			reminderTime,
			priority);
		return newTask;
	}
	else if(taskType == deadline){
		TaskDeadline newTask(id,
			description, 
			location, 
			reminderTime, 
			priority,  
			repeat, 
			endTime); 
		return newTask;
	}
	else if(taskType == timed){
		TaskTimed newTask(id, 
			description, 
			location, 
			reminderTime, 
			priority, 
			repeat, 
			startTime, 
			endTime);
		return newTask;
	}
	else{
		throw string(Message::MESSAGE_ERROR_COMMAND_ADD);
	}

}
Task* Executor::createTaskPtr(Task taskToCreate){
	Task* taskPtr;
	TaskType taskType = taskToCreate.getTaskType();
	long long ID = taskToCreate.getTaskId();
	string desc = taskToCreate.getTaskDescription();
	string location = taskToCreate.getTaskLocation();
	Priority priority = taskToCreate.getTaskPriority();
	time_t reminderTime = taskToCreate.getTaskReminder();
	//deadline variable
	time_t endTime = taskToCreate.getTaskEnd();
	RepeatType repeat = taskToCreate.getTaskRepeat();
	time_t nextOccurance = taskToCreate.getTaskNextOccurance();
	//timed variable
	time_t startTime = taskToCreate.getTaskStart();

	if(taskType == floating){
		taskPtr = new TaskFloating(ID);
		taskPtr->setTaskDescription(desc);
		taskPtr->setTaskLocation(location);
		taskPtr->setTaskPriority(priority);
		taskPtr->setTaskReminder(reminderTime);
		return taskPtr;
	}
	else if(taskType == deadline){
		taskPtr = new TaskDeadline(ID);
		taskPtr->setTaskDescription(desc);
		taskPtr->setTaskLocation(location);
		taskPtr->setTaskPriority(priority);
		taskPtr->setTaskReminder(reminderTime);
		taskPtr->setTaskEnd(endTime);
		taskPtr->setTaskRepeat(repeat);
		taskPtr->setTaskNextOccurance(nextOccurance);
		return taskPtr;
	}
	else if(taskType == timed){
		taskPtr = new TaskTimed(ID);
		taskPtr->setTaskDescription(desc);
		taskPtr->setTaskLocation(location);
		taskPtr->setTaskPriority(priority);
		taskPtr->setTaskReminder(reminderTime);
		taskPtr->setTaskEnd(endTime);
		taskPtr->setTaskRepeat(repeat);
		taskPtr->setTaskNextOccurance(nextOccurance);
		taskPtr->setTaskStart(startTime);
		return taskPtr;
	}
	else{
		throw string(MESSAGE_ERROR_INVALID_TASKTYPE);
	}
}