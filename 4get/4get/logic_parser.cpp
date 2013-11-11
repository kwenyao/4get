#include "logic_parser.h"

const char Parser::MARKER_COMMA = ',';
const size_t Parser::MARKER_COMMA_LENGTH = 1;
const char Parser::MARKER_ENCLOSE = ' ';
const size_t Parser::MARKER_ENCLOSE_LENGTH = 1;
const string Parser::MARKER_SPACE = " ";
const size_t Parser::MARKER_SPACE_LENGTH = 1;
const string Parser::MARKER_AT = ",at";
const size_t Parser::MARKER_AT_LENGTH = 3;
const string Parser::MARKER_NEAR = ",near";
const size_t Parser::MARKER_NEAR_LENGTH = 3;
const string Parser::MARKER_BY = ",by";
const size_t Parser::MARKER_BY_LENGTH = 3;
const string Parser::MARKER_DUE = ",due";
const size_t Parser::MARKER_DUE_LENGTH = 4;
const string Parser::MARKER_FROM = ",from";
const size_t Parser::MARKER_FROM_LENGTH = 5;
const string Parser::MARKER_TO = "to ";
const size_t Parser::MARKER_TO_LENGTH = 3;
const string Parser::MARKER_COMMA_TO = ",to";
const size_t Parser::MARKER_COMMA_TO_LENGTH = 3;
const string Parser::MARKER_ON = "on";
const size_t Parser::MARKER_ON_LENGTH = 2;
const string Parser::MARKER_REPEAT = ",repeat";
const size_t Parser::MARKER_REPEAT_LENGTH = 7;
const string Parser::MARKER_PRIORITY = ",!";
const size_t Parser::MARKER_PRIORITY_LENGTH = 2;
const string Parser::MARKER_PRIORITY_HIGH = ",high";
const size_t Parser::MARKER_PRIORITY_HIGH_LENGTH = 5;
const string Parser::MARKER_PRIORITY_NORMAL = ",normal";
const size_t Parser::MARKER_PRIORITY_NORMAL_LENGTH = 7;
const string Parser::MARKER_DONE = "done";
const size_t Parser::MARKER_DONE_LENGTH = 4;
const string Parser::MARKER_COMPLETED = "completed";
const size_t Parser::MARKER_COMPLETED_LENGTH = 9;
const string Parser::MARKER_UNDONE = "undone";
const size_t Parser::MARKER_UNDONE_LENGTH = 6;
const string Parser::MARKER_INCOMPLETE = "incomplete";
const size_t Parser::MARKER_INCOMPLETE_LENGTH = 10;

const int Parser::DICTIONARY_COMMAND_SIZE = 8;
const int Parser::DICTIONARY_ADD_INDEX = 0;
const int Parser::DICTIONARY_DELETE_INDEX = 1;
const int Parser::DICTIONARY_MARK_INDEX = 2;
const int Parser::DICTIONARY_MODIFY_INDEX = 3;
const int Parser::DICTIONARY_UNDO_INDEX = 4;
const int Parser::DICTIONARY_REDO_INDEX = 5;
const int Parser::DICTIONARY_SHOW_INDEX = 6;
const int Parser::DICTIONARY_SHOWALL_INDEX = 7;

const int Parser::REPEAT_COMMAND_SIZE = 5;
const int Parser::REPEAT_DAILY_INDEX = 0;
const int Parser::REPEAT_WEEKLY_INDEX = 1;
const int Parser::REPEAT_FORTNIGHTLY_INDEX = 2;
const int Parser::REPEAT_MONTHLY_INDEX = 3;
const int Parser::REPEAT_ANNUALLY_INDEX = 4;

const string Parser::REPEAT_DAILY = "daily";
const string Parser::REPEAT_EVERY_DAY = "every day";
const string Parser::REPEAT_WEEKLY = "weekly";
const string Parser::REPEAT_EVERY_WEEK = "every week";
const string Parser::REPEAT_FORTNIGHTLY = "fortnightly";
const string Parser::REPEAT_EVERY_FORTNIGHT = "every fortnight";
const string Parser::REPEAT_MONTHLY = "monthly";
const string Parser::REPEAT_EVERY_MONTH = "every month";
const string Parser::REPEAT_ANNUALLY = "annually";
const string Parser::REPEAT_EVERY_YEAR = "every year";
const string Parser::REPEAT_EVERY = "every";
const string Parser::REPEAT_NULL = "";

const int Parser::SLOT_COUNT_1 = 1;
const int Parser::SLOT_COUNT_2 = 2;
const int Parser::SPACE_DIFF_0 = 0;
const int Parser::SPACE_DIFF_3 = 3;
const int Parser::LENGTH_0 = 0;
const int Parser::LENGTH_3 = 3;
const int Parser::LENGTH_4 = 4;
const int Parser::LENGTH_5 = 5;
const int Parser::LENGTH_6 = 6;
const int Parser::LENGTH_10 = 10;
const int Parser::LENGTH_11 = 11;
const int Parser::DATE_MAX = 31;


/*************************************
PUBLIC FUNCTIONS            
*************************************/

