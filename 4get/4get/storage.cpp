#include "storage.h"

const string Storage::FILENAME_TODO = "todo.txt";
const string Storage::FILENAME_COMPLETED = "completed.txt";
const string Storage::FILENAME_OVERDUE = "overdue.txt";

const string Storage::MARKER_TASK_BEGIN = "---------Task Begin---------";
const string Storage::MARKER_TASK_TYPE = "Task Type:";
const string Storage::MARKER_ID = "Task ID:";
const string Storage::MARKER_DESCRIPTION = "Description:";
const string Storage::MARKER_LOCATION = "Location:";
const string Storage::MARKER_START_TIME = "Start Time:";
const string Storage::MARKER_END_TIME = "End Time:";
const string Storage::MARKER_REPEAT = "Repeat:";
const string Storage::MARKER_NEXT_OCCURANCE = "Next Occurance:";
const string Storage::MARKER_PRIORITY = "Priority:";
const string Storage::MARKER_REMINDER_TIME = "Reminder Time:";
//const string Storage::MARKER_STATUS = "Status:";  //to be deleted if not used
const string Storage::MARKER_TASK_END = "---------Task End---------";
const string Storage::EMPTY_LINE = "";

const string Storage::TASK_TYPE_FLOATING = "floating";
const string Storage::TASK_TYPE_DEADLINE = "deadline";
const string Storage::TASK_TYPE_TIMED = "timed";

const string Storage::REPEAT_TYPE_DAILY = "daily";
const string Storage::REPEAT_TYPE_WEEKLY = "weekly";
const string Storage::REPEAT_TYPE_FORTNIGHTLY = "fortnightly";
const string Storage::REPEAT_TYPE_MONTHLY = "monthly";
const string Storage::REPEAT_TYPE_ANNUALLY = "annually";
const string Storage::REPEAT_TYPE_NONE = "no repeat";

const string Storage::PRIORITY_HIGH = "high";
const string Storage::PRIORITY_NORMAL = "normal";

Storage::Storage(){}

bool Storage::save(const list<Task>& list, ListType listType, int listSize){
	string fileName;
	fileName = determineFile(listType);
	writeFileSetup(fileName, ios_base::trunc);
	saveList(list);
	closeFileWrite();
	return true; 
}

void Storage::closeFileWrite(){
	_fileWrite.flush();
	_fileWrite.close();
}

bool Storage::saveList(const list<Task>& listToSave){
	list<Task>::const_iterator iterator;
	list<Task>::const_iterator endOfList;
	iterator = listToSave.begin();
	endOfList = listToSave.end();
	while(iterator != endOfList){
		saveTaskToFile(*iterator);	
		++iterator;
	}
	return true;
}

void Storage::saveTaskToFile(const Task& taskToSave){
	writeLine(MARKER_TASK_BEGIN);
	writeTaskAttributes(taskToSave);
	writeLine(MARKER_TASK_END);
	writeLine(EMPTY_LINE);
}

void Storage::writeTaskAttributes(const Task& task){
	TaskType taskType = task.getTaskType();
	bool isTimed = (taskType == timed);
	bool isDeadLineORTimed = (taskType == deadline) || isTimed;
	writeTaskType(task);
	writeID(task);
	writeDescription(task);
	writeLocation(task);
	writePriority(task);
	writeReminderTime(task);
	if(isDeadLineORTimed){
		writeEndTime(task);
		writeRepeat(task);
		writeNextOccurance(task);
	}
	if(isTimed)
		writeStartTime(task);
}

void Storage::writeTaskType(const Task& task){
	writeLine(MARKER_TASK_TYPE);
	writeLine(convertToStr(task.getTaskType()));
}

void Storage::writeID(const Task& task){
	writeLine(MARKER_ID);
	writeLine(convertToStr(task.getTaskId()));
}

void Storage::writeDescription(const Task& task){
	writeLine(MARKER_DESCRIPTION);
	writeLine(task.getTaskDescription());
}

