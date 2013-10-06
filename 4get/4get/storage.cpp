#include "storage.h"

bool save(int listSize){
	ofstream tempSaveFile("temp_save.4get");
	tempSaveFile << listSize << endl;
	for(int i=0; i<listSize; i++){
		
	}
	tempSaveFile.close();
	return false; //stub
}

bool load(){
	return 0; //stub
}