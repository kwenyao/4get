#include "ui_convert.h"

using namespace UIConvert;

const int UiConvert::ITEM_INDEX_SLOT = 0;
const time_t UiConvert::EMPTY_TIME = 0;
const int UiConvert::INITIALISE_INT_ZERO = 0;
const int UiConvert::TIME_BUFFER_SIZE = 32;
const string UiConvert::INITIALISE_EMPTY_STD_STRING = "";
const string UiConvert::HIGH_PRIORITY_TEXT = "high";
const string UiConvert::NORMAL_PRIORITY_TEXT = "normal";

UiConvert::UiConvert(){};

void UiConvert::stringStdToSysConversion(String^& result, string& source){
	result = gcnew String(source.c_str());
}
string UiConvert::timetToStdString(time_t time){
	stringstream timeStream;
	timeStream << time;
	return timeStream.str();
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
	System::String^ sys_priority;
	time_t timeAsTimeT;
	struct tm timeTm;
	char timeBuffer[TIME_BUFFER_SIZE] = {0};
	string timeString = INITIALISE_EMPTY_STD_STRING;

	this->intToSysString(sys_index, taskIndex); //index
	this->stringStdToSysConversion(sys_desc, t1->getTaskDescription()); //description
	this->stringStdToSysConversion(sys_venue, t1->getTaskLocation()); //venue

	timeAsTimeT = t1->getTaskStart();
	if(timeAsTimeT != EMPTY_TIME){
		localtime_s(&timeTm,&timeAsTimeT);
		asctime_s(timeBuffer, TIME_BUFFER_SIZE, &timeTm);
		timeString = timeBuffer;
		this->stringStdToSysConversion(sys_start_time, timeString); //start time
	}

	timeAsTimeT = t1->getTaskEnd();
	if(timeAsTimeT != EMPTY_TIME){
		localtime_s(&timeTm,&timeAsTimeT);
		asctime_s(timeBuffer, TIME_BUFFER_SIZE, &timeTm);
		timeString = timeBuffer;
		this->stringStdToSysConversion(sys_end_time, timeString); //end time
	}

	this->stringStdToSysConversion(sys_priority, enumPriorityToStdString(t1->getTaskPriority())); //priority

	list->pop_front();

	item->BeginEdit();
	item->SubItems[ITEM_INDEX_SLOT]->Text = sys_index;
	item->SubItems->Add(sys_desc); //add description
	item->SubItems->Add(sys_start_time); //add time
	item->SubItems->Add(sys_end_time); //add due
	item->SubItems->Add(sys_venue); //add venue	 
	item->SubItems->Add(sys_priority); //add priority
}