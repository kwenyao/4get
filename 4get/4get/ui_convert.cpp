#include "ui_convert.h"
#include "logic_task.h"
#include "msclr\marshal_cppstd.h"

using namespace System;
using namespace msclr::interop;

UiConvert::UiConvert(){};

bool UiConvert::stringSysToStdConversion(String^ source, string& result){
	result = marshal_as<string>(source);
	return true;
}

string UiConvert::enumPriorityToStdString(Priority taskPriority){
	string result ="";
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


void UiConvert::printItem(System::Windows::Forms::ListViewItem^ item, list<Task> *list, int taskIndex)
{
	Task t1 = list->front();
	char timeBuffer[32] = "";
	//convert to system string
	System::String^ sys_index = System::Convert::ToString(taskIndex); //index
	System::String^ sys_desc = gcnew System::String(t1.getTaskDescription().c_str()); //description
	System::String^ sys_venue = gcnew System::String(t1.getTaskLocation().c_str()); //venue
	/****stub start*****/
	time_t rawTime;
	time(&rawTime);
	tm *testTime = localtime(&rawTime);
	/*****stub end*****/
	System::String^ sys_time;
	if(asctime_s(timeBuffer, 32, testTime)==0){
		sys_time = gcnew System::String(timeBuffer); //start time
	}
	System::String^ sys_due;
	if(asctime_s(timeBuffer, 32, testTime)==0){
		sys_due = gcnew System::String(timeBuffer); //due
	}
	System::String^ sys_priority = gcnew System::String(enumPriorityToStdString(t1.getTaskPriority()).c_str()); //priority

	list->pop_front();

	item->BeginEdit();

	item->SubItems[0]->Text = sys_index;

	//creating item for listview
	item->SubItems->Add(sys_desc); //add description
	item->SubItems->Add(sys_venue); //add venue	 
	item->SubItems->Add(sys_time); //add time
	item->SubItems->Add(sys_due); //add due
	item->SubItems->Add(sys_priority); //add priority
}