#include "logic_parser.h"

const char Parser::MARKER_COMMA = ',';
const std::size_t Parser::MARKER_COMMA_LENGTH = 1;

const char Parser::MARKER_ENCLOSE = ' ';
const std::size_t Parser::MARKER_ENCLOSE_LENGTH = 1;

const string Parser::MARKER_AT = ",at";
const std::size_t Parser::MARKER_AT_LENGTH = 3;

const string Parser::MARKER_NEAR = ",near";
const std::size_t Parser::MARKER_NEAR_LENGTH = 3;

const string Parser::MARKER_BY = ",by";
const std::size_t Parser::MARKER_BY_LENGTH = 3;

const string Parser::MARKER_FROM = ",from";
const std::size_t Parser::MARKER_FROM_LENGTH = 5;

const string Parser::MARKER_TO = "to";
const std::size_t Parser::MARKER_TO_LENGTH = 2;

const string Parser::MARKER_REMIND = ",remind";
const std::size_t Parser::MARKER_REMIND_LENGTH = 7;

const string Parser::MARKER_ON = "on";
const std::size_t Parser::MARKER_ON_LENGTH = 2;

const string Parser::MARKER_REPEAT = ",repeat";
const std::size_t Parser::MARKER_REPEAT_LENGTH = 7;

const string Parser::MARKER_PRIORITY = ",!";
const std::size_t Parser::MARKER_PRIORITY_LENGTH = 2;

const string Parser::MARKER_PRIORITY_HIGH = ",high";
const std::size_t Parser::MARKER_PRIORITY_HIGH_LENGTH = 5;

const string Parser::MARKER_PRIORITY_NORMAL = ",normal";
const std::size_t Parser::MARKER_PRIORITY_NORMAL_LENGTH = 7;

const string Parser::MARKER_DONE = "done";
const std::size_t Parser::MARKER_DONE_LENGTH = 4;

const string Parser::MARKER_COMPLETED = "completed";
const std::size_t Parser::MARKER_COMPLETED_LENGTH = 9;

const string Parser::MARKER_UNDONE = "undone";
const std::size_t Parser::MARKER_UNDONE_LENGTH = 6;

const string Parser::MARKER_INCOMPLETE = "incomplete";
const std::size_t Parser::MARKER_INCOMPLETE_LENGTH = 10;

const int Parser::DICTIONARY_ADD = 0;
const int Parser::DICTIONARY_DELETE = 1;
const int Parser::DICTIONARY_MARK = 2;
const int Parser::DICTIONARY_MODIFY = 3;
const int Parser::DICTIONARY_UNDO = 4;
const int Parser::DICTIONARY_REDO = 5;
const int Parser::DICTIONARY_SHOW = 6;
const int Parser::DICTIONARY_SHOWALL = 7;



