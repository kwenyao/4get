/////////////////////////////////////
// this function receives an array //
//   with parameters form input    //
//  and calls the approriate list  //
/////////////////////////////////////

#ifndef _LOGIC_EXECUTOR_H_
#define _LOGIC_EXECUTOR_H_

#include "logic_converter.h"
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
	Task taskGlobal;
	TaskList tasks;
	string task;
	vector<string> vectorOfInputs;
	Parser parser;
	int taskID;
	Converter convert;

	static const int CONSTANT_MULTIPLIER_YEAR;
	static const int CONSTANT_MULTIPLIER_MONTH;
	static const int CONSTANT_MULTIPLIER_DAY;


public:
	Executor();

	void stringCollector(string task);
	bool receive(string command);
	Command determineCommandType (string commandTypeString); 
	void loadListOfTasks();
	
	int determineTaskId();
	bool determineTaskType();
	bool adderFunction();
	bool addToTaskList();
	bool deleteFunction();
	list<Task> getUpdatedList(ListType listType);

	//helper functions
	bool isEqual(string str1, const string str2);
	ListType determineListType(vector<string> &input);
	int retrieveCurrentDate();
};
#endif