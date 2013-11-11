#pragma once
#ifndef UI_CONVERT_H
#define UI_CONVERT_H

#include <list>
#include <string>
#include <time.h>
#include <sstream>
#include "logic_task.h"
#include "common_message.h"
#include <vcclr.h>
#include "msclr\marshal_cppstd.h"

#define BUFFER_SIZE 255
namespace UIConvert {
	using namespace std;
	using namespace System;
	using namespace msclr::interop;

	class UiConvert
	{
	public:
		UiConvert();

		static char systemMessage[BUFFER_SIZE];
		static const bool isPrintSystemMessage = false;

	public:
		void stringStdToSysConversion(System::String^& result, string& source);
		string timetToStdString(time_t time);
		bool stringSysToStdConversion(System::String^ source, string& result);
		string enumPriorityToStdString(Priority priority);
		string enumRepeatToStdString(RepeatType repeat);
		string enumTaskTypeToStdString(TaskType taskType);
		int stringSysToIntConversion(System::String^ source);
		void intToSysString(System::String^& result, int source);
		void printItem(System::Windows::Forms::ListViewItem^ item, std::list<Task*> *list, int taskIndex);

	private:
		static const int ITEM_INDEX_SLOT;
		static const int TIME_BUFFER_SIZE;
		static const int INITIALISE_INT_ZERO;
		static const string INITIALISE_EMPTY_STD_STRING;
		static const string HIGH_PRIORITY_TEXT;
		static const string NORMAL_PRIORITY_TEXT;
		static const time_t EMPTY_TIME;
		static const string DAILY_REPEAT_TEXT;
		static const string WEEKLY_REPEAT_TEXT;
		static const string FORTNIGHTLY_REPEAT_TEXT;
		static const string MONTHLY_REPEAT_TEXT;
		static const string ANNUALLY_REPEAT_TEXT;
		static const string NONE_REPEAT_TEXT;
		static const string FLOATING_TYPE_TEXT;
		static const string DEADLINE_TYPE_TEXT;
		static const string TIMED_TYPE_TEXT;

	};
}
#endif