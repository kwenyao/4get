#include "logic_converter.h"

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
	else if(str.empty())
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
}
Priority Converter::convertStringToPriority(string str)
{
	if(isEqual(str, "high"))
		return high;
	else
		return normal;
}
tm* Converter::convertStringToTm(string str)
{
	transform(str.begin(), str.end(), str.begin(), ::tolower);
	
}
bool Converter::isEqual(string str1, const string str2)
{
	if(str1 == str2)
		return true;
	return false;
}