Parser::Parser()
{
	parseReset();
	loadDictionary();
}
void Parser::parseReset()
{
	textInput = INITIALIZE_STRING_BLANK;
	_textInput = INITIALIZE_STRING_BLANK;
	textCommand = INITIALIZE_STRING_BLANK;
	textDescription = INITIALIZE_STRING_BLANK;
	textVenue = INITIALIZE_STRING_BLANK;
	textStart = INITIALIZE_STRING_BLANK;
	textStartDate = INITIALIZE_STRING_BLANK;
	textStartTime = INITIALIZE_STRING_BLANK;
	textEnd = INITIALIZE_STRING_BLANK;
	textEndDate = INITIALIZE_STRING_BLANK;
	textEndTime = INITIALIZE_STRING_BLANK;
	textRepeat = INITIALIZE_STRING_BLANK;
	textPriority = INITIALIZE_STRING_BLANK;
	//textStatus = INITIALIZE_STRING_BLANK;
	textRemind = INITIALIZE_STRING_BLANK;
	textRemindDate = INITIALIZE_STRING_BLANK;
	textRemindTime = INITIALIZE_STRING_BLANK;
	textSlotStartNumber = INITIALIZE_STRING_BLANK;
	textSlotEndNumber = INITIALIZE_STRING_BLANK;
}
void Parser::processCommand(string commandString, vector<string>& inputBits)
{
	string command;
	try {
		try{
			command = scanCommandDictionary(commandString);
			if(command == COMMAND_NULL)
				throw MESSAGE_ERROR_COMMAND_ERROR;
		}
		catch(string error){
			throw;
		}
		inputBits[SLOT_COMMAND] = command;
		if(command == COMMAND_ADD){
			try{
				if(!separateFunctionAdd(inputBits))
					throw MESSAGE_ERROR_COMMAND_ADD;
			}

			catch(string error){
				throw error;
			}
		}
		else if(command == COMMAND_DELETE){
			try{
				if(!separateFunctionDelete(inputBits))
					throw MESSAGE_ERROR_COMMAND_DELETE;
			}

			catch(string error){
				throw error;
			}
		}
		else if(command == COMMAND_MARK){
			try{
				if(!separateFunctionMark(inputBits))
					throw MESSAGE_ERROR_COMMAND_MARK;
			}

			catch(string error){
				throw error;
			}
		}
		else if(command == COMMAND_MODIFY){
			try{
				if(!separateFunctionModify(inputBits))
					throw MESSAGE_ERROR_COMMAND_MODIFY;
			}

			catch(string error){
				throw error;
			}
		}
		else if(command == COMMAND_UNDO){
			try{
				if(!separateFunctionUndo(inputBits))
					throw MESSAGE_ERROR_COMMAND_UNDO;
			}

			catch(string error){
				throw error;
			}
		}
		else if(command == COMMAND_REDO){
			try{
				if(!separateFunctionRedo(inputBits))
					throw MESSAGE_ERROR_COMMAND_REDO;
			}

			catch(string error){
				throw error;
			}
		}
		else if(command == COMMAND_SHOW){
			try{
				if(!separateFunctionShow(inputBits))
					throw MESSAGE_ERROR_COMMAND_SHOW;
			}

			catch(string error){
				throw error;
			}
		}
		else if(command == COMMAND_SHOWALL){
			try{
				if(!separateFunctionShowAll(inputBits))
					throw MESSAGE_ERROR_COMMAND_SHOW;
			}
			catch(string error){
				throw error;
			}
		}
	}
	catch(string error){
		throw error;
	}
	/*
	try{
	if(commandString.compare(COMMAND_A)==COMPARE_SUCCESS || commandString.compare(COMMAND_ADD)==COMPARE_SUCCESS || commandString.compare(COMMAND_CREATE)==COMPARE_SUCCESS){
	inputBits[SLOT_COMMAND] = COMMAND_ADD;
	try{
	if(!separateInput(commandAdd, inputBits)){
	throw MESSAGE_ERROR_COMMAND_ADD;
	}
	}
	catch(string error){
	throw;
	}

	}

	else if(commandString.compare(COMMAND_DEL)==COMPARE_SUCCESS || commandString.compare(COMMAND_DELETE)==COMPARE_SUCCESS || commandString.compare(COMMAND_ERASE)==COMPARE_SUCCESS ||commandString.compare(COMMAND_REM)==COMPARE_SUCCESS || commandString.compare(COMMAND_REMOVE)==COMPARE_SUCCESS) {
	inputBits[SLOT_COMMAND] = COMMAND_DELETE;
	try{
	if(!separateInput(commandDelete, inputBits)){
	throw MESSAGE_ERROR_COMMAND_DELETE;
	}
	}
	catch(string error){
	throw;
	}
	}
	else if(commandString.compare(COMMAND_M)==COMPARE_SUCCESS || commandString.compare(COMMAND_MARK)==COMPARE_SUCCESS || commandString.compare(COMMAND_DONE)==COMPARE_SUCCESS) {
	inputBits[SLOT_COMMAND] = COMMAND_MARK;
	try{
	if(!separateInput(commandMark, inputBits)){
	throw MESSAGE_ERROR_COMMAND_MARK;
	}
	}
	catch(string error){
	throw;
	}
	}
	else if(commandString.compare(COMMAND_MOD)==COMPARE_SUCCESS || commandString.compare(COMMAND_MODIFY)==COMPARE_SUCCESS || commandString.compare(COMMAND_UPDATE)==COMPARE_SUCCESS) {
	inputBits[SLOT_COMMAND] = COMMAND_MODIFY;
	try{
	if(!separateInput(commandModify, inputBits)){
	throw MESSAGE_ERROR_COMMAND_MODIFY;
	}
	}
	catch(string error){
	throw;
	}
	}
	else if(commandString.compare(COMMAND_UNDO)==COMPARE_SUCCESS) {
	inputBits[SLOT_COMMAND] = COMMAND_UNDO;
	try{
	if(!separateInput(commandUndo, inputBits)){
	throw MESSAGE_ERROR_COMMAND_UNDO;
	}
	}
	catch(string error){
	throw;
	}
	}
	else if(commandString.compare(COMMAND_SHOW)==COMPARE_SUCCESS || commandString.compare(COMMAND_DISPLAY)==COMPARE_SUCCESS || commandString.compare(COMMAND_SEARCH)==COMPARE_SUCCESS){
	inputBits[SLOT_COMMAND] = COMMAND_SHOW;
	try{
	if(!separateInput(commandShow, inputBits)){
	throw MESSAGE_ERROR_COMMAND_SHOW;
	}
	}
	catch(string error){
	throw;
	}
	}
	else if(commandString.compare(COMMAND_SHOWALL)==COMPARE_SUCCESS || commandString.compare(COMMAND_DISPLAYALL)==COMPARE_SUCCESS || commandString.compare(COMMAND_SEARCHALL)==COMPARE_SUCCESS){
	inputBits[SLOT_COMMAND] = COMMAND_SHOWALL;
	try{
	if(!separateInput(commandShow, inputBits)){
	throw MESSAGE_ERROR_COMMAND_SHOW;
	}
	}
	catch(string error){
	throw;
	}
	}

	/*else if(commandString.compare(COMMAND_WHAT)==COMPARE_SUCCESS){
	inputBits[SLOT_COMMAND] = COMMAND_WHAT;
	if(!separateInput(commandQuery, inputBits)){
	throw MESSAGE_ERROR_COMMAND_QUERY;
	}
	}
	else if(commandString.compare(COMMAND_WHEN)==COMPARE_SUCCESS){
	inputBits[SLOT_COMMAND] = COMMAND_WHEN;
	if(!separateInput(commandQuery, inputBits)){
	throw MESSAGE_ERROR_COMMAND_QUERY;
	}
	}
	else if(commandString.compare(COMMAND_REDO)==COMPARE_SUCCESS) {
	inputBits[SLOT_COMMAND] = COMMAND_REDO;
	try{
	if(!separateInput(commandRedo, inputBits)){
	throw MESSAGE_ERROR_COMMAND_REDO;
	}
	}
	catch(string error){
	throw;
	}
	}
	}
	catch(string error)
	{
	throw error;
	}
	*/
}
void Parser::parseInput(string input, vector<string>& inputBits)
{
	parseReset();
	removeFirstWord(input);
	_textInput = textInput = input;
	toLowerCase(textInput);

	processCommand(textCommand, inputBits);
	removeAllBorderSpace();
	populateContainer(inputBits);

}
bool Parser::separateInput(Command userCommand, vector<string>& inputBits)
{

	switch (userCommand){
	case commandAdd: 
		return separateFunctionAdd(inputBits);
	case commandDelete:
		return separateFunctionDelete(inputBits);
	case commandMark:
		return separateFunctionMark(inputBits);
	case commandModify:
		return separateFunctionModify(inputBits);
	case commandUndo:
		return separateFunctionUndo(inputBits);
	case commandShow:
		return separateFunctionShow(inputBits);
	case commandRedo:
		return separateFunctionRedo(inputBits);
	case commandShowAll:
		return separateFunctionShowAll(inputBits);
	default:
		return false;
	}



}
bool Parser::separateFunctionAdd(vector<string>& inputBits)
{
	determineVenue();
	//cout << "no venue" << endl;
	determineDateAndTime();
	//cout << "no date and time" << endl;
	determineRepeat();
	//cout << "no repeat" << endl;
	determinePriority();
	//cout << "no priority" << endl;
	determineReminder();
	//cout << "no reminder" << endl;
	textDescription = _textInput;
	if(textDescription.empty())
		throw MESSAGE_ERROR_NO_DESCRIPTION;
	logging(MESSAGE_SUCCESS_PARSED, Info, Pass);
	/*
	cout << "command: <" << textCommand << ">" << endl;
	cout << "description: <" << textDescription << ">" << endl;
	cout << "venue: <" << textVenue << ">" << endl;
	cout << "start date: <" << textStartDate << ">" << endl;
	cout << "start time: <" << textStartTime << ">" << endl;
	cout << "end date: <" << textEndDate << ">" << endl;
	cout << "end time: <" << textEndTime << ">" << endl;
	cout << "repeat: <" << textRepeat << ">" << endl;
	cout << "priority: <" << textPriority << ">" << endl;
	cout << "reminder date: <" << textRemindDate << ">" << endl;
	cout << "reminder time: <" << textRemindTime << ">" << endl;
	*/

	return true;
}
bool Parser::separateFunctionDelete(vector<string>& inputBits)
{
	if(!determineSlot()){
		cout << "no slot" << endl;
		logging(MESSAGE_ERROR_NO_SLOT_NUM,Error,None);
		throw MESSAGE_ERROR_NO_SLOT_NUM;
	}

	logging(MESSAGE_SUCCESS_PARSED, Info, Pass);
	return true;
}
bool Parser::separateFunctionMark(vector<string>& inputBits)
{
	//if(!determineStatus())
	//	cout << "no status" << endl;
	if(!determineSlot()){
		cout << "no slot" << endl;
		logging(MESSAGE_ERROR_NO_SLOT_NUM,Error,None);
		throw MESSAGE_ERROR_NO_SLOT_NUM;
	}

	//cout << "slot number: <" << textSlotNumber << ">" << endl;
	//cout << "TaskStatus: <" << textStatus <<  ">" << endl;
	logging(MESSAGE_SUCCESS_PARSED,Info,None);
	return true;
}
bool Parser::separateFunctionModify(vector<string>& inputBits)
{
	if(!determineSlot()) {
		cout << "no slot" << endl;
		logging(MESSAGE_ERROR_NO_SLOT_NUM,Error,None);
		throw MESSAGE_ERROR_NO_SLOT_NUM;
	}
	if(!textSlotEndNumber.empty())
		throw MESSAGE_ERROR_LIMIT_ONE_SLOT;

	determineVenue();
	determineDateAndTime();
	determineRepeat();
	determinePriority();
	determineReminder();
	parseAllTimeAndDate();

	textDescription = _textInput;
	logging(MESSAGE_SUCCESS_PARSED, Info, Pass);

	return true;
}
bool Parser::separateFunctionUndo(vector<string>& inputBits)
{
	return true;
}
bool Parser::separateFunctionShow(vector<string>& inputBits)
{
	bool hasResult = false;

	if(determineDateAndTime()){											
		logging(MESSAGE_SUCCESS_PARSED, Info, Pass);					
		hasResult = true;
	}
	if(determineVenue()){
		logging(MESSAGE_SUCCESS_PARSED, Info, Pass);
		hasResult = true;
	}
	if(determineReminder()){
		logging(MESSAGE_SUCCESS_PARSED, Info, Pass);
		hasResult = true;
	}
	if(determinePriority()){
		logging(MESSAGE_SUCCESS_PARSED, Info, Pass);
		hasResult = true;
	}
	if(determineRepeat()){
		logging(MESSAGE_SUCCESS_PARSED, Info, Pass);
		hasResult = true;
	}

	if(!textInput.empty()){
		textDescription = _textInput;
		hasResult = true;
	}

	logging(MESSAGE_ERROR_COMMAND_SHOW, Info, Pass);
	return hasResult;
}
bool Parser::separateFunctionRedo(vector<string>& inputBits)
{
	return true;
}

bool Parser::separateFunctionShowAll(vector<string>& inputBits)
{
	return true;
}