void Storage::writeLocation(const Task& task){
	writeLine(MARKER_LOCATION);
	writeLine(task.getTaskLocation());
}

void Storage::writeStartTime(const Task& task){
	writeLine(MARKER_START_TIME);
	writeLine(convertToStr(task.getTaskStart()));
}

void Storage::writeEndTime(const Task& task){
	writeLine(MARKER_END_TIME);
	writeLine(convertToStr(task.getTaskEnd()));
}

void Storage::writeRepeat(const Task& task){
	writeLine(MARKER_REPEAT);
	writeLine(convertToStr(task.getTaskRepeat()));
}

void Storage::writeNextOccurance(const Task& task){
	writeLine(MARKER_NEXT_OCCURANCE);

}

void Storage::writePriority(const Task& task){
	writeLine(MARKER_PRIORITY);
	writeLine(convertToStr(task.getTaskPriority()));
}

void Storage::writeReminderTime(const Task& task){
	writeLine(MARKER_REMINDER_TIME);
	writeLine(convertToStr(task.getTaskReminder()));
}

void Storage::writeFileSetup(string fileName, ios_base::openmode mode){
	_fileWrite.open(fileName, mode);
}

string Storage::determineFile(ListType listType){
	switch (listType){
	case listToDo:
		return FILENAME_TODO;
	case listCompleted:
		return FILENAME_COMPLETED;
	case listOverdue:
		return FILENAME_OVERDUE;
	}
}

void Storage::writeLine(string line){
	_fileWrite << line << endl;
}

//string Storage::convertToStr(long long number){
//	return to_string(number);
//}

string Storage::convertToStr(TaskType taskType){
	switch(taskType){
	case deadline:
		return TASK_TYPE_DEADLINE;
	case timed:
		return TASK_TYPE_TIMED;
	default:
		return TASK_TYPE_FLOATING;
	}
}

string Storage::convertToStr(RepeatType repeatType){
	switch (repeatType){
	case Enum::daily:
		return REPEAT_TYPE_DAILY;
	case Enum::weekly:
		return REPEAT_TYPE_WEEKLY;
	case Enum::fortnightly:
		return REPEAT_TYPE_FORTNIGHTLY;
	case Enum::monthly:
		return REPEAT_TYPE_MONTHLY;
	case Enum::annually:
		return REPEAT_TYPE_ANNUALLY;
	default:
		return REPEAT_TYPE_NONE;
	}
}

string Storage::convertToStr(Priority priority){
	switch (priority){
	case high:
		return PRIORITY_HIGH;
	default:
		return PRIORITY_NORMAL;
	}
}

string Storage::convertToStr(time_t time){
	stringstream tempStream;
	tempStream << time;
	return tempStream.str();
}

string Storage::convertToStr(tm* time){
	stringstream tempStream;
	time_t tempTime;
	tempTime = mktime(time);
	tempStream << tempTime;
	return tempStream.str();
}


bool Storage::load(list<Task>& list,ListType listType ){
	string fileName = determineFile(listType);
	readFileSetup(fileName);
	loadIntoList(list);
	return 0; //stub
}

void Storage::readFileSetup(string fileName){
	_fileRead.open(fileName);
}

void Storage::loadIntoList(list<Task>& listToLoad){
	while(isLoadIncomplete()){
		Task newTask = getNewTask();
		insertTaskIntoList(listToLoad, newTask);
	}
}

bool Storage::isLoadIncomplete(){
	while(_fileRead.good()){
		if(foundNextTask())
			return true;
		else
			continue;
	}
	return false;
}

bool Storage::foundNextTask(){
	string nextLine = getNextLine();
	if(nextLine == MARKER_TASK_BEGIN)
		return true;
	else
		return false;
}

string Storage::getNextLine(){
	string nextLine;
	getline(_fileRead, nextLine);
	return nextLine;
}

