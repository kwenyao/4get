#ifndef _STORAGE_H_
#define _STORAGE_H_

#include <list>
#include <iostream>
#include <fstream>
#include "logic_task.h"
#include "common_message.h"

using namespace std;

class Storage{
private:
	ofstream _fileWrite;
	ifstream _fileRead;
	list<Task> _taskList;

	//constants
	static const string FILENAME_TODO;
	static const string FILENAME_COMPLETED;
	static const string FILENAME_OVERDUE;

	//markers
	static const string MARKER_TASK_BEGIN;
	static const string MARKER_ID;
	static const string MARKER_DESCRIPTION;
	static const string MARKER_LOCATION;
	static const string MARKER_START_TIME;
	static const string MARKER_END_TIME;
	static const string MARKER_REPEAT;
	static const string MARKER_NEXT_OCCURANCE;
	static const string MARKER_PRIORITY;
	static const string MARKER_REMINDER_TIME;
	static const string MARKER_STATUS;
	static const string MARKER_TASK_END;
	static const string EMPTY_LINE;

	void writeFileSetup(string fileName, ios_base::openmode mode);
	string determineFile(ListType listType);
	
	bool saveList(const list<Task>& listToSave);
	void saveTaskToFile(const Task& taskToSave);
	void closeFileWrite();
	void writeTaskAttributes(const Task& task);
	void writeLine(string line);

	
	void writeID(const Task& task);
	void writeDescription(const Task& task);
	void writeLocation(const Task& task);
	void writeStartTime(const Task& task);
	void writeEndTime(const Task& task);
	void writeRepeat(const Task& task);
	void writeNextOccurance(const Task& task);
	void writePriority(const Task& task);
	void writeReminderTime(const Task& task);
	void writeStatus(const Task& task);
	
public:
	//constructor
	Storage();
	
	bool save(const list<Task>& list,ListType listType, int listSize);
	int load(list<Task>& list, ListType listType);
};
#endif