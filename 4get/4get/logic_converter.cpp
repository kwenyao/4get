#include "logic_converter.h"

const string Converter::REPEAT_DAILY = "daily";
const string Converter::REPEAT_WEEKLY = "weekly";
const string Converter::REPEAT_FORGHTNIGHTLY = "fortnightly";
const string Converter::REPEAT_MONTHLY = "monthly";
const string Converter::REPEAT_ANNUALLY = "annually";
const string Converter::PRIORITY_HIGH = "!";
const string Converter::PRIORITY_HIGH2 = "high";

const int Converter::DEFAULT_END_HOUR = 23;
const int Converter::DEFAULT_END_MIN = 59;
const int Converter::DEFAULT_START_HOUR = 0;
const int Converter::DEFAULT_START_MIN = 0;
const int Converter::YEAR_21_CENTURY = 2000;
const int Converter::SLOT_DAY = 0;
const int Converter::SLOT_MONTH = 1;
const int Converter::SLOT_YEAR = 2;
const int Converter::SLOT_HOUR = 0;
const int Converter::SLOT_MIN = 1;

const int Converter::INDEX_TOMORROW_START = 0;
const int Converter::INDEX_TOMORROW_END = 3;

const int Converter::INDEX_MONDAY_START = 4;
const int Converter::INDEX_MONDAY_END = 5;
const int Converter::INDEX_TUESDAY_START = 6;
const int Converter::INDEX_TUESDAY_END = 8;
const int Converter::INDEX_WEDNESDAY_START = 9;
const int Converter::INDEX_WEDNESDAY_END = 10;
const int Converter::INDEX_THURSDAY_START = 11;
const int Converter::INDEX_THURSDAY_END = 14;
const int Converter::INDEX_FRIDAY_START = 15;
const int Converter::INDEX_FRIDAY_END = 16;
const int Converter::INDEX_SATURDAY_START = 17;
const int Converter::INDEX_SATURDAY_END = 18;
const int Converter::INDEX_SUNDAY_START = 19;
const int Converter::INDEX_SUNDAY_END = 20;

const int Converter::INDEX_JAN_START = 21;
const int Converter::INDEX_JAN_END = 22;
const int Converter::INDEX_FEB_START = 23;
const int Converter::INDEX_FEB_END = 24;
const int Converter::INDEX_MAR_START = 25;
const int Converter::INDEX_MAR_END = 26;
const int Converter::INDEX_APR_START = 27;
const int Converter::INDEX_APR_END = 28;
const int Converter::INDEX_MAY_START = 29;
const int Converter::INDEX_MAY_END = 29;
const int Converter::INDEX_JUN_START = 30;
const int Converter::INDEX_JUN_END = 31;
const int Converter::INDEX_JUL_START = 32;
const int Converter::INDEX_JUL_END = 33;
const int Converter::INDEX_AUG_START = 34;
const int Converter::INDEX_AUG_END = 35;
const int Converter::INDEX_SEP_START = 36;
const int Converter::INDEX_SEP_END = 38;
const int Converter::INDEX_OCT_START = 39;
const int Converter::INDEX_OCT_END = 40;
const int Converter::INDEX_NOV_START = 41;
const int Converter::INDEX_NOV_END = 42;
const int Converter::INDEX_DEC_START = 43; 
const int Converter::INDEX_DEC_END = 44;

const int Converter::DAY_SUNDAY = 0;
const int Converter::DAY_MONDAY = 1;
const int Converter::DAY_TUESDAY = 2;
const int Converter::DAY_WEDNESDAY = 3;
const int Converter::DAY_THURSDAY = 4;
const int Converter::DAY_FRIDAY = 5;
const int Converter::DAY_SATURDAY = 6;
const int Converter::MONTH_NUMBER_JAN = 1;
const int Converter::MONTH_NUMBER_FEB = 2;
const int Converter::MONTH_NUMBER_MAR = 3;
const int Converter::MONTH_NUMBER_APR = 4;
const int Converter::MONTH_NUMBER_MAY = 5;
const int Converter::MONTH_NUMBER_JUN = 6;
const int Converter::MONTH_NUMBER_JUL = 7;
const int Converter::MONTH_NUMBER_AUG = 8;
const int Converter::MONTH_NUMBER_SEP = 9;
const int Converter::MONTH_NUMBER_OCT = 10;
const int Converter::MONTH_NUMBER_NOV = 11;
const int Converter::MONTH_NUMBER_DEC = 12;

