//@author A0097592M
#include "Log.h"

/*
* =====================================================================================
*
*       Filename:  Log.cpp
*
*         Author:  KUAN CHOW LEONG JOHN (A0097592M), johnkuan@nus.edu.sg
*   Organization:  NUS, School of Computing
*
* =====================================================================================
*/

const string Log::LOGGING_NEW = " Log data on ";
const string Log::LOGGING_EXT = ".txt";
const string Log::LOGGING_STARTING = "---------------Log started---------------\n" ;
const string Log::LOGGING_ENDING = "---------------Log end---------------\n";
const string Log::LOGGING_TIME_STAMP = "---------------Log messages as of %s---------------\n";
const string Log::LOGGING_FORMAT = "Log Message: '%s' ";
const string Log::LOGGING_INDEX_BRACKET = ")";
const string Log::LOG_INFO = " [INFO]"; 
const string Log::LOG_DEBUG = " [DEBUG]"; 
const string Log::LOG_WARNING = " [WARNING]"; 
const string Log::LOG_ERROR = " [ERROR]";
const string Log::LOG_ASSERT_FAILURE = "";
const string Log::LOG_PASS = ": PASS\n";
const string Log::LOG_FAIL = ": FAIL\n";
const string Log::LOG_NONE = "\n";

#define BUFFER_SIZE 100

/*************************************
           PUBLIC FUNCTIONS            
*************************************/

void logging(std::string message, LogType type, LogStatus status)
{
	static std::ofstream _logFile;
	static std::string _logFileName;
	static int _logIndex = 1;

	openLog(_logFile, _logFileName);
	assert(logType(type)!=LOG_ASSERT_FAILURE);								//raise if type is wrongly inputted
	_logFile << _logIndex << LOGGING_INDEX_BRACKET << getTimeStamp(Current) << logMessages(LOGGING_FORMAT, message) << logType(type) << logStatus(status);
	_logIndex++;
}

/*************************************
           PRIVATE FUNCTIONS            
*************************************/

void Log::createFileName(string& _logFileName)
{
	_logFileName = getTimeStamp(New);
	_logFileName += LOGGING_EXT;
}

void Log::openLog(ofstream& _logFile, string& _logFileName)
{
	static bool isOpen = false;
	if(!isOpen){
		createFileName(_logFileName);
		_logFile.open(_logFileName, std::ios::out);
		assert(_logFile.is_open());												//raise if file has not been opened at this point
		isOpen = true;
		_logFile << logMessages(LOGGING_STARTING);
	}

	return;
}

string Log::logMessages(const string feedback)
{
	char buffer[BUFFER_SIZE];

	sprintf_s(buffer, feedback.c_str());

	return string(buffer);
}

string Log::logMessages(const string feedback, string input)
{
	char buffer[BUFFER_SIZE];

	sprintf_s(buffer, feedback.c_str(), input.c_str());

	return string(buffer);
}

string Log::logType(LogType type)
{
	switch(type){
	case Info:
		return LOG_INFO;
	case Debug:
		return LOG_DEBUG;
	case Warning:
		return LOG_WARNING;
	case Error:
		return LOG_ERROR;
	default:
		return LOG_ASSERT_FAILURE;
	}
}
string Log::logStatus(LogStatus status)
{
	switch(status){
	case Pass:
		return LOG_PASS;
	case Fail:
		return LOG_FAIL;
	default:
		return LOG_NONE;
	}
}

string Log::getTimeStamp(LogTime type)
{
	time_t now;
	string timeStamp;
	struct tm timeInfo = {0};
	time(&now);
	//timeInfo = localtime(&now);
	localtime_s(&timeInfo,&now);
	if(type == Current){
		timeStamp = INITIALIZE_STRING_BLANK;
		// [DD/MM/YY HH:MM:SS] 
		timeStamp += TIMER_SQUARE_BRACKETS_OPEN;
		timeStamp += std::to_string(timeInfo.tm_mday);
		timeStamp += TIMER_SLASH;
		timeStamp += std::to_string(timeInfo.tm_mon+1);
		timeStamp += TIMER_SLASH;
		timeStamp += std::to_string(timeInfo.tm_year+1900);
		timeStamp += TIMER_SPACE;
		timeStamp += std::to_string(timeInfo.tm_hour);
		timeStamp += TIMER_COLON;
		timeStamp += std::to_string(timeInfo.tm_min);
		timeStamp += TIMER_COLON;
		timeStamp += std::to_string(timeInfo.tm_sec);
		timeStamp += TIMER_SQUARE_BRACKETS_CLOSE;
	}
	else{
		timeStamp = APP_NAME + LOGGING_NEW;
		//DD-MM-YY HH.MM.SS
		timeStamp += std::to_string(timeInfo.tm_mday);
		timeStamp += TIMER_DASH;
		timeStamp += std::to_string(timeInfo.tm_mon+1);
		timeStamp += TIMER_DASH;
		timeStamp += std::to_string(timeInfo.tm_year+1900);
		timeStamp += TIMER_SPACE;
		timeStamp += std::to_string(timeInfo.tm_hour);
		timeStamp += TIMER_DOT;
		timeStamp += std::to_string(timeInfo.tm_min);
		timeStamp += TIMER_DOT;
		timeStamp += std::to_string(timeInfo.tm_sec);
	}

	return timeStamp;
}