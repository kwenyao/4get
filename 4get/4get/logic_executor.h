/////////////////////////////////////
// this function receives an array //
//   with parameters form input    //
//  and calls the approriate list  //
/////////////////////////////////////
#ifndef _LOGIC_EXECUTOR_H_
#define _LOGIC_EXECUTOR_H_

#include <assert.h>
#include "common_message.h"
#include "log.h"
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
//	Task *taskTempGlobal;
	TaskList taskList;
	Parser parser;
	Converter convert;
	stack<Task> undoTaskStack;
	stack<Command> undoCommandStack;
	stack<Task> redoTaskStack;
	stack<Command> redoCommandStack;
	stack<Task> redoModifiedTaskStack;
	ListType listType;
	long long taskID;

	Task* createTaskPtr(Task taskToCreate);

	static const int CONSTANT_MULTIPLIER_YEAR;
	static const int CONSTANT_MULTIPLIER_MONTH;
	static const int CONSTANT_MULTIPLIER_DAY;
	static const int CONSTANT_MONTH_ONE;

public:
	//constructor
	Executor();

	//UI call these functions
	bool stringCollector(string task);
	bool receive(string command, vector<string> vectorOfInputs);
	Command determineCommandType (string commandTypeString); 
	list<Task*> getUpdatedList(ListType listType);

	//Functions to be executed
	bool adderFunction(vector<string> vectorOfInputs);
	bool modifyFunction(vector<string> vectorOfInputs);
	bool deleteFunction(vector<string> vectorOfInputs);
	bool markFunction(vector<string> vectorOfInputs);
	bool undoFunction();
	bool redoFunction();
	
	//helper functions
	bool isEqual(string str1, const string str2);
	long long retrieveCurrentDate();
	bool storeTask(Task taskTemp);
	bool storeCommands(Command command);
	bool setListType(ListType listType);
	bool setParameters(string &description, 
						string &location, 
						Priority &priority,
						RepeatType &repeat,
						time_t &startTime, 
						time_t &endTime, 
						time_t &reminderTime, 
						TaskType &typeOfTask,
						vector<string> &vectorOfInputs);
	Task tempTaskCreator(Task* task);

	//assertions
	void empty_task();
};
#endif