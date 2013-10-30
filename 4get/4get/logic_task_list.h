#ifndef _LOGIC_TASK_LIST_H_
#define _LOGIC_TASK_LIST_H_

#include <list>
#include <ctime>
#include "logic_task.h"
#include "storage.h"
#include "log.h"

using namespace std;
using namespace Enum;
using namespace Constants;

class TaskList{
private:
	list<Task*> _toDoList;
	list<Task*> _completedList;
	list<Task*> _overdueList;
	list<Task*> _listToDisplay;
	list<Task*> _filteredList;
	Storage _storage;
	ListType _currentDisplayed;
	ListType _actualList;
	bool _isFiltered;

	void clearList(ListType listType);

	static const int INDEX_CORRECTION;
	static const string LOG_TASK_ADDED;
	static const string LOG_TASK_DELETED;
	static const string LOG_TASK_MARKED;

	list<Task*>::iterator getIterator(list<Task*>& insertionList, Task* task);
	list<Task*>::iterator iterateToTask(list<Task*>& listToEdit, int task);
	void findID(list<Task*>* listToEdit, long long IDNumber, list<Task*>::iterator& iterator);
	list<Task*>* determineList(ListType listType);
	void deleteFromFiltered(int indexUI);
	long long obtainTaskID(int indexUI, list<Task*> taskList);

	//compare functions for search
	bool isEqual(long long searchDate, list<Task*>::iterator iterator);
	bool isEqual(string searchStr, list<Task*>::iterator iterator);

public:
	TaskList();
	~TaskList();

	//storage functions
	void loadFromFile();
	void saveAll();

	//Public list manipulation functions
	bool addToList(Task* task, ListType listToAdd);
	void deleteFromList(int indexUI, bool isDelete);
	void deleteIDFromList(long long IDNumber, ListType listToDelete, bool isDelete);
	bool markDone(int taskToMark);

	//Getter functions
	list<Task*> obtainList(ListType listToReturn);
	Task* obtainTask(int indexUI);
	Task* obtainTask(long long taskID, ListType listType);

	//Search functions
	void searchList(string searchStr);
	//void searchList(time_t searchTime);
	void searchList(long long searchDate);

	//Functions used in testing only
	void setCurrentDisplayed(ListType listType);
};
#endif