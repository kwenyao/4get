#include "logic_task_list.h"

const int TaskList::INDEX_CORRECTION = -1;
const string TaskList::LOG_TASK_ADDED = "Task inserted into list";
const string TaskList::LOG_TASK_DELETED = "Task deleted from list";
const string TaskList::LOG_TASK_MARKED = "Task marked";

TaskList::TaskList(){
	loadFromFile();
}

TaskList::~TaskList(){
	clearList(listToDo);
	clearList(listCompleted);
	clearList(listOverdue);
}

void TaskList::clearList(ListType listType){
	list<Task*>* listToClear;
	list<Task*>::iterator iterator;
	listToClear = determineList(listType);
	for (iterator = listToClear->begin();
		iterator != listToClear->end();
		iterator++){
			delete *iterator;
	}
	listToClear->clear();
}

void TaskList::loadFromFile(){
	try{
	_storage.load(_toDoList, listToDo);
	_storage.load(_completedList, listCompleted);
	_storage.load(_overdueList, listOverdue);
	} catch (string errorStr){
		throw;
	}
}

void TaskList::saveAll(){
	try{
	_storage.save(_toDoList, listToDo);
	_storage.save(_completedList, listCompleted);
	_storage.save(_overdueList, listOverdue);
	} catch (string errorStr){
		throw;
	}
}

bool TaskList::addToList(Task* task, ListType listType){
	assert(task != NULL);
	list<Task*>* listToAdd;
	list<Task*>::iterator iterator;
	listToAdd = determineList(listType);
	iterator = getIterator(*listToAdd, task);
	listToAdd->insert(iterator,task);
	logging(LOG_TASK_ADDED, Info, Pass);
	_storage.save(*listToAdd, listType);
	return true;
}

void TaskList::deleteFromList(int indexUI, bool isDelete){
	assert(indexUI > 0); 
	list<Task*>* listToDeleteFrom;
	list<Task*>::iterator iterator;
	listToDeleteFrom = determineList(_currentDisplayed);
	try{
		if (listToDeleteFrom->empty())
			throw string(Message::MESSAGE_ERROR_LIST_EMPTY);
		iterator = iterateToTask(*listToDeleteFrom, indexUI);
		if(isDelete)
			delete *iterator;
		listToDeleteFrom->erase(iterator);
		logging(LOG_TASK_DELETED, Info, Pass);
		_storage.save(*listToDeleteFrom, _currentDisplayed);
	} catch(string e){
		cout << e << endl;
		throw;
	}
}

void TaskList::deleteIDFromList(long long IDNumber, ListType listToDelete, bool isDelete){
	list<Task*>::iterator iterator;
	list<Task*>* listPtr = determineList(listToDelete);
	try{
		findID(listPtr, IDNumber, iterator);
		if(isDelete)
			delete *iterator;
		listPtr->erase(iterator);
		logging(LOG_TASK_DELETED, Info, Pass);
		_storage.save(*listPtr, listToDelete);
	} catch(string e){
		cout << e << endl;
		throw;
	}
}

bool TaskList::markDone(int indexUI){
	assert(indexUI > 0); 
	Task* temp;
	list<Task*>* listToMark;
	list<Task*>::iterator iterator;
	listToMark = determineList(_currentDisplayed);
	iterator = iterateToTask(*listToMark, indexUI);
	temp = (*iterator);
	deleteFromList(indexUI, false);
	addToList(temp, listCompleted);
	logging(LOG_TASK_MARKED, Info, Pass);
	return true;
}

list<Task*> TaskList::obtainList(ListType listToReturn){
	_listToDisplay = *determineList(listToReturn);
	_currentDisplayed = listToReturn;
	return _listToDisplay;
}

Task* TaskList::obtainTask(int indexUI){
	Task* taskToReturn;
	list<Task*>::iterator iterator;
	iterator = iterateToTask(_listToDisplay, indexUI);
	taskToReturn = (*iterator);
	return taskToReturn;
}

list<Task*>::iterator TaskList::getIterator(list<Task*>& insertionList, Task* taskToAdd){
	long long tempTime;
	bool isEmpty = insertionList.empty();
	long long taskEndTime = taskToAdd->getTimeLong(timeEnd);
	list<Task*>::iterator iterator = insertionList.begin();
	if(isEmpty){
		return iterator;
	}
	int listSize = insertionList.size();
	for(int i=0; i<listSize; i++){
		tempTime = (*iterator)->getTimeLong(timeEnd);
		if(tempTime > taskEndTime)
			return iterator;
		++iterator;
	}
	return iterator;
}

list<Task*>::iterator TaskList::iterateToTask(list<Task*>& listToEdit, int indexUI){
	list<Task*>::iterator iterator;
	int indexList = indexUI + INDEX_CORRECTION;
	iterator = listToEdit.begin();
	for(int i=0; i<indexList; i++)
		++iterator;
	return iterator;
}

void TaskList::findID(list<Task*>* listToSearch, long long IDNumber, list<Task*>::iterator& iterator){
	long long tempID;
	iterator = listToSearch->begin();
	int listSize = listToSearch->size();
	for(int i=0; i <listSize; i++){
		tempID = (*iterator)->getTaskId();
		if(tempID == IDNumber)
			return;
		++iterator;
	}
	throw string(Message::MESSAGE_ERROR_INVALID_ID);
}

list<Task*>* TaskList::determineList(ListType listType){
	switch (listType){
	case listCompleted:
		return &_completedList;
	case listOverdue:
		return &_overdueList;
	default:
		return &_toDoList;
	}
}

void TaskList::setCurrentDisplayed(ListType listType){
	_currentDisplayed = listType;
}

Task* TaskList::obtainTask(long long taskID, ListType listType){
	list<Task*>* listToFind;
	list<Task*>::iterator iterator;
	listToFind = determineList(listType);
	findID(listToFind, taskID, iterator);
	return (*iterator);
}