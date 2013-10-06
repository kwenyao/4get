#ifndef _COMMON_MESSAGE_H_
#define _COMMON_MESSAGE_H_
#include <iostream>

using namespace std;

namespace Message{
};


namespace Enum{
	enum ListType{
		toDo,
		completed,
		overdue,
	};

	enum RepeatType{
		NONE, DAILY, WEEKLY, FORTNIGHTLY, MONTHLY, ANNUALLY
	};

	enum Priority{
		HIGH, NORMAL
	};

	enum Status{
		COMPLETED, INCOMPLETE, OVERDUED
	};

	enum TaskType{
		FLOATING, TIMED, DEADLINE
	};

	enum Command{
		ADD, DELETE, DELETE_ALL, MARK, MARK_DONE, MODIFY, UNDO, UPDATE
	};


};


// Constant Strings //

//system constants
const int COMPARE_SUCCESS = 0;
const int FOUND_SUCCESS = 0;

//variants of add
const string COMMAND_ADD = "add";
const string COMMAND_A = "a";
const string COMMAND_NEW_TASK= "new task";

//variants of delete
const string COMMAND_DELETE = "delete";
const string COMMAND_REMOVE = "remove";
const string COMMAND_ERASE = "erase";
const string COMMAND_DEL = "del";
const string COMMAND_REM = "rem";


//variants of delete all
const string COMMAND_DELETE_ALL= "delete all";
const string COMMAND_REMOVE_ALL = "remove all";
const string COMMAND_ERASE_ALL = "erase all";
const string COMMAND_DEL_ALL= "del all";
const string COMMAND_REM_ALL = "rem all";

//variants of mark
const string COMMAND_MARK = "mark";
const string COMMAND_M = "m";
const string COMMAND_MARK_DONE = "mark done";
const string COMMAND_M_DONE = "m done";


//variants of modify
const string COMMAND_MODIFY = "modify";
const string COMMAND_MOD = "mod";

//variants of undo
const string COMMAND_UNDO = "undo";

//variants of update
const string COMMAND_UPDATE = "update";


//error messages
const string ERROR_COMMAND_ADD = "System was unable to add your task.";
const string ERROR_COMMAND_DELETE = "System was unable to delete your task.";
const string ERROR_COMMAND_MARK = "System was unable to mark your task.";
const string ERROR_COMMAND_MODIFY = "System was unable to modify your task.";
const string ERROR_COMMAND_UNDO = "System was unable to undo to your previous task.";
const string ERROR_COMMAND_UPDATE = "System was unable to perform an update of your current task.";


//Input Bits slots
const int SLOT_DESCRIPTION = 0;
const int SLOT_LOCATION = 1;
const int SLOT_REMIND_TIME = 2;
const int SLOT_PRIORITY = 3;
const int SLOT_REPEAT = 4;
const int SLOT_START_TIME = 5;
const int SLOT_END_TIME = 6;

//parser markers

const char MARKER_COMMA = ',';
const string MARKER_ENCLOSE = " ";
const string MARKER_AT = ",at";
const string MARKER_NEAR = ",near";
const string MARKER_BY = ",by";
const string MARKER_FROM = ",from";
const string MARKER_TO = " to ";
const string MARKER_REMIND = ",remind";
const string MARKER_ON = " on ";
const string MARKER_REPEAT = ",repeat";



#endif