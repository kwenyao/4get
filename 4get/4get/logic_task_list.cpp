#include "logic_task_list.h"

const int TaskList::INDEX_CORRECTION = -1;

TaskList::TaskList(){
	_storage.load(_toDoList, listToDo);
	_storage.load(_completedList, listCompleted);
	_storage.load(_overdueList, listOverdue);
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
	list<Task>* listToAdd;
	list<Task>::iterator iterator;
	listToAdd = determineList(listType);
	iterator = getIterator(*listToAdd, task);
	listToAdd->insert(iterator,task);
	saveToFile();
	return true;
}

void TaskList::deleteFromList(int taskToDelete){
	list<Task>* listToDeleteFrom;
	list<Task>::iterator iterator;
	listToDeleteFrom = determineList(_currentDisplayed);
	try{
		if (listToDeleteFrom->empty())
			throw string(Message::MESSAGE_ERROR_LIST_EMPTY);
		iterator = iterateToTask(*listToDeleteFrom, taskToDelete);
		listToDeleteFrom->erase(iterator);
	} catch(string e){
		cout << e << endl;
		throw;
	}
}

void TaskList::deleteIDFromList(long long IDNumber, ListType listToDelete){
	list<Task>::iterator iterator;
	list<Task>* listPtr = determineList(listToDelete);
	try{
		findID(listPtr, IDNumber, iterator);
		listPtr->erase(iterator);
	} catch(string e){
		cout << e << endl;
		throw;
	}
}

bool TaskList::markDone(int taskToMark){
	Task temp;
	list<Task>* listToMark;
	list<Task>::iterator iterator;
	listToMark = determineList(_currentDisplayed);
	iterator = iterateToTask(*listToMark, taskToMark);
	temp = *iterator;
	deleteFromList(taskToMark);
	addToList(temp, listCompleted);
	return true;
}

list<Task> TaskList::obtainList(ListType listToReturn){
	_listToDisplay = determineList(listToReturn);
	_currentDisplayed = listToReturn;
	return *_listToDisplay;
}

Task* TaskList::obtainTask(int taskToGet){
	Task* taskToReturn;
	list<Task>::iterator iterator;
	iterator = iterateToTask(*_listToDisplay, taskToGet);
	taskToReturn = &*iterator;
	return taskToReturn;
}

list<Task>::iterator TaskList::getIterator(list<Task>& insertionList, Task taskToAdd){
	long long tempTime;
	bool isEmpty = insertionList.empty();
	long long taskEndTime = taskToAdd.getTimeLong(timeEnd);
	list<Task>::iterator iterator = insertionList.begin();
	if(isEmpty){
		return iterator;
	}
	int listSize = insertionList.size();
	for(int i=0; i<listSize; i++){
		tempTime = iterator->getTimeLong(timeEnd);
		if(tempTime > taskEndTime)
			return iterator;
		++iterator;
	}
	return iterator;
}

list<Task>::iterator TaskList::iterateToTask(list<Task>& listToEdit, int task){
	list<Task>::iterator iterator;
	int indexToDelete = task + INDEX_CORRECTION;
	iterator = listToEdit.begin();
	for(int i=0; i<indexToDelete; i++)
		++iterator;
	return iterator;
}

void TaskList::findID(list<Task>* listToSearch, long long IDNumber, list<Task>::iterator& iterator){
	long long tempID;
	iterator = listToSearch->begin();
	int listSize = listToSearch->size();
	for(int i=0; i <listSize; i++){
		tempID = iterator->getTaskId();
		if(tempID == IDNumber)
			return;
		++iterator;
	}
	throw string(Message::MESSAGE_ERROR_INVALID_ID);
}

list<Task>* TaskList::determineList(ListType listType){
	switch (listType){
	case listCompleted:
		return &_completedList;
	case listOverdue:
		return &_overdueList;
	default:
		return &_toDoList;
	}
}