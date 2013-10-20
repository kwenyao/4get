#include "ui_convert.h"
#include "logic_task.h"
#include "msclr\marshal_cppstd.h"

using namespace System;
using namespace msclr::interop;

UiConvert::UiConvert(){};

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


void UiConvert::printItem(System::Windows::Forms::ListViewItem^ item, list<Task*> *list, int taskIndex)
{
	Task* t1 = list->front();
	char timeBuffer[32] = "";
	/****stub start*****/
	/*time_t rawTime;
	time(&rawTime);
	tm *testTime = localtime(&rawTime);*/
	/*****stub end*****/

	System::String^ sys_index = System::Convert::ToString(taskIndex); //index
	System::String^ sys_desc = gcnew System::String(t1->getTaskDescription().c_str()); //description
	System::String^ sys_venue = gcnew System::String(t1->getTaskLocation().c_str()); //venue

	//if(t1.getTaskStart() != NULL){
	//	asctime_s(timeBuffer, 32, testTime);
	//	sys_time = gcnew System::String(timeBuffer); //start time
	//}
	//if(t1.getTaskEnd() != NULL){
	//	asctime_s(timeBuffer, 32, testTime);
	//	sys_due = gcnew System::String(timeBuffer); //due
	//}

	//for when time becomes time_t
	time_t timeAsTimeT;
	tm*  timeAsTm=NULL;
	System::String^ sys_time = "";
	System::String^ sys_due = "";

	timeAsTimeT = t1->getTaskStart();
	if(timeAsTimeT != 0){
		timeAsTm = localtime(&timeAsTimeT);
		asctime_s(timeBuffer, 32, timeAsTm);
		sys_time = gcnew System::String(timeBuffer);
	}

	timeAsTm = NULL;
	timeAsTimeT = t1->getTaskEnd();
	if(timeAsTimeT != 0){
		timeAsTm = localtime(&timeAsTimeT);
		asctime_s(timeBuffer, 32, timeAsTm);
		sys_due = gcnew System::String(timeBuffer);
	}
	/*System::String^ sys_time = gcnew System::String(timetToStdString(t1.getTaskStart()).c_str());
	System::String^ sys_due = gcnew System::String(timetToStdString(t1.getTaskEnd()).c_str());*/

	System::String^ sys_priority = gcnew System::String(enumPriorityToStdString(t1->getTaskPriority()).c_str()); //priority

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