/*
 * =====================================================================================
 *
 *       Filename:  logic_converter.cpp
 *
 *         Author:  KOH WEN YAO (A0097210M), kwenyao@nus.edu.sg
 *   Organization:  NUS, School of Computing
 *
 * =====================================================================================
 */

#include "logic_converter.h"

const string Converter::REPEAT_DAILY = "daily";
const string Converter::REPEAT_WEEKLY = "weekly";
const string Converter::REPEAT_FORGHTNIGHTLY = "fortnightly";
const string Converter::REPEAT_MONTHLY = "monthly";
const string Converter::REPEAT_ANNUALLY = "annually";
const string Converter::REPEAT_YEARLY = "yearly";
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

const int Converter::DATE_DICTIONARY_SIZE = 22;
const int Converter::INDEX_TMR = 0;
const int Converter::INDEX_MON = 1;
const int Converter::INDEX_TUE = 2;
const int Converter::INDEX_WED = 3;
const int Converter::INDEX_THU = 4;
const int Converter::INDEX_FRI = 5;
const int Converter::INDEX_SAT = 6;
const int Converter::INDEX_SUN = 7;
const int Converter::INDEX_TDY = 8;

const int Converter::INDEX_JAN = 9;
const int Converter::INDEX_FEB = 10;
const int Converter::INDEX_MAR = 11;
const int Converter::INDEX_APR = 12;
const int Converter::INDEX_MAY = 13;
const int Converter::INDEX_JUN = 14;
const int Converter::INDEX_JUL = 15;
const int Converter::INDEX_AUG = 16;
const int Converter::INDEX_SEP = 17;
const int Converter::INDEX_OCT = 18;
const int Converter::INDEX_NOV = 19;
const int Converter::INDEX_DEC = 20;
const int Converter::INDEX_NXT = 21;

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
const int Converter::DATE_NEXT_CORRECTION = 7;
const int Converter::YEAR_INT_MULTIPLIER = 10000;
const int Converter::MONTH_INT_MULTIPLIER = 100;
const int Converter::DAY_INT_MULTIPLIER = 1;
const string Converter::DATE_DELIMITER = "/-";
const string Converter::TIME_DELIMITER = ":.";

Converter::Converter(){
	_dateDictionary.resize(DATE_DICTIONARY_SIZE);
	initialiseDateDictionary();
	initialiseTimeVector();
}