const int Converter::TIME_SPECIFIER_LENGTH = 2;
const int Converter::TIME_PM_CORRECTION = 12;
const int Converter::YEAR_INT_MULTIPLIER = 10000;
const int Converter::MONTH_INT_MULTIPLIER = 100;
const int Converter::DAY_INT_MULTIPLIER = 1;
const string Converter::DATE_DELIMITER = "/-";
const string Converter::TIME_DELIMITER = ":.";

Converter::Converter(){
	initialiseDateVector();
	initialiseTimeVector();
}

void Converter::initialiseDateVector(){
	_dateVector.push_back(TIMER_TOMORROW); 
	_dateVector.push_back(TIMER_TML);
	_dateVector.push_back(TIMER_TMR);
	_dateVector.push_back(TIMER_TMRW);

	_dateVector.push_back(TIMER_MONDAY); 
	_dateVector.push_back(TIMER_MON); 
	_dateVector.push_back(TIMER_TUESDAY);
	_dateVector.push_back(TIMER_TUES);
	_dateVector.push_back(TIMER_TUE);
	_dateVector.push_back(TIMER_WED);
	_dateVector.push_back(TIMER_WEDNESDAY);
	_dateVector.push_back(TIMER_THURSDAY);
	_dateVector.push_back(TIMER_THURS);
	_dateVector.push_back(TIMER_THU);
	_dateVector.push_back(TIMER_THUR);
	_dateVector.push_back(TIMER_FRIDAY);
	_dateVector.push_back(TIMER_FRI);
	_dateVector.push_back(TIMER_SATURDAY);
	_dateVector.push_back(TIMER_SAT);
	_dateVector.push_back(TIMER_SUN);
	_dateVector.push_back(TIMER_SUNDAY);

	_dateVector.push_back(MONTH_JAN);
	_dateVector.push_back(MONTH_JANUARY);
	_dateVector.push_back(MONTH_FEB);
	_dateVector.push_back(MONTH_FEBRUARY);
	_dateVector.push_back(MONTH_MAR);
	_dateVector.push_back(MONTH_MARCH);
	_dateVector.push_back(MONTH_APRIL);
	_dateVector.push_back(MONTH_APR);
	_dateVector.push_back(MONTH_MAY);
	_dateVector.push_back(MONTH_JUN);
	_dateVector.push_back(MONTH_JUNE);
	_dateVector.push_back(MONTH_JUL);
	_dateVector.push_back(MONTH_JULY);
	_dateVector.push_back(MONTH_AUG);
	_dateVector.push_back(MONTH_AUGUST);
	_dateVector.push_back(MONTH_SEPT);
	_dateVector.push_back(MONTH_SEP);
	_dateVector.push_back(MONTH_SEPTEMBER);
	_dateVector.push_back(MONTH_OCT);
	_dateVector.push_back(MONTH_OCTOBER);
	_dateVector.push_back(MONTH_NOV);
	_dateVector.push_back(MONTH_NOVEMBER);
	_dateVector.push_back(MONTH_DEC);
	_dateVector.push_back(MONTH_DECEMBER);
	
}

void Converter::initialiseTimeVector(){

}

int Converter::convertStringToInt(string str)
{
	int strInt;
	stringstream stringer(str);
	stringer >> strInt;
	return strInt;
}

