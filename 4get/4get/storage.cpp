#include "storage.h"

const string Storage::FILENAME_TODO = "todo.txt";
const string Storage::FILENAME_COMPLETED = "completed.txt";
const string Storage::FILENAME_OVERDUE = "overdue.txt";

Storage::Storage(){}

bool Storage::save(list<Task> list, ListType listType, int listSize){
	switch (listType){
	case listToDo:
		writeFileSetup(FILENAME_TODO, ios_base::trunc);
		break;
	case listCompleted:
		writeFileSetup(FILENAME_COMPLETED, ios_base::trunc);
		break;
	case listOverdue:
		writeFileSetup(FILENAME_OVERDUE, ios_base::trunc);
		break;
	default:
		break;
	}

	return true; 
}

void Storage::writeFileSetup(string fileName, ios_base::openmode mode){
	_fileWrite.open(fileName, mode);
}

int Storage::load(list<Task> list,ListType listType ){
	int listSize = 0;

	return listSize;
}