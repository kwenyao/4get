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
	list<Task> toDoList;
	list<Task> completedList;
	list<Task> overdueList;
	list<Task> listToDisplay;
	Storage storage;
	ListType currentDisplayed;
	int toDoListSize;
	int completedListSize;
	int overdueListSize;

	bool sort(ListType listType);
	bool addToDoList(Task task);
	bool addCompletedList(Task task);
	bool addOverdueList(Task task);

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