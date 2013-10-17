/////////////////////////////////////
// this function receives an array //
//   with parameters form input    //
//  and calls the approriate list  //
/////////////////////////////////////
#ifndef _LOGIC_EXECUTOR_H_
#define _LOGIC_EXECUTOR_H_

#include <assert.h>
#include "common_message.h"
#include "logic_converter.h"
#include "logic_parser.h"
#include "logic_task.h"
#include "logic_task_list.h"
#include "logic_task_floating.h"
#include "logic_task_deadline.h"
#include "logic_task_timed.h"
#include <stack>
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
	string task;
	Task *taskGlobal;
	TaskList taskList;
	Parser parser;
	Converter convert;
	stack<Task> taskStack;
	stack<Command> commandStack;
	ListType listType;
	long long taskID;

	static const int CONSTANT_MULTIPLIER_YEAR;
	static const int CONSTANT_MULTIPLIER_MONTH;
	static const int CONSTANT_MULTIPLIER_DAY;
	static const int CONSTANT_MONTH_ONE;

public:
	//constructor
	Executor();

	//UI call these functions
	void stringCollector(string task);
	bool receive(string command, vector<string> vectorOfInputs);
	Command determineCommandType (string commandTypeString); 
	list<Task> getUpdatedList(ListType listType);

	//Functions to be executed
	bool adderFunction(vector<string> vectorOfInputs);
	bool modifyFunction(vector<string> vectorOfInputs);
	bool deleteFunction(vector<string> vectorOfInputs);
	bool markFunction(vector<string> vectorOfInputs);
	bool undoFunction();
	
	//helper functions
	bool isEqual(string str1, const string str2);
	long long retrieveCurrentDate();
	bool storeTask(Task taskTemp);
	bool storeCommands(Command command);
	bool setListType(ListType listType);
};
#endif