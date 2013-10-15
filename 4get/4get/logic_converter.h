#ifndef _LOGIC_CONVERTER_H_
#define _LOGIC_CONVERTER_H_
#include "logic_task.h"
#include "common_message.h"
#include <sstream>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace Enum;
using namespace Constants;
using namespace chrono;

class Converter
{
private:
	int extractYear(string timeStr);
	int extractMonth(string timeStr);
	int extractDay(string timeStr);
	int extractHour(string timeStr);
	int extractMin(string timeStr);

	static const int MONTH_CORRECTION;
	static const int YEAR_CORRECTION;
	static const int DEFAULT_END_HOUR;
	static const int DEFAULT_END_MIN;
	static const int DEFAULT_START_HOUR;
	static const int DEFAULT_START_MIN;
	static const int YEAR_21_CENTURY;

	void getEndDate(bool isNoEndDate, int& year, int& month, int& day, string endDate);
	void getEndTime(bool isNoEndTime, int& hour, int& min, string endTime);
	void getStartDate(bool isNoStartDate, int& year, int& month, int& day, string startDate);
	void getStartTime(bool isNoStartTime, int& hour, int& min, string startTime);

	void getTodayDate(int& year, int& month, int& day);

	void getDefaultEndTime(int& hour, int& min);
	void getDefaultStartTime(int& hour, int& min);

	void extractDate(string dateStr, int& year, int& month, int& day);
	void extractTime(string timeStr, int& hour, int& min);

	time_t createTime(int year, int month, int day, int hour, int min);

public:
	Converter();
	int convertStringToInt(string);
	tm* convertStringToTm(string);
	Status convertStringToStatus(string);
	RepeatType convertStringToRepeatType(string);
	Priority convertStringToPriority(string);
	bool isEqual(string str1, const string str2);

	bool convertStringToTime(string timeStr, time_t returnTime);
	bool convertStringToTime(string startDate, 
			  				 string startTime, 
							 string endDate, 
							 string endTime, 
							 time_t& returnStart, 
							 time_t& returnEnd);
};
#endif