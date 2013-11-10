#ifndef _LOGIC_PARSER_H_
#define _LOGIC_PARSER_H_
#define PROGRAM_NAME "4get"
#include <ctype.h>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <assert.h>
#include "common_message.h"
#include "Log.h"

// handled by John Kuan (A0097592M)

using namespace std;
using namespace Enum;
using namespace Commands;
using namespace Message;
using namespace Constants;
class Parser
{
	vector< vector<string> > dictionaryCommands;
	vector< vector<string> > dictionaryRepeatCommands;
	vector<string> dictionaryDates;
	vector<string> dictionaryMonth;
	vector<string> dictionaryTime;
	vector<string> dictionaryMarker;

private:
	static const char MARKER;
	static const size_t MARKER_LENGTH;
	static const char MARKER_COMMA;
	static const size_t MARKER_COMMA_LENGTH;
	static const char MARKER_ENCLOSE;
	static const size_t MARKER_ENCLOSE_LENGTH;
	static const string MARKER_SPACE;
	static const size_t MARKER_SPACE_LENGTH;
	static const string MARKER_AT;
	static const size_t MARKER_AT_LENGTH;
	static const string MARKER_NEAR;
	static const size_t MARKER_NEAR_LENGTH;
	static const string MARKER_BY;
	static const size_t MARKER_BY_LENGTH;
	static const string MARKER_DUE;
	static const size_t MARKER_DUE_LENGTH;
	static const string MARKER_FROM;
	static const size_t MARKER_FROM_LENGTH;
	static const string MARKER_TO;
	static const size_t MARKER_TO_LENGTH;
	static const string MARKER_COMMA_TO;
	static const size_t MARKER_COMMA_TO_LENGTH;
	static const string MARKER_ON;
	static const size_t MARKER_ON_LENGTH;
	static const string MARKER_REPEAT;
	static const size_t MARKER_REPEAT_LENGTH;
	static const string MARKER_PRIORITY;
	static const size_t MARKER_PRIORITY_LENGTH;
	static const string MARKER_PRIORITY_HIGH;
	static const size_t MARKER_PRIORITY_HIGH_LENGTH;
	static const string MARKER_PRIORITY_NORMAL;
	static const size_t MARKER_PRIORITY_NORMAL_LENGTH;
	static const string MARKER_DONE;
	static const size_t MARKER_DONE_LENGTH;
	static const string MARKER_COMPLETED;
	static const size_t MARKER_COMPLETED_LENGTH;
	static const string MARKER_UNDONE;
	static const size_t MARKER_UNDONE_LENGTH;
	static const string MARKER_INCOMPLETE;
	static const size_t MARKER_INCOMPLETE_LENGTH;

	static const int DICTIONARY_COMMAND_SIZE;
	static const int DICTIONARY_ADD_INDEX;
	static const int DICTIONARY_DELETE_INDEX;
	static const int DICTIONARY_MODIFY_INDEX;
	static const int DICTIONARY_MARK_INDEX;
	static const int DICTIONARY_UNDO_INDEX;
	static const int DICTIONARY_REDO_INDEX;
	static const int DICTIONARY_SHOW_INDEX;
	static const int DICTIONARY_SHOWALL_INDEX;
	static const int REPEAT_COMMAND_SIZE;
	static const int REPEAT_DAILY_INDEX;
	static const int REPEAT_WEEKLY_INDEX;
	static const int REPEAT_FORTNIGHTLY_INDEX;
	static const int REPEAT_MONTHLY_INDEX;
	static const int REPEAT_ANNUALLY_INDEX;
	static const string REPEAT_DAILY;
	static const string REPEAT_EVERY_DAY;
	static const string REPEAT_WEEKLY;
	static const string REPEAT_EVERY_WEEK;
	static const string REPEAT_FORTNIGHTLY;
	static const string REPEAT_EVERY_FORTNIGHT;
	static const string REPEAT_MONTHLY;
	static const string REPEAT_EVERY_MONTH;
	static const string REPEAT_ANNUALLY;
	static const string REPEAT_EVERY_YEAR;
	static const string REPEAT_EVERY;
	static const string REPEAT_NULL;

	static const int SLOT_COUNT_1;
	static const int SLOT_COUNT_2;
	static const int SPACE_DIFF_0;
	static const int SPACE_DIFF_3;
	static const int LENGTH_0;
	static const int LENGTH_3;
	static const int LENGTH_4;
	static const int LENGTH_5;
	static const int LENGTH_6;
	static const int LENGTH_10;
	static const int LENGTH_11;
	static const int DATE_MAX;

	//istringstream iss;
	string _textInput; // Main input
	string textInput; // lower case input
	string textCommand;
	string textDescription;
	string textVenue;
	string textStart;
	string textStartDate;
	string textStartTime;
	string textEnd;
	string textEndDate;
	string textEndTime;
	string textRepeat;
	string textPriority;
	string textSlotStartNumber;
	string textSlotEndNumber;

public:
	// callable by executor
	Parser();
	void parseInput(string, vector<string>&);
	string getCommand(); // function for testing validity of command
	

private:	
	void parseReset();
	void processCommand(string, vector<string>&);
	void populateContainer(vector<string>& );

	//separate functions
	bool separateInput(Command, vector<string>&);
	bool separateFunctionAdd(vector<string>&);
	bool separateFunctionDelete(vector<string>&);
	bool separateFunctionMark(vector<string>& );
	bool separateFunctionModify(vector<string>&);
	bool separateFunctionUndo(vector<string>&);
	bool separateFunctionShow(vector<string>&);
	bool separateFunctionRedo(vector<string>&);
	bool separateFunctionShowAll(vector<string>&);

	//determine functions
	bool determineVenue();
	bool determineDateAndTime();
	bool determinePriority();
	bool determineRepeat();
	bool determineSlot();
	bool determineStatus();
	size_t determindExtractLength(size_t, 
								  size_t, 
								  string, 
								  size_t&);

	//parser dictionary setup
	void loadDictionary();
	void loadDatesDictionary();
	void loadMonthDictionary();
	void loadTimeDictionary();
	void loadCommandDictionary();
	void loadRepeatDictionary();
	void loadMarkerDictionary();

	//parser scan dictionaries
	bool scanDictionary(string);
	bool scanTimerDictionary(string);
	bool scanTimeDictionary(string);
	bool scanDatesDictionary(string);
	bool scanMonthDictionary(string);
	string scanCommandDictionary(string);
	string scanRepeatDictionary(string);
	bool scanMarkerDictionary(string);

	void shortenInput(size_t, size_t);
	void removeAllBorderSpace();
	void removeBorderSpaces(string& );
	void parseAllTimeAndDate();
	bool parseTimeAndDate(string&, string&, string&);

	void toLowerCase(string&);
	string getFirstWord(string);
	void removeFirstWord(string&);
	bool isParseInt(string, int&);
	bool isInt(string);
};
#endif