RepeatType Converter::convertStringToRepeatType(string str){
	toLowerCase(str);
	if(isEqual(str, REPEAT_DAILY))
		return daily;
	else if(isEqual(str, REPEAT_WEEKLY))
		return weekly;
	else if(isEqual(str, REPEAT_FORGHTNIGHTLY))
		return fortnightly;
	else if(isEqual(str, REPEAT_MONTHLY))
		return monthly;
	else if(isEqual(str, REPEAT_ANNUALLY))
		return annually;
	else
		return repeatNone;
}

Priority Converter::convertStringToPriority(string str){
	if(isEqual(str, PRIORITY_HIGH) || isEqual(str,PRIORITY_HIGH2))
		return high;
	else
		return normal;
}

bool Converter::isEqual(string string1, const string string2){
	if(string1 == string2)
		return true;
	return false;
}

long long Converter::convertDateToInt(string dateStr){
	assert(!dateStr.empty());
	int year  = 0;
	int month = 0;
	int day   = 0;
	long long timeInt;
	time_t returnTime = 0;
	try{
		extractDate(dateStr, year, month, day);
		year = year * YEAR_INT_MULTIPLIER;
		month = month * MONTH_INT_MULTIPLIER;
		day = day * DAY_INT_MULTIPLIER;
		timeInt = year + month + day;
		return timeInt;
	} catch(string errStr){
		throw;
	}
}

time_t Converter::convertStringToTime(string dateStr, string timeStr){
	int year = 0;
	int month = 0;
	int day = 0;
	int hour = 0;
	int min = 0;
	time_t returnTime = 0;
	bool isNoDate = dateStr.empty();
	bool isNoTime = timeStr.empty();
	if(isNoDate && isNoTime)
		return returnTime;
	if(!isNoDate)
		extractDate(dateStr, year, month, day);
	if(!isNoTime)
		extractTime(timeStr, hour, min);
	returnTime = createTime(year, month, day, hour, min);
	return returnTime;
}

TaskType Converter::convertStringToTime(string startDate, 
										string startTime, 
										string endDate, 
										string endTime, 
										time_t& returnStart, 
										time_t& returnEnd)
{
	int startYear  = 0, endYear  = 0;
	int startMonth = 0, endMonth = 0;
	int startDay   = 0, endDay   = 0;
	int startHour  = 0, endHour  = 0;
	int startMin   = 0, endMin   = 0;
	bool isNoStartDate = startDate.empty();
	bool isNoStartTime = startTime.empty();
	bool isNoEndDate   = endDate.empty();
	bool isNoEndTime   = endTime.empty();
	returnStart = 0;
	returnEnd   = 0;

	if(isNoStartDate && isNoStartTime && isNoEndDate &&isNoEndTime)
		return floating;
	if(isNoEndDate && isNoEndTime)
		throw string(Message::MESSAGE_ERROR_NO_END_TIME);

	getDate(isNoEndDate, endYear, endMonth, endDay, endDate);
	getEndTime(isNoEndTime, endHour, endMin, endTime);
	returnEnd = createTime(endYear, endMonth, endDay, endHour, endMin);

	if(isNoStartDate && isNoStartTime)
		return deadline;

	getDate(isNoStartDate, startYear, startMonth, startDay, startDate);
	getStartTime(isNoStartTime, startHour, startMin, startTime);
	returnStart = createTime(startYear, startMonth, startDay, startHour, startMin);

	if(difftime(returnEnd, returnStart) > 0)
		return timed;
	else
		throw string(Message::MESSAGE_ERROR_START_AFTER_END);
}

void Converter::getDate(bool isNoDate, int& year, int& month, int& day, string dateStr){
	if(isNoDate)
		getTodayDate(year, month, day);
	else
		extractDate(dateStr, year, month, day);
}

void Converter::getEndTime(bool isNoEndTime, int& hour, int& min, string endTime){
	if(isNoEndTime)
		getDefaultEndTime(hour, min);
	else
		extractTime(endTime, hour, min);
}

