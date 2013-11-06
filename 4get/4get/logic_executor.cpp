#include "logic_executor.h"

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
	try{
		Command commandType = determineCommandType(usercommand);
		if(!(commandType == commandRedo || commandType == commandUndo)){
			storeIntoUndoCommandStack(commandType); 
			undoListTypeStack.push(listType);
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
		case commandShow:
			return searchFunction(vectorOfInputs);
		case commandShowAll:
			return showAllFunction();
		default: throw string(MESSAGE_ERROR_WRONG_KEYWORD);
		}
	}catch(string error){
		throw;
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
	else if(isEqual(commandTypeString, COMMAND_SHOW))
		return Command::commandShow;
	else if(isEqual(commandTypeString, COMMAND_SHOWALL))
		return Command::commandShowAll;
	else
		throw string(MESSAGE_ERROR_WRONG_KEYWORD);
}
list<Task*> Executor::getUpdatedList(ListType listType){
	return taskList.obtainList(listType);
}
bool Executor::adderFunction(vector<string> vectorOfInputs){
	try{
		long long id;
		string description, location;
		time_t reminderTime, startTime, endTime;
		RepeatType repeat;
		Priority priority;
		TaskType taskTypeToCreate;

		id = retrieveTaskID();
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
			assert(taskGlobal != NULL);
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
			assert(taskGlobal != NULL);
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
			assert(taskGlobal != NULL);
		}
		else{
			throw string(Message::MESSAGE_ERROR_COMMAND_ADD);
		}
		storeIntoUndoTaskStack(*taskGlobal);
		taskList.addToList(taskGlobal, listToDo);
		return true;
	}catch(string error){
		throw;
	}
}
bool Executor::deleteFunction(vector<string> vectorOfInputs){
	try{
		int deleteStartNumber,
			deleteEndNumber,
			deleteSize;
		deleteStartNumber = convert.convertStringToInt(vectorOfInputs[SLOT_SLOT_START_NUMBER]);
		if (deleteStartNumber < 1){
			throw string(MESSAGE_ERROR_COMMAND_DELETE);
		}
		if(!vectorOfInputs[SLOT_SLOT_END_NUMBER].empty()){
			deleteEndNumber = convert.convertStringToInt(vectorOfInputs[SLOT_SLOT_END_NUMBER]);
		}
		if(!vectorOfInputs[SLOT_SLOT_END_NUMBER].empty()){
			if(deleteEndNumber > deleteStartNumber){
				deleteSize = getSizeFunction(deleteStartNumber, deleteEndNumber);
				undoDeleteNumberStack.push(deleteSize);
			}
			else if(deleteEndNumber < deleteStartNumber){
				deleteSize = swapValueAndGetSizeFunction(deleteStartNumber, deleteEndNumber);
				undoDeleteNumberStack.push(deleteSize);
			}
		}
		if(!vectorOfInputs[SLOT_SLOT_END_NUMBER].empty()){
			for(int i = 0; i < deleteSize ; i++){
				if(deleteStartNumber < deleteEndNumber){
					helperDeleteFunction(deleteStartNumber);
				}
				else if(deleteEndNumber < deleteStartNumber){
					helperDeleteFunction(deleteEndNumber);
				}
			}
		}
		else{
			helperDeleteFunction(deleteStartNumber);
		}
		return true;
	}catch(string error){
		throw;
	}
}
bool Executor::markFunction(vector<string> vectorOfInputs){
	try{
		int markStartNumber,
			markEndNumber,
			markSize;
		markStartNumber = convert.convertStringToInt(vectorOfInputs[SLOT_SLOT_START_NUMBER]);
		if(markStartNumber < 1){
			throw string(MESSAGE_ERROR_COMMAND_MARK);
		}
		if(!vectorOfInputs[SLOT_SLOT_END_NUMBER].empty()){
			markEndNumber = convert.convertStringToInt(vectorOfInputs[SLOT_SLOT_END_NUMBER]);
		}
		if(!vectorOfInputs[SLOT_SLOT_END_NUMBER].empty()){
			if(markEndNumber > markStartNumber){
				markSize = getSizeFunction(markStartNumber, markEndNumber);
				undoMarkNumberStack.push(markSize);
			}
			else if(markEndNumber < markStartNumber){
				markSize = swapValueAndGetSizeFunction(markStartNumber, markEndNumber);
				undoMarkNumberStack.push(markSize);
			}
		}
		if(!vectorOfInputs[SLOT_SLOT_END_NUMBER].empty()){
			for(int i = 0; i < markSize ; i++){
				if(markStartNumber < markEndNumber){
					helperMarkFunction(markStartNumber);
				}
				else if(markEndNumber < markStartNumber){
					helperMarkFunction(markEndNumber);
				}
			}
		}
		else{
			helperMarkFunction(markStartNumber);
		}
		return true;
	}catch (string errorStr){
		throw;
	}
}
bool Executor::modifyFunction(vector<string> vectorOfInputs){
	try{
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

		modifyNumber = convert.convertStringToInt(vectorOfInputs[SLOT_SLOT_START_NUMBER]);
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
		if(!vectorOfInputs[SLOT_PRIORITY].empty())
		{
			taskTemp->setTaskPriority(priority);
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
			taskList.deleteIDFromList(id, listType,true);
			taskList.addToList(taskNew, listType);
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
			taskList.deleteIDFromList(id, listType, true);
			taskList.addToList(taskNew, listType);
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
			taskList.deleteIDFromList(id, listType, true);
			taskList.addToList(taskNew, listType);
		}
		return true;
	}catch(string error){
		throw;
	}
}
bool Executor::undoFunction(){
	try{
		Task taskTemp;
		Command commandType;
		Task* taskPtrToAdd;
		ListType undoListType;
		int deleteSize = 0;
		int markSize = 0;

		if(undoCommandStack.empty()){
			throw string(MESSAGE_ERROR_COMMAND_UNDO);
		}
		commandType = undoCommandStack.top();
		if(undoListTypeStack.empty()){
			throw string(MESSAGE_ERROR_COMMAND_UNDO);
		}
		undoListType = undoListTypeStack.top();
		if((commandType != commandDelete) && (commandType != commandMark)){
			taskTemp = undoTaskStack.top();
			taskPtrToAdd = createTaskPtr(taskTemp);
		}

		storeIntoRedoCommandStack(commandType);
		if((commandType != commandModify) && (commandType != commandDelete) && (commandType != commandMark)){
			storeIntoRedoTaskStack(taskTemp);
		}
		if(commandType == commandDelete && !undoDeleteNumberStack.empty()){
			deleteSize = undoDeleteNumberStack.top();
		}
		if(commandType == commandMark && !undoMarkNumberStack.empty()){
			markSize = undoMarkNumberStack.top();
		}
		switch(commandType)
		{
		case commandAdd:
			taskList.deleteIDFromList(taskTemp.getTaskId(), undoListType, true);
			undoTaskStack.pop();
			break;
		case commandDelete:
			if(deleteSize == 0){
				taskTemp = undoTaskStack.top();
				storeIntoRedoTaskStack(taskTemp);
				taskPtrToAdd = createTaskPtr(taskTemp);
				taskList.addToList(taskPtrToAdd, undoListType);
				undoTaskStack.pop();
			}
			else if(deleteSize != 0){
				redoDeleteNumberStack.push(deleteSize);
				while(deleteSize != 0){
					taskTemp = undoTaskStack.top();
					storeIntoRedoTaskStack(taskTemp);
					taskPtrToAdd = createTaskPtr(taskTemp);
					taskList.addToList(taskPtrToAdd, undoListType);
					undoTaskStack.pop();
					deleteSize--;
				}
				undoDeleteNumberStack.pop();
			}
			break;
		case commandMark:
			if(markSize == 0){
				taskTemp = undoTaskStack.top();
				storeIntoRedoTaskStack(taskTemp);
				taskPtrToAdd = createTaskPtr(taskTemp);
				taskList.deleteIDFromList(taskTemp.getTaskId(), listCompleted, true);
				taskList.addToList(taskPtrToAdd, undoListType);
				undoTaskStack.pop();
			}
			else if(markSize != 0){
				redoMarkNumberStack.push(markSize);
				while(markSize != 0){
					taskTemp = undoTaskStack.top();
					storeIntoRedoTaskStack(taskTemp);
					taskPtrToAdd = createTaskPtr(taskTemp);
					taskList.deleteIDFromList(taskTemp.getTaskId(), listCompleted, true);
					taskList.addToList(taskPtrToAdd, undoListType);
					undoTaskStack.pop();
					markSize--;
				}
				undoMarkNumberStack.pop();
			}
			break;
		case commandModify:
			storeIntoRedoTaskStack(*taskList.obtainTask(taskTemp.getTaskId(), listType));  //get the task currently in the list
			taskList.deleteIDFromList(taskTemp.getTaskId(), listType, true);     //delete away the task current in the list
			taskList.addToList(taskPtrToAdd, undoListType);								//add the task.
			undoTaskStack.pop();
			break;
		default:
			throw string(MESSAGE_ERROR_COMMAND_UNDO);
		}
		undoCommandStack.pop();
		redoListTypeStack.push(undoListType);
		undoListTypeStack.pop();
		return true;
	}catch(string error){
		throw;
	}
}
bool Executor::redoFunction(){
	try{
		Task taskTemp;
		Task taskUndo;
		Command commandType;
		Task* taskPtrToAdd;
		int deleteSize = 0;
		int markSize = 0;
		ListType redoListType;

		if(redoCommandStack.empty()){
			throw string(MESSAGE_ERROR_COMMAND_REDO);
		}
		commandType = redoCommandStack.top();
		if(redoListTypeStack.empty()){
			throw string(MESSAGE_ERROR_COMMAND_REDO);
		}
		redoListType = redoListTypeStack.top();
		if(commandType == commandDelete && !redoDeleteNumberStack.empty()){
			deleteSize = redoDeleteNumberStack.top();
			if(deleteSize != 0){
				undoDeleteNumberStack.push(deleteSize);
			}
		}
		if(commandType == commandMark && !redoMarkNumberStack.empty()){
			markSize = redoMarkNumberStack.top();
			if(markSize != 0){
				undoMarkNumberStack.push(markSize);
			}
		}
		switch(commandType)
		{
		case commandAdd:
			taskTemp = redoTaskStack.top();
			taskPtrToAdd = createTaskPtr(taskTemp);
			taskList.addToList(taskPtrToAdd, redoListType);
			storeIntoUndoTaskStack(taskTemp);
			redoTaskStack.pop();
			break;
		case commandDelete:
			if(deleteSize == 0){
				taskTemp = redoTaskStack.top();
				taskList.deleteIDFromList(taskTemp.getTaskId(), redoListType, true);
				storeIntoUndoTaskStack(taskTemp);
				redoTaskStack.pop();
			}
			else if(deleteSize != 0){
				while(deleteSize != 0)
				{
					taskTemp = redoTaskStack.top();
					taskList.deleteIDFromList(taskTemp.getTaskId(), redoListType, true);
					storeIntoUndoTaskStack(taskTemp);
					redoTaskStack.pop();
					deleteSize--;
				}
				redoDeleteNumberStack.pop();
			}
			break;
		case commandMark:
			if(markSize == 0){
				taskTemp = redoTaskStack.top();
				taskPtrToAdd = createTaskPtr(taskTemp);
				taskList.addToList(taskPtrToAdd, listCompleted);
				taskList.deleteIDFromList(taskTemp.getTaskId(), redoListType, true);
				storeIntoUndoTaskStack(taskTemp);
				redoTaskStack.pop();
			}
			else if(markSize != 0){
				while(markSize != 0)
				{
					taskTemp = redoTaskStack.top();
					taskPtrToAdd = createTaskPtr(taskTemp);
					taskList.addToList(taskPtrToAdd, listCompleted);
					taskList.deleteIDFromList(taskTemp.getTaskId(), redoListType, true);
					storeIntoUndoTaskStack(taskTemp);
					redoTaskStack.pop();
					markSize--;
				}
				redoMarkNumberStack.pop();
			}
			/*taskTemp = redoTaskStack.top();
			taskPtrToAdd = createTaskPtr(taskTemp);
			taskList.addToList(taskPtrToAdd, listCompleted);
			taskList.deleteIDFromList(taskTemp.getTaskId(), redoListType, true);
			storeIntoUndoTaskStack(taskTemp);
			redoTaskStack.pop();*/
			break;
		case commandModify:
			taskTemp = redoTaskStack.top();
			taskPtrToAdd = createTaskPtr(taskTemp);
			storeIntoUndoTaskStack(*taskList.obtainTask(taskTemp.getTaskId(), redoListType));
			taskList.deleteIDFromList(taskTemp.getTaskId(), redoListType, true);
			taskList.addToList(taskPtrToAdd, redoListType);
			redoTaskStack.pop();
			break;
		default:
			throw string(MESSAGE_ERROR_NOTHING_TO_REDO);
		}
		storeIntoUndoCommandStack(commandType);
		redoCommandStack.pop();
		undoListTypeStack.push(redoListType);
		redoListTypeStack.pop();
		return true;
	}catch(string error){
		throw;
	}
}
bool Executor::searchFunction(vector<string> vectorOfInputs){
	try{
		string searchDescription,
			searchLocation;
		time_t searchStartT,
			searchEndT;


		searchDescription =  vectorOfInputs[SLOT_DESCRIPTION];
		searchLocation = vectorOfInputs[SLOT_LOCATION];
		searchStartT = convert.convertStringToTime(vectorOfInputs[SLOT_START_DATE], vectorOfInputs[SLOT_START_TIME]);
		searchEndT = convert.convertStringToTime(vectorOfInputs[SLOT_END_DATE], vectorOfInputs[SLOT_END_TIME]);

		if(!vectorOfInputs[SLOT_DESCRIPTION].empty()){
			taskList.searchDescription(searchDescription);
		}
		if(!vectorOfInputs[SLOT_LOCATION].empty()){
			taskList.searchLocation(searchLocation);
		}
		if(!vectorOfInputs[SLOT_START_TIME].empty() && !vectorOfInputs[SLOT_START_DATE].empty()){
			taskList.searchStart(searchStartT);
		}
		else if(vectorOfInputs[SLOT_START_TIME].empty() && !vectorOfInputs[SLOT_START_DATE].empty()){
			taskList.searchStartDate(searchStartT);
		}
		else if(!vectorOfInputs[SLOT_START_TIME].empty() && vectorOfInputs[SLOT_START_DATE].empty()){
			taskList.searchStartTime(searchStartT);
		}

		if(!vectorOfInputs[SLOT_END_TIME].empty() && !vectorOfInputs[SLOT_END_DATE].empty()){
			taskList.searchEnd(searchEndT);
		}
		else if(vectorOfInputs[SLOT_END_TIME].empty() && !vectorOfInputs[SLOT_END_DATE].empty()){
			taskList.searchEndDate(searchEndT);
		}
		else if(!vectorOfInputs[SLOT_END_TIME].empty() && vectorOfInputs[SLOT_END_DATE].empty()){
			taskList.searchEndTime(searchEndT);
		}

		return true;
	}catch(string error){
		throw;
	}
}
bool Executor::showAllFunction(){
	try{
		taskList.turnOffFilter();
		return true;
	}catch(string error){
		throw;
	}
}
bool Executor::isEqual(string str1, const string str2){
	try{
		if(str1 == str2){
			return true;
		}
		return false;
	}catch(string error){
		throw;
	}
}
long long Executor::retrieveTaskID(){
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
								 try{
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
								 }catch(string error){
									 throw;
								 }
}
void Executor::assertNotEmptyTask(){
	assert(taskGlobal != NULL);
}
Task* Executor::createTaskPtr(Task taskToCreate){
	try{
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
	}catch(string error){
		throw;
	}
}
bool Executor::helperDeleteFunction(int deleteStartNumber){
	try{
		Task taskTemp;
		taskTemp = *taskList.obtainTask(deleteStartNumber);
		storeIntoUndoTaskStack(taskTemp);
		taskList.deleteFromList(deleteStartNumber, true);
		return true;
	}catch(string error){
		throw;
	}
}
void Executor::helperMarkFunction(int markStartNumber){
	try{
		Task taskTemp;
		taskTemp = *taskList.obtainTask(markStartNumber);
		storeIntoUndoTaskStack(taskTemp);
		taskList.markDone(markStartNumber);
	}catch(string error){
		throw;
	}
}
void Executor::refreshAll(){
	try{
		taskList.refreshAll(convert.getNow());
	}catch (string Error){
		throw;
	}
}
int Executor::swapValueAndGetSizeFunction(int start, int end){
	int temp,
		size;

	temp = end;
	end = start;
	start = temp;
	return size = end - start + 1;
}
int Executor::getSizeFunction(int start, int end){
	int size;
	return size = end - start + 1;
}