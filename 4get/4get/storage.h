#ifndef _STORAGE_H_
#define _STORAGE_H_

#include <list>
#include <iostream>
#include <fstream>
#include <sstream>
#include "logic_task.h"
#include "logic_task_floating.h"
#include "logic_task_deadline.h"
#include "logic_task_timed.h"

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
	static const string MARKER_TASK_TYPE;
	static const string MARKER_ID;
	static const string MARKER_DESCRIPTION;
	static const string MARKER_LOCATION;
	static const string MARKER_START_TIME;
	static const string MARKER_END_TIME;
	static const string MARKER_REPEAT;
	static const string MARKER_NEXT_OCCURANCE;
	static const string MARKER_PRIORITY;
	static const string MARKER_REMINDER_TIME;
	//static const string MARKER_STATUS; //to be deleted if not used
	static const string MARKER_TASK_END;
	static const string EMPTY_LINE;

	static const string TASK_TYPE_FLOATING;
	static const string TASK_TYPE_DEADLINE;
	static const string TASK_TYPE_TIMED;

	static const string REPEAT_TYPE_DAILY;
	static const string REPEAT_TYPE_WEEKLY;
	static const string REPEAT_TYPE_FORTNIGHTLY;
	static const string REPEAT_TYPE_MONTHLY;
	static const string REPEAT_TYPE_ANNUALLY;
	static const string REPEAT_TYPE_NONE;

	static const string PRIORITY_HIGH;
	static const string PRIORITY_NORMAL;

	void writeFileSetup(string fileName, ios_base::openmode mode);
	string determineFile(ListType listType);

	bool saveList(const list<Task>& listToSave);
	void saveTaskToFile(const Task& taskToSave);
	void closeFileWrite();
	void writeTaskAttributes(const Task& task);
	void writeLine(string line);

	void writeTaskType(const Task& task);
	void writeID(const Task& task);
	void writeDescription(const Task& task);
	void writeLocation(const Task& task);
	void writeStartTime(const Task& task);
	void writeEndTime(const Task& task);
	void writeRepeat(const Task& task);
	void writeNextOccurance(const Task& task);
	void writePriority(const Task& task);
	void writeReminderTime(const Task& task);
	//void writeStatus(const Task& task);  //to be deleted if not used

	//Functions to convert to string
	//string convertToStr(long long number);
	string convertToStr(tm* time);
	string convertToStr(time_t time);
	string convertToStr(TaskType taskType);
	string convertToStr(RepeatType repeatType);
	string convertToStr(Priority priority);
	

	//load functions
	void readFileSetup(string fileName);
	void loadIntoList(list<Task>& listToLoad);
	bool isLoadIncomplete();
	bool foundNextTask();
	string getNextLine();
	Task getNewTask();
	Task constructTask(TaskType taskType, string IDString);
	void insertTaskIntoList (list<Task>& listToInsert, Task task);
	list<Task>::iterator getIterator(list<Task>& insertionList, Task task);

	TaskType convertToTaskType(string str);
	int convertToInt(string str);
	time_t convertToTime(string str);
	RepeatType convertToRepeatType(string str);
	Priority convertToPriority(string str);

public:
	//constructor
	Storage();

	bool save(const list<Task>& list,ListType listType, int listSize);
	bool load(list<Task>& listToLoadTo, ListType listType);
};
#endif