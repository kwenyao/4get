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
	list<Task> tempList;
public:
	//constructor
	Storage();
	
	bool save(list<Task> list,ListType listType, int listSize);
	int load(list<Task> list, ListType listType);
};
#endif