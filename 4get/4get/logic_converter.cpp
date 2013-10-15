#include "logic_converter.h"

const int Converter::MONTH_CORRECTION = 1;
const int Converter::YEAR_CORRECTION = 1900;
const int Converter::DEFAULT_END_HOUR = 23;
const int Converter::DEFAULT_END_MIN = 59;
const int Converter::DEFAULT_START_HOUR = 0;
const int Converter::DEFAULT_START_MIN = 0;
const int Converter::YEAR_21_CENTURY = 2000;

Converter::Converter(){}

int Converter::convertStringToInt(string str)
{
	int strInt;
	stringstream stringer(str);
	stringer >> strInt;
	return strInt;
}

Status Converter::convertStringToStatus(string str)
{
	transform(str.begin(), str.end(), str.begin(), ::tolower);
	if(isEqual(str, "completed"))
		return completed;
	else if(isEqual(str, "incomplete"))
		return incomplete;
	else if(isEqual(str, "overdued"))
		return overdued;
	else 
		return statusNone;
}
RepeatType Converter::convertStringToRepeatType(string str)
{
	transform(str.begin(), str.end(), str.begin(), ::tolower);
	if(isEqual(str, "daily"))
		return daily;
	else if(isEqual(str, "weekly"))
		return weekly;
	else if(isEqual(str, "fortnightly"))
		return fortnightly;
	else if(isEqual(str, "monthly"))
		return monthly;
	else if(isEqual(str, "annually"))
		return annually;
	else
		return repeatNone;
}
Priority Converter::convertStringToPriority(string str)
{
	if(isEqual(str, "!"))
		return high;
	else
		return normal;
}
tm* Converter::convertStringToTm(string str)  //this function work for dates that are eg. 02/02/13
{
	tm* Time;
	Time = new tm;
	if(str.empty())
	{
		return Time;
	}
	transform(str.begin(), str.end(), str.begin(), ::tolower);
	if(str[2] == '/')
	{
		char DELIMITER = '/';
		int day, month, year;
		istringstream stm(str);
		stm >> day >> DELIMITER;
		stm >> month >> DELIMITER;
		stm >> year;
		if(year < 100)
		{
			year += 2000;
		}

		Time ->tm_mday = day;
		Time ->tm_mon = month;
		Time ->tm_year = year;

		return Time;
	}
	else if(str[1] == ':'|| str[2] == ':')
	{
		int hour, mins;
		char DELIMITER = ':';
		char DELIMITER_MINS = 'a';
		istringstream stm(str);
		stm >> hour>> DELIMITER;
		stm >> mins >> DELIMITER_MINS;

		Time ->tm_hour = hour;
		Time->tm_min = mins;

		return Time;
	}
}

bool Converter::isEqual(string str1, const string str2)
{
	if(str1 == str2)
		return true;
	return false;
}

TaskType Converter::convertStringToTime(string startDate, string startTime, string endDate, string endTime, time_t& returnStart, time_t& returnEnd){
	int startYear, endYear;
	int startMonth, endMonth;
	int startDay, endDay;
	int startHour, endHour;
	int startMin, endMin;
	bool isNoStartDate = startDate.empty();
	bool isNoStartTime = startTime.empty();
	bool isNoEndDate = endDate.empty();
	bool isNoEndTime = endTime.empty();
	returnStart = 0;
	returnEnd = 0;

	if(isNoStartDate && isNoStartTime && isNoEndDate &&isNoEndTime)
		return floating;
	if(isNoEndDate && isNoEndTime)
		return taskInvalid;

	getEndDate(isNoEndDate, endYear, endMonth, endDay, endDate);
	getEndTime(isNoEndTime, endHour, endMin, endTime);
	returnEnd = createTime(endYear, endMonth, endDay, endHour, endMin);

	if(isNoStartDate && isNoStartTime)
		return deadline;

	getStartDate(isNoStartDate, startYear, startMonth, startDay, startDate);
	getStartTime(isNoStartTime, startHour, startMin, startTime);
	returnStart = createTime(startYear, startMonth, startDay, startHour, startMin);

	if(difftime(returnEnd, returnStart) > 0)
		return timed;
	else
		return taskInvalid;
}

void Converter::extractDate(string dateStr, int& year, int& month, int& day){
	day = convertStringToInt(dateStr.substr(0,2));
	month = convertStringToInt(dateStr.substr(3,2));
	year = convertStringToInt(dateStr.substr(6,2));
	year = year + YEAR_21_CENTURY;
}

void Converter::extractTime(string timeStr, int& hour, int& min){
	hour = convertStringToInt(timeStr.substr(0,2));
	min = convertStringToInt(timeStr.substr(3,2));
}

void Converter::getTodayDate(int& year, int& month, int& day){
	time_t temp;
	tm* currentTime;
	time(&temp);
	currentTime = localtime(&temp);
	day = currentTime->tm_mday;
	month = currentTime->tm_mon + MONTH_CORRECTION;
	year = currentTime->tm_year + YEAR_CORRECTION;
}

void Converter::getDefaultEndTime(int& hour, int& min){
	hour = DEFAULT_END_HOUR;
	min = DEFAULT_END_MIN;
}

void Converter::getDefaultStartTime(int& hour, int& min){
	hour = DEFAULT_START_HOUR;
	min = DEFAULT_START_MIN;
}

time_t Converter::createTime(int year, int month, int day, int hour, int min){
	struct tm  time={0,0,0,0,0,0};
	time.tm_year=year;
	time.tm_mon=month;
	time.tm_mday=day;
	time.tm_hour=hour;
	time.tm_min=min;
	return mktime(&time);
}

void Converter::getEndDate(bool isNoEndDate, int& year, int& month, int& day, string endDate){
	if(isNoEndDate)
		getTodayDate(year, month, day);
	else
		extractDate(endDate, year, month, day);
}

void Converter::getEndTime(bool isNoEndTime, int& hour, int& min, string endTime){
	if(isNoEndTime)
		getDefaultEndTime(hour, min);
	else
		extractTime(endTime, hour, min);
}

void Converter::getStartDate(bool isNoStartDate, int& year, int& month, int& day, string startDate){
	if(isNoStartDate)
		getTodayDate(year, month, day);
	else
		extractDate(startDate, year, month, day);
}

void Converter::getStartTime(bool isNoStartTime, int& hour, int& min, string startTime){
	if(isNoStartTime)
		getDefaultStartTime(hour, min);
	else
		extractTime(startTime, hour, min);
}