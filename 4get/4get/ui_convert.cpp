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

bool UiConvert::stringStdToSysConversion(String^ result, string& source){
	result = marshal_as<String^>(source);
	return true;
}

bool UiConvert::intToSysStringConversion(System::String^ result, int& source){
	source = Convert::ToInt32(result);
	return true;
}

void UiConvert::printItem(System::Windows::Forms::ListViewItem^ item, list<Task> *list)
{
	//Task t1 = list->front();
	//convert to system string
	//System::String^ sys_index = System::Convert::ToString(t1.getTaskId()); //index
	//System::String^ sys_desc = gcnew System::String(t1.getTaskDescription().c_str()); //description
	//System::String^ sys_venue = gcnew System::String(t1.getTaskLocation().c_str()); //venue
	System::String^ sys_index = "1";
	System::String^ sys_desc = "description";
	System::String^ sys_venue = "location";
	System::String^ sys_time = "1200"; //time
	System::String^ sys_due = "05-10-2013"; //due
	System::String^ sys_priority = "high"; //priority

	//list->pop_front();

	item->BeginEdit();

	//item->SubItems[0]->Text = sys_index;

	//creating item for listview
	item->SubItems->Add(sys_index);
	item->SubItems->Add(sys_desc); //add description
	item->SubItems->Add(sys_venue); //add venue	 
	item->SubItems->Add(sys_time); //add time
	item->SubItems->Add(sys_due); //add due
	item->SubItems->Add(sys_priority); //add priority
}