bool Parser::determineVenue()
{
	std::size_t found = INITIALIZE_SIZE_T;
	std::size_t foundComma = INITIALIZE_SIZE_T;
	std::size_t extractStartPos = INITIALIZE_SIZE_T;
	std::size_t extractLength = INITIALIZE_SIZE_T;
	std::size_t stringLength = textInput.size();
	std::size_t i = INITIALIZE_SIZE_T;
	string marker = INITIALIZE_STRING_BLANK;

	bool isVenueDetermined = !textVenue.empty();
	if(isVenueDetermined)

	if(textInput.find(MARKER_AT)!=std::string::npos){
		found = textInput.find(MARKER_AT);
		if(textInput.find(MARKER_COMMA, found+MARKER_AT_LENGTH)!=std::string::npos){
			foundComma = textInput.find(MARKER_COMMA, found+MARKER_AT_LENGTH);
			extractLength = determindExtractLength(found, foundComma, MARKER_AT, extractStartPos);
			i = foundComma;
			while(textInput[i]!=MARKER_ENCLOSE && i!=stringLength)
				marker += textInput[i++];
			if(marker==MARKER_BY || marker==MARKER_FROM || marker==MARKER_REMIND || marker==MARKER_REPEAT || marker==MARKER_PRIORITY || marker==MARKER_PRIORITY_HIGH || marker==MARKER_PRIORITY_NORMAL){
				textVenue = _textInput.substr(extractStartPos, extractLength);
				shortenInput(found, foundComma);
				return true;
			}
			else{
				logging(MESSAGE_ERROR_WRONG_KEYWORD,Error,None);
				throw MESSAGE_ERROR_WRONG_KEYWORD;
			}
		}
		else{
			extractLength = determindExtractLength(found, stringLength, MARKER_AT, extractStartPos);
			textVenue = _textInput.substr(extractStartPos, ++extractLength);
			shortenInput(found, stringLength);
			return true;
		}
	}
	else if(textInput.find(MARKER_NEAR)!=std::string::npos){
		found = textInput.find(MARKER_NEAR);
		if(textInput.find(MARKER_COMMA, found+MARKER_NEAR_LENGTH)!=std::string::npos){
			foundComma = textInput.find(MARKER_COMMA, found+MARKER_NEAR_LENGTH);
			extractLength = determindExtractLength(found, foundComma, MARKER_NEAR, extractStartPos);
			i = foundComma;
			while(textInput[i]!=MARKER_ENCLOSE && i!=stringLength)
				marker += textInput[i++];
			if(marker==MARKER_BY || marker==MARKER_FROM || marker==MARKER_REMIND || marker==MARKER_REPEAT || marker==MARKER_PRIORITY || marker==MARKER_PRIORITY_HIGH || marker==MARKER_PRIORITY_NORMAL){
				textVenue = _textInput.substr(extractStartPos, extractLength);
				shortenInput(found, foundComma);
				return true;
			}
			else{
				logging(MESSAGE_ERROR_WRONG_KEYWORD,Error,None);
				throw MESSAGE_ERROR_WRONG_KEYWORD;
			}
		}
		else{
			extractLength = determindExtractLength(found, stringLength, MARKER_NEAR, extractStartPos);
			textVenue = _textInput.substr(extractStartPos, ++extractLength);
			shortenInput(found, stringLength);
			return true;
		}
	}
	else
		return false;																			//No location keywords found
}
bool Parser::determineDateAndTime()
{
	std::size_t found = INITIALIZE_SIZE_T;
	std::size_t foundComma = INITIALIZE_SIZE_T;
	std::size_t foundTo = INITIALIZE_SIZE_T;
	std::size_t extractStartPos = INITIALIZE_SIZE_T;
	std::size_t extractLength = INITIALIZE_SIZE_T;
	std::size_t stringLength = textInput.size();
	std::size_t i = INITIALIZE_SIZE_T;
	string marker = INITIALIZE_STRING_BLANK;

	//If found By
	if(textInput.find(MARKER_BY)!=std::string::npos){
		found = textInput.find(MARKER_BY);
		if(textInput.find(MARKER_COMMA, found+MARKER_BY_LENGTH)!=std::string::npos ){			//try find comma
			foundComma = textInput.find(MARKER_COMMA, found+MARKER_BY_LENGTH);
			extractLength = determindExtractLength(found, foundComma, MARKER_BY, extractStartPos);
			i = foundComma; 
			while(textInput[i]!=MARKER_ENCLOSE && i!=stringLength)								//try forming keyword
				marker += textInput[i++];
			if(marker==MARKER_AT || marker==MARKER_NEAR || marker==MARKER_REMIND || marker==MARKER_REPEAT || marker==MARKER_PRIORITY || marker==MARKER_PRIORITY_HIGH || marker==MARKER_PRIORITY_NORMAL){
				textEnd = _textInput.substr(extractStartPos, extractLength);
				shortenInput(found, foundComma);
				parseAllTimeAndDate();
				return true;
			}
			else{
				logging(MESSAGE_ERROR_WRONG_KEYWORD,Error,None);
				throw MESSAGE_ERROR_WRONG_KEYWORD;
			}//wrong keyword definition
		}
		else{																					//by keyword is the last key input
			extractLength = determindExtractLength(found, stringLength, MARKER_BY, extractStartPos);
			textEnd = _textInput.substr(extractStartPos, ++extractLength);
			shortenInput(found, stringLength);
			parseAllTimeAndDate();
			return true;
		}
	}
	else if(textInput.find(MARKER_FROM)!=std::string::npos){									//try find from
		found = textInput.find(MARKER_FROM);
		if(textInput.find(MARKER_TO, found+MARKER_FROM_LENGTH)!=std::string::npos){				//try find to
			foundTo = textInput.find(MARKER_TO, found+MARKER_FROM_LENGTH);
			extractLength = determindExtractLength(found, foundTo, MARKER_FROM, extractStartPos);
			textStart = _textInput.substr(extractStartPos, extractLength);
			if(textInput.find(MARKER_COMMA, foundTo)!=std::string::npos){						//try find comma
				foundComma = textInput.find(MARKER_COMMA, foundTo);
				extractLength = determindExtractLength(foundTo, foundComma, MARKER_TO, extractStartPos);
				i = foundComma; 
				while(textInput[i]!=MARKER_ENCLOSE && i!=stringLength)							//try forming keyword
					marker += textInput[i++];
				if(marker==MARKER_AT || marker==MARKER_NEAR || marker==MARKER_REMIND || marker==MARKER_REPEAT || marker==MARKER_PRIORITY || marker==MARKER_PRIORITY_HIGH || marker==MARKER_PRIORITY_NORMAL){
					textEnd = _textInput.substr(extractStartPos, extractLength);
					shortenInput(found, foundComma);
					parseAllTimeAndDate();
					return true;
				}
				else{
					logging(MESSAGE_ERROR_WRONG_KEYWORD,Error,None);
					throw MESSAGE_ERROR_WRONG_KEYWORD;
				}
			}
			else{																				//from and to combination keyword is the last keyword  
				extractLength = determindExtractLength(foundTo, stringLength, MARKER_TO, extractStartPos);
				textEnd = _textInput.substr(extractStartPos, ++extractLength);
				shortenInput(found, stringLength);
				parseAllTimeAndDate();
				return true;
			}
		}
		else{																					//wrong keyword definition
			logging(MESSAGE_ERROR_WRONG_KEYWORD,Error,None);
			throw MESSAGE_ERROR_WRONG_KEYWORD;
		}
	}
	else																						//not specified date aka. Floating
		return true; 
}
bool Parser::determineRepeat()
{
	std::size_t found = INITIALIZE_SIZE_T;
	std::size_t foundComma = INITIALIZE_SIZE_T;
	std::size_t extractStartPos = INITIALIZE_SIZE_T;
	std::size_t extractLength = INITIALIZE_SIZE_T;
	std::size_t stringLength = textInput.size();
	std::size_t i = INITIALIZE_SIZE_T;
	string marker = INITIALIZE_STRING_BLANK;


	if(textInput.find(MARKER_REPEAT)!=std::string::npos){
		found = textInput.find(MARKER_REPEAT);
		if(textInput.find(MARKER_COMMA, found+MARKER_REPEAT_LENGTH)!=std::string::npos){
			foundComma = textInput.find(MARKER_COMMA, found+MARKER_REPEAT_LENGTH);
			extractLength = determindExtractLength(found, foundComma, MARKER_REPEAT, extractStartPos);
			i = foundComma;
			while(textInput[i]!=MARKER_ENCLOSE && i!=stringLength)
				marker += textInput[i++];
			if(marker==MARKER_AT || marker==MARKER_NEAR || marker==MARKER_REMIND || marker==MARKER_BY || marker==MARKER_FROM || marker==MARKER_PRIORITY || marker==MARKER_PRIORITY_HIGH || marker==MARKER_PRIORITY_NORMAL){
				textRepeat = _textInput.substr(extractStartPos, extractLength);
				shortenInput(found, foundComma);
				return true;
			}
			else{
				logging(MESSAGE_ERROR_WRONG_KEYWORD,Error,None);
				throw MESSAGE_ERROR_WRONG_KEYWORD;
			}
		}
		else{
			extractLength = determindExtractLength(found, stringLength, MARKER_REPEAT, extractStartPos);
			textRepeat = _textInput.substr(extractStartPos, ++extractLength);
			shortenInput(found, stringLength);
			return true;
		}
	}

	else
		return false; 
}
bool Parser::determinePriority()
{
	std::size_t found = INITIALIZE_SIZE_T;
	std::size_t foundComma = INITIALIZE_SIZE_T;
	std::size_t foundEnclose = INITIALIZE_SIZE_T;
	std::size_t extractStartPos = INITIALIZE_SIZE_T;
	std::size_t extractLength = INITIALIZE_SIZE_T;
	std::size_t stringLength = textInput.size();
	std::size_t i = INITIALIZE_SIZE_T;
	string marker = INITIALIZE_STRING_BLANK;


	if(textInput.rfind(MARKER_PRIORITY)!=std::string::npos){
		found = textInput.find(MARKER_PRIORITY);
		if(textInput.find(MARKER_ENCLOSE, found+MARKER_PRIORITY_LENGTH)!=std::string::npos){
			foundEnclose = textInput.find(MARKER_ENCLOSE, found+MARKER_PRIORITY_LENGTH);
			extractLength = determindExtractLength(found, foundEnclose, MARKER_PRIORITY, extractStartPos);
			textPriority = _textInput.substr(extractStartPos, extractLength);
			shortenInput(found, foundEnclose);
			return true;
		}

		else{
			extractStartPos = found;
			textPriority = _textInput.substr(++extractStartPos);
			shortenInput(found, MARKER_PRIORITY_LENGTH);
			return true;
		}
	}

	else if(textInput.find(MARKER_PRIORITY_HIGH)!=std::string::npos){
		found = textInput.find(MARKER_PRIORITY_HIGH);
		if(textInput.find(MARKER_COMMA, found+MARKER_PRIORITY_HIGH_LENGTH)!=std::string::npos){
			foundComma = textInput.find(MARKER_COMMA, found+MARKER_PRIORITY_HIGH_LENGTH);
			extractLength = determindExtractLength(found, foundComma, MARKER_PRIORITY_HIGH, extractStartPos);
			i = foundComma;
			while(textInput[i]!=MARKER_ENCLOSE && i!=stringLength)
				marker += textInput[i++];
			if(marker==MARKER_AT || marker==MARKER_NEAR ||marker==MARKER_BY || marker==MARKER_FROM || marker==MARKER_REMIND || marker==MARKER_REPEAT){
				textPriority = _textInput.substr(extractStartPos, extractLength);
				shortenInput(found, foundComma);
				return true;
			}
			else{
				logging(MESSAGE_ERROR_WRONG_KEYWORD,Error,None);
				throw MESSAGE_ERROR_WRONG_KEYWORD;
			}
		}
		else{
			extractLength = determindExtractLength(found, stringLength, MARKER_PRIORITY_HIGH, extractStartPos);
			textPriority = _textInput.substr(extractStartPos, ++extractLength);
			shortenInput(found, stringLength);
			return true;
		}
	}

	else if(textInput.find(MARKER_PRIORITY_NORMAL)!=std::string::npos){
		found = textInput.find(MARKER_PRIORITY_NORMAL);
		if(textInput.find(MARKER_COMMA, found+MARKER_PRIORITY_NORMAL_LENGTH)!=std::string::npos){
			foundComma = textInput.find(MARKER_COMMA, found+MARKER_PRIORITY_NORMAL_LENGTH);
			extractLength = determindExtractLength(found, foundComma, MARKER_PRIORITY_NORMAL, extractStartPos);
			i = foundComma;
			while(textInput[i]!=MARKER_ENCLOSE && i!=stringLength)
				marker += textInput[i++];
			if(marker==MARKER_AT || marker==MARKER_NEAR ||marker==MARKER_BY || marker==MARKER_FROM || marker==MARKER_REMIND || marker==MARKER_REPEAT){
				textPriority = _textInput.substr(extractStartPos, extractLength);
				shortenInput(found, foundComma);
				return true;
			}
			else{
				logging(MESSAGE_ERROR_WRONG_KEYWORD,Error,None);
				throw MESSAGE_ERROR_WRONG_KEYWORD;
			}
		}
		else{
			extractLength = determindExtractLength(found, stringLength, MARKER_PRIORITY_NORMAL, extractStartPos);
			textPriority = _textInput.substr(extractStartPos, ++extractLength);
			shortenInput(found, stringLength);
			return true;
		}
	}

	else 
		return false;

}
//reminder is not neccessary. If user defines Reminder in input, then it will process.
bool Parser::determineReminder()
{
	std::size_t found = INITIALIZE_SIZE_T;
	std::size_t foundComma = INITIALIZE_SIZE_T;
	std::size_t extractStartPos = INITIALIZE_SIZE_T;
	std::size_t extractLength = INITIALIZE_SIZE_T;
	std::size_t stringLength = textInput.size();
	std::size_t i = INITIALIZE_SIZE_T;
	string marker = INITIALIZE_STRING_BLANK;


	if(textInput.find(MARKER_REMIND)!=std::string::npos){
		found = textInput.find(MARKER_REMIND);
		if(textInput.find(MARKER_COMMA, found+MARKER_REMIND_LENGTH)!=std::string::npos){
			foundComma = textInput.find(MARKER_COMMA, found+MARKER_REMIND_LENGTH);
			extractLength = determindExtractLength(found, foundComma, MARKER_REMIND, extractStartPos);
			i = foundComma;
			while(textInput[i]!=MARKER_ENCLOSE && i!=stringLength)
				marker += textInput[i++];
			if(marker==MARKER_AT || marker==MARKER_NEAR || marker==MARKER_REPEAT || marker==MARKER_BY || marker==MARKER_FROM || marker==MARKER_PRIORITY || marker==MARKER_PRIORITY_HIGH || marker==MARKER_PRIORITY_NORMAL && textInput.find(MARKER_ON, found)!=std::string::npos){
				textRemind = _textInput.substr(extractStartPos, extractLength);
				shortenInput(found, foundComma);
				return parseTimeAndDate(textRemind, textRemindDate, textRemindTime);
			}
			else{
				logging(MESSAGE_ERROR_WRONG_KEYWORD,Error,None);
				return false;
			}
		}
		else{
			extractLength = determindExtractLength(found, stringLength, MARKER_REMIND, extractStartPos);
			textRemind = _textInput.substr(extractStartPos, ++extractLength);
			shortenInput(found, stringLength);
			return parseTimeAndDate(textRemind, textRemindDate, textRemindTime);
		}
	}

	else
		return true; 
}
bool Parser::determineSlot()
{
	std::size_t extractStartPos = INITIALIZE_SIZE_T;
	size_t extractEndPos = INITIALIZE_SIZE_T;
	std::size_t found = INITIALIZE_SIZE_T;
	bool hasRange = false;
	bool startSlotFilled = false;
	int slotNumber = INITIALIZE_INT;
	int count = INITIALIZE_INT;
	istringstream buffer(textInput);
	string temp;
	while(!buffer.eof()){
		buffer >> temp;
		count++;
		if(isParseInt(temp, slotNumber) && !startSlotFilled){
			textSlotStartNumber = std::to_string(slotNumber);
			startSlotFilled = true;
			continue;
		}
		if(scanMarkerDictionary(temp) && temp!=MARKER_TO)
			break;
		else{
			if (temp==MARKER_TO)
				hasRange = true;
			else if(hasRange && startSlotFilled && isParseInt(temp, slotNumber)){
				textSlotEndNumber = std::to_string(slotNumber);
			}
			else
				throw MESSAGE_ERROR_WRONG_FORMAT;
		}
	}
	if((count == 1 || count == 3) && startSlotFilled){
		found = textInput.find(temp);
		extractEndPos = found + temp.size();
		shortenInput(extractStartPos, extractEndPos);
		return true;
	}
	else
		throw MESSAGE_ERROR_WRONG_FORMAT;
}
/*
bool Parser::determineTaskList()
{
std::size_t found = INITIALIZE_SIZE_T;
std::size_t stringLength = textInput.size();

if(textInput.rfind(LIST_COMPLETED)!=std::string::npos){
found = textInput.rfind(LIST_COMPLETED);
textTaskList = _textInput.substr(found, LIST_COMPLETED_LENGTH);
shortenInput(found, stringLength);
return true;
}
else if(textInput.rfind(LIST_TO_DO)!=std::string::npos){
found = textInput.rfind(LIST_TO_DO);
textTaskList = _textInput.substr(found, LIST_TO_DO_LENGTH);
shortenInput(found, stringLength);
return true;
}
else if(textInput.rfind(LIST_OVERDUED)!=std::string::npos){
found = textInput.rfind(LIST_OVERDUED);
textTaskList = _textInput.substr(found, LIST_OVERDUED_LENGTH);
shortenInput(found, stringLength);
return true;
}

else
return false;
}
*/
/*
bool Parser::determineStatus()
{
std::size_t found = INITIALIZE_SIZE_T;
std::size_t extractEndPos = INITIALIZE_SIZE_T;


if(textInput.find(MARKER_UNDONE)!=std::string::npos){
found = textInput.find(MARKER_UNDONE);
if(textInput.find(MARKER_ENCLOSE,found)!=std::string::npos)
extractEndPos = textInput.find(MARKER_ENCLOSE,found);
else
extractEndPos = textInput.size();
textStatus = _textInput.substr(found, MARKER_UNDONE_LENGTH);
shortenInput(found, --extractEndPos);
return true;
}

else if(textInput.find(MARKER_INCOMPLETE)!=std::string::npos){
found = textInput.find(MARKER_INCOMPLETE);
if(textInput.find(MARKER_ENCLOSE,found)!=std::string::npos)
extractEndPos = textInput.find(MARKER_ENCLOSE,found);
else
extractEndPos = textInput.size();
textStatus = _textInput.substr(found, MARKER_INCOMPLETE_LENGTH);
shortenInput(found, --extractEndPos);
return true;
}

else if(textInput.find(MARKER_DONE)!=std::string::npos){
found = textInput.find(MARKER_DONE);
if(textInput.find(MARKER_ENCLOSE,found)!=std::string::npos)
extractEndPos = textInput.find(MARKER_ENCLOSE,found);
else
extractEndPos = textInput.size();
textStatus = _textInput.substr(found, MARKER_DONE_LENGTH);
shortenInput(found, --extractEndPos);
return true;
}

else if(textInput.find(MARKER_COMPLETED)!=std::string::npos){
found = textInput.find(MARKER_COMPLETED);
if(textInput.find(MARKER_ENCLOSE,found)!=std::string::npos)
extractEndPos = textInput.find(MARKER_COMPLETED,found);
else
extractEndPos = textInput.size();
textStatus = _textInput.substr(found, MARKER_COMPLETED_LENGTH);
shortenInput(found, --extractEndPos);
return true;
}

else
return false;
}
*/
std::size_t Parser::determindExtractLength(std::size_t partitionStart, std::size_t partitionEnd, string markConstant, std::size_t& extractStartPos)
{
	extractStartPos = INITIALIZE_SIZE_T;
	std::size_t extractEndPos;
	std::size_t shiftPos = INITIALIZE_SIZE_T;

	if(markConstant == MARKER_PRIORITY || markConstant == MARKER_PRIORITY_HIGH || markConstant == MARKER_PRIORITY_NORMAL){
		shiftPos = shiftPos;
	}
	else if(markConstant == MARKER_REMIND){
		if(textInput.find(MARKER_ON,partitionStart)!=std::string::npos){
			partitionStart = textInput.find(MARKER_ON,partitionStart);
			shiftPos = MARKER_ON_LENGTH;
		}
		else{
			shiftPos = MARKER_REMIND_LENGTH;
		}
	}

	else
		shiftPos = markConstant.size();

	extractStartPos = partitionStart + (++shiftPos); //shift the pos to first pos of text to be extracted.
	extractEndPos = --partitionEnd;

	return extractEndPos - extractStartPos;
}
void Parser::shortenInput(std::size_t partitionStart, std::size_t partitionEnd)
{
	std::size_t partitionLength = partitionEnd-partitionStart;

	textInput.erase(partitionStart, partitionLength);
	_textInput.erase(partitionStart, partitionLength);
}
void Parser::removeAllBorderSpace()
{
	removeBorderSpaces(_textInput);
	removeBorderSpaces(textInput);
	removeBorderSpaces(textDescription);
	removeBorderSpaces(textVenue);
	removeBorderSpaces(textStartDate);
	removeBorderSpaces(textStartTime);
	removeBorderSpaces(textEndDate);
	removeBorderSpaces(textEndTime);
	removeBorderSpaces(textRepeat);
	removeBorderSpaces(textPriority);
	removeBorderSpaces(textRemindDate);
	removeBorderSpaces(textRemindTime);
	removeBorderSpaces(textSlotStartNumber);
	removeBorderSpaces(textSlotEndNumber);
}
void Parser::removeBorderSpaces(string& str)
{
	if(str.empty())
		return;

	while(str.front()==MARKER_ENCLOSE){
		str.erase(INITIALIZE_SIZE_T, MARKER_ENCLOSE_LENGTH);
	}

	while(str.back()==MARKER_ENCLOSE){
		str.pop_back();
	}
}
void Parser::parseAllTimeAndDate()
{
	parseTimeAndDate(textStart, textStartDate, textStartTime);
	parseTimeAndDate(textEnd, textEndDate, textEndTime);
}
/*
bool Parser::parseTimeAndDate(string& str, string& strDate, string& strTime)
{
stringstream buffer(str);
string stringcheck;
string _stringcheck;
std::size_t foundLeft;
std::size_t foundRight;

if(str.empty())
return true;
while(!buffer.eof()){
buffer >> _stringcheck;
stringcheck = _stringcheck;
toLowerCase(stringcheck);
if(stringcheck.find(TIMER_SLASH)!=std::string::npos || stringcheck.find(TIMER_DASH)!=std::string::npos){
if(stringcheck.find(TIMER_SLASH)!=std::string::npos){
foundLeft = stringcheck.find(TIMER_SLASH);
if(stringcheck.rfind(TIMER_SLASH)!=std::string::npos){
foundRight = stringcheck.rfind(TIMER_SLASH);
if(foundRight!=foundLeft)
strDate = _stringcheck;
else{
logging(MESSAGE_ERROR_WRONG_FORMAT,Error,None);
throw MESSAGE_ERROR_WRONG_FORMAT;
}
}
else{
logging(MESSAGE_ERROR_WRONG_FORMAT,Error,None);
throw MESSAGE_ERROR_WRONG_FORMAT;
}
}
else{
foundLeft = stringcheck.find(TIMER_DASH);
if(stringcheck.rfind(TIMER_DASH)!=std::string::npos){
foundRight = stringcheck.rfind(TIMER_DASH);
if(foundRight!=foundLeft)
strDate = _stringcheck;
else{
logging(MESSAGE_ERROR_WRONG_FORMAT,Error,None);
throw MESSAGE_ERROR_WRONG_FORMAT;
}
}
else{
logging(MESSAGE_ERROR_WRONG_FORMAT,Error,None);
throw MESSAGE_ERROR_WRONG_FORMAT;
}
}
}
else if(stringcheck.size()>TIMER_TIME_LOWER_LENGTH && stringcheck.size()<TIMER_TIME_UPPER_LENGTH && stringcheck.size()!=TIMER_TIME_EXCLUDED_LENGTH){
if(stringcheck.size()==TIMER_24HR_LENGTH) {
int i = 0;
bool is24hr = true;
while(i<TIMER_24HR_LENGTH){
if(!isdigit(stringcheck[i]))
is24hr = false;
i++;
}
if(is24hr)
strTime = _stringcheck;
else{
logging(MESSAGE_ERROR_WRONG_FORMAT,Error,None);
throw MESSAGE_ERROR_WRONG_FORMAT;
}
}
else if(stringcheck.find(TIMER_COLON)!=std::string::npos || stringcheck.find(TIMER_DOT)!=std::string::npos || 
stringcheck.find(TIMER_AM)!=std::string::npos || stringcheck.find(TIMER_PM)!=std::string::npos){
strTime = _stringcheck;
}
}
else
strDate = _stringcheck;
}
return true;
}*/
/*
int Parser::separateInput(int state)
{
string temp;
iss >> temp;

if(temp == ",at"){
temp.clear();
iss >> temp;
textVenue+= temp + " ";
return 1;
}
else if(temp ==",by"){
temp.clear();
iss >> temp;
textDateAndTime+= temp + " ";
return 2;
}
else if(state == 1){
textVenue+= temp + " ";
return 1;
}
else if (state == 2){
textDateAndTime+= temp + " ";
return 2;
}
else
{
textDescription += temp + " ";
}
}
*/
void Parser::populateContainer(vector<string>& inputBits)
{
	inputBits[SLOT_DESCRIPTION] = textDescription;
	inputBits[SLOT_LOCATION] = textVenue;
	inputBits[SLOT_REMIND_DATE] = textRemindDate;
	inputBits[SLOT_REMIND_TIME] = textRemindTime;
	inputBits[SLOT_PRIORITY] = textPriority;
	inputBits[SLOT_REPEAT] = textRepeat;
	inputBits[SLOT_START_DATE] = textStartDate;
	inputBits[SLOT_START_TIME] = textStartTime;
	inputBits[SLOT_END_DATE] = textEndDate;
	inputBits[SLOT_END_TIME] = textEndTime;
	inputBits[SLOT_SLOT_START_NUMBER] = textSlotStartNumber;
	inputBits[SLOT_SLOT_END_NUMBER] = textSlotEndNumber;
	//inputBits[SLOT_STATUS] = textStatus;
}
void Parser::toLowerCase(string &str)
{
	const int length = str.length();
	for(int i=0; i < length; ++i)
	{
		str[i] = tolower(str[i]);
	}
}
//To retrieve the first word which is the command.
string Parser::getFirstWord(string input)
{
	string firstword;
	istringstream streamInput (input);
	streamInput >> firstword;
	return firstword;
}
//Remove the command from _input after retrieving it, change command to lower case
void Parser::removeFirstWord(string &input)
{
	textCommand = getFirstWord(input);
	std::size_t found = input.find(textCommand);
	toLowerCase(textCommand);
	input.replace(0, found+textCommand.length()+1, "");
}
//Check if the first character is a valid digit
bool Parser::isParseInt(string input, int &value)
{	
	int stringLength = input.size();
	int i = 0;
	bool isDigit = isInt(input);
	if(isDigit){
		value = atoi(input.c_str());
		return isDigit;
	}
	else
		return isDigit;
}
bool Parser::isInt(string input)
{
	int stringLength = input.size();
	int i = 0;
	bool isDigit = true;
	while(i != stringLength){
		isDigit = isdigit(input[i]) != 0;
		if(!isDigit){
			return isDigit;
		}
		i++;
	}
	return isDigit;
}

