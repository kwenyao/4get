/*
 * =====================================================================================
 *
 *       Filename:  logic_executor.h
 *
 *         Author:  POH HUAN YU (A0101831X), a0101831@nus.edu.sg
 *   Organization:  NUS, School of Computing
 *
 * =====================================================================================
 */
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
	TaskList taskList;
	Task *taskGlobal;
	Parser parser;
	Converter convert;
	stack<Task> undoTaskStack;
	stack<Command> undoCommandStack;
	stack<Task> redoTaskStack;
	stack<Command> redoCommandStack;
	stack<int> undoDeleteNumberStack;
	stack<int> redoDeleteNumberStack;
	stack<int> undoMarkNumberStack;
	stack<int> redoMarkNumberStack;
	stack<ListType> undoListTypeStack;
	stack<ListType> redoListTypeStack;
	ListType listType;
	Task* createTaskPtr(Task taskToCreate);
	static const int LEAST_INDEX;
	static const int SIZE_CORRECTION;
	static const int ID_MULTIPLIER;
	static const int SINGLE_OPERATION;
	static const string LOGGING_MESSAGE_STRINGCOLLECTOR;

	//Functions to be executed
	bool receive(string command, vector<string> vectorOfInputs);
	Command determineCommandType (string commandTypeString); 
	bool adderFunction(vector<string> vectorOfInputs);
	bool modifyFunction(vector<string> vectorOfInputs);
	bool deleteFunction(vector<string> vectorOfInputs);
	bool markFunction(vector<string> vectorOfInputs);
	bool undoFunction();
	bool redoFunction();
	bool searchFunction(vector<string> vectorOfInputs);
	bool showAllFunction();
	
	//helper functions
	bool isEqual(string str1, const string str2);
	long long retrieveTaskID();
	void helperDeleteFunction(int deleteStartNumber);
	void helperMarkFunction(int markStartNumber);
	void storeIntoUndoTaskStack(Task taskTemp);
	void storeIntoUndoCommandStack(Command command);
	void storeIntoRedoTaskStack(Task taskTemp);
	void storeIntoRedoCommandStack(Command command);
	void undoCorrector();
	bool setParameters(string &description, 
						string &location, 
						Priority &priority,
						RepeatType &repeat,
						time_t &startTime, 
						time_t &endTime, 
						TaskType &typeOfTask,
						vector<string> &vectorOfInputs);
	int swapValueAndGetSizeFunction(int start, int end);
	int getSizeFunction(int start, int end);
	
	//assertions
	void assertNotEmptyTask();

public:
	//constructor
	Executor();

	//Functions to be used by UI
	bool stringCollector(string task);
	void refreshAll();
	list<Task*> getUpdatedList(ListType listType);
	bool setListType(ListType listType);
};
#endif