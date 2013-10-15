#ifndef _LOGIC_TASK_LIST_H_
#define _LOGIC_TASK_LIST_H_

#include <list>
#include <time.h>
#include "logic_task.h"
#include "storage.h"

using namespace std;
using namespace Enum;
using namespace Constants;

class TaskList{
private:
	list<Task> _toDoList;
	list<Task> _completedList;
	list<Task> _overdueList;
	list<Task>* _listToDisplay;
	Storage _storage;
	ListType _currentDisplayed;
	int _toDoListSize;
	int _completedListSize;
	int _overdueListSize;

	static const int INDEX_CORRECTION;

	list<Task>::iterator getIterator(list<Task>& insertionList, Task task);
	list<Task>::iterator iterateToTask(list<Task>& listToEdit, int task);
	list<Task>* determineList(ListType listType);

public:
	TaskList();

	//storage functions
	bool loadFromFile();
	bool saveToFile();

	//Public list manipulation functions
	bool addToList(Task task, ListType listToAdd);
	bool deleteFromList(int taskToDelete);
	bool markDone(int taskToMark);

	list<Task> obtainList(ListType listToReturn);
	Task* obtainTask(int taskToGet);
};
#endif