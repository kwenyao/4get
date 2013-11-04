#ifndef _LOGIC_CONVERTER_H_
#define _LOGIC_CONVERTER_H_
#include "logic_task.h"
#include "common_message.h"
#include <sstream>
#include <algorithm>
#include <chrono>
#include <vector>
#include <cctype>
#include <assert.h>

using namespace std;
using namespace Enum;
using namespace Constants;
using namespace chrono;

class Converter
{
private:
	vector<vector<string>> _dateDictionary;
	vector<vector<string>> _timeDictionary;
	vector<string> _dateVector;
	vector<string> _timeVector;
	int _dayDigit;
	int _yearDigit;
	bool _isNext;
	int _matchedIndex;

	enum DateTimeType{
		dateEnum,
		timeEnum
	};

	enum DateType{
		weekDayEnum,
		monthDayEnum,
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

	static const int DATE_DICTIONARY_SIZE;
	static const int INDEX_TMR;
	static const int INDEX_MON;
	static const int INDEX_TUE;
	static const int INDEX_WED;
	static const int INDEX_THU;
	static const int INDEX_FRI;
	static const int INDEX_SAT;
	static const int INDEX_SUN;
	static const int INDEX_JAN;
	static const int INDEX_FEB;
	static const int INDEX_MAR;
	static const int INDEX_APR;
	static const int INDEX_MAY;
	static const int INDEX_JUN;
	static const int INDEX_JUL;
	static const int INDEX_AUG;
	static const int INDEX_SEP;
	static const int INDEX_OCT;
	static const int INDEX_NOV;
	static const int INDEX_DEC;
	static const int INDEX_NXT;

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
	static const int DATE_NEXT_CORRECTION;
	static const int YEAR_INT_MULTIPLIER;
	static const int MONTH_INT_MULTIPLIER;
	static const int DAY_INT_MULTIPLIER;
	static const string DATE_DELIMITER;
	static const string TIME_DELIMITER;

	void initialiseDateDictionary();
	void initialiseTimeVector();

	//functions to determine type of string
	//returns true if format is in words
	bool determineFormat(DateTimeType dateTime, string compareStr);
	bool checkDictionary(vector<vector<string>> dictionary, string compareStr);
	bool checkWord(vector<vector<string>> dictionary, string compareStr);
	bool checkNumber(string compareStr);

	void determineDate(int& year, int& month, int& day);
	void dayCorrection(int& year, int& month, int& day);
	void monthCorrection(int& year, int& month, int& day);
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

	bool verifyDate(int year, int month, int day);
	time_t createTime(int year, int month, int day, int hour, int min);

	void splitString(string str, const string delimiter, vector<string>& strVector);
	void toLowerCase(string &str);

	bool isEqual(string string1, const string string2);
	bool isNumber(const string& str);
	bool isKeyWord(vector<string> keyWordVector, string compareStr);

	void saveIndex(int index);

public:
	Converter();
	int convertStringToInt(string);
	RepeatType convertStringToRepeatType(string);
	Priority convertStringToPriority(string);
	long long convertDateToInt(string dateStr);
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