Parser::Parser()
{
	dictionaryCommands.resize(DICTIONARY_COMMAND_SIZE);
	dictionaryRepeatCommands.resize(REPEAT_COMMAND_SIZE);
	parseReset();
	loadDictionary();
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

string Parser::getCommand()
{
	return textCommand;
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
	textSlotStartNumber = INITIALIZE_STRING_BLANK;
	textSlotEndNumber = INITIALIZE_STRING_BLANK;
}

/*************************************
PRIVATE FUNCTIONS            
*************************************/

void Parser::processCommand(string commandString, vector<string>& inputBits)
{
	try {
		try{
			textCommand = scanCommandDictionary(commandString);
			if(textCommand == COMMAND_NULL)
				throw MESSAGE_ERROR_COMMAND_ERROR;
		}
		catch(string error){
			throw;
		}
		inputBits[SLOT_COMMAND] = textCommand;
		if(textCommand == COMMAND_ADD){
			try{
				if(!separateFunctionAdd(inputBits))
					throw MESSAGE_ERROR_COMMAND_ADD;
			}
			catch(string error){
				throw error;
			}
		}
		else if(textCommand == COMMAND_DELETE){
			try{
				if(!separateFunctionDelete(inputBits))
					throw MESSAGE_ERROR_COMMAND_DELETE;
			}
			catch(string error){
				throw error;
			}
		}
		else if(textCommand == COMMAND_MARK){
			try{
				if(!separateFunctionMark(inputBits))
					throw MESSAGE_ERROR_COMMAND_MARK;
			}
			catch(string error){
				throw error;
			}
		}
		else if(textCommand == COMMAND_MODIFY){
			try{
				if(!separateFunctionModify(inputBits))
					throw MESSAGE_ERROR_COMMAND_MODIFY;
			}
			catch(string error){
				throw error;
			}
		}
		else if(textCommand == COMMAND_UNDO){
			try{
				if(!separateFunctionUndo(inputBits))
					throw MESSAGE_ERROR_COMMAND_UNDO;
			}
			catch(string error){
				throw error;
			}
		}
		else if(textCommand == COMMAND_REDO){
			try{
				if(!separateFunctionRedo(inputBits))
					throw MESSAGE_ERROR_COMMAND_REDO;
			}
			catch(string error){
				throw error;
			}
		}
		else if(textCommand == COMMAND_SHOW){
			try{
				if(!separateFunctionShow(inputBits))
					throw MESSAGE_ERROR_COMMAND_SHOW;
			}
			catch(string error){
				throw error;
			}
		}
		else if(textCommand == COMMAND_SHOWALL){
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
}

void Parser::populateContainer(vector<string>& inputBits)
{
	inputBits[SLOT_DESCRIPTION] = textDescription;
	inputBits[SLOT_LOCATION] = textVenue;
	inputBits[SLOT_PRIORITY] = textPriority;
	inputBits[SLOT_REPEAT] = textRepeat;
	inputBits[SLOT_START_DATE] = textStartDate;
	inputBits[SLOT_START_TIME] = textStartTime;
	inputBits[SLOT_END_DATE] = textEndDate;
	inputBits[SLOT_END_TIME] = textEndTime;
	inputBits[SLOT_SLOT_START_NUMBER] = textSlotStartNumber;
	inputBits[SLOT_SLOT_END_NUMBER] = textSlotEndNumber;
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
	determineDateAndTime();
	determineRepeat();
	determinePriority();
	textDescription = _textInput;
	if(textDescription.empty())
		throw MESSAGE_ERROR_NO_DESCRIPTION;
	logging(MESSAGE_SUCCESS_PARSED, Info, Pass);

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
	if(!determineSlot()){
		cout << "no slot" << endl;
		logging(MESSAGE_ERROR_NO_SLOT_NUM,Error,None);
		throw MESSAGE_ERROR_NO_SLOT_NUM;
	}

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
	size_t found = INITIALIZE_SIZE_T;
	size_t foundComma = INITIALIZE_SIZE_T;
	size_t extractStartPos = INITIALIZE_SIZE_T;
	size_t extractLength = INITIALIZE_SIZE_T;
	size_t stringLength = textInput.size();
	size_t i = INITIALIZE_SIZE_T;
	string marker = INITIALIZE_STRING_BLANK;

	bool isVenueDetermined = !textVenue.empty();
	if(!isVenueDetermined){

		if(textInput.find(MARKER_AT)!=string::npos){
			found = textInput.find(MARKER_AT);
			if(textInput.find(MARKER_COMMA, found+MARKER_AT_LENGTH)!=string::npos){
				foundComma = textInput.find(MARKER_COMMA, found+MARKER_AT_LENGTH);
				extractLength = determindExtractLength(found, foundComma, MARKER_AT, extractStartPos);
				i = foundComma;
				while(textInput[i]!=MARKER_ENCLOSE && i!=stringLength)
					marker += textInput[i++];
				if(scanMarkerDictionary(marker)){
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
		else if(textInput.find(MARKER_NEAR)!=string::npos){
			found = textInput.find(MARKER_NEAR);
			if(textInput.find(MARKER_COMMA, found+MARKER_NEAR_LENGTH)!=string::npos){
				foundComma = textInput.find(MARKER_COMMA, found+MARKER_NEAR_LENGTH);
				extractLength = determindExtractLength(found, foundComma, MARKER_NEAR, extractStartPos);
				i = foundComma;
				while(textInput[i]!=MARKER_ENCLOSE && i!=stringLength)
					marker += textInput[i++];
				if(scanMarkerDictionary(marker)){
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
			return false;																//No location keywords found
	}
	return true;																		//venue was determined before
}

bool Parser::determineDateAndTime()
{
	size_t found = INITIALIZE_SIZE_T;
	size_t foundComma = INITIALIZE_SIZE_T;
	size_t foundTo = INITIALIZE_SIZE_T;
	size_t extractStartPos = INITIALIZE_SIZE_T;
	size_t extractLength = INITIALIZE_SIZE_T;
	size_t stringLength = textInput.size();
	size_t i = INITIALIZE_SIZE_T;
	string marker = INITIALIZE_STRING_BLANK;

	bool isDateAmdTimeDetermined = !textStart.empty() || !textEnd.empty();
	if(!isDateAmdTimeDetermined){
		//If found By
		if(textInput.find(MARKER_BY)!=string::npos){
			found = textInput.find(MARKER_BY);

			if(textInput.find(MARKER_COMMA, found+MARKER_BY_LENGTH)!=string::npos ){			//try find comma
				foundComma = textInput.find(MARKER_COMMA, found+MARKER_BY_LENGTH);
				extractLength = determindExtractLength(found, foundComma, MARKER_BY, extractStartPos);
				i = foundComma; 
				while(textInput[i]!=MARKER_ENCLOSE && i!=stringLength)								//try forming keyword
					marker += textInput[i++];
				if(scanMarkerDictionary(marker)){
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

		else if(textInput.find(MARKER_DUE)!=string::npos){
			found = textInput.find(MARKER_DUE);
			if(textInput.find(MARKER_COMMA, found+MARKER_DUE_LENGTH)!=string::npos ){			//try find comma
				foundComma = textInput.find(MARKER_COMMA, found+MARKER_DUE_LENGTH);
				extractLength = determindExtractLength(found, foundComma, MARKER_DUE, extractStartPos);
				i = foundComma; 
				while(textInput[i]!=MARKER_ENCLOSE && i!=stringLength)								//try forming keyword
					marker += textInput[i++];
				if(scanMarkerDictionary(marker)){
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
				extractLength = determindExtractLength(found, stringLength, MARKER_DUE, extractStartPos);
				textEnd = _textInput.substr(extractStartPos, ++extractLength);
				shortenInput(found, stringLength);
				parseAllTimeAndDate();
				return true;
			}
		}
		else if(textInput.find(MARKER_FROM)!=string::npos){									//try find from
			found = textInput.find(MARKER_FROM);
			if(textInput.find(MARKER_TO, found+MARKER_FROM_LENGTH)!=string::npos){				//try find to
				foundTo = textInput.find(MARKER_TO, found+MARKER_FROM_LENGTH);
				extractLength = determindExtractLength(found, foundTo, MARKER_FROM, extractStartPos);
				textStart = _textInput.substr(extractStartPos, extractLength);
				if(textInput.find(MARKER_COMMA, foundTo+MARKER_TO_LENGTH)!=string::npos){						//try find comma
					foundComma = textInput.find(MARKER_COMMA, foundTo+MARKER_TO_LENGTH);
					extractLength = determindExtractLength(foundTo, foundComma, MARKER_TO, extractStartPos);
					i = foundComma; 
					while(textInput[i]!=MARKER_ENCLOSE && i!=stringLength)							//try forming keyword
						marker += textInput[i++];
					if(scanMarkerDictionary(marker)){
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
					extractLength = determindExtractLength(foundTo, stringLength, MARKER_COMMA_TO, extractStartPos);
					textEnd = _textInput.substr(extractStartPos, ++extractLength);
					shortenInput(found, stringLength);
					parseAllTimeAndDate();
					return true;
				}
			}
			else if(textCommand==COMMAND_MODIFY || textCommand==COMMAND_SHOW){
				if(textInput.find(MARKER_COMMA, found+MARKER_FROM_LENGTH)!=string::npos ){			//try find comma
					foundComma = textInput.find(MARKER_COMMA, found+MARKER_FROM_LENGTH);
					extractLength = determindExtractLength(found, foundComma, MARKER_FROM, extractStartPos);
					i = foundComma; 
					while(textInput[i]!=MARKER_ENCLOSE && i!=stringLength)								//try forming keyword
						marker += textInput[i++];
					if(scanMarkerDictionary(marker)){
						textStart = _textInput.substr(extractStartPos, extractLength);
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
					extractLength = determindExtractLength(found, stringLength, MARKER_FROM, extractStartPos);
					textStart = _textInput.substr(extractStartPos, ++extractLength);
					shortenInput(found, stringLength);
					parseAllTimeAndDate();
					return true;
				}
			}
			else{																					//wrong keyword definition
				logging(MESSAGE_ERROR_UNABLE_TO_FORM_TIMED_TASK ,Error,None);
				throw MESSAGE_ERROR_UNABLE_TO_FORM_TIMED_TASK;
			}
		}
		else if(textInput.find(MARKER_COMMA_TO)!=string::npos && textCommand==COMMAND_MODIFY){
			found = textInput.find(MARKER_COMMA_TO);
			if(textInput.find(MARKER_COMMA, found+MARKER_COMMA_TO_LENGTH)!=string::npos ){			//try find comma
				foundComma = textInput.find(MARKER_COMMA, found+MARKER_COMMA_TO_LENGTH);
				extractLength = determindExtractLength(found, foundComma, MARKER_COMMA_TO, extractStartPos);
				i = foundComma; 
				while(textInput[i]!=MARKER_ENCLOSE && i!=stringLength)								//try forming keyword
					marker += textInput[i++];
				if(scanMarkerDictionary(marker)){
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
				extractLength = determindExtractLength(found, stringLength, MARKER_COMMA_TO, extractStartPos);
				textEnd = _textInput.substr(extractStartPos, ++extractLength);
				shortenInput(found, stringLength);
				parseAllTimeAndDate();
				return true;
			}
		}
		else																						//not specified date aka. Floating
			return true; 
	}
	else 
		return isDateAmdTimeDetermined;
}

bool Parser::determineRepeat()
{
	size_t found = INITIALIZE_SIZE_T;
	size_t foundComma = INITIALIZE_SIZE_T;
	size_t extractStartPos = INITIALIZE_SIZE_T;
	size_t extractLength = INITIALIZE_SIZE_T;
	size_t stringLength = textInput.size();
	size_t i = INITIALIZE_SIZE_T;
	string marker = INITIALIZE_STRING_BLANK;

	bool isRepeatDetermined = !textRepeat.empty();
	if(!isRepeatDetermined){
		if(textInput.find(MARKER_REPEAT)!=string::npos){
			found = textInput.find(MARKER_REPEAT);
			if(textInput.find(MARKER_COMMA, found+MARKER_REPEAT_LENGTH)!=string::npos){
				foundComma = textInput.find(MARKER_COMMA, found+MARKER_REPEAT_LENGTH);
				extractLength = determindExtractLength(found, foundComma, MARKER_REPEAT, extractStartPos);
				i = foundComma;
				while(textInput[i]!=MARKER_ENCLOSE && i!=stringLength)
					marker += textInput[i++];
				if(scanMarkerDictionary(marker)){
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
	else
		return isRepeatDetermined;
}

bool Parser::determinePriority()
{
	size_t found = INITIALIZE_SIZE_T;
	size_t foundComma = INITIALIZE_SIZE_T;
	size_t foundEnclose = INITIALIZE_SIZE_T;
	size_t extractStartPos = INITIALIZE_SIZE_T;
	size_t extractLength = INITIALIZE_SIZE_T;
	size_t stringLength = textInput.size();
	size_t i = INITIALIZE_SIZE_T;
	string marker = INITIALIZE_STRING_BLANK;

	bool isPriorityDetermined = !textPriority.empty();
	if(!isPriorityDetermined){
		if(textInput.rfind(MARKER_PRIORITY)!=string::npos){
			found = textInput.rfind(MARKER_PRIORITY);
			if(textInput.find(MARKER_ENCLOSE, found+MARKER_PRIORITY_LENGTH)!=string::npos){
				foundEnclose = textInput.find(MARKER_ENCLOSE, found+MARKER_PRIORITY_LENGTH);
				extractLength = determindExtractLength(found, foundEnclose, MARKER_PRIORITY, extractStartPos);
				textPriority = _textInput.substr(extractStartPos, extractLength);
				shortenInput(found, foundEnclose);
				return true;
			}

			else{
				extractStartPos = found;
				textPriority = _textInput.substr(++extractStartPos);
				shortenInput(found, stringLength);
				return true;
			}
		}

		else if(textInput.find(MARKER_PRIORITY_HIGH)!=string::npos){
			found = textInput.find(MARKER_PRIORITY_HIGH);
			if(textInput.find(MARKER_COMMA, found+MARKER_PRIORITY_HIGH_LENGTH)!=string::npos){
				foundComma = textInput.find(MARKER_COMMA, found+MARKER_PRIORITY_HIGH_LENGTH);
				extractLength = determindExtractLength(found, foundComma, MARKER_PRIORITY_HIGH, extractStartPos);
				i = foundComma;
				while(textInput[i]!=MARKER_ENCLOSE && i!=stringLength)
					marker += textInput[i++];
				if(scanMarkerDictionary(marker)){
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

		else if(textInput.find(MARKER_PRIORITY_NORMAL)!=string::npos){
			found = textInput.find(MARKER_PRIORITY_NORMAL);
			if(textInput.find(MARKER_COMMA, found+MARKER_PRIORITY_NORMAL_LENGTH)!=string::npos){
				foundComma = textInput.find(MARKER_COMMA, found+MARKER_PRIORITY_NORMAL_LENGTH);
				extractLength = determindExtractLength(found, foundComma, MARKER_PRIORITY_NORMAL, extractStartPos);
				i = foundComma;
				while(textInput[i]!=MARKER_ENCLOSE && i!=stringLength)
					marker += textInput[i++];
				if(scanMarkerDictionary(marker)){
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
	else
		return isPriorityDetermined;
}

bool Parser::determineSlot()
{
	size_t extractStartPos = INITIALIZE_SIZE_T;
	size_t extractEndPos = INITIALIZE_SIZE_T;
	size_t found = INITIALIZE_SIZE_T;
	size_t foundTo = INITIALIZE_SIZE_T;
	bool hasRange = false;
	bool startSlotFilled = false;
	bool endSlotFilled = false;
	int slotNumber = INITIALIZE_INT;
	int count = INITIALIZE_INT;
	string tempInput = textInput;
	istringstream buffer(tempInput);
	string temp;
	while(!buffer.eof()){
		if(startSlotFilled && endSlotFilled)
			break;
		buffer >> temp;
		count++;
		if(isParseInt(temp, slotNumber) && !startSlotFilled){
			textSlotStartNumber = to_string(slotNumber);
			startSlotFilled = true;
			continue;
		}
		if(scanMarkerDictionary(temp) && temp!=MARKER_TO) // this statement handles if the word is keyword
			break;
		else{
			if (MARKER_TO.find(temp)!=string::npos && count == SLOT_COUNT_2)
				hasRange = true;
			else if(hasRange && startSlotFilled && isParseInt(temp, slotNumber)){
				textSlotEndNumber = to_string(slotNumber);
				endSlotFilled = true;
				continue;
			}
			else
				break;
		}
	}
	if(startSlotFilled){
		if(endSlotFilled){
			found = textInput.find(temp);
			extractEndPos = found + temp.size();
			shortenInput(extractStartPos, extractEndPos);
			return true;
		}
		else if(count == SLOT_COUNT_2){
			found = textInput.find(temp);
			extractEndPos = --found;
			shortenInput(extractStartPos, extractEndPos);
			return true;

		}
		else if(count == SLOT_COUNT_1){
			found = textInput.find(temp);
			extractEndPos = found+1;
			shortenInput(extractStartPos, extractEndPos);
			return true;
		}
		else
			throw MESSAGE_ERROR_WRONG_FORMAT;
	}
	else
		throw MESSAGE_ERROR_WRONG_FORMAT;
}

size_t Parser::determindExtractLength(size_t partitionStart, 
									  size_t partitionEnd, 
									  string markConstant, 
									  size_t& extractStartPos)
{
	extractStartPos = INITIALIZE_SIZE_T;
	size_t extractEndPos;
	size_t shiftPos = INITIALIZE_SIZE_T;

	if(markConstant == MARKER_PRIORITY || markConstant == MARKER_PRIORITY_HIGH || markConstant == MARKER_PRIORITY_NORMAL){
		shiftPos = shiftPos;
	}

	else
		shiftPos = markConstant.size();

	extractStartPos = partitionStart + (shiftPos); //shift the pos to first pos of text to be extracted.
	extractEndPos = partitionEnd;

	return extractEndPos - extractStartPos;
}

void Parser::loadDictionary()
{
	loadCommandDictionary();
	loadDatesDictionary();
	loadTimeDictionary();
	loadMonthDictionary();
	loadMarkerDictionary();
	loadRepeatDictionary();
}

void Parser::loadDatesDictionary()
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
	dictionaryTime.push_back(TIMER_TML);
	dictionaryTime.push_back(TIMER_TMR);
	dictionaryTime.push_back(TIMER_TMRW);
	dictionaryTime.push_back(TIMER_TOMORROW);
	dictionaryTime.push_back(TIMER_NEXT);
	dictionaryTime.push_back(TIMER_TODAY);
}

void Parser::loadCommandDictionary()
{
	//ADD COMMANDS
	dictionaryCommands[DICTIONARY_ADD_INDEX].push_back(COMMAND_ADD);
	dictionaryCommands[DICTIONARY_ADD_INDEX].push_back(COMMAND_A);
	dictionaryCommands[DICTIONARY_ADD_INDEX].push_back(COMMAND_CREATE);
	//DELETE COMMANDS
	dictionaryCommands[DICTIONARY_DELETE_INDEX].push_back(COMMAND_DELETE);
	dictionaryCommands[DICTIONARY_DELETE_INDEX].push_back(COMMAND_DEL);
	dictionaryCommands[DICTIONARY_DELETE_INDEX].push_back(COMMAND_REMOVE);
	dictionaryCommands[DICTIONARY_DELETE_INDEX].push_back(COMMAND_REM);
	dictionaryCommands[DICTIONARY_DELETE_INDEX].push_back(COMMAND_ERASE);
	//MARK COMMANDS
	dictionaryCommands[DICTIONARY_MARK_INDEX].push_back(COMMAND_MARK);
	dictionaryCommands[DICTIONARY_MARK_INDEX].push_back(COMMAND_M);
	//MODIFY COMMANDS
	dictionaryCommands[DICTIONARY_MODIFY_INDEX].push_back(COMMAND_MODIFY);
	dictionaryCommands[DICTIONARY_MODIFY_INDEX].push_back(COMMAND_MOD);
	dictionaryCommands[DICTIONARY_MODIFY_INDEX].push_back(COMMAND_UPDATE);
	//UNDO COMMANDS
	dictionaryCommands[DICTIONARY_UNDO_INDEX].push_back(COMMAND_UNDO);
	//REDO COMMANDS
	dictionaryCommands[DICTIONARY_REDO_INDEX].push_back(COMMAND_REDO);
	//SHOW COMMANDS
	dictionaryCommands[DICTIONARY_SHOW_INDEX].push_back(COMMAND_SHOW);
	dictionaryCommands[DICTIONARY_SHOW_INDEX].push_back(COMMAND_DISPLAY);
	dictionaryCommands[DICTIONARY_SHOW_INDEX].push_back(COMMAND_SEARCH);
	//SHOWALL COMMANDS
	dictionaryCommands[DICTIONARY_SHOWALL_INDEX].push_back(COMMAND_SHOWALL);
	dictionaryCommands[DICTIONARY_SHOWALL_INDEX].push_back(COMMAND_DISPLAYALL);
	dictionaryCommands[DICTIONARY_SHOWALL_INDEX].push_back(COMMAND_SEARCHALL);
}

void Parser::loadRepeatDictionary()
{
	dictionaryRepeatCommands[REPEAT_DAILY_INDEX].push_back(REPEAT_DAILY);
	dictionaryRepeatCommands[REPEAT_DAILY_INDEX].push_back(REPEAT_EVERY_DAY);
	dictionaryRepeatCommands[REPEAT_WEEKLY_INDEX].push_back(REPEAT_WEEKLY);
	dictionaryRepeatCommands[REPEAT_WEEKLY_INDEX].push_back(REPEAT_EVERY_WEEK);
	dictionaryRepeatCommands[REPEAT_FORTNIGHTLY_INDEX].push_back(REPEAT_FORTNIGHTLY);
	dictionaryRepeatCommands[REPEAT_FORTNIGHTLY_INDEX].push_back(REPEAT_EVERY_FORTNIGHT);
	dictionaryRepeatCommands[REPEAT_MONTHLY_INDEX].push_back(REPEAT_MONTHLY);
	dictionaryRepeatCommands[REPEAT_MONTHLY_INDEX].push_back(REPEAT_EVERY_MONTH);
	dictionaryRepeatCommands[REPEAT_ANNUALLY_INDEX].push_back(REPEAT_ANNUALLY);
	dictionaryRepeatCommands[REPEAT_ANNUALLY_INDEX].push_back(REPEAT_EVERY_YEAR);
}

void Parser::loadMarkerDictionary()
{
	dictionaryMarker.push_back(MARKER_AT);
	dictionaryMarker.push_back(MARKER_NEAR);
	dictionaryMarker.push_back(MARKER_BY);
	dictionaryMarker.push_back(MARKER_DUE);
	dictionaryMarker.push_back(MARKER_FROM);
	dictionaryMarker.push_back(MARKER_TO);
	dictionaryMarker.push_back(MARKER_COMMA_TO);
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
	if(scanTimerDictionary(word) || scanMonthDictionary(word))
		return true;
	else
		return false;
}

bool Parser::scanTimerDictionary(string word){
	if(scanTimeDictionary(word) || scanDatesDictionary(word))
		return true;
	else
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
	int foundCommand = FOUND_FAILED;
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
	case DICTIONARY_ADD_INDEX:
		return COMMAND_ADD;
	case DICTIONARY_DELETE_INDEX:
		return COMMAND_DELETE;
	case DICTIONARY_MARK_INDEX:
		return COMMAND_MARK;
	case DICTIONARY_MODIFY_INDEX:
		return COMMAND_MODIFY;
	case DICTIONARY_UNDO_INDEX:
		return COMMAND_UNDO;
	case DICTIONARY_REDO_INDEX:
		return COMMAND_REDO;
	case DICTIONARY_SHOW_INDEX:
		return COMMAND_SHOW;
	case DICTIONARY_SHOWALL_INDEX:
		return COMMAND_SHOWALL;
	default:
		return COMMAND_NULL;
	}
}

string Parser::scanRepeatDictionary(string word)
{
	size_t foundRepeat;
	size_t currentDictionarySize;
	bool found = false;;
	for(size_t i=0; i<dictionaryRepeatCommands.size() && !found; i++){
		currentDictionarySize = (dictionaryRepeatCommands.at(i)).size();
		for(size_t k=0; k<currentDictionarySize; k++){
			if(dictionaryRepeatCommands[i][k]==word){
				foundRepeat = i;
				found = true;
				break;
			}
		}
	}

	switch(foundRepeat){
	case REPEAT_DAILY_INDEX:
		return REPEAT_DAILY;
	case REPEAT_WEEKLY_INDEX:
		return REPEAT_WEEKLY;
	case REPEAT_FORTNIGHTLY_INDEX:
		return REPEAT_FORTNIGHTLY;
	case REPEAT_MONTHLY_INDEX:
		return REPEAT_MONTHLY;
	case REPEAT_ANNUALLY_INDEX:
		return REPEAT_ANNUALLY;
	default:
		return REPEAT_NULL;
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

void Parser::shortenInput(size_t partitionStart, size_t partitionEnd)
{
	size_t partitionLength = partitionEnd-partitionStart;

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
	removeBorderSpaces(textSlotStartNumber);
	removeBorderSpaces(textSlotEndNumber);
}

void Parser::removeBorderSpaces(string& str)
{
	if(str.empty())
		return;

	while(!str.empty() && str.front()==MARKER_ENCLOSE){

		str.erase(INITIALIZE_SIZE_T, MARKER_ENCLOSE_LENGTH);
	}

	while(!str.empty() && str.back()==MARKER_ENCLOSE){
		str.pop_back();
	}
}

void Parser::parseAllTimeAndDate()
{
	removeBorderSpaces(textStart);
	removeBorderSpaces(textEnd);
	parseTimeAndDate(textStart, textStartDate, textStartTime);
	parseTimeAndDate(textEnd, textEndDate, textEndTime);
}

bool Parser::parseTimeAndDate(string& str, string& strDate, string& strTime)
{
	stringstream buffer(str);
	string stringCheck;
	string _stringCheck;
	string repeatCheck = INITIALIZE_STRING_BLANK;
	//string scanResult;
	size_t foundLeft;
	size_t foundRight;
	bool foundRepeat = false;
	bool dateDetermined = false;
	bool dateDayDetermine = false;
	bool dateMonthDetermined = false;
	bool dateYearDetermine = false;

	bool timeDetermined = false;
	size_t stringLength;
	bool isChar = false;
	bool isDigit = false;

	if(str.empty() || str==TIMER_SPACE)
		return true;
	while(!buffer.eof()){
		buffer >> _stringCheck;
		stringCheck = _stringCheck;
		toLowerCase(stringCheck);
		stringLength = stringCheck.size();

		if(dateDetermined && timeDetermined && !stringCheck.empty()){
			logging(MESSAGE_ERROR_DATE_TIME_ALREADY_FOUND,Error,None);
			throw MESSAGE_ERROR_DATE_TIME_ALREADY_FOUND;							// If Date and Time has been determined and stringCheck still has a new word, it is an error
		}
		if(dateDayDetermine && dateMonthDetermined && dateYearDetermine)
			dateDetermined = dateDayDetermine && dateMonthDetermined && dateYearDetermine; // if components of date are determined, turn dateDetermined as true

		if(stringCheck==TIMER_REMOVE_TIME){
			if(textCommand==COMMAND_MODIFY){
				strDate = TIMER_REMOVE_TIME;
				strTime = TIMER_REMOVE_TIME;
				dateDetermined = true;
				timeDetermined = true;
				return true;
			}
			else{
				logging(MESSAGE_ERROR_INVALID_REMOVAL_OF_TIME,Error,None);
				throw MESSAGE_ERROR_INVALID_REMOVAL_OF_TIME;				// If user specify "*" not in modify, it will be an error.
			}
		}
		/*scanResult = scanRepeatDictionary(stringCheck);
		if(scanResult!=REPEAT_NULL && !foundRepeat){
		repeatCheck = scanResult;
		foundRepeat = true;
		continue;
		}*/

		if(stringCheck == REPEAT_EVERY || (!repeatCheck.empty() && !foundRepeat)){
			if(repeatCheck.empty()){
				repeatCheck = stringCheck;
				continue;
			}
			else if(scanDatesDictionary(stringCheck)){
				repeatCheck = REPEAT_EVERY_WEEK;
				foundRepeat = true;
			}
			else{
				repeatCheck += TIMER_SPACE + stringCheck;
				foundRepeat = true;
				continue;
			}
		}
		if(!dateDetermined){
			if(stringLength > LENGTH_0 && stringLength < LENGTH_3 && !dateDayDetermine){					// Date Format: 7 or 07  => Date day fragment, expect Date month fragment 
				int i = INITIALIZE_INT;
				while(i != stringLength){
					isDigit = isdigit(stringCheck[i]) != IS_COMPARE_FAIL;
					if(!isDigit){
						logging(MESSAGE_ERROR_WRONG_DATE_IS_NOT_DIGIT,Error,None);
						throw MESSAGE_ERROR_WRONG_DATE_IS_NOT_DIGIT;
					}
					i++;
				}
				if(atoi(stringCheck.c_str()) > DATE_MAX){						// Date Format: Date cannot be more than 31
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
			else if(stringLength >= LENGTH_3 && stringLength < LENGTH_6) {				// Date Format: 1/2 || 01/02 || 1/2/3 || MONTH_SHORT_WORD || YYYY
				if(stringCheck.find(TIMER_SLASH)!=string::npos){	
					foundLeft = stringCheck.find(TIMER_SLASH);
					if(stringCheck.rfind(TIMER_SLASH)!=string::npos){	
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
				else if(stringCheck.find(TIMER_DASH)!=string::npos){
					foundLeft = stringCheck.find(TIMER_DASH);
					if(stringCheck.rfind(TIMER_DASH)!=string::npos){	
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
				else if (stringLength < LENGTH_5 && scanMonthDictionary(stringCheck)){								// Date Format: May or Sept  => Date month fragment, expect Date day fragment
					int i = INITIALIZE_INT;
					while(i != stringLength){
						isChar = isalpha(stringCheck[i]) != IS_COMPARE_FAIL;
						if(!isChar){
							logging(MESSAGE_ERROR_WRONG_DATE_FORMAT_MONTH,Error,None);
							throw MESSAGE_ERROR_WRONG_DATE_FORMAT_MONTH;
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
				else if(stringLength == LENGTH_4 && isdigit(stringCheck.front()) && !(stringCheck.find(TIME_ANTE_MERIDIAN)!=string::npos || stringCheck.find(TIME_POST_MERIDIAN)!=string::npos)){
					int i = INITIALIZE_INT;
					while(i != stringLength){
						isDigit = isdigit(stringCheck[i]) != IS_COMPARE_FAIL;
						if(!isDigit){
							logging(MESSAGE_ERROR_WRONG_DATE_FORMAT_YEAR,Error,None);
							throw MESSAGE_ERROR_WRONG_DATE_FORMAT_YEAR;
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
				else if(scanTimerDictionary(stringCheck)){
					if(stringCheck==TIMER_NEXT)
						strDate += _stringCheck;
					else if(!strDate.empty() && scanDatesDictionary(stringCheck)){
						strDate += TIMER_SPACE + _stringCheck;									//Date Format: Tml, today etc.
						dateDetermined = true;
					}
					else{
						strDate = _stringCheck;
						dateDetermined = true;
					}
					continue;
				}
			}
			else if(stringLength >= LENGTH_6 && stringLength < LENGTH_11){				// Date Format: 1/2/13 == 01/02/2013 || MONTH_FULL_WORD
				if(stringCheck.find(TIMER_SLASH)!=string::npos){	
					foundLeft = stringCheck.find(TIMER_SLASH);
					if(stringCheck.rfind(TIMER_SLASH)!=string::npos){	
						foundRight = stringCheck.rfind(TIMER_SLASH);
						if((foundRight-foundLeft)<=SPACE_DIFF_3 && (foundRight-foundLeft)>SPACE_DIFF_0){
							strDate = _stringCheck;							// Date Format: 1/2/13 => Shorter representation of date with year
							dateDetermined = true;
							continue;
						}
						else{
							logging(MESSAGE_ERROR_WRONG_DATE_FORMAT_NOT_2_SLASH,Error,None);
							throw MESSAGE_ERROR_WRONG_DATE_FORMAT_NOT_2_SLASH;
						}
					}
					else{
						logging(MESSAGE_ERROR_WRONG_DATE_FORMAT_NOT_2_SLASH,Error,None);
						throw MESSAGE_ERROR_WRONG_DATE_FORMAT_NOT_2_SLASH;
					}
				}
				else if(stringCheck.find(TIMER_DASH)!=string::npos){
					foundLeft = stringCheck.find(TIMER_DASH);
					if(stringCheck.rfind(TIMER_DASH)!=string::npos){	
						foundRight = stringCheck.rfind(TIMER_DASH);
						if((foundRight-foundLeft)<=SPACE_DIFF_3 && (foundRight-foundLeft)>SPACE_DIFF_0){
							strDate = _stringCheck;							// Date Format: 1-2-13 => Shorter representation of date
							dateDetermined = true;
							continue;
						}
						else{
							logging(MESSAGE_ERROR_WRONG_DATE_FORMAT_NOT_2_DASH,Error,None);
							throw MESSAGE_ERROR_WRONG_DATE_FORMAT_NOT_2_DASH;
						}
					}
					else{
						logging(MESSAGE_ERROR_WRONG_DATE_FORMAT_NOT_2_DASH,Error,None);
						throw MESSAGE_ERROR_WRONG_DATE_FORMAT_NOT_2_DASH;
					}
				}
				else if (stringLength < LENGTH_10 && scanMonthDictionary(stringCheck)){								// Date Format: January or September  => Date month fragment, expect Date day fragment
					int i = INITIALIZE_INT;
					while(i != stringLength){
						isChar = isalpha(stringCheck[i]) != IS_COMPARE_FAIL;
						if(!isChar){
							logging(MESSAGE_ERROR_WRONG_DATE_FORMAT_MONTH,Error,None);
							throw MESSAGE_ERROR_WRONG_DATE_FORMAT_MONTH;
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
				else if(scanTimerDictionary(stringCheck)){
					if(stringCheck==TIMER_NEXT)
						strDate += _stringCheck;
					else if(!strDate.empty() && scanDatesDictionary(stringCheck)){
						strDate += TIMER_SPACE + _stringCheck;									//Date Format: Tomorrow
						dateDetermined = true;
					}
					else{
						strDate = _stringCheck;
						dateDetermined = true;
					}
					continue;
				}
			}
		}
		if(!timeDetermined){
			if(stringCheck.find(TIMER_COLON)!=string::npos){
				if(stringCheck.find(TIME_ANTE_MERIDIAN)!=string::npos || stringCheck.find(TIME_POST_MERIDIAN)!=string::npos){
					foundLeft = stringCheck.find(TIMER_COLON);
					foundRight = stringCheck.rfind(TIMER_COLON);
					if(foundLeft==foundRight){
						strTime = _stringCheck;								// Time Format: 09:00AM
						timeDetermined = true;
						continue;
					}
					else{
						logging(MESSAGE_ERROR_WRONG_TIME_FORMAT_2_COLONS,Error,None);
						throw MESSAGE_ERROR_WRONG_TIME_FORMAT_2_COLONS;				// Time Format: error, 09:00:00AM
					}
				}
				else{
					logging(MESSAGE_ERROR_WRONG_TIME_FORMAT_NO_AM_PM ,Error,None);
					throw MESSAGE_ERROR_WRONG_TIME_FORMAT_NO_AM_PM ;					// Time Format: error, 09:00, use 24hr format instead or put AM/PM
				}
			}
			else if(stringCheck.find(TIMER_DOT)!=string::npos){
				if(stringCheck.find(TIME_ANTE_MERIDIAN)!=string::npos || stringCheck.find(TIME_POST_MERIDIAN)!=string::npos){
					foundLeft = stringCheck.find(TIMER_DOT);
					foundRight = stringCheck.rfind(TIMER_DOT);
					if(foundLeft==foundRight){
						strTime = _stringCheck;								// Time Format: 09.00AM
						timeDetermined = true;
						continue;
					}
					else{
						logging(MESSAGE_ERROR_WRONG_TIME_FORMAT_2_DOTS,Error,None);
						throw MESSAGE_ERROR_WRONG_TIME_FORMAT_2_DOTS;				// Time Format: error, 09.00.00AM
					}
				}
				else{
					logging(MESSAGE_ERROR_WRONG_TIME_FORMAT_NO_AM_PM ,Error,None);
					throw MESSAGE_ERROR_WRONG_TIME_FORMAT_NO_AM_PM ;					// Time Format: error, 09.00, use 24hr format instead or put AM/PM
				}
			}
			else if(stringLength==TIMER_24HR_LENGTH) {
				int i = INITIALIZE_INT;
				bool is24hr = stringCheck.find(TIMER_HR)!=string::npos;
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
					logging(MESSAGE_ERROR_WRONG_TIME_FORMAT_NOT_24HR,Error,None);
					throw MESSAGE_ERROR_WRONG_TIME_FORMAT_NOT_24HR;
				}
			}
			else if(stringCheck==TIME_ANTE_MERIDIAN || stringCheck==TIME_POST_MERIDIAN){
				logging(MESSAGE_ERROR_WRONG_TIME_FORMAT_AM_PM,Error,None);
				throw MESSAGE_ERROR_WRONG_TIME_FORMAT_AM_PM;									// Time Format : Cannot be 10 PM => only 10PM works
			}
			else if((stringCheck.find(TIME_ANTE_MERIDIAN)!=string::npos || stringCheck.find(TIME_POST_MERIDIAN)!=string::npos) && stringLength > TIMER_TIME_LOWER_LENGTH){
				strTime = _stringCheck;
				timeDetermined = true;
				continue;
			}
			else{
				logging(MESSAGE_ERROR_WRONG_TIME_FORMAT,Error,None);
				throw MESSAGE_ERROR_WRONG_TIME_FORMAT;
			}
		}
		else{
			logging(MESSAGE_ERROR_WRONG_TIME_FORMAT,Error,None);
			throw MESSAGE_ERROR_WRONG_TIME_FORMAT;
		}
	}
	if((!dateYearDetermine && dateMonthDetermined && !dateDayDetermine) || 
		(!dateYearDetermine && !dateMonthDetermined && dateDayDetermine)){
			logging(MESSAGE_ERROR_FOUND_INCOMPLETE_DATE_FORMAT,Error,None);
			throw MESSAGE_ERROR_FOUND_INCOMPLETE_DATE_FORMAT;
	}
	if(dateYearDetermine && !dateMonthDetermined && !dateDayDetermine){
		logging(MESSAGE_ERROR_FOUND_INCOMPLETE_DATE_OR_YEAR_ONLY,Error,None);
		throw MESSAGE_ERROR_FOUND_INCOMPLETE_DATE_OR_YEAR_ONLY;
	}
	if(foundRepeat){
		if(!textRepeat.empty())
			throw MESSAGE_ERROR_NO_DOUBLE_REPEATS;
		try{
			textRepeat = scanRepeatDictionary(repeatCheck);
			if(textRepeat == COMMAND_NULL){
				logging(MESSAGE_ERROR_WRONG_FORMAT,Error,None);
				throw MESSAGE_ERROR_WRONG_FORMAT;
			}
		}
		catch(string error){
			throw;
		}
	}
	return true;
}

void Parser::toLowerCase(string &str)
{
	const int length = str.length();
	for(int i=INITIALIZE_INT; i < length; ++i)
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
	size_t found = input.find(textCommand);
	toLowerCase(textCommand);
	input.replace(0, found+textCommand.length()+1, "");
}

//Check if the first character is a valid digit
bool Parser::isParseInt(string input, int &value)
{	
	int stringLength = input.size();
	int i = INITIALIZE_INT;
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
	int i = INITIALIZE_INT;
	bool isDigit = true;
	while(i != stringLength){
		isDigit = isdigit(input[i]) != IS_COMPARE_FAIL;
		if(!isDigit){
			return isDigit;
		}
		i++;
	}
	return isDigit;
}
