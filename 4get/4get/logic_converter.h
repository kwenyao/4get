#ifndef _LOGIC_CONVERTER_H_
#define _LOGIC_CONVERTER_H_
#include "logic_task.h"
#include "common_message.h"
#include <sstream>
#include <algorithm>

using namespace std;
using namespace Enum;
using namespace Constants;

class Converter
{
public:
	Converter();
	int convertStringToInt(string);
	tm* convertStringToTm(string);
	Status convertStringToStatus(string);
	RepeatType convertStringToRepeatType(string);
	Priority convertStringToPriority(string);
	bool isEqual(string str1, const string str2);
};
#endif