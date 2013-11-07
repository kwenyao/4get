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

	/// <summary>
	/// Summary for ui_display
	/// </summary>
	public ref class ui_display : public System::Windows::Forms::Form
	{
	public:
		ui_display(void);
	protected:
		~ui_display();
#pragma endregion

#pragma region initialise
	private: UiConvert* converter;
			 Executor* execute;
			 list<Task*>* listOfTasks;
			 int selectedItem;
			 bool loaded, up;
			 string *commandKeyword;

	private: static String^ TAG_NAME = "Name: ";
			 static String^ TAG_LOCATION = "Location: ";
			 static String^ TAG_START_TIME = "Start Time: ";
			 static String^ TAG_END_TIME = "End Time: ";
			 static String^ TAG_PRIORITY = "Priority: ";
			 static String^ NEWLINE = "\n";

			 static String^ COMMAND_ADD_HELP = "add <task description>";
			 static String^ COMMAND_ADD_HELP_LOCATION = ",at <venue>";
			 static String^ COMMAND_ADD_HELP_START = ",from <start time of timed task>";
			 static String^ COMMAND_ADD_HELP_END = ",to <end time of timed task>";
			 static String^ COMMAND_ADD_HELP_DUE = ",by <due time>";
			 static String^ COMMAND_ADD_HELP_REMIND = ",remind on <reminder time>";
			 static String^ COMMAND_ADD_HELP_PRIORITY = ",!";

			 static String^ COMMAND_DEL_HELP = "del <task index>";
			 static String^ COMMAND_DEL_HELP_MULTIPLE = "del <start task index> to <end task index>";

			 static String^ COMMAND_MOD_HELP = "mod <taskindex> <task description>";
			 static String^ COMMAND_MOD_HELP_LOCATION = ",at <venue>";
			 static String^ COMMAND_MOD_HELP_START = ",from <start time of timed task>";
			 static String^ COMMAND_MOD_HELP_END = ",to <end time of timed task>";
			 static String^ COMMAND_MOD_HELP_DUE = ",by <due time>";
			 static String^ COMMAND_MOD_HELP_REMIND = ",remind on <reminder time>";
			 static String^ COMMAND_MOD_HELP_PRIORITY = ",!";

			 static String^ COMMAND_MARK_HELP = "mark <taskindex>";
			 static String^ COMMAND_MARK_HELP_MULTIPLE = "mark <start task index> to <end task index>";

			 static String^ MESSAGE_HELP_ADD = "type \"add\" to add a task";
			 static String^ MESSAGE_HELP_DEL = "type \"del\" to delete a task";
			 static String^ MESSAGE_HELP_MOD = "type \"mod\" to modify a task";
			 static String^ MESSAGE_HELP_MARK = "type \"mark\" to change the status of a task";
			 static String^ MESSAGE_HELP_SEARCH = "type \"search\" to search list";

	private: System::Windows::Forms::TabControl^  tabContainer;
	private: System::Windows::Forms::TabPage^  tabTodo;
	private: System::Windows::Forms::TabPage^  tabCompleted;
	private: System::Windows::Forms::TabPage^  tabOverdue;
	private: System::Windows::Forms::TextBox^  textboxInput;
	private: System::Windows::Forms::FlowLayoutPanel^  inputContainer;
	private: ListType activeListType;


	private: System::Windows::Forms::FlowLayoutPanel^  messageContainer;
	private: System::Windows::Forms::RichTextBox^  messageBox;

			 //to do list view
	private: System::Windows::Forms::ListView^  todoListView;
	private: System::Windows::Forms::ColumnHeader^  tIndex;
	private: System::Windows::Forms::ColumnHeader^  tDescription;
	private: System::Windows::Forms::ColumnHeader^  tVenue;
	private: System::Windows::Forms::ColumnHeader^  tTime;
	private: System::Windows::Forms::ColumnHeader^  tDueDate;
	private: System::Windows::Forms::ColumnHeader^  tPriority;
			 //completed list view
	private: System::Windows::Forms::ListView^  completedListView;
	private: System::Windows::Forms::ColumnHeader^  cIndex;
	private: System::Windows::Forms::ColumnHeader^  cDescription;
	private: System::Windows::Forms::ColumnHeader^  cVenue;
	private: System::Windows::Forms::ColumnHeader^  cTime;
	private: System::Windows::Forms::ColumnHeader^  cDueDate;
	private: System::Windows::Forms::ColumnHeader^  cPriority;
			 //overdue list view
	private: System::Windows::Forms::ListView^  overdueListView;
	private: System::Windows::Forms::ColumnHeader^  oIndex;
	private: System::Windows::Forms::ColumnHeader^  oDescription;
	private: System::Windows::Forms::ColumnHeader^  oVenue;
	private: System::Windows::Forms::ColumnHeader^  oTime;
	private: System::Windows::Forms::ColumnHeader^  oDueDate;
	private: System::Windows::Forms::ColumnHeader^  oPriority;

	private: System::Windows::Forms::NotifyIcon^  notifyIcon1;
	private: System::Windows::Forms::Timer^  timerRefresh;
	private: System::Windows::Forms::Label^  itemDisplayLabel;
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

	private: void printList();
	private: void printToDoList();
	private: void printCompletedList();
	private: void printOverdueList();
	private: void passUserInput();
	private: void printError(string error);
	public: System::Void textboxInput_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);
	private: System::Void textboxInput_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
	private: System::Void textboxInput_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
	private: System::Void checkInput();
	private: System::Void printAddMessage();
	private: System::Void printDelMessage();
	private: System::Void printModMessage();
	private: System::Void printMarMessage();
	private: System::Void printHelpMessage();
	private: bool SetFocus(Control ^ control);
	private: System::Void tabContainer_Selected(System::Object^  sender, System::Windows::Forms::TabControlEventArgs^  e);
	private: System::Void ui_display_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);
	private: System::Void ui_display_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
	private: System::Void notifyIcon1_DoubleClick(System::Object^  sender, System::EventArgs^  e);
	private: System::Void ui_display_Resize(System::Object^  sender, System::EventArgs^  e);
			 /*private: void focusItem();
			 private: void focusToDoItem();
			 private: void focusCompletedItem();
			 private: void focusOverdueItem();*/
	private: System::Void timerRefresh_Tick(System::Object^  sender, System::EventArgs^  e);
			 /*private: System::Void todoListView_ItemActivate(System::Object^  sender, System::EventArgs^  e);
			 private: System::Void completedListView_ItemActivate(System::Object^  sender, System::EventArgs^  e);
			 private: System::Void overdueListView_ItemActivate(System::Object^  sender, System::EventArgs^  e);	*/
	private: void printLabel(ListViewItem^ item);
	private: void focusList(ListType activeListType);
	};
}
