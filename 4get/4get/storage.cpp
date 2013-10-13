#include "storage.h"

const string Storage::FILENAME_TODO = "todo.txt";
const string Storage::FILENAME_COMPLETED = "completed.txt";
const string Storage::FILENAME_OVERDUE = "overdue.txt";

const string Storage::MARKER_TASK_BEGIN = "---------Task Begin---------";
const string Storage::MARKER_ID = "Task ID:";
const string Storage::MARKER_DESCRIPTION = "Description:";
const string Storage::MARKER_LOCATION = "Location:";
const string Storage::MARKER_START_TIME = "Start Time:";
const string Storage::MARKER_END_TIME = "End Time:";
const string Storage::MARKER_REPEAT = "Repeat:";
const string Storage::MARKER_NEXT_OCCURANCE = "Next Occurance:";
const string Storage::MARKER_PRIORITY = "Priority:";
const string Storage::MARKER_REMINDER_TIME = "Reminder Time:";
const string Storage::MARKER_STATUS = "Status:";
const string Storage::MARKER_TASK_END = "---------Task End---------";
const string Storage::EMPTY_LINE = "";

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
	writeID(task);
	writeDescription(task);
	writeLocation(task);
	writeStartTime(task);
	writeEndTime(task);
	writeRepeat(task);
	writeNextOccurance(task);
	writePriority(task);
	writeReminderTime(task);
}

void Storage::writeID(const Task& task){
	writeLine(MARKER_ID);
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
}
void Storage::writeEndTime(const Task& task){
	writeLine(MARKER_END_TIME);
}
void Storage::writeRepeat(const Task& task){
	writeLine(MARKER_REPEAT);
}
void Storage::writeNextOccurance(const Task& task){
	writeLine(MARKER_NEXT_OCCURANCE);
}
void Storage::writePriority(const Task& task){
	writeLine(MARKER_PRIORITY);
}
void Storage::writeReminderTime(const Task& task){
	writeLine(MARKER_REMINDER_TIME);
}
void Storage::writeStatus(const Task& task){
	writeLine(MARKER_STATUS);
}

void Storage::writeFileSetup(string fileName, ios_base::openmode mode){
	_fileWrite.open(fileName, mode);
}

int Storage::load(list<Task>& list,ListType listType ){
	string fileName;
	determineFile(listType);

	return 0; //stub
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