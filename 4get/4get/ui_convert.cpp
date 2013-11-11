#include "ui_convert.h"

using namespace UIConvert;

const int UiConvert::ITEM_INDEX_SLOT = 0;
const time_t UiConvert::EMPTY_TIME = 0;
const int UiConvert::INITIALISE_INT_ZERO = 0;
const int UiConvert::TIME_BUFFER_SIZE = 32;
const string UiConvert::INITIALISE_EMPTY_STD_STRING = "";
const string UiConvert::HIGH_PRIORITY_TEXT = "High";
const string UiConvert::NORMAL_PRIORITY_TEXT = "Normal";
const string UiConvert::DAILY_REPEAT_TEXT = "Daily";
const string UiConvert::WEEKLY_REPEAT_TEXT = "Weekly";
const string UiConvert::FORTNIGHTLY_REPEAT_TEXT = "Fortnightly";
const string UiConvert::MONTHLY_REPEAT_TEXT = "Monthly";
const string UiConvert::ANNUALLY_REPEAT_TEXT = "Annually";
const string UiConvert::NONE_REPEAT_TEXT = "None";
const string UiConvert::FLOATING_TYPE_TEXT = "Floating Task";
const string UiConvert::DEADLINE_TYPE_TEXT = "Deadline Task";
const string UiConvert::TIMED_TYPE_TEXT = "Timed Task";

UiConvert::UiConvert(){};

void UiConvert::stringStdToSysConversion(String^& result, string& source){
	result = gcnew String(source.c_str());
}
bool UiConvert::timetToSysString(time_t timeAsTimeT, System::String^& sys_time){
	struct tm timeTm;
	char timeBuffer[TIME_BUFFER_SIZE] = {0};
	string timeString = INITIALISE_EMPTY_STD_STRING;

	if(timeAsTimeT != EMPTY_TIME){
		localtime_s(&timeTm,&timeAsTimeT);
		asctime_s(timeBuffer, TIME_BUFFER_SIZE, &timeTm);
		timeString = timeBuffer;
		this->stringStdToSysConversion(sys_time, timeString);
		return true;
	}
	else
		return false;
}
bool UiConvert::stringSysToStdConversion(String^ source, string& result){
	result = marshal_as<string>(source);
	return true;
}
string UiConvert::enumPriorityToStdString(Priority taskPriority){
	string result = INITIALISE_EMPTY_STD_STRING;
	switch(taskPriority){
	case high:
		result = HIGH_PRIORITY_TEXT;
		break;
	default:
		result = NORMAL_PRIORITY_TEXT;
		break;
	}
	return result;
}
string UiConvert::enumRepeatToStdString(RepeatType taskRepeat){
	string result = INITIALISE_EMPTY_STD_STRING;
	switch(taskRepeat){
	case daily:
		result = DAILY_REPEAT_TEXT;
		break;
	case weekly:
		result = WEEKLY_REPEAT_TEXT;
		break;
	case fortnightly:
		result = FORTNIGHTLY_REPEAT_TEXT;
		break;
	case monthly:
		result = MONTHLY_REPEAT_TEXT;
		break;
	case annually:
		result = ANNUALLY_REPEAT_TEXT;
		break;
	default:
		result = NONE_REPEAT_TEXT;
		break;
	}
	return result;
}
string UiConvert::enumTaskTypeToStdString(TaskType taskType){
	string result = INITIALISE_EMPTY_STD_STRING;
	switch(taskType){
	case floating:
		result = FLOATING_TYPE_TEXT;
		break;
	case deadline:
		result = DEADLINE_TYPE_TEXT;
		break;
	case timed:
		result = TIMED_TYPE_TEXT;
		break;
	}
	return result;
}
int UiConvert::stringSysToIntConversion(String^ source){
	int result = INITIALISE_INT_ZERO;
	result = int::Parse(source);
	return result;
}
void UiConvert::intToSysString(String^& result, int source){
	result = System::Convert::ToString(source);
}

void UiConvert::printItem(System::Windows::Forms::ListViewItem^ item, list<Task*> *list, int taskIndex)
{
	if(list->empty())
		return;
	Task* t1 = list->front();
	System::String^ sys_index;
	System::String^ sys_desc;
	System::String^ sys_venue;
	System::String^ sys_start_time;
	System::String^ sys_end_time;
	System::String^ sys_repeat;
	System::String^ sys_priority;
	System::String^ sys_task_type;
	char timeBuffer[TIME_BUFFER_SIZE] = {0};
	string timeString = INITIALISE_EMPTY_STD_STRING;

	this->intToSysString(sys_index, taskIndex); //index
	this->stringStdToSysConversion(sys_desc, t1->getTaskDescription()); //description
	this->stringStdToSysConversion(sys_venue, t1->getTaskLocation()); //venue

	this->timetToSysString(t1->getTaskStart(), sys_start_time);
	this->timetToSysString(t1->getTaskStart(), sys_end_time);

	this->stringStdToSysConversion(sys_repeat, enumRepeatToStdString(t1->getTaskRepeat())); //repeat

	this->stringStdToSysConversion(sys_priority, enumPriorityToStdString(t1->getTaskPriority())); //priority

	this->stringStdToSysConversion(sys_task_type, enumTaskTypeToStdString(t1->getTaskType())); //task type

	list->pop_front();

	item->BeginEdit();
	item->SubItems[ITEM_INDEX_SLOT]->Text = sys_index;
	item->SubItems->Add(sys_desc); //add description
	item->SubItems->Add(sys_start_time); //add time
	item->SubItems->Add(sys_end_time); //add due
	item->SubItems->Add(sys_venue); //add venue
	item->SubItems->Add(sys_repeat); //add repeat
	item->SubItems->Add(sys_priority); //add priority
	item->SubItems->Add(sys_task_type); //add task type
}