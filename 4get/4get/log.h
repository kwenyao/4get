#ifndef LOG_H_
#define LOG_H_

#include <fstream>
#include <ctime>
#include <iostream>
#include <cctype>
#include <string>

#include <sstream>
#include <algorithm>
#include <assert.h>

enum LogType {Info, Debug, Warning, Error};
enum LogStatus {None, Pass, Fail};
#define APP_NAME "4get"

using namespace std;

class Log 
{
private:

	static const string LOGGING_NEW;
	static const string LOGGING_STARTING;
	static const string LOGGING_ENDING;
	static const string LOGGING_TIME_STAMP;
	static const string LOGGING_FORMAT;
	static const string LOG_INFO;
	static const string LOG_WARNING;
	static const string LOG_ERROR;
	static const string LOG_DEBUG;
	static const string LOG_PASS;
	static const string LOG_FAIL;
	static const string LOG_NONE;

	fstream _logFile;
	string _logFileName;
	int _logIndex;

	bool isFileEmpty();
	void openLog();
	void saveLog();

public:
	Log();
	~Log();
	void logDetails(std::string, LogType, LogStatus);
	static std::string getCurrentTime(void);
	string logMessages(const string);
	string logMessages(const string, string);
	string logType(LogType);
	string logStatus(LogStatus);

};
#endif
