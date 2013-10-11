#include "logic_task_list.h"

TaskList::TaskList(){
	nextTaskID = retrieveCurrentDate();
}

bool TaskList::loadFromFile(){
	storage.load(toDoList, listToDo);
	storage.load(completedList, listCompleted);
	storage.load(overdueList, listOverdue);
	return 0; //stub
}

bool TaskList::saveToFile(){
	storage.save(toDoList, listToDo, toDoListSize);
	storage.save(completedList, listCompleted, completedListSize);
	storage.save(overdueList, listOverdue, overdueListSize);
	return 0; //stub
}

bool TaskList::addToList(Task task, ListType listToAdd){
	switch (listToAdd){
	case listToDo:
		return addToDoList(task);
	case listCompleted:
		return addCompletedList(task);
	case listOverdue:
		return addOverdueList(task);
	}
	return false; 
}

bool TaskList::addToDoList(Task task){
	toDoList.push_back(task);
	sort(listToDo);
	return 0; //stub
}

bool TaskList::addCompletedList(Task task){
	completedList.push_back(task);
	sort(listCompleted);
	return 0; //stub
}

bool TaskList::addOverdueList(Task task){
	overdueList.push_back(task);
	sort(listOverdue);
	return 0; //stub
}

bool TaskList::deleteFromList(int taskToDelete, ListType list){
	switch (list){
	case listToDo:
		return deleteFromToDo(taskToDelete);
	case listCompleted:
		return deleteFromCompleted(taskToDelete);
	case listOverdue:
		return deleteFromOverdue(taskToDelete);
	}
	return 0; //stub
}

bool TaskList::deleteFromToDo(int taskToDelete){
	list<Task>::iterator iterator;
	for(int i=0; i<taskToDelete; i++)
		++iterator;
	toDoList.erase(iterator);
	return false; //stub
}

bool TaskList::deleteFromCompleted(int taskToDelete){
	return 0; //stub
}

bool TaskList::deleteFromOverdue(int taskToDelete){
	return 0;
}

bool sort(ListType listType){
	return false; //stub
}

int TaskList::getNextID(){
	int temp =  nextTaskID;
	nextTaskID++;
	return temp;
}

int TaskList::retrieveCurrentDate(){
	time_t temp = time(NULL);
	int yearMonthDay;
	tm* currentTime; 
	currentTime = localtime(&temp);
	int day = currentTime ->tm_mday;
	int month = currentTime ->tm_mon;
	int year = currentTime ->tm_year + CONSTANT_START_YEAR;
	day = day*CONSTANT_MULTIPLIER_DAY;
	month = month*CONSTANT_MULTIPLIER_MONTH;
	year = year*CONSTANT_MULTIPLIER_YEAR;
	yearMonthDay = (year + month + day);
	return yearMonthDay;
}

list<Task> TaskList::obtainList(ListType listToReturn){
	switch (listToReturn){
	case listToDo:
		listToDisplay = toDoList;
		break;
	case listCompleted:
		listToDisplay = completedList;
		break;
	case listOverdue:
		listToDisplay = overdueList;
		break;
	}
	currentDisplayed = listToReturn;
	return listToDisplay;
}