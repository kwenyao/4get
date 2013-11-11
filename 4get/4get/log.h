#ifndef LOG_H_
#define LOG_H_
#include <fstream>
#include <ctime>
#include <string>
#include <assert.h>
#include "common_message.h"

/*
* =====================================================================================
*
*       Filename:  Log.h
*
*         Author:  KUAN CHOW LEONG JOHN (A0097592M), johnkuan@nus.edu.sg
*   Organization:  NUS, School of Computing
*
* =====================================================================================
*/

#undef logging

using namespace std;
using namespace Constants;
using namespace Enum;

#define logging(string, LogType, LogStatus) Log::logging(string, LogType, LogStatus)
#define APP_NAME "4get"

class Log 
{
private:

	static const string LOGGING_NEW;
	static const string LOGGING_EXT;
	static const string LOGGING_STARTING;
	static const string LOGGING_ENDING;
	static const string LOGGING_TIME_STAMP;
	static const string LOGGING_FORMAT;
	static const string LOGGING_INDEX_BRACKET;
	static const string LOG_INFO;
	static const string LOG_WARNING;
	static const string LOG_ERROR;
	static const string LOG_DEBUG;
	static const string LOG_ASSERT_FAILURE;
	static const string LOG_PASS;
	static const string LOG_FAIL;
	static const string LOG_NONE;

	static void createFileName(string& _logFileName);
	static void openLog(ofstream& _logFile, string& _logFileName);
	static string getTimeStamp(LogTime type);
	static string logMessages(const string);
	static string logMessages(const string, string);
	static string logType(LogType);
	static string logStatus(LogStatus);

public:
	static void logging(std::string, LogType, LogStatus);
};
#endif
