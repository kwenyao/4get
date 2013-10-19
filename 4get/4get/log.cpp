#include "log.h"

const string Log::LOGGING_NEW = "A new Log File, %s, has been created.\n";
const string Log::LOGGING_STARTING = "---------------Log started---------------\n" ;
const string Log::LOGGING_ENDING = "---------------Log end---------------\n";
const string Log::LOGGING_TIME_STAMP = "---------------Log messages as of %s---------------\n";
const string Log::LOGGING_FORMAT = " Log for %s. ";
const string Log::LOG_INFO = " [INFO]"; 
const string Log::LOG_DEBUG = " [DEBUG]"; 
const string Log::LOG_WARNING = " [WARNING]"; 
const string Log::LOG_ERROR = " [ERROR]"; 
const string Log::LOG_PASS = ": PASS\n";
const string Log::LOG_FAIL = ": FAIL\n";
const string Log::LOG_NONE = "\n";

#define BUFFER_SIZE 100

Log::Log()
{
	_logFileName = APP_NAME;
	_logIndex = 1;
	openLog();
}
Log::~Log()
{
	saveLog();
}
void Log::logDetails(std::string function, LogType type, LogStatus status)
{
	assert(_logFile.is_open());
	_logFile << _logIndex << logMessages(LOGGING_FORMAT, function) << logType(type) << logStatus(status);
	_logIndex++;
}

void Log::openLog()
{
	if(!_logFile.is_open()){
		_logFile.open(_logFileName, ios::in | ios::out | ios::app);
		if(isFileEmpty())
			_logFile << LOGGING_NEW;
	}
	_logFile << logMessages(LOGGING_STARTING);
	_logFile << logMessages(LOGGING_TIME_STAMP); //need to implement time stamp: DD/MM/YY HH:MM
	return;
}

void Log::saveLog()
{
	_logFile << logMessages(LOGGING_ENDING);
	_logFile.close();
}

bool Log::isFileEmpty()
{
	_logFile.seekg(0, _logFile.end);
	std::streamoff length = _logFile.tellg();
	_logFile.seekg(0, _logFile.beg);
	if(length == -1)
		return true;
	else
		return false;
}

string Log::logMessages(const string feedback)
{
	char buffer[BUFFER_SIZE];

	sprintf_s(buffer, feedback.c_str());

	return buffer;
}



string Log::logMessages(const string feedback, string input)
{
	char buffer[BUFFER_SIZE];

	sprintf_s(buffer, feedback.c_str(), input.c_str());
	
	return buffer;
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