void Converter::initialiseDateDictionary(){
	_dateDictionary[INDEX_TMR].push_back(TIMER_TOMORROW);
	_dateDictionary[INDEX_TMR].push_back(TIMER_TML);
	_dateDictionary[INDEX_TMR].push_back(TIMER_TMR);
	_dateDictionary[INDEX_TMR].push_back(TIMER_TMRW);

	_dateDictionary[INDEX_MON].push_back(TIMER_MONDAY);
	_dateDictionary[INDEX_MON].push_back(TIMER_MON);

	_dateDictionary[INDEX_TUE].push_back(TIMER_TUESDAY);
	_dateDictionary[INDEX_TUE].push_back(TIMER_TUES);
	_dateDictionary[INDEX_TUE].push_back(TIMER_TUE);

	_dateDictionary[INDEX_WED].push_back(TIMER_WEDNESDAY);
	_dateDictionary[INDEX_WED].push_back(TIMER_WED);

	_dateDictionary[INDEX_THU].push_back(TIMER_THURSDAY);
	_dateDictionary[INDEX_THU].push_back(TIMER_THUR);
	_dateDictionary[INDEX_THU].push_back(TIMER_THURS);
	_dateDictionary[INDEX_THU].push_back(TIMER_THU);

	_dateDictionary[INDEX_FRI].push_back(TIMER_FRIDAY);
	_dateDictionary[INDEX_FRI].push_back(TIMER_FRI);

	_dateDictionary[INDEX_SAT].push_back(TIMER_SATURDAY);
	_dateDictionary[INDEX_SAT].push_back(TIMER_SAT);

	_dateDictionary[INDEX_SUN].push_back(TIMER_SUNDAY);
	_dateDictionary[INDEX_SUN].push_back(TIMER_SUN);

	_dateDictionary[INDEX_JAN].push_back(MONTH_JANUARY);
	_dateDictionary[INDEX_JAN].push_back(MONTH_JAN);

	_dateDictionary[INDEX_FEB].push_back(MONTH_FEBRUARY);
	_dateDictionary[INDEX_FEB].push_back(MONTH_FEB);

	_dateDictionary[INDEX_MAR].push_back(MONTH_MARCH);
	_dateDictionary[INDEX_MAR].push_back(MONTH_MAR);

	_dateDictionary[INDEX_APR].push_back(MONTH_APRIL);
	_dateDictionary[INDEX_APR].push_back(MONTH_APR);

	_dateDictionary[INDEX_MAY].push_back(MONTH_MAY);

	_dateDictionary[INDEX_JUN].push_back(MONTH_JUNE);
	_dateDictionary[INDEX_JUN].push_back(MONTH_JUN);

	_dateDictionary[INDEX_JUL].push_back(MONTH_JULY);
	_dateDictionary[INDEX_JUL].push_back(MONTH_JUL);

	_dateDictionary[INDEX_AUG].push_back(MONTH_AUGUST);
	_dateDictionary[INDEX_AUG].push_back(MONTH_AUG);

	_dateDictionary[INDEX_SEP].push_back(MONTH_SEPTEMBER);
	_dateDictionary[INDEX_SEP].push_back(MONTH_SEPT);
	_dateDictionary[INDEX_SEP].push_back(MONTH_SEP);

	_dateDictionary[INDEX_OCT].push_back(MONTH_OCTOBER);
	_dateDictionary[INDEX_OCT].push_back(MONTH_OCT);

	_dateDictionary[INDEX_NOV].push_back(MONTH_NOVEMBER);
	_dateDictionary[INDEX_NOV].push_back(MONTH_NOV);

	_dateDictionary[INDEX_DEC].push_back(MONTH_DECEMBER);
	_dateDictionary[INDEX_DEC].push_back(MONTH_DEC);

	_dateDictionary[INDEX_TDY].push_back(TIMER_TODAY);
	_dateDictionary[INDEX_NXT].push_back(TIMER_NEXT);
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
	else if(isEqual(str, REPEAT_ANNUALLY)||isEqual(str, REPEAT_YEARLY))
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

time_t Converter::convertStringToTime(string dateStr, string timeStr, bool isStart){
	int year  = 0;
	int month = 0;
	int day   = 0;
	int hour  = 0;
	int min   = 0;
	time_t returnTime = 0;
	bool isNoDate = dateStr.empty();
	bool isNoTime = timeStr.empty();
	if(isNoDate && isNoTime)
		return returnTime;
	try{
		if(!isNoDate)
			extractDate(dateStr, year, month, day);
		else
			getTodayDate(year, month, day);
		if(!isNoTime)
			extractTime(timeStr, hour, min);
		else
			if(isStart)
				getDefaultStartTime(hour, min);
			else
				getDefaultEndTime(hour, min);
		returnTime = createTime(year, month, day, hour, min);
		return returnTime;
	} catch (string errString) {
		throw;
	}
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
	try{
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
	} catch (string errString) {
		throw;
	}
}

void Converter::getDate(bool isNoDate, int& year, int& month, int& day, string dateStr){
	try{
		if(isNoDate)
			getTodayDate(year, month, day);
		else
			extractDate(dateStr, year, month, day);
	} catch (string errString) {
		throw;
	}
}

void Converter::getEndTime(bool isNoEndTime, int& hour, int& min, string endTime){
	try{
		if(isNoEndTime)
			getDefaultEndTime(hour, min);
		else
			extractTime(endTime, hour, min);
	} catch (string errString) {
		throw;
	}
}

void Converter::getStartTime(bool isNoStartTime, int& hour, int& min, string startTime){
	try{
		if(isNoStartTime)
			getDefaultStartTime(hour, min);
		else
			extractTime(startTime, hour, min);
	} catch (string errString) {
		throw;
	}
}

void Converter::getTodayDate(int& year, int& month, int& day){
	time_t temp;
	struct tm currentTime;
	time(&temp);
	localtime_s(&currentTime,&temp);
	day   = currentTime.tm_mday;
	month = currentTime.tm_mon + MONTH_CORRECTION;
	year  = currentTime.tm_year + YEAR_CORRECTION;
}

void Converter::getWordDate(int correction, int& year, int& month, int& day){
	time_t temp;
	struct tm currentTime;
	time(&temp);
	localtime_s(&currentTime,&temp);
	day   = currentTime.tm_mday + correction;
	month = currentTime.tm_mon + MONTH_CORRECTION;
	year  = currentTime.tm_year + YEAR_CORRECTION;
	if(_isNext)
		day = day + DATE_NEXT_CORRECTION;
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

time_t Converter::getNow(){
	time_t returnTime;
	time(&returnTime);
	return returnTime;
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
	_dayDigit = 0;
	_yearDigit = 0;
	_matchedIndex = -1;
	_isNext = false;
	bool isWordFormat = determineFormat(dateEnum, dateStr);
	try{
		if(isWordFormat)
			determineDate(year, month, day);
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

void Converter::determineDate(int& year, int& month, int& day){
	assert(_matchedIndex > -1);
	try{
		if(_matchedIndex < INDEX_JAN)
			dayCorrection(year, month, day);
		else if(_matchedIndex > INDEX_SUN && _matchedIndex < INDEX_NXT)
			monthCorrection(year, month, day);
		else
			throw string(Message::MESSAGE_ERROR_WRONG_DATE);
	} catch(string errStr) {
		throw;
	}
}

void Converter::monthCorrection(int& year, int& month, int& day){
	if(_matchedIndex == INDEX_JAN)
		month = MONTH_NUMBER_JAN;
	else if(_matchedIndex == INDEX_FEB)
		month = MONTH_NUMBER_FEB;
	else if(_matchedIndex == INDEX_MAR)
		month = MONTH_NUMBER_MAR;
	else if(_matchedIndex == INDEX_APR)
		month = MONTH_NUMBER_APR;
	else if(_matchedIndex == INDEX_MAY)
		month = MONTH_NUMBER_MAY;
	else if(_matchedIndex == INDEX_JUN)
		month = MONTH_NUMBER_JUN;
	else if(_matchedIndex == INDEX_JUL)
		month = MONTH_NUMBER_JUL;
	else if(_matchedIndex == INDEX_AUG)
		month = MONTH_NUMBER_AUG;
	else if(_matchedIndex == INDEX_SEP)
		month = MONTH_NUMBER_SEP;
	else if(_matchedIndex == INDEX_OCT)
		month = MONTH_NUMBER_OCT;
	else if(_matchedIndex == INDEX_NOV)
		month = MONTH_NUMBER_NOV;
	else if(_matchedIndex == INDEX_DEC)
		month = MONTH_NUMBER_DEC;

	if(_dayDigit < 1)
		throw string(Message::MESSAGE_ERROR_MISSING_DAY);
	else
		day = _dayDigit;

	if(_yearDigit != 0)
		year = _yearDigit;
	else
		year = getToday(yearEnum);
}

void Converter::dayCorrection(int& year, int& month, int& day){
	int dayToday = getToday(weekDayEnum);
	int correction;
	if(_matchedIndex == INDEX_TMR)
		correction = 1;
	else if(_matchedIndex == INDEX_MON){
		if(dayToday == DAY_SUNDAY)
			correction = 1;
		else
			correction = 8 - dayToday;
	}
	else if(_matchedIndex == INDEX_TUE){
		if(dayToday < DAY_TUESDAY)
			correction = 2 - dayToday;
		else
			correction = 9 - dayToday;
	}
	else if(_matchedIndex == INDEX_WED){
		if(dayToday < DAY_WEDNESDAY)
			correction = 3 - dayToday;
		else
			correction = 10 - dayToday;
	}
	else if(_matchedIndex == INDEX_THU){
		if(dayToday < DAY_THURSDAY)
			correction = 4 - dayToday;
		else
			correction = 11 - dayToday;
	}
	else if(_matchedIndex == INDEX_FRI){
		if(dayToday < DAY_FRIDAY)
			correction = 5 - dayToday;
		else
			correction = 12 - dayToday;
	}
	else if(_matchedIndex == INDEX_SAT){
		if(dayToday < DAY_SATURDAY)
			correction = 6 - dayToday;
		else
			correction = 13 - dayToday;
	}
	else if(_matchedIndex == INDEX_SUN)
		correction = 7 - dayToday;
	else if(_matchedIndex == INDEX_TDY)
		correction = 0;
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
	if(is24HR){ //e.g. 1420HR
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
	time.tm_year = year - YEAR_CORRECTION;
	time.tm_mon  = month - MONTH_CORRECTION;
	time.tm_mday = day;
	time.tm_hour = hour;
	time.tm_min  = min;
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

bool Converter::determineFormat(DateTimeType dateTime, string compareStr){
	vector<vector<string>> dictionary;
	switch (dateTime){
	case Converter::dateEnum:
		dictionary = _dateDictionary;
		break;
	case Converter::timeEnum:
		dictionary = _timeDictionary;
		break;
	default:
		break;
	}
	return checkDictionary(dictionary,compareStr);
}

bool Converter::checkDictionary(vector<vector<string>> dictionary, string compareStr){
	stringstream tempStream(compareStr);
	string tempString;
	bool isWord = false;
	while(tempStream>>tempString){
		if(isNumber(tempString))
			checkNumber(tempString);
		else if(checkWord(dictionary, tempString))
			isWord = true;
	}
	return isWord;
}

bool Converter::checkNumber(string compareStr){
	assert(!compareStr.empty());
	if(compareStr.size() < 3){
		_dayDigit = convertStringToInt(compareStr);
		return true;
	}
	else if(compareStr.size() == 4){
		_yearDigit = convertStringToInt(compareStr);
		return true;
	}
	return false;
}

bool Converter::checkWord(vector<vector<string>> dictionary, string compareStr){
	int vectorSize = dictionary.size();
	for(int i=0; i<vectorSize; i++){
		if(isKeyWord(dictionary[i], compareStr)){
			saveIndex(i);
			return true;
		}
		else
			continue;
	}
	return false;
}

bool Converter::isKeyWord(vector<string> keyWordVector, string compareStr){
	int vectorSize = keyWordVector.size();
	for(int i=0; i<vectorSize; i++){
		if(compareStr == keyWordVector[i])
			return true;
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

void Converter::saveIndex(int index){
	if(index == INDEX_NXT)
		_isNext = true;
	else
		_matchedIndex = index;
}