void Converter::getStartTime(bool isNoStartTime, int& hour, int& min, string startTime){
	if(isNoStartTime)
		getDefaultStartTime(hour, min);
	else
		extractTime(startTime, hour, min);
}

void Converter::getTodayDate(int& year, int& month, int& day){
	time_t temp;
	struct tm currentTime;
	time(&temp);
	localtime_s(&currentTime,&temp);
	day = currentTime.tm_mday;
	month = currentTime.tm_mon + MONTH_CORRECTION;
	year = currentTime.tm_year + YEAR_CORRECTION;
}

void Converter::getWordDate(int correction, int& year, int& month, int& day){
	time_t temp;
	struct tm currentTime;
	time(&temp);
	localtime_s(&currentTime,&temp);
	day = currentTime.tm_mday + correction;
	month = currentTime.tm_mon + MONTH_CORRECTION;
	year = currentTime.tm_year + YEAR_CORRECTION;
}

int Converter::getToday(DateType dateType){
	time_t temp;
	struct tm currentTime;
	time(&temp);
	localtime_s(&currentTime,&temp);
	switch (dateType){
	case Converter::weekDayEnum:
		return currentTime.tm_wday;
	case Converter::monthDayEnum:
		return currentTime.tm_mday;
	case Converter::monthEnum:
		return (currentTime.tm_mon + MONTH_CORRECTION);
	case Converter::yearEnum:
		return (currentTime.tm_year + YEAR_CORRECTION);
	default:
		return -1;
	}
}

void Converter::getDefaultEndTime(int& hour, int& min){
	hour = DEFAULT_END_HOUR;
	min = DEFAULT_END_MIN;
}

void Converter::getDefaultStartTime(int& hour, int& min){
	hour = DEFAULT_START_HOUR;
	min = DEFAULT_START_MIN;
}

void Converter::extractDate(string dateStr, int& year, int& month, int& day){
	vector<string> dateVector;
	int index;
	int dayDigit = 0, yearDigit = 0;
	bool isWordFormat = determineFormat(dateEnum, dateStr, index, dayDigit, yearDigit);
	try{
		if(isWordFormat){
			determineDate(index, dayDigit, yearDigit, year, month, day);
		}
		else{
			splitString(dateStr, DATE_DELIMITER, dateVector);
			declareDate(dateVector, year, month, day);
		}
		if(year < YEAR_21_CENTURY)
			year = year + YEAR_21_CENTURY;
		verifyDate(year,month,day);
	} catch (string errStr){
		throw;
	}
}

bool Converter::verifyDate(int year, int month, int day){
	int todayYear = getToday(yearEnum);
	int todayMonth = getToday(monthEnum);
	int todayDay = getToday(monthDayEnum);
	bool isYearEqual = todayYear == year;
	bool isMonthEqual = todayMonth == month;
	if(year < todayYear)
		throw string(Message::MESSAGE_ERROR_INVALID_YEAR);
	else if(isYearEqual && month<todayMonth)
		throw string(Message::MESSAGE_ERROR_INVALID_MONTH);
	else if(isYearEqual && isMonthEqual && day<todayDay)
		throw string(Message::MESSAGE_ERROR_INVALID_DAY);
	else
		return true;
}

void Converter::determineDate(int index, int dayDigit, int yearDigit, int& year, int& month, int& day){
	try{
		if(index < INDEX_JAN_START)
			dayCorrection(index, year, month, day);
		else if(index > INDEX_SUNDAY_END && index < INDEX_DEC_END)
			monthCorrection(index, dayDigit, yearDigit, year, month, day);
		else
			throw string(Message::MESSAGE_ERROR_WRONG_DATE);
	} catch(string errStr) {
		throw;
	}
}

