#include "logic_task_list.h"

TaskList::TaskList(){
}

bool TaskList::loadFromFile(){
	_storage.load(_toDoList, listToDo);
	_storage.load(_completedList, listCompleted);
	_storage.load(_overdueList, listOverdue);
	return 0; //stub
}

bool TaskList::saveToFile(){
	_storage.save(_toDoList, listToDo, _toDoListSize);
	_storage.save(_completedList, listCompleted, _completedListSize);
	_storage.save(_overdueList, listOverdue, _overdueListSize);
	return 0; //stub
}

bool TaskList::addToList(Task task, ListType listType){
	list<Task> listToAdd;
	list<Task>::iterator iterator;
	listToAdd = determineList(listType);
	iterator = getIterator(listToAdd, task);
	listToAdd.insert(iterator, task);
	return true;
}

bool TaskList::deleteFromList(int taskToDelete){
	list<Task> listToDeleteFrom;
	list<Task>::iterator iterator;
	for(int i=0; i<taskToDelete; i++)
		++iterator;
	listToDeleteFrom = determineList(_currentDisplayed);
	listToDeleteFrom.erase(iterator);
	return true; //stub
}

list<Task> TaskList::obtainList(ListType listToReturn){
	_listToDisplay = determineList(listToReturn);
	_currentDisplayed = listToReturn;
	return _listToDisplay;
}

list<Task>::iterator TaskList::getIterator(list<Task> insertionList, Task taskToAdd){
	int tempTime;
	int taskEndTime = taskToAdd.getTimeInt(timeEnd);
	list<Task>::iterator iterator = insertionList.begin();
	int listSize = insertionList.size();
	for(int i=0; i<listSize; i++){
		tempTime = iterator->getTimeInt(timeEnd);
		if(tempTime > taskEndTime){
			return iterator;
		}
		++iterator;
	}
	return iterator;
}

list<Task> TaskList::determineList(ListType listType){
	switch (listType){
	case listToDo:
		return _toDoList;
	case listCompleted:
		return _completedList;
	case listOverdue:
		return _overdueList;
	}
}