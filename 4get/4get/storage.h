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