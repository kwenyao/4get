#ifndef _LOGIC_CONVERTER_H_
#define _LOGIC_CONVERTER_H_
#include "logic_task.h"
#include "common_message.h"
#include <sstream>
#include <algorithm>
#include <chrono>
#include <vector>
#include <cctype>

using namespace std;
using namespace Enum;
using namespace Constants;
using namespace chrono;

class Converter
{
private:
	vector<string> _dateVector;
	vector<string> _timeVector;

	enum DateTimeType{
		dateEnum,
		timeEnum
	};

	enum DateType{
		dayEnum,
		monthEnum,
		yearEnum
	};

	int extractYear(string timeStr);
	int extractMonth(string timeStr);
	int extractDay(string timeStr);
	int extractHour(string timeStr);
	int extractMin(string timeStr);

	static const string REPEAT_DAILY;
	static const string REPEAT_WEEKLY;
	static const string REPEAT_FORGHTNIGHTLY;
	static const string REPEAT_MONTHLY;
	static const string REPEAT_ANNUALLY;
	static const string PRIORITY_HIGH;
	static const string PRIORITY_HIGH2;

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

	static const int INDEX_TOMORROW_START;
	static const int INDEX_TOMORROW_END;
	static const int INDEX_MONDAY_START;
	static const int INDEX_MONDAY_END;
	static const int INDEX_TUESDAY_START;
	static const int INDEX_TUESDAY_END;
	static const int INDEX_WEDNESDAY_START;
	static const int INDEX_WEDNESDAY_END;
	static const int INDEX_THURSDAY_START;
	static const int INDEX_THURSDAY_END;
	static const int INDEX_FRIDAY_START;
	static const int INDEX_FRIDAY_END;
	static const int INDEX_SATURDAY_START;
	static const int INDEX_SATURDAY_END;
	static const int INDEX_SUNDAY_START;
	static const int INDEX_SUNDAY_END;
	static const int INDEX_JAN_START;
	static const int INDEX_JAN_END;
	static const int INDEX_FEB_START;
	static const int INDEX_FEB_END;
	static const int INDEX_MAR_START;
	static const int INDEX_MAR_END;
	static const int INDEX_APR_START;
	static const int INDEX_APR_END;
	static const int INDEX_MAY_START;
	static const int INDEX_MAY_END;
	static const int INDEX_JUN_START;
	static const int INDEX_JUN_END;
	static const int INDEX_JUL_START;
	static const int INDEX_JUL_END;
	static const int INDEX_AUG_START;
	static const int INDEX_AUG_END;
	static const int INDEX_SEP_START;
	static const int INDEX_SEP_END;
	static const int INDEX_OCT_START;
	static const int INDEX_OCT_END;
	static const int INDEX_NOV_START;
	static const int INDEX_NOV_END;
	static const int INDEX_DEC_START;
	static const int INDEX_DEC_END;

	static const int DAY_SUNDAY;
	static const int DAY_MONDAY;
	static const int DAY_TUESDAY;
	static const int DAY_WEDNESDAY;
	static const int DAY_THURSDAY;
	static const int DAY_FRIDAY;
	static const int DAY_SATURDAY;
	static const int MONTH_NUMBER_JAN;
	static const int MONTH_NUMBER_FEB;
	static const int MONTH_NUMBER_MAR;
	static const int MONTH_NUMBER_APR;
	static const int MONTH_NUMBER_MAY;
	static const int MONTH_NUMBER_JUN;
	static const int MONTH_NUMBER_JUL;
	static const int MONTH_NUMBER_AUG;
	static const int MONTH_NUMBER_SEP;
	static const int MONTH_NUMBER_OCT;
	static const int MONTH_NUMBER_NOV;
	static const int MONTH_NUMBER_DEC;
	static const int TIME_SPECIFIER_LENGTH;
	static const int TIME_PM_CORRECTION;
	static const string DATE_DELIMITER;
	static const string TIME_DELIMITER;

	void initialiseDateVector();
	void initialiseTimeVector();

	//functions to determine type of string
	//returns true if format is in words
	bool determineFormat(DateTimeType dateTime, string compareStr, int& index, int& dayDigit, int& yearDigit);
	bool checkDictionary(vector<string> dictionary, string compareStr, int& index, int& dayDigit, int& yearDigit);
	bool checkWord(vector<string> dictionary, string compareStr, int& index);
	bool checkNumber(string compareStr, int& dayDigit, int& yearDigit);

	void determineDate(int index, int dayDigit, int yearDigit, int& year, int& month, int& day);
	void dayCorrection(int index, int& year, int& month, int& day);
	void monthCorrection(int index, int dayDigit, int yearDigit, int& year, int& month, int& day);
	void declareDate(vector<string>& dateVector, int& year, int& month, int& day);

	void getDate(bool isNoDate, int& year, int& month, int& day, string endDate);
	void getEndTime(bool isNoEndTime, int& hour, int& min, string endTime);
	void getStartTime(bool isNoStartTime, int& hour, int& min, string startTime);
	void getTodayDate(int& year, int& month, int& day);
	void getWordDate(int correction, int& year, int& month, int& day);
	int getToday(DateType dateType);

	void getDefaultEndTime(int& hour, int& min);
	void getDefaultStartTime(int& hour, int& min);

	void extractDate(string dateStr, int& year, int& month, int& day);
	void extractTime(string timeStr, int& hour, int& min);

	time_t createTime(int year, int month, int day, int hour, int min);

	void splitString(string str, const string delimiter, vector<string>& strVector);
	void toLowerCase(string &str);

	bool isEqual(string string1, const string string2);
	bool isNumber(const string& str);

public:
	Converter();
	int convertStringToInt(string);
	RepeatType convertStringToRepeatType(string);
	Priority convertStringToPriority(string);
	bool convertStringToTime(string timeStr, time_t returnTime);
	time_t convertStringToTime(string dateStr, string timeStr);
	TaskType convertStringToTime(string startDate, 
			  				     string startTime, 
							     string endDate, 
							     string endTime, 
							     time_t& returnStart, 
							     time_t& returnEnd);
};
#endif