/////////////////////////////////////
// this function receives an array //
//   with parameters form input    //
//  and calls the approriate list  //
/////////////////////////////////////

#ifndef _LOGIC_EXECUTOR_H_
#define _LOGIC_EXECUTOR_H_

#include "logic_task.h"
#include "logic_parser.h"
#include "logic_task_list.h"
#include <locale.h>
#include <vector>
#include <string>

using namespace std;
using namespace Message;
using namespace Enum;
using namespace Constants;


class Executor
{
	private:
	Task _task;
	TaskList tasks;
	string task;
	vector<string> vectorOfInputs;
	Parser parser;
	int taskID;

public:
	Executor();

	void stringCollector(string task);
	bool receive(string command);
	Command determineCommandType (string commandTypeString); 
	void loadListOfTasks();
	
	bool determineTaskType();
	bool adderFunction();
	bool addToTaskList();
	bool deleteFunction();
	list<Task> getUpdatedList();

	//helper functions
	bool isEqual(string str1, const string str2);
	string determineListType();
	tm* convertStringToTm();
	int retrieveCurrentDate();
	

	
};
#endif