string Parser::getCommand()
{
	return textCommand;
}
/*
bool Parser::determineDateAndTime()
{
std::size_t found = INITIALIZE_SIZE_T;
std::size_t foundComma = INITIALIZE_SIZE_T;
std::size_t foundTo = INITIALIZE_SIZE_T;

if(textInput.find(MARKER_BY)!=std::string::npos){
found = textInput.find(MARKER_BY);

if(textInput.find(MARKER_COMMA, found+MARKER_BY_LENGTH)!=std::string::npos ){			//try find comma
foundComma = textInput.find(MARKER_COMMA, found+MARKER_BY_LENGTH);
extractLength = determindExtractLength(found, foundComma, MARKER_BY, extractStartPos);
i = foundComma; 
while(textInput[i]!=MARKER_ENCLOSE && i!=stringLength)								//try forming keyword
marker += textInput[i++];
if(marker==MARKER_AT || marker==MARKER_NEAR || marker==MARKER_REMIND || marker==MARKER_REPEAT || marker==MARKER_PRIORITY){
textEnd = _textInput.substr(extractStartPos, extractLength);
shortenInput(found, foundComma);
parseAllTimeAndDate();
return true;
}
else{
logging(MESSAGE_ERROR_WRONG_KEYWORD,Error,None);
throw MESSAGE_ERROR_WRONG_KEYWORD;
}//wrong keyword definition
}
else{																					//by keyword is the last key input
extractLength = determindExtractLength(found, stringLength, MARKER_BY, extractStartPos);
textEnd = _textInput.substr(extractStartPos, ++extractLength);
shortenInput(found, stringLength);
parseAllTimeAndDate();
return true;
}
}

}*/


