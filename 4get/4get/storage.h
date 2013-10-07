#ifndef _STORAGE_H_
#define _STORAGE_H_

#include <iostream>
#include <fstream>

using namespace std;

class Storage{
private:

public:
	//constructor
	Storage();

	bool save();
	bool load();
};
#endif