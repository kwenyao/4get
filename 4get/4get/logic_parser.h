#ifndef _LOGIC_PARSER_H_
#define _LOGIC_PARSER_H_
#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <assert.h>
#include "common_message.h"

// handled by John Kuan (A0097592M)

using namespace std;
using namespace Enum;
using namespace Commands;
using namespace Message;
using namespace Constants;
class Parser
{
private:

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
	bool parseTimeAndDate(string& str, string& strDate, string& strTime);

	//int separateInput(int state);
	void toLowerCase(string &string);
	string getFirstWord(string input);
	void removeFirstWord(string &input);
	bool isParseInt(string input, int &value);
};
#endif