bool Parser::parseTimeAndDate(string& str, string& strDate, string& strTime)
{
	stringstream buffer(str);
	string stringCheck;
	string _stringCheck;
	std::size_t foundLeft;
	std::size_t foundRight;
	bool dateDetermined = false;
	bool dateDayDetermine = false;
	bool dateMonthDetermined = false;
	bool dateYearDetermine = false;

	bool timeDetermined = false;
	size_t stringLength;
	bool isChar = false;
	bool isDigit = false;

	if(str.empty())
		return true;
	while(!buffer.eof()){
		buffer >> _stringCheck;
		stringCheck = _stringCheck;
		toLowerCase(stringCheck);
		stringLength = stringCheck.size();

		if(dateDetermined && timeDetermined && !stringCheck.empty()){
			logging(MESSAGE_ERROR_WRONG_FORMAT,Error,None);
			throw MESSAGE_ERROR_WRONG_FORMAT;							// If Date and Time has been determined and stringCheck still has a new word, it is an error
		}
		if(dateDayDetermine && dateMonthDetermined && dateYearDetermine)
			dateDetermined = dateDayDetermine && dateMonthDetermined && dateYearDetermine; // if components of date are determined, turn dateDetermined as true


		if(!dateDetermined){
			if(stringLength > 0 && stringLength < 3 && !dateDayDetermine){					// Date Format: 7 or 07  => Date day fragment, expect Date month fragment 
				int i = 0;
				while(i != stringLength){
					isDigit = isdigit(stringCheck[i]) != 0;
					if(!isDigit){
						logging(MESSAGE_ERROR_WRONG_FORMAT,Error,None);
						throw MESSAGE_ERROR_WRONG_FORMAT;
					}
					i++;
				}
				if(atoi(stringCheck.c_str()) > 31){						// Date Format: Date cannot be more than 31
					logging(MESSAGE_ERROR_WRONG_DATE,Error,None);
					throw MESSAGE_ERROR_WRONG_DATE;
				}
				if(!strDate.empty()){									
					strDate += TIMER_SPACE +_stringCheck;				// Date Format: YYYY MONTH DD
				}
				else													
					strDate = _stringCheck;								// Date Format: DD
				dateDayDetermine = true;
				continue;
			}
			else if(stringLength >= 3 && stringLength < 6) {				// Date Format: 1/2 || 01/02 || 1/2/3 || MONTH_SHORT_WORD || YYYY
				if(stringCheck.find(TIMER_SLASH)!=std::string::npos){	
					foundLeft = stringCheck.find(TIMER_SLASH);
					if(stringCheck.rfind(TIMER_SLASH)!=std::string::npos){	
						foundRight = stringCheck.rfind(TIMER_SLASH);
						if(foundRight!=foundLeft){
							strDate = _stringCheck;							// Date Format: 1/2/3 => Unusual representation of date, but implies 1st Feb 2003. 
							dateDetermined = true;
							continue;
						}
						else{
							strDate = _stringCheck;							// Date Format: 1/2 == 01/02 => year is implied to be current year and ommited. 
							dateDetermined = true;
							continue;
						}
					}
				}
				else if(stringCheck.find(TIMER_DASH)!=std::string::npos){
					foundLeft = stringCheck.find(TIMER_DASH);
					if(stringCheck.rfind(TIMER_DASH)!=std::string::npos){	
						foundRight = stringCheck.rfind(TIMER_DASH);
						if(foundRight!=foundLeft){
							strDate = _stringCheck;							// Date Format: 1-2-3 => Unusual representation of date, but implies 1st Feb 2003. 
							dateDetermined = true;
							continue;
						}
						else{
							strDate = _stringCheck;							// Date Format: 1-2 == 01-02 => year is implied to be current year and ommited. 
							dateDetermined = true;
							continue;
						}
					}
				}
				else if (stringLength < 5 && scanMonthDictionary(stringCheck)){								// Date Format: May or Sept  => Date month fragment, expect Date day fragment
					int i = 0;
					while(i != stringLength){
						isChar = isalpha(stringCheck[i]) != 0;
						if(!isChar){
							logging(MESSAGE_ERROR_WRONG_FORMAT,Error,None);
							throw MESSAGE_ERROR_WRONG_FORMAT;
						}
						i++;
					}
					if(!strDate.empty()){								
						strDate += TIMER_SPACE +_stringCheck;			// Date Format: DD YYYY MONTH
					}
					else												
						strDate = _stringCheck;							// Date Format: MONTH
					dateMonthDetermined = true;
					continue;
				}
				else if(stringLength == 4 && isdigit(stringCheck.front())){
					int i = 0;
					while(i != stringLength){
						isDigit = isdigit(stringCheck[i]) != 0;
						if(!isDigit){
							logging(MESSAGE_ERROR_WRONG_FORMAT,Error,None);
							throw MESSAGE_ERROR_WRONG_FORMAT;
						}
						i++;
					}
					if(!strDate.empty()){									
						strDate += TIMER_SPACE +_stringCheck;				// Date Format: MONTH DD YYYY
					}
					else													
						strDate = _stringCheck;								// Date Format: YYYY
					dateYearDetermine = true;
					continue;
				}
				else if(scanDatesDictionary(stringCheck)){
					strDate = _stringCheck;									//Date Format: Tml, today etc.
					dateDetermined = true;
					continue;
				}
			}
			else if(stringLength >= 6 && stringLength < 11){				// Date Format: 1/2/13 == 01/02/2013 || MONTH_FULL_WORD
				if(stringCheck.find(TIMER_SLASH)!=std::string::npos){	
					foundLeft = stringCheck.find(TIMER_SLASH);
					if(stringCheck.rfind(TIMER_SLASH)!=std::string::npos){	
						foundRight = stringCheck.rfind(TIMER_SLASH);
						if(foundRight!=foundLeft){
							strDate = _stringCheck;							// Date Format: 1/2/13 => Shorter representation of date with year
							dateDetermined = true;
							continue;
						}
						else{
							logging(MESSAGE_ERROR_WRONG_DATE_FORMAT,Error,None);
							throw MESSAGE_ERROR_WRONG_DATE_FORMAT;
						}
					}
				}
				else if(stringCheck.find(TIMER_DASH)!=std::string::npos){
					foundLeft = stringCheck.find(TIMER_DASH);
					if(stringCheck.rfind(TIMER_DASH)!=std::string::npos){	
						foundRight = stringCheck.rfind(TIMER_DASH);
						if(foundRight!=foundLeft){
							strDate = _stringCheck;							// Date Format: 1-2-13 => Shorter representation of date
							dateDetermined = true;
							continue;
						}
						else{
							logging(MESSAGE_ERROR_WRONG_DATE_FORMAT,Error,None);
							throw MESSAGE_ERROR_WRONG_DATE_FORMAT;
						}
					}
				}
				else if (stringLength < 10 && scanMonthDictionary(stringCheck)){								// Date Format: January or September  => Date month fragment, expect Date day fragment
					int i = 0;
					while(i != stringLength){
						isChar = isalpha(stringCheck[i]) != 0;
						if(!isChar){
							logging(MESSAGE_ERROR_WRONG_FORMAT,Error,None);
							throw MESSAGE_ERROR_WRONG_FORMAT;
						}
						i++;
					}
					if(!strDate.empty()){								
						strDate += TIMER_SPACE +_stringCheck;			// Date Format: YYYY DD MONTH
					}
					else												
						strDate = _stringCheck;							// Date Format: MONTH
					dateMonthDetermined = true;
					continue;
				}
				else if(scanDatesDictionary(stringCheck)){
					strDate = _stringCheck;									//Date Format: Tomorrow, 
					dateDetermined = true;
					continue;
				}
			}
			else{
				logging(MESSAGE_ERROR_WRONG_TIME_FORMAT,Error,None);
				throw MESSAGE_ERROR_WRONG_TIME_FORMAT;
			}

		}

		if(!timeDetermined){
			if(stringCheck.find(TIMER_COLON)!=std::string::npos){
				if(stringCheck.find(TIME_ANTE_MERIDIAN)!=std::string::npos || stringCheck.find(TIME_POST_MERIDIAN)!=std::string::npos){
					foundLeft = stringCheck.find(TIMER_COLON);
					foundRight = stringCheck.rfind(TIMER_COLON);
					if(foundLeft==foundRight){
						strTime = _stringCheck;								// Time Format: 09:00AM
						timeDetermined = true;
						continue;
					}
					else{
						logging(MESSAGE_ERROR_WRONG_TIME_FORMAT,Error,None);
						throw MESSAGE_ERROR_WRONG_TIME_FORMAT;				// Time Format: error, 09:00:00AM
					}
				}
				else{
					logging(MESSAGE_ERROR_WRONG_TIME_FORMAT,Error,None);
					throw MESSAGE_ERROR_WRONG_TIME_FORMAT;					// Time Format: error, 09:00, use 24hr format instead or put AM/PM
				}
			}
			else if(stringCheck.find(TIMER_DOT)!=std::string::npos){
				if(stringCheck.find(TIME_ANTE_MERIDIAN)!=std::string::npos || stringCheck.find(TIME_POST_MERIDIAN)!=std::string::npos){
					foundLeft = stringCheck.find(TIMER_DOT);
					foundRight = stringCheck.rfind(TIMER_DOT);
					if(foundLeft==foundRight){
						strTime = _stringCheck;								// Time Format: 09.00AM
						timeDetermined = true;
						continue;
					}
					else{
						logging(MESSAGE_ERROR_WRONG_TIME_FORMAT,Error,None);
						throw MESSAGE_ERROR_WRONG_TIME_FORMAT;				// Time Format: error, 09.00.00AM
					}
				}
				else{
					logging(MESSAGE_ERROR_WRONG_TIME_FORMAT,Error,None);
					throw MESSAGE_ERROR_WRONG_TIME_FORMAT;					// Time Format: error, 09.00, use 24hr format instead or put AM/PM
				}
			}
			else if(stringLength==TIMER_24HR_LENGTH) {
				int i = 0;
				bool is24hr = stringCheck.find(TIMER_HR)!=std::string::npos;
				while(i<TIMER_24_LENGTH && is24hr){
					if(!isdigit(stringCheck[i]))
						is24hr = false;
					i++;
				}
				if(is24hr){
					strTime = _stringCheck;									// Time Format: 0900hr
					timeDetermined = true;
					continue;
				}
				else{
					logging(MESSAGE_ERROR_WRONG_FORMAT,Error,None);
					throw MESSAGE_ERROR_WRONG_FORMAT;
				}
			}
			else if(stringCheck==TIME_ANTE_MERIDIAN || stringCheck==TIME_POST_MERIDIAN){
				logging(MESSAGE_ERROR_WRONG_FORMAT,Error,None);
				throw MESSAGE_ERROR_WRONG_FORMAT;									// Time Format : Cannot be 10 PM => only 10PM works
			}
			else if((stringCheck.find(TIME_ANTE_MERIDIAN)!=std::string::npos || stringCheck.find(TIME_POST_MERIDIAN)!=std::string::npos) && stringLength > TIMER_TIME_LOWER_LENGTH){
				strTime = _stringCheck;
				timeDetermined = true;
				continue;
			}
		}
		else{
			logging(MESSAGE_ERROR_WRONG_TIME_FORMAT,Error,None);
			throw MESSAGE_ERROR_WRONG_TIME_FORMAT;
		}
		/*
		else if(stringLength>TIMER_TIME_LOWER_LENGTH && stringLength<TIMER_TIME_UPPER_LENGTH && stringLength!=TIMER_TIME_EXCLUDED_LENGTH){
		if(stringLength==TIMER_24HR_LENGTH) {
		int i = 0;
		bool is24hr = true;
		while(i<TIMER_24HR_LENGTH){
		if(!isdigit(stringCheck[i]))
		is24hr = false;
		i++;
		}
		if(is24hr)
		strTime = _stringCheck;
		else{
		logging(MESSAGE_ERROR_WRONG_FORMAT,Error,None);
		throw MESSAGE_ERROR_WRONG_FORMAT;
		}
		}
		else if(stringCheck.find(TIMER_COLON)!=std::string::npos || stringCheck.find(TIMER_DOT)!=std::string::npos || 
		stringCheck.find(TIMER_AM)!=std::string::npos || stringCheck.find(TIMER_PM)!=std::string::npos){
		strTime = _stringCheck;
		}
		}
		else
		strDate = _stringCheck;
		*/
	}

	if(dateYearDetermine && !dateMonthDetermined && !dateDayDetermine){
		logging(MESSAGE_ERROR_WRONG_TIME_FORMAT,Error,None);
		throw MESSAGE_ERROR_WRONG_TIME_FORMAT;
	}

	if(!dateYearDetermine && dateMonthDetermined && !dateDayDetermine){
		logging(MESSAGE_ERROR_WRONG_TIME_FORMAT,Error,None);
		throw MESSAGE_ERROR_WRONG_TIME_FORMAT;
	}

	if(!dateYearDetermine && !dateMonthDetermined && dateDayDetermine){
		logging(MESSAGE_ERROR_WRONG_TIME_FORMAT,Error,None);
		throw MESSAGE_ERROR_WRONG_TIME_FORMAT;
	}

	return true;
}

