#include "logic_converter.h"

const string Converter::REPEAT_DAILY = "daily";
const string Converter::REPEAT_WEEKLY = "weekly";
const string Converter::REPEAT_FORGHTNIGHTLY = "fortnightly";
const string Converter::REPEAT_MONTHLY = "monthly";
const string Converter::REPEAT_ANNUALLY = "annually";
const string Converter::PRIORITY_HIGH = "!";

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
const string Converter::DATE_DELIMITER = "/-";
const string Converter::TIME_DELIMITER = ":.";
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
	if(isEqual(str, PRIORITY_HIGH))
		return high;
	else
		return normal;
}

//tm* Converter::convertStringToTm(string str)  //this function work for dates that are eg. 02/02/13
//{
//	tm* Time;
//	Time = new tm;
//	if(str.empty())
//	{
//		return Time;
//	}
//	transform(str.begin(), str.end(), str.begin(), ::tolower);
//	if(str[2] == '/')
//	{
//		char DELIMITER = '/';
//		int day, month, year;
//		istringstream stm(str);
//		stm >> day >> DELIMITER;
//		stm >> month >> DELIMITER;
//		stm >> year;
//		if(year < 100)
//		{
//			year += 2000;
//		}
//
//		Time ->tm_mday = day;
//		Time ->tm_mon = month;
//		Time ->tm_year = year;
//
//		return Time;
//	}
//	else if(str[1] == ':'|| str[2] == ':')
//	{
//		int hour, mins;
//		char DELIMITER = ':';
//		char DELIMITER_MINS = 'a';
//		istringstream stm(str);
//		stm >> hour>> DELIMITER;
//		stm >> mins >> DELIMITER_MINS;
//
//		Time ->tm_hour = hour;
//		Time->tm_min = mins;
//
//		return Time;
//	}
//}

bool Converter::isEqual(string string1, const string string2){
	if(string1 == string2)
		return true;
	return false;
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
	int startYear,  endYear;
	int startMonth, endMonth;
	int startDay,   endDay;
	int startHour,  endHour;
	int startMin,   endMin;
	bool isNoStartDate = startDate.empty();
	bool isNoStartTime = startTime.empty();
	bool isNoEndDate   = endDate.empty();
	bool isNoEndTime   = endTime.empty();
	returnStart = 0;
	returnEnd = 0;

	if(isNoStartDate && isNoStartTime && isNoEndDate &&isNoEndTime)
		return floating;
	if(isNoEndDate && isNoEndTime)
		return taskInvalid;

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
		return taskInvalid;
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
	//currentTime = localtime(&temp);
	day = currentTime.tm_mday;
	month = currentTime.tm_mon + MONTH_CORRECTION;
	year = currentTime.tm_year + YEAR_CORRECTION;
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
	splitString(dateStr, DATE_DELIMITER, dateVector);
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
		splitString(timeStr, TIME_DELIMITER, timeVector);
		hour = convertStringToInt(timeVector[SLOT_HOUR]);
		min = convertStringToInt(timeVector[SLOT_MIN]);
	}
	if(isPM)
		hour = hour + TIME_PM_CORRECTION;
}

time_t Converter::createTime(int year, int month, int day, int hour, int min){
	struct tm  time={0,0,0,0,0,0};
	time_t returnTime;
	time.tm_year=year;
	time.tm_mon=month;
	time.tm_mday=day;
	time.tm_hour=hour;
	time.tm_min=min;
	returnTime = mktime(&time);
	cout << "Converter time_t:" << returnTime;
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