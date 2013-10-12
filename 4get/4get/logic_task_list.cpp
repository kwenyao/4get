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

bool TaskList::addToList(Task task, ListType listType){
	list<Task> listToAdd;
	list<Task>::iterator iterator;
	switch (listType){
	case listToDo:
		listToAdd = toDoList;
		break;
	case listCompleted:
		listToAdd = completedList;
		break;
	case listOverdue:
		listToAdd = overdueList;
		break;
	default:
		return false;
	}
	iterator = getIterator(listToAdd, task);
	listToAdd.insert(iterator, task);
	return true;
}

bool sort(list<Task> listToSort){
	
	return false; //stub
}

bool TaskList::addToDoList(Task task){
	list<Task>::iterator iterator;
	iterator = getIterator(toDoList);
	toDoList.insert(iterator, task);
	//toDoList.push_back(task);
	//sort(toDoList);
	return 0; //stub
}

bool TaskList::addCompletedList(Task task){
	completedList.push_back(task);
	//sort(completedList);
	return 0; //stub
}

bool TaskList::addOverdueList(Task task){
	overdueList.push_back(task);
	//sort(overdueList);
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