void Parser::loadDictionary()
{
	loadCommandDictionary();
	loadDateDictionary();
	loadTimeDictionary();
	loadMonthDictionary();
	loadMarkerDictionary();
}
void Parser::loadDateDictionary()
{
	dictionaryDates.push_back(TIMER_MON);
	dictionaryDates.push_back(TIMER_MONDAY);
	dictionaryDates.push_back(TIMER_TUE);
	dictionaryDates.push_back(TIMER_TUES);
	dictionaryDates.push_back(TIMER_TUESDAY);
	dictionaryDates.push_back(TIMER_WED);
	dictionaryDates.push_back(TIMER_WEDNESDAY);
	dictionaryDates.push_back(TIMER_THU);
	dictionaryDates.push_back(TIMER_THUR);
	dictionaryDates.push_back(TIMER_THURS);
	dictionaryDates.push_back(TIMER_THURSDAY);
	dictionaryDates.push_back(TIMER_FRI);
	dictionaryDates.push_back(TIMER_FRIDAY);
	dictionaryDates.push_back(TIMER_SAT);
	dictionaryDates.push_back(TIMER_SATURDAY);
	dictionaryDates.push_back(TIMER_SUN);
	dictionaryDates.push_back(TIMER_SUNDAY);
	dictionaryDates.push_back(TIMER_TML);
	dictionaryDates.push_back(TIMER_TMR);
	dictionaryDates.push_back(TIMER_TMRW);
	dictionaryDates.push_back(TIMER_TOMORROW);
	dictionaryDates.push_back(TIMER_NEXT);
	dictionaryDates.push_back(TIMER_LATER);
	dictionaryDates.push_back(TIMER_TODAY);
}
void Parser::loadMonthDictionary()
{
	dictionaryMonth.push_back(MONTH_JAN);
	dictionaryMonth.push_back(MONTH_JANUARY);
	dictionaryMonth.push_back(MONTH_FEB);
	dictionaryMonth.push_back(MONTH_FEBRUARY);
	dictionaryMonth.push_back(MONTH_MAR);
	dictionaryMonth.push_back(MONTH_MARCH);
	dictionaryMonth.push_back(MONTH_APR);
	dictionaryMonth.push_back(MONTH_APRIL);
	dictionaryMonth.push_back(MONTH_MAY);
	dictionaryMonth.push_back(MONTH_JUN);
	dictionaryMonth.push_back(MONTH_JUNE);
	dictionaryMonth.push_back(MONTH_JUL);
	dictionaryMonth.push_back(MONTH_JULY);
	dictionaryMonth.push_back(MONTH_AUG);
	dictionaryMonth.push_back(MONTH_AUGUST);
	dictionaryMonth.push_back(MONTH_SEP);
	dictionaryMonth.push_back(MONTH_SEPT);
	dictionaryMonth.push_back(MONTH_SEPTEMBER);
	dictionaryMonth.push_back(MONTH_OCT);
	dictionaryMonth.push_back(MONTH_OCTOBER);
	dictionaryMonth.push_back(MONTH_NOV);
	dictionaryMonth.push_back(MONTH_NOVEMBER);
	dictionaryMonth.push_back(MONTH_DEC);
	dictionaryMonth.push_back(MONTH_DECEMBER);
}