Task Storage::getNewTask(){
	string marker;
	string newAttribute;
	Task newTask;
	TaskType newTaskType = taskInvalid;
	while(_fileRead.good()){
		marker = getNextLine();
		newAttribute = getNextLine();
		if(marker == MARKER_TASK_END)
			break;
		else if(marker == MARKER_TASK_TYPE)
			newTaskType = convertToTaskType(newAttribute);
		else if(marker == MARKER_ID)
			newTask = constructTask(newTaskType, newAttribute);
		else if(marker == MARKER_DESCRIPTION)
			newTask.setTaskDescription(newAttribute);
		else if(marker == MARKER_LOCATION)
			newTask.setTaskLocation(newAttribute);
		else if(marker == MARKER_START_TIME){
			time_t startTime = convertToTime(newAttribute);
			newTask.setTaskStart(startTime);
		}
		else if(marker == MARKER_END_TIME){
			time_t endTime = convertToTime(newAttribute);
			newTask.setTaskStart(endTime);
		}
		else if(marker == MARKER_REPEAT){
			RepeatType repeatType = convertToRepeatType(newAttribute);
			newTask.setTaskRepeat(repeatType);
		}
		else if(marker == MARKER_NEXT_OCCURANCE){
			time_t nextOccurance = convertToTime(newAttribute);
			newTask.setTaskNextOccurance(nextOccurance);
		}
		else if(marker == MARKER_PRIORITY){
			Priority priority = convertToPriority(newAttribute);
			newTask.setTaskPriority(priority);
		}
		else if(marker == MARKER_REMINDER_TIME){
			time_t remindTime = convertToTime(newAttribute);
			newTask.setTaskReminder(remindTime);
		}
	}
	return newTask;
}

Task Storage::constructTask(TaskType taskType, string IDString){
	int IDNumber = convertToInt(IDString);
	if(taskType == floating){
		TaskFloating newTask(IDNumber);
		return newTask;
	}
	else if(taskType == deadline){
		TaskDeadline newTask(IDNumber);
		return newTask;
	}
	else if(taskType == timed){
		TaskTimed newTask(IDNumber);
		return newTask;
	}
}

void Storage::insertTaskIntoList(list<Task>& listToInsert, Task task){
	list<Task>::iterator iterator;
	iterator = getIterator(listToInsert, task);
	listToInsert.insert(iterator,task);

}

list<Task>::iterator Storage::getIterator(list<Task>& insertionList, Task taskToAdd){
	long long tempTime;
	bool isEmpty = insertionList.empty();
	long long taskEndTime = taskToAdd.getTimeLong(timeEnd);
	list<Task>::iterator iterator = insertionList.begin();
	if(isEmpty){
		return iterator;
	}
	int listSize = insertionList.size();
	for(int i=0; i<listSize; i++){
		tempTime = iterator->getTimeLong(timeEnd);
		if(tempTime > taskEndTime)
			return iterator;
		++iterator;
	}
	return iterator;
}

TaskType Storage::convertToTaskType(string str){
	if(str == TASK_TYPE_FLOATING)
		return floating;
	else if(str == TASK_TYPE_DEADLINE)
		return deadline;
	else if(str == TASK_TYPE_TIMED)
		return timed;
	else
		return taskInvalid;
}

int Storage::convertToInt(string str){
	stringstream tempStream(str);
	int integer;
	tempStream >> integer;
	return integer;
}

time_t Storage::convertToTime(string str){
	stringstream tempStream(str);
	time_t time;
	tempStream >> time;
	return time;
}

RepeatType Storage::convertToRepeatType(string str){
	if(str == REPEAT_TYPE_DAILY)
		return daily;
	else if(str == REPEAT_TYPE_WEEKLY)
		return weekly;
	else if(str == REPEAT_TYPE_FORTNIGHTLY)
		return fortnightly;
	else if(str == REPEAT_TYPE_MONTHLY)
		return monthly;
	else if(str == REPEAT_TYPE_ANNUALLY)
		return monthly;
	else
		return repeatNone;
}

Priority Storage::convertToPriority(string str){
	if(str == PRIORITY_HIGH)
		return high;
	else
		return normal;
}