#include "logic_converter.h"

const int Converter::MONTH_CORRECTION = 1;
const int Converter::YEAR_CORRECTION = 1900;
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
const int Converter::TIME_SPECIFIER_LENGTH = 2;
const int Converter::TIME_PM_CORRECTION = 12;
const string Converter::DATE_DELIMITER_1 = "/";
const string Converter::DATE_DELIMITER_2 = "-";
const string Converter::TIME_DELIMITER_1 = ":";
const string Converter::TIME_DELIMITER_2 = ".";
const string Converter::TIME_ANTE_MERIDIAN = "am";
const string Converter::TIME_POST_MERIDIAN = "pm";

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
	vector<string> dateVector;
	if(dateStr.find(DATE_DELIMITER_1) != string::npos){
		splitString(dateStr, DATE_DELIMITER_1, dateVector);
	}
	else if(dateStr.find(DATE_DELIMITER_2) != string::npos){
		splitString(dateStr, DATE_DELIMITER_2, dateVector);
	}
	day = convertStringToInt(dateVector[SLOT_DAY]);
	month = convertStringToInt(dateVector[SLOT_MONTH]);
	year = convertStringToInt(dateVector[SLOT_YEAR]);
	if(year < YEAR_21_CENTURY)
		year = year + YEAR_21_CENTURY;
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
		if(timeStr.find(TIME_DELIMITER_1) != string::npos)
			splitString(timeStr, TIME_DELIMITER_1, timeVector);
		else if(timeStr.find(TIME_DELIMITER_2) != string::npos)
			splitString(timeStr, TIME_DELIMITER_2, timeVector);
		hour = convertStringToInt(timeVector[SLOT_HOUR]);
		min = convertStringToInt(timeVector[SLOT_MIN]);
	}
	if(isPM)
		hour = hour + TIME_PM_CORRECTION;
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

void Converter::splitString(string str,const string delimiter, vector<string>& strVector){
	string::size_type lastPos = str.find_first_not_of(delimiter, 0);
	string::size_type pos = str.find_first_of(delimiter, lastPos);
	while (string::npos != pos || string::npos != lastPos){
		strVector.push_back(str.substr(lastPos, pos - lastPos));
		lastPos = str.find_first_not_of(delimiter, pos);
		pos = str.find_first_of(delimiter, lastPos);
	}
}

void Converter::toLowerCase(string &str){
	const int length = str.length();
	for(int i=0; i < length; ++i){
		str[i] = tolower(str[i]);
	}
}