#include "logic_parser.h"

Parser::Parser()
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
	textSlotNumber = INITIALIZE_STRING_BLANK;
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
	textSlotNumber = INITIALIZE_STRING_BLANK;
}
void Parser::processCommand(string commandString, vector<string>& inputBits)
{
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
		else if(commandString.compare(COMMAND_SHOW)==COMPARE_SUCCESS || commandString.compare(COMMAND_DISPLAY)==COMPARE_SUCCESS){
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
		}*/
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

	parseAllTimeAndDate();

	textDescription = _textInput;
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
bool Parser::separateFunctionUndo(vector<string>& inputBits)
{
	return true;
}
bool Parser::separateFunctionShow(vector<string>& inputBits)
{
	if(!determineDateAndTime())												//if user specified with formats, startTime or endTime will have the time 
		textStartTime = _textInput;										//else whatever the user input after show will be assumed to be strings indicating time.
												
	logging(MESSAGE_SUCCESS_PARSED, Info, Pass);
	return true;
}
bool Parser::separateFunctionRedo(vector<string>& inputBits)
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

	if(textInput.find(MARKER_AT)!=std::string::npos){
		found = textInput.find(MARKER_AT);
		if(textInput.find(MARKER_COMMA, found+MARKER_AT_LENGTH)!=std::string::npos){
			foundComma = textInput.find(MARKER_COMMA, found+MARKER_AT_LENGTH);
			extractLength = determindExtractLength(found, foundComma, MARKER_AT, extractStartPos);
			i = foundComma;
			while(textInput[i]!=MARKER_ENCLOSE && i!=stringLength)
				marker += textInput[i++];
			if(marker==MARKER_BY || marker==MARKER_FROM || marker==MARKER_REMIND || marker==MARKER_REPEAT || marker==MARKER_PRIORITY){
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
			if(marker==MARKER_BY || marker==MARKER_FROM || marker==MARKER_REMIND || marker==MARKER_REPEAT || marker==MARKER_PRIORITY){
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
				if(marker==MARKER_AT || marker==MARKER_NEAR || marker==MARKER_REMIND || marker==MARKER_REPEAT || marker==MARKER_PRIORITY){
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
			if(marker==MARKER_AT || marker==MARKER_NEAR || marker==MARKER_REMIND || marker==MARKER_BY || marker==MARKER_FROM || marker==MARKER_PRIORITY){
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
	std::size_t foundEnclose = INITIALIZE_SIZE_T;
	std::size_t extractStartPos = INITIALIZE_SIZE_T;
	std::size_t extractLength = INITIALIZE_SIZE_T;

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
			if(marker==MARKER_AT || marker==MARKER_NEAR || marker==MARKER_REPEAT || marker==MARKER_BY || marker==MARKER_FROM || marker==MARKER_PRIORITY && textInput.find(MARKER_ON, found)!=std::string::npos){
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
	std::size_t found = INITIALIZE_SIZE_T;
	int slotNumber =0;
	istringstream iss(_textInput);
	string temp;
	iss >> temp;

	if(!isParseInt(temp, slotNumber))
		return false;
	textSlotNumber = std::to_string(slotNumber);
	found = textInput.find(MARKER_ENCLOSE);
	shortenInput(extractStartPos, ++found);

	return true;
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
std::size_t Parser::determindExtractLength(std::size_t found, std::size_t foundComma, string markConstant, std::size_t& extractStartPos)
{
	extractStartPos = INITIALIZE_SIZE_T;
	std::size_t extractEndPos;
	std::size_t shiftPos = INITIALIZE_SIZE_T;

	if(markConstant == MARKER_PRIORITY){
		shiftPos = shiftPos;
	}
	else if(markConstant == MARKER_REMIND){
		if(textInput.find(MARKER_ON,found)!=std::string::npos){
			found = textInput.find(MARKER_ON,found);
			shiftPos = MARKER_ON_LENGTH;
		}
	}

	else
		shiftPos = markConstant.size();

	extractStartPos = found + (++shiftPos); //shift the pos to first pos of text to be extracted.
	extractEndPos = --foundComma;

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
	removeBorderSpaces(textSlotNumber);
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
}
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
	inputBits[SLOT_SLOT_NUMBER] = textSlotNumber;
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
	if (isdigit(input[0]))
	{
		value = atoi(input.c_str());
		return true;
	}
	else
		return false;
}
string Parser::getCommand()
{
	return textCommand;
}