void Converter::monthCorrection(int index, int dayDigit, int yearDigit, int& year, int& month, int& day){
	if(index >= INDEX_JAN_START && index <= INDEX_JAN_END){
		month = MONTH_NUMBER_JAN;
	}
	else if(index >= INDEX_FEB_START && index <= INDEX_FEB_END){
		month = MONTH_NUMBER_FEB;
	}
	else if(index >= INDEX_MAR_START && index <= INDEX_MAR_END){
		month = MONTH_NUMBER_MAR;
	}
	else if(index >= INDEX_APR_START && index <= INDEX_APR_END){
		month = MONTH_NUMBER_APR;
	}
	else if(index >= INDEX_MAY_START && index <= INDEX_MAY_END){
		month = MONTH_NUMBER_MAY;
	}
	else if(index >= INDEX_JUN_START && index <= INDEX_JUN_END){
		month = MONTH_NUMBER_JUN;
	}
	else if(index >= INDEX_JUL_START && index <= INDEX_JUL_END){
		month = MONTH_NUMBER_JUL;
	}
	else if(index >= INDEX_AUG_START && index <= INDEX_AUG_END){
		month = MONTH_NUMBER_AUG;
	}
	else if(index >= INDEX_SEP_START && index <= INDEX_SEP_END){
		month = MONTH_NUMBER_SEP;
	}
	else if(index >= INDEX_OCT_START && index <= INDEX_OCT_END){
		month = MONTH_NUMBER_OCT;
	}
	else if(index >= INDEX_NOV_START && index <= INDEX_NOV_END){
		month = MONTH_NUMBER_NOV;
	}
	else if(index >= INDEX_DEC_START && index <= INDEX_DEC_END){
		month = MONTH_NUMBER_DEC;
	}
	if(dayDigit < 1)
		throw string(Message::MESSAGE_ERROR_MISSING_DAY);
	else
		day = dayDigit;

	if(yearDigit != 0)
		year = yearDigit;
	else
		year = getToday(yearEnum);
}

void Converter::dayCorrection(int index, int& year, int& month, int& day){
	int dayToday = getToday(weekDayEnum);
	int correction;
	if( index >= INDEX_TOMORROW_START && index <= INDEX_TOMORROW_END)
		correction = 1;
	else if(index >= INDEX_MONDAY_START && index <= INDEX_MONDAY_END){
		if(dayToday == DAY_SUNDAY)
			correction = 1;
		else
			correction = 8 - dayToday;
	}
	else if(index >= INDEX_TUESDAY_START && index <= INDEX_TUESDAY_END){
		if(dayToday < DAY_TUESDAY)
			correction = 2 - dayToday;
		else
			correction = 9 - dayToday;
	}
	else if(index >= INDEX_WEDNESDAY_START && index <= INDEX_WEDNESDAY_END){
		if(dayToday < DAY_WEDNESDAY)
			correction = 3 - dayToday;
		else
			correction = 10 - dayToday;
	}
	else if(index >= INDEX_THURSDAY_START && index <= INDEX_THURSDAY_END){
		if(dayToday < DAY_THURSDAY)
			correction = 4 - dayToday;
		else
			correction = 11 - dayToday;
	}
	else if(index >= INDEX_FRIDAY_START && index <= INDEX_FRIDAY_END){
		if(dayToday < DAY_FRIDAY)
			correction = 5 - dayToday;
		else
			correction = 12 - dayToday;
	}
	else if(index >= INDEX_SATURDAY_START && index <= INDEX_SATURDAY_END){
		if(dayToday < DAY_SATURDAY)
			correction = 6 - dayToday;
		else
			correction = 13 - dayToday;
	}
	else if(index >= INDEX_SUNDAY_START && index <= INDEX_SUNDAY_END)
		correction = 7 - dayToday;
	getWordDate(correction, year, month, day);
}

void Converter::declareDate(vector<string>& dateVector, int& year, int& month, int& day){
	day = convertStringToInt(dateVector[SLOT_DAY]);
	month = convertStringToInt(dateVector[SLOT_MONTH]);
	year = convertStringToInt(dateVector[SLOT_YEAR]);
}

