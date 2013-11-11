#pragma once

#include "ui_convert.h"
#include "logic_executor.h"
#include "logic_task.h"
#include "common_message.h"
#include <string>
#include <list>
#include <time.h>
#include <Windows.h>
#include <ctype.h>

namespace UIDisplay {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace UIConvert;

	/// <summary>
	/// Summary for UiDisplay
	/// </summary>
	public ref class UiDisplay : public System::Windows::Forms::Form
	{
	public:
		UiDisplay(void);
	protected:
		~UiDisplay();
#pragma endregion

#pragma region initialise
	private: static const int LEAST_INDEX = 0;
			 static const int EMPTY_LIST_COUNT = 0;
			 static const int ITEM_INDEX_SLOT = 0;
			 static const int MOST_RECENT_SELECTED_ITEM = 0;
			 static const int ITEM_DESCRIPTION_SLOT = 1;
			 static const int ITEM_STARTTIME_SLOT = 2;
			 static const int ITEM_ENDTIME_SLOT = 3;
			 static const int ITEM_LOCATION_SLOT = 4;
			 static const int ITEM_REPEAT_SLOT = 5;
			 static const int ITEM_PRIORITY_SLOT = 6;
			 static const int ITEM_TASKTYPE_SLOT = 7;
			 static const int TAB_INDEX_TODO = 0;
			 static const int TAB_INDEX_COMPLETED = 1;
			 static const int TAB_INDEX_OVERDUE = 2;
			 static const int INPUT_LENGTH_SHOW_HELP_INFO = 3;
			 static const int MAX_EMPTY_TEXTBOX_LENGTH = 1;
			 static const int INITIALISE_INT_ZERO = 0;
			 static const int POSITION_AFTER_FIRST_CHAR = 1;

			 static const bool INITIALISE_BOOLEAN = false;
			 static const ListType INITIALISE_LIST_TYPE = listToDo;

			 static String^ HIGH_PRIORITY_NAME = "High";

			/* static String^ TAG_NAME = "Name: ";
			 static String^ TAG_LOCATION = "Location: ";
			 static String^ TAG_START_TIME = "Start Time: ";
			 static String^ TAG_END_TIME = "End Time: ";
			 static String^ TAG_PRIORITY = "Priority: ";*/
			 static String^ NEWLINE = "\n";

			 static String^ COMMAND_ADD_HELP = "add <task description>";
			 static String^ COMMAND_ADD_HELP_LOCATION = ",at <venue>";
			 static String^ COMMAND_ADD_HELP_START = ",from <start time of timed task>";
			 static String^ COMMAND_ADD_HELP_END = ",to <end time of timed task>";
			 static String^ COMMAND_ADD_HELP_DUE = ",by <due time>";
			 static String^ COMMAND_ADD_HELP_REPEAT = ",repeat <frequency>";
			 static String^ COMMAND_ADD_HELP_PRIORITY = ",!";
			 static String^ COMMAND_ADD_HELP_TIME_DATE = "date: jan, january, feb, feburary, mar, ...";
			 static String^ COMMAND_ADD_HELP_TIME_DAY = "day: today, tomorrow, monday, tuesday, wednesday, ...";
			 static String^ COMMAND_ADD_HELP_TIME_TIME = "time: 1800hr, 6pm, 0900hr, 9am, ...";
			 static String^ COMMAND_ADD_HELP_REMIND_FREQUENCY = "remind frequency: daily, weekly, monthy, yearly";
			 static String^ COMMAND_ADD_FLOATING_EXAMPLE = "E.g. add get newspaper ,at newstand";
			 static String^ COMMAND_ADD_DEADLINE_EXAMPLE = "E.g. add do homework ,by 8 nov 9pm";
			 static String^ COMMAND_ADD_TIMED_EXAMPLE = "E.g. add tuition ,at crown centre ,from saturday 2pm to 4pm ,repeat weekly ,!";

			 static String^ COMMAND_DEL_HELP = "del <task index>";
			 static String^ COMMAND_DEL_HELP_MULTIPLE = "del <start task index> to <end task index>";
			 static String^ COMMAND_DEL_HELP_EXAMPLE = "E.g. del 1";
			 static String^ COMMAND_DEL_HELP_MULTIPLE_EXAMPLE = "E.g. del 1 to 3";

			 static String^ COMMAND_MOD_HELP = "mod <taskindex> <task description>";
			 static String^ COMMAND_MOD_HELP_LOCATION = ",at <venue>";
			 static String^ COMMAND_MOD_HELP_START = ",from <start time of task>";
			 static String^ COMMAND_MOD_HELP_END = ",to <end time of task>";
			 static String^ COMMAND_MOD_HELP_DUE = ",by <due time>";
			 static String^ COMMAND_MOD_HELP_PRIORITY = ",<priority state>";
			 static String^ COMMAND_MOD_HELP_PRIORITY_STATES = "priority states: normal, high";
			 static String^ COMMAND_MOD_HELP_EXAMPLE1 = "changing to a timed task: \n mod 3 ,at grand pacific hotel ,from 9pm to 11pm";
			 static String^ COMMAND_MOD_HELP_EXAMPLE2 = "changing to a deadline task: \n mod 5 project ,by 20 dec ,normal";
			 static String^ COMMAND_MOD_HELP_EXAMPLE3 = "changing to a floating task: \n mod 1 dinner ,by 0 ,at charles' house";

			 static String^ COMMAND_MARK_HELP = "mark <taskindex>";
			 static String^ COMMAND_MARK_HELP_MULTIPLE = "mark <start task index> to <end task index>";
			 static String^ COMMAND_MARK_HELP_EXAMPLE = "E.g. mark 1";
			 static String^ COMMAND_MARK_HELP_MULTIPLE_EXAMPLE = "E.g. mark 1 to 3";

			 static String^ COMMAND_SEARCH_HELP = "search ";
			 static String^ COMMAND_SEARCH_HELP_LOCATION = ",at <venue>";
			 static String^ COMMAND_SEARCH_HELP_START = ",from <start time of task>";
			 static String^ COMMAND_SEARCH_HELP_END = ",to <end time of task>";
			 static String^ COMMAND_SEARCH_HELP_DUE = ",by <due time>";
			 static String^ COMMAND_SEARCH_HELP_PRIORITY = ",<priority state>";
			 static String^ COMMAND_SEARCH_HELP_PRIORITY_STATES = "priority states: normal, high";
			 static String^ COMMAND_SEARCH_HELP_INSTRUCTIONS = "Choose the keywords according to the category you wish to search under.";

			 static String^ MESSAGE_HELP_INSTRUCTIONS = "type in any of the keywords below to get started";
			 static String^ MESSAGE_HELP_ADD = "type \"add\" to add a task";
			 static String^ MESSAGE_HELP_DEL = "type \"del\" to delete a task";
			 static String^ MESSAGE_HELP_MOD = "type \"mod\" to modify a task";
			 static String^ MESSAGE_HELP_MARK = "type \"mark\" to change the status of a task";
			 static String^ MESSAGE_HELP_SEARCH = "type \"search\" to search list";

	private: UiConvert* converter;
			 Executor* execute;
			 list<Task*>* listOfTasks;
			 int selectedItem;
			 bool loaded, up;
			 string *commandKeyword;
			 ListType activeListType;
			 //list tab pages
	private: System::Windows::Forms::TabControl^  tabContainer;
	private: System::Windows::Forms::TabPage^  tabTodo;
	private: System::Windows::Forms::TabPage^  tabCompleted;
	private: System::Windows::Forms::TabPage^  tabOverdue;
	private: System::Windows::Forms::TextBox^  textboxInput;


			 //feedback message box



			 //label that display task details


			 //to do list view
	private: System::Windows::Forms::ListView^  todoListView;
	private: System::Windows::Forms::ColumnHeader^  tIndex;
	private: System::Windows::Forms::ColumnHeader^  tDescription;
	private: System::Windows::Forms::ColumnHeader^  tDueDate;

			 //completed list view
	private: System::Windows::Forms::ListView^  completedListView;
	private: System::Windows::Forms::ColumnHeader^  cIndex;
	private: System::Windows::Forms::ColumnHeader^  cDescription;
	private: System::Windows::Forms::ColumnHeader^  cDueDate;

			 //overdue list view
	private: System::Windows::Forms::ListView^  overdueListView;
	private: System::Windows::Forms::ColumnHeader^  oIndex;
	private: System::Windows::Forms::ColumnHeader^  oDescription;
	private: System::Windows::Forms::ColumnHeader^  oDueDate;

			 //system tray icon
	private: System::Windows::Forms::NotifyIcon^  notifyIcon1;

			 //timer to refresh every minute
	private: System::Windows::Forms::Timer^  timerRefresh;
private: System::Windows::Forms::ColumnHeader^  tStartTime;
private: System::Windows::Forms::ColumnHeader^  cStartTime;
private: System::Windows::Forms::ColumnHeader^  oStartTime;
private: System::Windows::Forms::RichTextBox^  messageBox;
private: System::Windows::Forms::GroupBox^  labelContainer;
private: System::Windows::Forms::Label^  labelTagPriority;
private: System::Windows::Forms::Label^  labelTagEndTime;
private: System::Windows::Forms::Label^  labelTagStartTime;
private: System::Windows::Forms::Label^  labelTagVenue;
private: System::Windows::Forms::Label^  labelTagDesc;
private: System::Windows::Forms::Label^  labelTaskPriority;

private: System::Windows::Forms::Label^  labelTaskEndTime;

private: System::Windows::Forms::Label^  labelTaskStartTime;

private: System::Windows::Forms::Label^  labelTaskVenue;

private: System::Windows::Forms::Label^  labelTaskDesc;
private: System::Windows::Forms::Label^  labelTaskType;

private: System::Windows::Forms::Label^  labelTaskRepeat;

private: System::Windows::Forms::Label^  labelTagTaskType;
private: System::Windows::Forms::Label^  labelTagRepeat;


	private: System::ComponentModel::IContainer^  components;


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void);
#pragma endregion

