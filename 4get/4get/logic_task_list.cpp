#include "logic_task_list.h"

TaskList::TaskList(){
	nextTaskID = retrieveCurrentDate();
}

bool TaskList::loadListFromFile(){
	return 0; //stub
}

bool TaskList::saveListToFile(){
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
	return 0; //stub
}

bool TaskList::addCompletedList(Task task){
	completedList.push(task);
	return 0; //stub
}

bool TaskList::addOverdueList(Task task){
	overdueList.push(task);
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

int TaskList::getNextID(){
	int temp =  nextTaskID;
	nextTaskID++;
	return temp;
}

int TaskList::retrieveCurrentDate(){
	time_t temp = time(0);
	struct tm* currentTime = localtime(&temp);
	int day = currentTime ->tm_mday;
	int month = currentTime->tm_mon;
	int year = currentTime -> tm_year + 1900;
	int yearMonthDay = (year*100000 + month*1000 + day*10);
	return yearMonthDay;
}


