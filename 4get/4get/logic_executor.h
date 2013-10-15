/////////////////////////////////////
// this function receives an array //
//   with parameters form input    //
//  and calls the approriate list  //
/////////////////////////////////////
#undef assert
#define assert(x) ((void)0)
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
	Task *taskGlobal;
	TaskList tasks;
	string task;
	Parser parser;
	long long taskID;
	Converter convert;
	stack<Task> taskStack;
	stack<Command> commandStack;
	ListType listType;
	
	bool addToTaskList();
	
	static const int CONSTANT_MULTIPLIER_YEAR;
	static const int CONSTANT_MULTIPLIER_MONTH;
	static const int CONSTANT_MULTIPLIER_DAY;
	static const int CONSTANT_MONTH_ONE;

public:
	Executor();

	void stringCollector(string task);
	bool receive(string command, vector<string> vectorOfInputs);
	Command determineCommandType (string commandTypeString); 
	void loadListOfTasks();
	bool storeTask(Task taskTemp);
	bool storeCommands(Command command);
	bool setListType(ListType listType);
	
	bool determineTaskType();
	bool adderFunction(vector<string> vectorOfInputs);
	bool modifyFunction(vector<string> vectorOfInputs);
	bool deleteFunction(vector<string> vectorOfInputs);
	bool markFunction(vector<string> vectorOfInputs);
	bool undoFunction();
	list<Task> getUpdatedList(ListType listType);

	//helper functions
	bool isEqual(string str1, const string str2);
	long long retrieveCurrentDate();
};
#endif