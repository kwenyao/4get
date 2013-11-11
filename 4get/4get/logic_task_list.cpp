/*
* =====================================================================================
*
*       Filename:  logic_task_list.cpp
*
*         Author:  KOH WEN YAO (A0097210M), kwenyao@nus.edu.sg
*   Organization:  NUS, School of Computing
*
* =====================================================================================
*/

#include "logic_task_list.h"

const int TaskList::INDEX_CORRECTION = -1;
const string TaskList::LOG_TASK_ADDED = "Task inserted into list";
const string TaskList::LOG_TASK_DELETED = "Task deleted from list";
const string TaskList::LOG_TASK_MARKED = "Task marked";
const int TaskList::YYYYMMDD_YEAR_MULTIPLIER = 10000;
const int TaskList::YYYYMMDD_MONTH_MULTIPLIER = 100;
const int TaskList::HHMM_HOUR_MULTIPLIER = 100;

/*************************************
           PUBLIC FUNCTIONS                      
*************************************/

TaskList::TaskList(){
	loadFromFile();
	_isFiltered = false;
}

TaskList::TaskList(time_t timeNow){
	loadFromFile();
	refreshAll(timeNow);
	_isFiltered = false;
}

TaskList::~TaskList(){
	clearList(listToDo);
	clearList(listCompleted);
	clearList(listOverdue);
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

void TaskList::saveToDoList(){
	_storage.save(_toDoList, listToDo);
}

bool TaskList::addToList(Task* task, ListType listType){
	assert(task != NULL);
	list<Task*>* listToAdd;
	list<Task*>::iterator iterator;
	listToAdd = determineList(listType);
	listToAdd->push_back(task);
	listToAdd->sort(&TaskList::compareEndThenPriority);
	logging(LOG_TASK_ADDED, Info, Pass);
	_storage.save(*listToAdd, listType);
	return true;
}

void TaskList::deleteIndexFromList(int indexUI, bool isDelete){
	assert(indexUI > 0);
	list<Task*>* listToDeleteFrom;
	list<Task*>::iterator iterator;
	int listSize;
	try{
		if(_currentDisplayed == listFiltered)
			deleteFromFiltered(indexUI);
		listToDeleteFrom = determineList(_currentDisplayed);
		if (listToDeleteFrom->empty())
			throw string(Message::MESSAGE_ERROR_LIST_EMPTY);
		listSize = listToDeleteFrom->size();
		if (listSize < indexUI)
			throw string(Message::MESSAGE_ERROR_INVALID_INDEX);
		iterator = iterateToTask(*listToDeleteFrom, indexUI);
		if(isDelete)
			delete *iterator;
		listToDeleteFrom->erase(iterator);
		logging(LOG_TASK_DELETED, Info, Pass);
		if(_currentDisplayed == listFiltered)
			_storage.save(*listToDeleteFrom, _actualList);
		else
			_storage.save(*listToDeleteFrom, _currentDisplayed);
	} catch(string errString){
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
	} catch(string errString){
		throw;
	}
}

bool TaskList::markDone(int indexUI){
	assert(indexUI > 0); 
	Task* taskPtr;
	list<Task*>* listToMark;
	list<Task*>::iterator iterator;
	int listSize;
	listToMark = determineList(_currentDisplayed);
	listSize = listToMark->size();
	if (listSize < indexUI)
		throw string(Message::MESSAGE_ERROR_INVALID_INDEX);
	iterator = iterateToTask(*listToMark, indexUI);
	taskPtr = (*iterator);
	deleteIndexFromList(indexUI, false);
	addToList(taskPtr, listCompleted);
	logging(LOG_TASK_MARKED, Info, Pass);
	return true;
}

list<Task*> TaskList::obtainList(ListType listToReturn){
	if(_isFiltered && listToReturn == _actualList){
		assert(_currentDisplayed == listFiltered);
		return _filteredList;
	}
	_listToDisplay = *determineList(listToReturn);
	_currentDisplayed = listToReturn;
	_isFiltered = false;
	return _listToDisplay;
}

Task* TaskList::obtainTask(int indexUI){
	Task* taskToReturn;
	int listSize;
	list<Task*>::iterator iterator;
	list<Task*>* listToFind = determineList(_currentDisplayed); 
	listSize = listToFind->size();
	if (listSize < indexUI)
		throw string(Message::MESSAGE_ERROR_INVALID_INDEX);
	iterator = iterateToTask((*listToFind), indexUI);
	taskToReturn = (*iterator);
	return taskToReturn;
}

Task* TaskList::obtainTask(long long taskID, ListType listType){
	list<Task*>* listToFind;
	list<Task*>::iterator iterator;
	try{
	listToFind = determineList(listType);
	findID(listToFind, taskID, iterator);
	} catch(string errString) {
		throw;
	}
	return (*iterator);
}

void TaskList::searchList(string searchStr){
	_isFiltered = true;
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
}

void TaskList::searchList(long long searchDate){
	_isFiltered = true;
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
}

void TaskList::searchDescription(string searchStr){
	try{
		searchSetup();
		populateFilteredList(descriptionAttr, searchStr);
	} catch (string errString) {
		throw;
	}
}

void TaskList::searchLocation(string searchStr){
	try{
		searchSetup();
		populateFilteredList(locationAttr, searchStr);
	} catch (string errString) {
		throw;
	}
}

void TaskList::searchStart(time_t searchTime){
	try{
		searchSetup();
		populateFilteredList(startAttr, searchTime, specificSearch);
	} catch (string errString) {
		throw;
	}
}

void TaskList::searchStartTime(time_t searchTime){
	try{
		searchSetup();
		populateFilteredList(startAttr, searchTime, timeSearch);
	} catch (string errString) {
		throw;
	}
}

void TaskList::searchStartDate(time_t searchDate){
	try{
		searchSetup();
		populateFilteredList(startAttr, searchDate, dateSearch);
	} catch (string errString) {
		throw;
	}
}

void TaskList::searchEnd(time_t searchTime){
	try{
		searchSetup();
		populateFilteredList(endAttr, searchTime, specificSearch);
	} catch (string errString) {
		throw;
	}
}

void TaskList::searchEndTime(time_t searchTime){
	try{
		searchSetup();
		populateFilteredList(endAttr, searchTime, timeSearch);
	} catch (string errString) {
		throw;
	}
}

void TaskList::searchEndDate(time_t searchDate){
	try{
		searchSetup();
		populateFilteredList(endAttr, searchDate, dateSearch);
	} catch (string errString) {
		throw;
	}
}

void TaskList::turnOffFilter(){
	_isFiltered = false;
}

void TaskList::refreshAll(time_t timeNow){
	if(_toDoList.empty())
		return;
	int listSize = _toDoList.size();
	int marker = 0;
	list<Task*>::iterator iterator = _toDoList.begin();
	for(int i=0; i<listSize; i++){
		if(isExpiredTask((*iterator),timeNow)){
			moveTask(iterator, _toDoList, _overdueList);
			iterator = _toDoList.begin();
			advance(iterator,marker);
		}
		else{
			marker++;
			++iterator;
		}
	}
	_toDoList.sort(&compareEndThenPriority);
	saveAll();
}

void TaskList::setCurrentDisplayed(ListType listType){
	_currentDisplayed = listType;
}

/*************************************
          PRIVATE FUNCTIONS            
*************************************/

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

void TaskList::searchSetup(){
	if(!_isFiltered){
		_activeList = determineList(_currentDisplayed);
		_actualList = _currentDisplayed;
	}
	else{
		_tempList = _filteredList;
		_activeList = &_tempList;
	}
	_filteredList.clear();
	_currentDisplayed = listFiltered;
	if(_activeList->empty())
		throw string(Message::MESSAGE_ERROR_LIST_EMPTY);
	_searchIterator = _activeList->begin();
}

void TaskList::populateFilteredList(AttributeType attrType, string searchStr){
	int listSize;
	listSize = _activeList->size();
	assert(listSize != 0);
	for(int i=0; i<listSize; i++){
		if(isEqual(attrType, searchStr))
			_filteredList.push_back(*_searchIterator);
		++_searchIterator;
	}
	if(_filteredList.empty())
		throw string(Message::MESSAGE_NO_SEARCH_RESULT);
	_isFiltered = true;
}

void TaskList::populateFilteredList(AttributeType attrType, time_t searchTime, SearchTimeType searchType){
	int listSize;
	listSize = _activeList->size();
	assert(listSize != 0);
	for(int i=0; i<listSize; i++){
		if(isEqual(attrType, searchTime, searchType))
			_filteredList.push_back(*_searchIterator);
		++_searchIterator;
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

bool TaskList::isEqual(AttributeType attType, string searchStr){
	string compareStr;
	switch (attType){
	case Enum::descriptionAttr:
		compareStr = (*_searchIterator)->getTaskDescription();
		break;
	case Enum::locationAttr:
		compareStr = (*_searchIterator)->getTaskLocation();
		break;
	default:
		return false;
	}
	return (compareStr == searchStr);
}

bool TaskList::isEqual(AttributeType attType, time_t searchTime, SearchTimeType searchType){
	time_t compareTime;
	switch (attType){
	case Enum::startAttr:
		compareTime = (*_searchIterator)->getTaskStart();
		break;
	case Enum::endAttr:
		compareTime = (*_searchIterator)->getTaskEnd();
		break;
	default:
		return false;
	}
	switch (searchType){
	case dateSearch:
		compareTime = getDate(compareTime);
		searchTime = getDate(searchTime);
		break;
	case timeSearch:
		compareTime = getTime(compareTime);
		searchTime = getTime(searchTime);
		break;
	default:
		break;
	}
	return (compareTime == searchTime);
}

bool TaskList::compareEndThenPriority(Task* firstTask, Task* secondTask){
	time_t firstEnd = firstTask->getTaskEnd();
	time_t secondEnd = secondTask->getTaskEnd();
	Priority firstPriority = firstTask->getTaskPriority();
	Priority secondPriority = secondTask->getTaskPriority();
	bool isFirstHigh = (firstPriority == high);
	bool isSecondHigh = (secondPriority == high);
	if(firstEnd < secondEnd)
		return true;
	else if(firstEnd > secondEnd)
		return false;
	else{ //if end time same
		if(isFirstHigh && !isSecondHigh)
			return true;
		else 
			return false;
	}
}

int TaskList::getDate(time_t dateAndTime){
	int year;
	int month;
	int day;
	struct tm newtime;
	localtime_s(&newtime, &dateAndTime);
	year = newtime.tm_year + YEAR_CORRECTION;
	month = newtime.tm_mon + MONTH_CORRECTION;
	day = newtime.tm_mday;
	year = year * YYYYMMDD_YEAR_MULTIPLIER;
	month = month * YYYYMMDD_MONTH_MULTIPLIER;
	return (year + month + day);
}

int TaskList::getTime(time_t dateAndTime){
	int hour;
	int min;
	struct tm newtime;
	localtime_s(&newtime, &dateAndTime);
	hour = newtime.tm_hour * HHMM_HOUR_MULTIPLIER;
	min = newtime.tm_min;
	return (hour + min);
}

void TaskList::moveTask(list<Task*>::iterator fromIterator, list<Task*>& fromList, list<Task*>& toList){
	Task* taskPtr = (*fromIterator);
	fromList.erase(fromIterator);
	toList.push_front(taskPtr);
}

bool TaskList::isExpiredTask(Task* testTask, time_t timeNow){
	time_t taskTime = testTask->getTaskEnd();
	RepeatType taskRepeat = testTask->getTaskRepeat();
	bool isRepeat = (taskRepeat != repeatNone);
	bool isOver = (taskTime < timeNow);
	bool isNotFloating = (taskTime > 0);
	if(isNotFloating && isOver && isRepeat){
		testTask->setNextOccurance();
		return false;
	}
	else if(isNotFloating && isOver)
		return true;
	else
		return false;
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

int TaskList::getCurrentListSize(){
	list<Task*>* currentList = determineList(_currentDisplayed);
	return currentList->size();
}
