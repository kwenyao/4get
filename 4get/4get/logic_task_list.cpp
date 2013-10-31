#include "logic_task_list.h"

const int TaskList::INDEX_CORRECTION = -1;
const string TaskList::LOG_TASK_ADDED = "Task inserted into list";
const string TaskList::LOG_TASK_DELETED = "Task deleted from list";
const string TaskList::LOG_TASK_MARKED = "Task marked";

TaskList::TaskList(){
	loadFromFile();
	_isFiltered = false;
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
	try{
		if(_currentDisplayed == listFiltered)
			deleteFromFiltered(indexUI);
		listToDeleteFrom = determineList(_currentDisplayed);
		if (listToDeleteFrom->empty())
			throw string(Message::MESSAGE_ERROR_LIST_EMPTY);
		iterator = iterateToTask(*listToDeleteFrom, indexUI);
		if(isDelete)
			delete *iterator;
		listToDeleteFrom->erase(iterator);
		logging(LOG_TASK_DELETED, Info, Pass);
		_storage.save(*listToDeleteFrom, _currentDisplayed);
	} catch(string e){
		throw;
	}
}

void TaskList::deleteFromFiltered(int indexUI){
	long long taskID;
	list<Task*>::iterator iterator;
	list<Task*>* listToDeleteFrom = determineList(_actualList);
	try{
		taskID = obtainTaskID(indexUI, _filteredList);
		deleteIDFromList(taskID, _actualList, false);
	} catch(string e){
		throw;
	}
}

long long TaskList::obtainTaskID(int indexUI, list<Task*> taskList){
	list<Task*>::iterator iterator = iterateToTask(taskList, indexUI);
	return (*iterator)->getTaskId();
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
	Task* taskPtr;
	list<Task*>* listToMark;
	list<Task*>::iterator iterator;
	listToMark = determineList(_currentDisplayed);
	iterator = iterateToTask(*listToMark, indexUI);
	taskPtr = (*iterator);
	deleteFromList(indexUI, false);
	addToList(taskPtr, listCompleted);
	logging(LOG_TASK_MARKED, Info, Pass);
	return true;
}

list<Task*> TaskList::obtainList(ListType listToReturn){
	if(_isFiltered){
		_isFiltered = false;
		_currentDisplayed = listFiltered;
		return _filteredList;
	}
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
	time_t tempTime;
	bool isEmpty = insertionList.empty();
	time_t taskEndTime = taskToAdd->getTaskEnd();
	list<Task*>::iterator iterator = insertionList.begin();
	if(isEmpty){
		return iterator;
	}
	int listSize = insertionList.size();
	for(int i=0; i<listSize; i++){
		tempTime = (*iterator)->getTaskEnd();
		if(tempTime > taskEndTime)
			return iterator;
		++iterator;
	}
	return iterator;
}

list<Task*>::iterator TaskList::iterateToTask(list<Task*>& listToEdit, int indexUI){
	assert(!listToEdit.empty());
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
	case listFiltered:
		return &_filteredList;
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

void TaskList::searchList(string searchStr){
	list<Task*> *listToFilter = determineList(_currentDisplayed);
	_actualList = _currentDisplayed;
	if(listToFilter->empty())
		throw string(Message::MESSAGE_ERROR_LIST_EMPTY);
	int listSize = listToFilter->size();
	_filteredList.clear();
	list<Task*>::iterator iterator = listToFilter->begin();
	for(int i=0; i<listSize; i++){
		if(isEqual(searchStr, iterator))
			_filteredList.push_back(*iterator);
		++iterator;
	}
	_isFiltered = true;
}

//void TaskList::searchList(time_t searchTime){
//	list<Task*> *listToFilter = determineList(_currentDisplayed);
//	_actualList = _currentDisplayed;
//	if(listToFilter->empty())
//		throw string(Message::MESSAGE_ERROR_LIST_EMPTY);
//	int listSize = listToFilter->size();
//	_filteredList.clear();
//	list<Task*>::iterator iterator = listToFilter->begin();
//	for(int i=0; i<listSize; i++){
//		if( (*iterator)->getTaskEnd() == searchTime)
//			_filteredList.push_back(*iterator);
//		else if( (*iterator)->getTaskStart() == searchTime)
//			_filteredList.push_back(*iterator);
//		++iterator;
//	}
//	_isFiltered = true;
//}

void TaskList::searchList(long long searchDate){
	list<Task*>* listToFilter = determineList(_currentDisplayed);
	if(listToFilter->empty())
		throw string(Message::MESSAGE_ERROR_LIST_EMPTY);
	_actualList = _currentDisplayed;
	int listSize = listToFilter->size();
	_filteredList.clear();
	list<Task*>::iterator iterator = listToFilter->begin();
	for(int i=0; i<listSize; i++){
		if(isEqual(searchDate,iterator))
			_filteredList.push_back(*iterator);
		++iterator;
	}
	_isFiltered = true;
}

bool TaskList::isEqual(long long searchDate, list<Task*>::iterator iterator){
	long long tempStart;
	long long tempEnd;
	tempStart = (*iterator)->getTimeLong(timeStart);
	tempEnd = (*iterator)->getTimeLong(timeEnd);
	if(tempEnd == searchDate)
		return true;
	else if(tempStart == searchDate)
		return true;
	else
		return false;
}

bool TaskList::isEqual(string searchStr, list<Task*>::iterator iterator){
	if( (*iterator)->getTaskDescription() == searchStr)
		return true;
	else if( (*iterator)->getTaskLocation() == searchStr)
		return true;
	else 
		return false;
}