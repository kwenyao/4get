#include "logic_task_list.h"

TaskList::TaskList(){
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

bool sort(ListType listType){
	return false; //stub
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

bool TaskList::deleteFromList(int taskToDelete){
	list<Task>::iterator iterator;
	for(int i=0; i<taskToDelete; i++)
		++iterator;
	switch (currentDisplayed){
	case listToDo:
		toDoList.erase(iterator);
		break;
	case listCompleted:
		completedList.erase(iterator);
		break;
	case listOverdue:
		overdueList.erase(iterator);
		break;
	default:
		return false;
	}
	return true; //stub
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