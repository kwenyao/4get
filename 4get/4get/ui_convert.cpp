#include "ui_convert.h"
#include "logic_task.h"
#include "msclr\marshal_cppstd.h"

using namespace System;
using namespace msclr::interop;

UiConvert::UiConvert(){};

void UiConvert::stringStdToSysConversion(String^ result, string& source){
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
	string result = "";
	switch(taskPriority){
	case high:
		result = "high";
		break;
	default:
		result = "normal";
		break;
	}
	return result;
}

int UiConvert::stringSysToIntConversion(System::String^ source){
	int result = 0;
	result = int::Parse(source);
	return result;
}

void UiConvert::printItem(System::Windows::Forms::ListViewItem^ item, list<Task*> *list, int taskIndex)
{
	Task* t1 = list->front();
	char timeBuffer[32] = "";
	string timeString = "";

	System::String^ sys_index = System::Convert::ToString(taskIndex); //index
	System::String^ sys_desc;
	this->stringStdToSysConversion(sys_desc, t1->getTaskDescription()); //description
	System::String^ sys_venue;
	this->stringStdToSysConversion(sys_venue, t1->getTaskLocation()); //venue

	time_t timeAsTimeT;
	tm*  timeAsTm=NULL;
	System::String^ sys_time = "";
	System::String^ sys_due = "";
	timeAsTimeT = t1->getTaskStart();
	if(timeAsTimeT != 0){
		timeAsTm = localtime(&timeAsTimeT);
		asctime_s(timeBuffer, 32, timeAsTm);
		timeString = timeBuffer;
		this->stringStdToSysConversion(sys_time, timeString);
	}

	timeAsTm = NULL;
	timeAsTimeT = t1->getTaskEnd();
	if(timeAsTimeT != 0){
		timeAsTm = localtime(&timeAsTimeT);
		asctime_s(timeBuffer, 32, timeAsTm);
		timeString = timeBuffer;
		this->stringStdToSysConversion(sys_time, timeString);
	}

	System::String^ sys_priority;
	this->stringStdToSysConversion(sys_priority, enumPriorityToStdString(t1->getTaskPriority())); //priority

	list->pop_front();

	item->BeginEdit();
	item->SubItems[ITEM_INDEX_SLOT]->Text = sys_index;
	item->SubItems->Add(sys_desc); //add description
	item->SubItems->Add(sys_time); //add time
	item->SubItems->Add(sys_due); //add due
	item->SubItems->Add(sys_venue); //add venue	 
	item->SubItems->Add(sys_priority); //add priority
}