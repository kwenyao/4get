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
	vector<string> dictionaryAddCommands;
	vector<string> dictionaryDeleteCommands;
	vector<string> dictionaryModifyCommands;
	vector<string> dictionaryMarkCommands;
	vector<string> dictionaryUndoCommands;
	vector<string> dictionaryRedoCommands;
	vector<string> dictionaryShowCommands;
	vector<string> dictionaryDates;
	vector<string> dictionaryMonth;
	vector<string> dictionaryTime;
	vector<string> dictionaryMarker;

private:

	static const char MARKER;
	static const std::size_t MARKER_LENGTH;
	static const char MARKER_COMMA;
	static const std::size_t MARKER_COMMA_LENGTH;
	static const char MARKER_ENCLOSE;
	static const std::size_t MARKER_ENCLOSE_LENGTH;
	static const string MARKER_AT;
	static const std::size_t MARKER_AT_LENGTH;
	static const string MARKER_NEAR;
	static const std::size_t MARKER_NEAR_LENGTH;
	static const string MARKER_BY;
	static const std::size_t MARKER_BY_LENGTH;
	static const string MARKER_FROM;
	static const std::size_t MARKER_FROM_LENGTH;
	static const string MARKER_TO;
	static const std::size_t MARKER_TO_LENGTH;
	static const string MARKER_REMIND;
	static const std::size_t MARKER_REMIND_LENGTH;
	static const string MARKER_ON;
	static const std::size_t MARKER_ON_LENGTH;
	static const string MARKER_REPEAT;
	static const std::size_t MARKER_REPEAT_LENGTH;
	static const string MARKER_PRIORITY;
	static const std::size_t MARKER_PRIORITY_LENGTH;
	static const string MARKER_PRIORITY_HIGH;
	static const std::size_t MARKER_PRIORITY_HIGH_LENGTH;
	static const string MARKER_PRIORITY_NORMAL;
	static const std::size_t MARKER_PRIORITY_NORMAL_LENGTH;
	static const string MARKER_DONE;
	static const std::size_t MARKER_DONE_LENGTH;
	static const string MARKER_COMPLETED;
	static const std::size_t MARKER_COMPLETED_LENGTH;
	static const string MARKER_UNDONE;
	static const std::size_t MARKER_UNDONE_LENGTH;
	static const string MARKER_INCOMPLETE;
	static const std::size_t MARKER_INCOMPLETE_LENGTH;


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
	//string textStatus;
	string textRemind;
	string textRemindDate;
	string textRemindTime;
	string textSlotNumber;

public:
	Parser();

	// callable by executor

	void parseInput(string input, vector<string>& inputBits);
	// function for testing validity of command
	string getCommand();
	bool parseTimeAndDate(string& str, string& strDate, string& strTime);

private:	
	void parseReset();
	void processCommand(string commandString, vector<string>& inputBits);
	void populateContainer(vector<string>& inputBits);

	//separate functions
	bool separateInput(Command userCommand, vector<string>& inputBits);
	bool separateFunctionAdd(vector<string>& inputBits);
	bool separateFunctionDelete(vector<string>& inputBits);
	//bool separateFunctionDeleteAll(vector<string>& inputBits);
	bool separateFunctionMark(vector<string>& inputBits);
	//bool separateFunctionMarkDone(vector<string>& inputBits);
	bool separateFunctionModify(vector<string>& inputBits);
	bool separateFunctionUndo(vector<string>& inputBits);
	bool separateFunctionShow(vector<string>& inputBits); // Show, Display, GoTo. This show user task in a timespan.
	bool separateFunctionRedo(vector<string>& inputBits);

	bool determineVenue();
	bool determineDateAndTime();
	bool determineReminder();
	bool determinePriority();
	bool determineRepeat();
	bool determineSlot();
	//bool determineTaskList();
	bool determineStatus();
	std::size_t determindExtractLength(std::size_t found, std::size_t foundComma, string markerConstant, std::size_t& extractStart);

	void shortenInput(std::size_t partitionStart, std::size_t partitionEnd);
	void removeAllBorderSpace();
	void removeBorderSpaces(string& str);
	void parseAllTimeAndDate();

	//int separateInput(int state);
	void toLowerCase(string &string);
	string getFirstWord(string input);
	void removeFirstWord(string &input);
	bool isParseInt(string input, int &value);

	//parser dictionary setup
	void loadDictionary();
	void loadDateDictionary();
	void loadMonthDictionary();
	void loadTimeDictionary();
	void loadCommandDictionary();
	void loadMarkerDictionary();
	bool scanDictionary(string);
	bool scanTimeDictionary(string);
	bool scanDatesDictionary(string);
	bool scanMonthDictionary(string);
	string scanCommandDictonary(string);
	bool scanMarkerDictionary(string);
};
#endif