void Parser::loadTimeDictionary()
{

}
void Parser::loadCommandDictionary()
{
	dictionaryAddCommands.push_back(COMMAND_ADD);
	dictionaryAddCommands.push_back(COMMAND_A);
	dictionaryAddCommands.push_back(COMMAND_CREATE);

	dictionaryDeleteCommands.push_back(COMMAND_DELETE);
	dictionaryDeleteCommands.push_back(COMMAND_DEL);
	dictionaryDeleteCommands.push_back(COMMAND_REMOVE);
	dictionaryDeleteCommands.push_back(COMMAND_REM);
	dictionaryDeleteCommands.push_back(COMMAND_ERASE);

	dictionaryMarkCommands.push_back(COMMAND_MARK);
	dictionaryMarkCommands.push_back(COMMAND_M);

	dictionaryModifyCommands.push_back(COMMAND_MODIFY);
	dictionaryModifyCommands.push_back(COMMAND_MOD);
	dictionaryModifyCommands.push_back(COMMAND_UPDATE);

	dictionaryUndoCommands.push_back(COMMAND_UNDO);

	dictionaryRedoCommands.push_back(COMMAND_REDO);

	dictionaryShowCommands.push_back(COMMAND_SHOW);
	dictionaryShowCommands.push_back(COMMAND_DISPLAY);
	dictionaryShowCommands.push_back(COMMAND_SEARCH);

	dictionaryShowAllCommands.push_back(COMMAND_SHOWALL);
	dictionaryShowAllCommands.push_back(COMMAND_DISPLAYALL);
	dictionaryShowAllCommands.push_back(COMMAND_SEARCHALL);

	dictionaryCommands.push_back(dictionaryAddCommands);
	dictionaryCommands.push_back(dictionaryDeleteCommands);
	dictionaryCommands.push_back(dictionaryMarkCommands);
	dictionaryCommands.push_back(dictionaryModifyCommands);
	dictionaryCommands.push_back(dictionaryUndoCommands);
	dictionaryCommands.push_back(dictionaryRedoCommands);
	dictionaryCommands.push_back(dictionaryShowCommands);
	dictionaryCommands.push_back(dictionaryShowAllCommands);
}

