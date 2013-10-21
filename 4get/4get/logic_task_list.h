#ifndef _LOGIC_TASK_LIST_H_
#define _LOGIC_TASK_LIST_H_

#include <list>
#include <ctime>
#include "logic_task.h"
#include "storage.h"

using namespace std;
using namespace Enum;
using namespace Constants;

class TaskList{
private:
	list<Task*> _toDoList;
	list<Task*> _completedList;
	list<Task*> _overdueList;
	list<Task*> _listToDisplay;
	Storage _storage;
	ListType _currentDisplayed;

	static const int INDEX_CORRECTION;

	void clearList(ListType listType);

	list<Task*>::iterator getIterator(list<Task*>& insertionList, Task* task);
	list<Task*>::iterator iterateToTask(list<Task*>& listToEdit, int task);
	void findID(list<Task*>* listToEdit, long long IDNumber, list<Task*>::iterator& iterator);
	list<Task*>* determineList(ListType listType);

public:
	TaskList();
	~TaskList();

	//storage functions
	void loadFromFile();
	bool saveAll();

	//Public list manipulation functions
	bool addToList(Task* task, ListType listToAdd);
	void deleteFromList(int taskToDelete, bool isDelete);
	void deleteIDFromList(long long IDNumber, ListType listToDelete, bool isDelete);
	bool markDone(int taskToMark);

	//Getter functions
	list<Task*> obtainList(ListType listToReturn);
	Task* obtainTask(int taskToGet);
};
#endif