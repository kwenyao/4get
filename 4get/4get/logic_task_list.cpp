#include "logic_task_list.h"

bool TaskList::loadListFromFile(){

}

bool TaskList::saveListToFile(){

}

bool TaskList::addToList(Task* task, ListType listToAdd){
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

bool TaskList::addToDoList(Task* task){
	toDoList.push_back(task);
}

bool TaskList::addCompletedList(Task* task){
	completedList.push(task);
}

bool TaskList::addOverdueList(Task* task){
	overdueList.push(task);
}

bool TaskList::deleteFromList(int taskToDelete){

}

int TaskList::getNextID(){
	int temp =  nextTaskID;
	nextTaskID++;
	return temp;
}