void Parser::loadMarkerDictionary()
{
	dictionaryMarker.push_back(MARKER_AT);
	dictionaryMarker.push_back(MARKER_NEAR);
	dictionaryMarker.push_back(MARKER_BY);
	dictionaryMarker.push_back(MARKER_FROM);
	dictionaryMarker.push_back(MARKER_TO);
	dictionaryMarker.push_back(MARKER_REMIND);
	dictionaryMarker.push_back(MARKER_ON);
	dictionaryMarker.push_back(MARKER_REPEAT);
	dictionaryMarker.push_back(MARKER_PRIORITY);
	dictionaryMarker.push_back(MARKER_PRIORITY_HIGH);
	dictionaryMarker.push_back(MARKER_PRIORITY_NORMAL);
	dictionaryMarker.push_back(MARKER_DONE);
	dictionaryMarker.push_back(MARKER_UNDONE);
}

bool Parser::scanDictionary(string word)
{
	if(scanTimeDictionary(word))
		return true;
	if(scanDatesDictionary(word))
		return true;
	if(scanMonthDictionary(word))
		return true;
	return false;
}
bool Parser::scanTimeDictionary(string word)
{
	for(size_t i=0; i<dictionaryTime.size(); i++){
		if(dictionaryTime[i]==word)
			return true;
	}

	return false;
}
bool Parser::scanDatesDictionary(string word)
{
	for(size_t i=0; i<dictionaryDates.size(); i++){
		if(dictionaryDates[i]==word)
			return true;
	}

	return false;
}
bool Parser::scanMonthDictionary(string word)
{
	for(size_t i=0; i<dictionaryMonth.size(); i++){
		if(dictionaryMonth[i]==word)
			return true;
	}

	return false;
}
string Parser::scanCommandDictionary(string word)
{
	int foundCommand;
	bool found = false;;
	for(size_t i=0; i<dictionaryCommands.size() && !found; i++){
		size_t currentDictionarySize = dictionaryCommands[i].size();
		for(size_t k=0; k<currentDictionarySize; k++){
			if(dictionaryCommands[i][k]==word){
				foundCommand = i;
				found = true;
				break;
			}
		}
	}

	switch(foundCommand){
	case DICTIONARY_ADD:
		return COMMAND_ADD;
	case DICTIONARY_DELETE:
		return COMMAND_DELETE;
	case DICTIONARY_MARK:
		return COMMAND_MARK;
	case DICTIONARY_MODIFY:
		return COMMAND_MODIFY;
	case DICTIONARY_UNDO:
		return COMMAND_UNDO;
	case DICTIONARY_REDO:
		return COMMAND_REDO;
	case DICTIONARY_SHOW:
		return COMMAND_SHOW;
	case DICTIONARY_SHOWALL:
		return COMMAND_SHOWALL;
	default:
		return COMMAND_NULL;
	}
}
bool Parser::scanMarkerDictionary(string word)
{
	for(size_t i=0; i<dictionaryMarker.size(); i++){
		if(dictionaryMarker[i]==word)
			return true;
	}
	return false;
}