void Converter::extractTime(string timeStr, int& hour, int& min){
	vector<string> timeVector;
	bool isAM;
	bool isPM;
	bool is24HR;
	int stringLength = timeStr.size();
	string timeAMPM = timeStr.substr(stringLength - TIME_SPECIFIER_LENGTH);
	toLowerCase(timeAMPM);
	isAM = (timeAMPM == TIME_ANTE_MERIDIAN);
	isPM = (timeAMPM == TIME_POST_MERIDIAN);
	is24HR = (!isAM && !isPM);
	if(is24HR){
		hour = convertStringToInt(timeStr.substr(0,2));
		min = convertStringToInt(timeStr.substr(2,2));
	}
	else if(stringLength == 3){ //e.g. 8pm
		hour = convertStringToInt(timeStr.substr(0,1));
		min = 0;
	}
	else if(stringLength == 4){ //e.g. 11am
		hour = convertStringToInt(timeStr.substr(0,2));
		min = 0;
	}
	else{ //e.g. 11:31pm OR 11.31pm
		splitString(timeStr, TIME_DELIMITER, timeVector);
		hour = convertStringToInt(timeVector[SLOT_HOUR]);
		min = convertStringToInt(timeVector[SLOT_MIN]);
	}
	if(isPM)
		hour = hour + TIME_PM_CORRECTION;
}

time_t Converter::createTime(int year, int month, int day, int hour, int min){
	struct tm  time = {0,0,0,0,0,0};
	time_t returnTime;
	time.tm_year=year - YEAR_CORRECTION;
	time.tm_mon=month - MONTH_CORRECTION;
	time.tm_mday=day;
	time.tm_hour=hour;
	time.tm_min=min;
	returnTime = mktime(&time);
	return returnTime;
}

void Converter::splitString(string str,const string delimiter, vector<string>& strVector){
	string::size_type start = str.find_first_not_of(delimiter, 0);
	string::size_type end = str.find_first_of(delimiter, start);
	while (string::npos != end || string::npos != start){
		strVector.push_back(str.substr(start, end - start));
		start = str.find_first_not_of(delimiter, end);
		end = str.find_first_of(delimiter, start);
	}
}

void Converter::toLowerCase(string &str){
	const int length = str.length();
	for(int i=0; i < length; ++i){
		str[i] = tolower(str[i]);
	}
}

bool Converter::determineFormat(DateTimeType dateTime, string compareStr, int& index, int& dayDigit, int& yearDigit){
	vector<string> dictionary;
	switch (dateTime){
	case Converter::dateEnum:
		dictionary = _dateVector;
		break;
	case Converter::timeEnum:
		dictionary = _timeVector;
		break;
	default:
		break;
	}
	return checkDictionary(dictionary,compareStr, index, dayDigit, yearDigit);
}

bool Converter::checkDictionary(vector<string> dictionary, string compareStr, int& index, int& dayDigit, int& yearDigit){
	stringstream tempStream(compareStr);
	string tempString;
	while(tempStream>>tempString){
		if(isNumber(tempString))
			checkNumber(tempString, dayDigit, yearDigit);
		else if(checkWord(dictionary, tempString, index))
			return true;
	}
	return false;
}

bool Converter::checkNumber(string compareStr, int& dayDigit, int& yearDigit){
	if(compareStr.size() == 2){
		dayDigit = convertStringToInt(compareStr);
		return true;
	}
	else if(compareStr.size() == 4){
		yearDigit = convertStringToInt(compareStr);
		return true;
	}
	return false;
}

bool Converter::checkWord(vector<string> dictionary, string compareStr, int& index){
	int vectorSize = dictionary.size();
	for(int i=0; i<vectorSize; i++){
		if(compareStr == dictionary[i]){
			index = i;
			return true;
		}
		else
			continue;
	}
	return false;
}

bool Converter::isNumber(const string& str){
	string::const_iterator it = str.begin();
	while (it != str.end() && isdigit(*it))
		++it;
	return !str.empty() && it == str.end();
}