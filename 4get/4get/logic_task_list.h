#ifndef _LOGIC_TASK_LIST_H_
#define _LOGIC_TASK_LIST_H_

#include <list>
#include <time.h>
#include "logic_task.h"
#include "common_message.h"
#include "storage.h"

using namespace std;
using namespace Enum;
using namespace Constants;

class TaskList{
private:
	list<Task> _toDoList;
	list<Task> _completedList;
	list<Task> _overdueList;
	list<Task> _listToDisplay;
	Storage _storage;
	ListType _currentDisplayed;
	int _toDoListSize;
	int _completedListSize;
	int _overdueListSize;

	list<Task>::iterator getIterator(list<Task>& insertionList, Task task);

	list<Task> determineList(ListType listType);

public:
	TaskList();

	//storage functions
	bool loadFromFile();
	bool saveToFile();

	//list manipulation functions
	bool addToList(Task task, ListType listToAdd);
	bool deleteFromList(int taskToDelete);

	list<Task> obtainList(ListType listToReturn);
};
#endif