#ifndef _LOGIC_CONVERTER_H_
#define _LOGIC_CONVERTER_H_
#include "logic_task.h"
#include "common_message.h"
#include <sstream>
#include <algorithm>
#include <chrono>
#include <vector>

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
	static const int SLOT_DAY;
	static const int SLOT_MONTH;
	static const int SLOT_YEAR;
	static const int SLOT_HOUR;
	static const int SLOT_MIN;
	static const int TIME_SPECIFIER_LENGTH;
	static const int TIME_PM_CORRECTION;
	static const string DATE_DELIMITER_1;
	static const string DATE_DELIMITER_2;
	static const string TIME_DELIMITER_1;
	static const string TIME_DELIMITER_2;
	static const string TIME_ANTE_MERIDIAN;
	static const string TIME_POST_MERIDIAN;

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

	void splitString(string str, const string delimiter, vector<string>& strVector);

	void toLowerCase(string &str);

public:
	Converter();
	int convertStringToInt(string);
	tm* convertStringToTm(string);
	Status convertStringToStatus(string);
	RepeatType convertStringToRepeatType(string);
	Priority convertStringToPriority(string);
	bool isEqual(string str1, const string str2);

	bool convertStringToTime(string timeStr, time_t returnTime);
	TaskType convertStringToTime(string startDate, 
			  				 string startTime, 
							 string endDate, 
							 string endTime, 
							 time_t& returnStart, 
							 time_t& returnEnd);
};
#endif