		//printing functions
	private: void printList();
			 void printToDoList();
			 void printCompletedList();
			 void printOverdueList();
			 void passUserInput();
			 void changeLabelColour(String^ priority);
			 void printLabel(ListViewItem^ item);
			 void printError(string error);
			 System::Void printAddMessage();
			 System::Void printDelMessage();
			 System::Void printModMessage();
			 System::Void printMarMessage();
			 System::Void printSearchMessage();
			 System::Void printHelpMessage();

			 //check ui interaction
	private:System::Void textboxInput_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
			System::Void textboxInput_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);
			System::Void textboxInput_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
			//check user input to display help messages
			System::Void checkInput();
			//check keyboard shortcuts
			System::Void UiDisplay_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);
			System::Void UiDisplay_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
			//user selects an item
			System::Void todoListView_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
			System::Void completedListView_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
			System::Void overdueListView_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);

			//minimising application	
	private:System::Void notifyIcon1_DoubleClick(System::Object^  sender, System::EventArgs^  e);
			System::Void UiDisplay_Resize(System::Object^  sender, System::EventArgs^  e);

	private:bool SetFocus(Control ^ control);
			void focusList(ListType activeListType);
			//user changes displayed list
			System::Void tabContainer_Selected(System::Object^  sender, System::Windows::Forms::TabControlEventArgs^  e);

			//refresh list
	private: System::Void timerRefresh_Tick(System::Object^  sender, System::EventArgs^  e);

private: System::Void labelContainer_Enter(System::Object^  sender, System::EventArgs^  e) {
		 }
};
}
