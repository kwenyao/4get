#include "logic_task_list.h"

bool TaskList::loadListFromFile(){
	return 0; //stub
}

bool TaskList::saveListToFile(){
	return 0; //stub
}

bool TaskList::addToList(Task task, ListType listToAdd){
	switch (listToAdd){
	case toDo:
		return addToDoList(task);
	case completed:
		return addCompletedList(task);
	case overdue:
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
	case toDo:
		return deleteFromToDo(taskToDelete);
	case completed:
		return deleteFromCompleted(taskToDelete);
	case overdue:
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

int TaskList::getNextID(){
	int temp =  nextTaskID;
	nextTaskID++;
	return temp;
}

