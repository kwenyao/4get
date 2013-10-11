#include "storage.h"

Storage::Storage(){}

bool Storage::save(list<Task> list, ListType listType, int listSize){
	ofstream tempSaveFile("temp_save.4get");
	tempSaveFile << listSize << endl;
	for(int i=0; i<listSize; i++){
		
	}
	tempSaveFile.close();
	return false; //stub
}

int Storage::load(list<Task> list,ListType listType ){
	int listSize;

	return listSize;
}