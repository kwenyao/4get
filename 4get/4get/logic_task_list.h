#ifndef _LOGIC_TASK_LIST_H_
#define _LOGIC_TASK_LIST_H_

#include <iostream>
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
	Storage storage;
	list<Task> toDoList;
	list<Task> completedList;
	list<Task> overdueList;
	int nextTaskID;

public:
	TaskList();
	bool loadListFromFile();
	bool saveListToFile();
	bool addToList(Task task, ListType listToAdd);
	bool addToDoList(Task task);
	bool addCompletedList(Task task);
	bool addOverdueList(Task task);

	bool deleteFromList(int taskToDelete, ListType list);
	bool sort();

	bool deleteFromToDo(int taskToDelete);
	bool deleteFromCompleted(int taskToDelete);
	bool deleteFromOverdue(int taskToDelete);

	int getNextID();
	int retrieveCurrentDate();

	list<Task> obtainList(ListType listToReturn);
};
#endif