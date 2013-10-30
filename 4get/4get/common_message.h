#ifndef _COMMON_MESSAGE_H_
#define _COMMON_MESSAGE_H_
#include <iostream>
#include <vector>

using namespace std;
namespace Commands{
	//variants of add
	const string COMMAND_ADD = "add";
	const string COMMAND_A = "a";
	const string COMMAND_CREATE= "create";

	//variants of delete
	const string COMMAND_DELETE = "delete";
	const string COMMAND_REMOVE = "remove";
	const string COMMAND_ERASE = "erase";
	const string COMMAND_DEL = "del";
	const string COMMAND_REM = "rem";

	//variants of mark
	const string COMMAND_MARK = "mark";
	const string COMMAND_M = "m";

	//variants of modify
	const string COMMAND_MODIFY = "modify";
	const string COMMAND_MOD = "mod";
	const string COMMAND_UPDATE = "update";
	const string COMMAND_DONE = "done";

	//variants of undo
	const string COMMAND_UNDO = "undo";

	//variants of redo
	const string COMMAND_REDO = "redo";

	//variants of show
	const string COMMAND_SHOW = "show";
	const string COMMAND_DISPLAY = "display";

	//variants of query
	const string COMMAND_WHAT = "what";
	const string COMMAND_WHEN = "when";
}

namespace Message{
	//error messages
	const string MESSAGE_ERROR_COMMAND_ADD = "System was unable to add your task.";
	const string MESSAGE_ERROR_COMMAND_DELETE = "System was unable to delete your task.";
	const string MESSAGE_ERROR_COMMAND_MARK = "System was unable to mark your task.";
	const string MESSAGE_ERROR_COMMAND_MODIFY = "System was unable to modify your task.";
	const string MESSAGE_ERROR_COMMAND_UNDO = "System was unable to undo to your previous task.";
	const string MESSAGE_ERROR_COMMAND_REDO = "System was unable to redo your previous task.";
	const string MESSAGE_ERROR_COMMAND_SHOW = "System was unable to display your task(s).";
	const string MESSAGE_ERROR_NOTHING_TO_REDO = "Error: There is nothing to redo.";
	const string MESSAGE_ERROR_COMMAND_QUERY = "System was unable to process your query.";
	
	const string MESSAGE_ERROR_LIST_EMPTY = "Error: List is empty.";
	const string MESSAGE_ERROR_INVALID_LIST = "Error: Invalid List.";
	const string MESSAGE_ERROR_NO_DESCRIPTION = "Error: No description indicated";
	const string MESSAGE_ERROR_NO_SLOT_NUM = "Error: No slot number.";
	
	const string MESSAGE_ERROR_INVALID_ID = "Error: Task ID does not exist";
	const string MESSAGE_ERROR_WRONG_KEYWORD = "Error: Wrong Keyword.";
	const string MESSAGE_ERROR_WRONG_FORMAT = "Error: Wrong Format.";
	const string MESSAGE_ERROR_WRONG_DATE_FORMAT ="Error: Wrong date format.";
	const string MESSAGE_ERROR_WRONG_TIME_FORMAT ="Error: Wrong time format."; 
	const string MESSAGE_ERROR_WRONG_DATE = "Error: No such date exists";
	const string MESSAGE_ERROR_WRONG_MONTH = "Error: No such month exists";
	const string MESSAGE_ERROR_INVALID_TASKTYPE = "Error: Type of task do not exist.";
	const string MESSAGE_ERROR_INVALID_YEAR = "Error: Year input is invalid.";
	const string MESSAGE_ERROR_INVALID_MONTH = "Error: Month input is invalid.";
	const string MESSAGE_ERROR_INVALID_DAY = "Error: Day input is invalid.";
	const string MESSAGE_ERROR_MISSING_DAY = "Error: Missing day of the month";

	const string MESSAGE_ERROR_START_AFTER_END = "Error: Start time is before end time.";
	const string MESSAGE_ERROR_NO_END_TIME = "Error: Please enter end time for task.";

	const string MESSAGE_SUCCESS_PARSED = "Input has been parsed.";
};

namespace Enum{
	enum TimeType{
		timeStart,
		timeEnd,
		timeNext,
		timeReminder
	};
	enum ListType{
		listToDo,
		listCompleted,
		listOverdue,
		listFiltered
	};

	enum RepeatType{
		repeatNone, 
		daily, 
		weekly, 
		fortnightly, 
		monthly, 
		annually
	};

	enum Priority{
		normal,
		high, 
	};

	enum TaskType{
		floating, 
		timed, 
		deadline,
		taskInvalid
	};


	enum Command{
		commandAdd, 
		commandDelete, 
		commandMark, 
		commandModify, 
		commandUndo, 
		commandRedo,
		commandShow,
		commandInvalid
	};

