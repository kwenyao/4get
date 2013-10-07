#include <iostream>
#include <list>
#include <stack>
#include <queue>
#include "logic_task.h"
#include "logic_task_timed.h"
#include "logic_task_deadline.h"
#include "common_message.h"
#include "storage.h"
#include <time.h>

using namespace std;
using namespace Enum; 

class TaskList{
private:
	Storage storage;
	list<Task> toDoList;
	stack<Task> completedList;
	queue<Task> overdueList;
	int nextTaskID;
	
public:
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
};