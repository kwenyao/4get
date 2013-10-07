#ifndef _COMMON_MESSAGE_H_
#define _COMMON_MESSAGE_H_
#include <iostream>

using namespace std;
namespace Commands{
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
}

namespace Message{
	//error messages
	const string MESSAGE_ERROR_COMMAND_ADD = "System was unable to add your task.";
	const string MESSAGE_ERROR_COMMAND_DELETE = "System was unable to delete your task.";
	const string MESSAGE_ERROR_COMMAND_MARK = "System was unable to mark your task.";
	const string MESSAGE_ERROR_COMMAND_MODIFY = "System was unable to modify your task.";
	const string MESSAGE_ERROR_COMMAND_UNDO = "System was unable to undo to your previous task.";
	const string MESSAGE_ERROR_COMMAND_UPDATE = "System was unable to perform an update of your current task.";
};

namespace Enum{
	enum ListType{
		listToDo,
		listCompleted,
		listOverdue,
	};

	enum RepeatType{
		none, 
		daily, 
		weekly, 
		fortnightly, 
		monthly, 
		annually
	};

	enum Priority{
		high, 
		normal
	};

	enum Status{
		completed, 
		incomplete, 
		overdued
	};

	enum TaskType{
		floating, 
		timed, 
		deadline
	};

	enum Command{
		commandAdd, 
		commandDelete, 
		commandDeleteAll, 
		commandMark, 
		commandMarkDone, 
		commandModify, 
		commandUndo, 
		commandUpdate
	};
};

namespace Constants{
	// Constant Strings //

	//system constants
	const int COMPARE_SUCCESS = 0;
	const int FOUND_SUCCESS = 0;

	//Initializer
	const string INITIALIZE_STRING_BLANK = "";
	const size_t INITIALIZE_SIZE_T = 0;

	//Input Bits slots
	const int SLOT_SIZE = 10;
	const int SLOT_COMMAND = 0;
	const int SLOT_DESCRIPTION = 1;
	const int SLOT_LOCATION = 2;
	const int SLOT_REMIND_TIME = 3;
	const int SLOT_PRIORITY = 4;
	const int SLOT_REPEAT = 5;
	const int SLOT_TIME = 6;

	//parser markers
	const char MARKER_COMMA = ',';
	const std::size_t MARKER_COMMA_LENGTH = 1;

	const char MARKER_ENCLOSE = ' ';
	const std::size_t MARKER_ENCLOSE_LENGTH = 1;

	const string MARKER_AT = ",at";
	const std::size_t MARKER_AT_LENGTH = 3;

	const string MARKER_NEAR = ",near";
	const std::size_t MARKER_NEAR_LENGTH = 3;

	const string MARKER_BY = ",by";
	const std::size_t MARKER_BY_LENGTH = 3;

	const string MARKER_FROM = ",from";
	const std::size_t MARKER_FROM_LENGTH = 5;

	const string MARKER_TO = " to ";
	const std::size_t MARKER_TO_LENGTH = 4;

	const string MARKER_REMIND = ",remind";
	const std::size_t MARKER_REMIND_LENGTH = 7;

	const string MARKER_ON = " on ";
	const std::size_t MARKER_ON_LENGTH = 4;

	const string MARKER_REPEAT = ",repeat";
	const std::size_t MARKER_REPEAT_LENGTH = 7;

	const string MARKER_PRIORITY = ",!";
	const std::size_t MARKER_PRIORITY_LENGTH = 2;
};

#endif