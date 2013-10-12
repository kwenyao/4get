#ifndef _STORAGE_H_
#define _STORAGE_H_

#include <list>
#include <iostream>
#include <fstream>
#include "logic_task.h"
#include "common_message.h"

using namespace std;

class Storage{
private:
	ofstream _fileWrite;
	ifstream _fileRead;
	list<Task> tempList;

	//constants
	static const string FILENAME_TODO;
	static const string FILENAME_COMPLETED;
	static const string FILENAME_OVERDUE;

	void writeFileSetup(string fileName, ios_base::openmode mode);
	

public:
	//constructor
	Storage();
	
	bool save(list<Task> list,ListType listType, int listSize);
	int load(list<Task> list, ListType listType);
};
#endif