	enum LogType {
		Info,
		Debug,
		Warning,
		Error
	};

	enum LogStatus {
		None,
		Pass,
		Fail
	};

	enum LogTime {New,
		Current
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
	const int INITIALIZE_INT = 0;

	//Input Bits slots
	const int SLOT_SIZE = 15;
	const int SLOT_COMMAND = 0;
	const int SLOT_DESCRIPTION = 1;
	const int SLOT_LOCATION = 2;
	const int SLOT_REMIND_DATE = 3;
	const int SLOT_REMIND_TIME = 4;
	const int SLOT_PRIORITY = 5;
	const int SLOT_REPEAT = 6;
	const int SLOT_START_DATE = 7;
	const int SLOT_START_TIME = 8;
	const int SLOT_END_DATE = 9;
	const int SLOT_END_TIME = 10;
	const int SLOT_SLOT_NUMBER = 11;
	const int SLOT_STATUS = 12;
	const int SLOT_USER_RESPONSE = 13;

	//Time Container slots;
	const int TIME_SLOT_SIZE = 10;
	const int TIME_SLOT_YEAR = 0;
	const int TIME_SLOT_MONTH = 1;
	const int TIME_SLOT_DATE = 2;
	const int TIME_SLOT_HOUR = 3;
	const int TIME_SLOT_MIN = 4;
	const int TIME_SLOT_DAY = 5;


	//parser timer constants
	const string TIMER_SLASH = "/";
	const string TIMER_SPACE = " ";
	const string TIMER_DASH = "-";
	const string TIMER_COLON = ":";
	const string TIMER_DOT = ".";
	const string TIMER_SQUARE_BRACKETS_OPEN = " [";
	const string TIMER_SQUARE_BRACKETS_CLOSE = "] ";
	const string TIMER_AM = "am";
	const string TIMER_PM = "pm";
	const string TIMER_TOMORROW = "tommorrow";
	const string TIMER_TML = "tml";
	const string TIMER_TMR = "tmr";
	const string TIMER_MONDAY = "monday";
	const string TIMER_MON = "mon";
	const string TIMER_TUESDAY = "tuesday";
	const string TIMER_TUE = "tue";
	const string TIMER_TUES = "tues";
	const string TIMER_WEDNESDAY = "wednesday";
	const string TIMER_WED = "wed";
	const string TIMER_THURSDAY = "thursday";
	const string TIMER_THU = "thu";
	const string TIMER_THURS = "thurs";
	const string TIMER_FRIDAY = "friday";
	const string TIMER_FRI = "fri";
	const string TIMER_SATURDAY = "saturday";
	const string TIMER_SAT = "sat";
	const string TIMER_SUNDAY = "sunday";
	const string TIMER_SUN = "sun";
	const string TIMER_NEXT = "next";
	const string TIMER_HR = "hr";

	const string MONTH_JANUARY = "january";
	const string MONTH_JAN = "jan";
	const string MONTH_FEBRUARY = "february";
	const string MONTH_FEB = "feb";
	const string MONTH_MARCH = "march";
	const string MONTH_MAR = "mar";
	const string MONTH_APRIL = "april";
	const string MONTH_APR = "apr";
	const string MONTH_MAY = "may";
	const string MONTH_JUNE = "june";
	const string MONTH_JUN = "jun";
	const string MONTH_JULY = "july";
	const string MONTH_JUL = "jul";
	const string MONTH_AUGUST = "august";
	const string MONTH_AUG = "aug";
	const string MONTH_SEPTEMBER = "september";
	const string MONTH_SEPT = "sept";
	const string MONTH_SEP = "sep";
	const string MONTH_OCTOBER = "october";
	const string MONTH_OCT = "oct";
	const string MONTH_NOVEMBER = "november";
	const string MONTH_NOV = "nov";
	const string MONTH_DECEMBER = "december";
	const string MONTH_DEC = "dec";



	const std::size_t TIMER_24HR_LENGTH = 6;
	const std::size_t TIMER_24_LENGTH = 4;
	const std::size_t TIMER_TIME_LOWER_LENGTH = 2;
	const std::size_t TIMER_TIME_UPPER_LENGTH = 8;
	const std::size_t TIMER_TIME_EXCLUDED_LENGTH = 5;

	//tasklist constants
	const string LIST_COMPLETED = " listcompleted";
	const std::size_t LIST_COMPLETED_LENGTH = 14;
	const string LIST_TO_DO = " listtodo";
	const std::size_t LIST_TO_DO_LENGTH = 9;
	const string LIST_OVERDUED = " listoverdued";
	const std::size_t LIST_OVERDUED_LENGTH = 13;

	const string TIME_ANTE_MERIDIAN = "am";
	const string TIME_POST_MERIDIAN = "pm";
	const int MONTH_CORRECTION = 1;
	const int YEAR_CORRECTION = 1900;
};

#endif