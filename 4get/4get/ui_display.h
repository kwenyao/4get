#pragma once

#include "ui_convert.h"
#include "logic_executor.h"
#include "logic_task.h"
#include "common_message.h"
#include <string>
#include <list>
#include <time.h>
#include <Windows.h>

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
	private: Executor* execute;
	private: list<Task*>* listOfTasks;

	private: bool loaded;
	private: string *commandKeyword;

	private: System::Windows::Forms::TabControl^  tabContainer;
	private: System::Windows::Forms::TabPage^  tabTodo;
	private: System::Windows::Forms::TabPage^  tabCompleted;
	private: System::Windows::Forms::TabPage^  tabOverdue;
	private: System::Windows::Forms::TextBox^  textboxInput;
	private: System::Windows::Forms::FlowLayoutPanel^  inputContainer;
	private: ListType activeListType;


	private: System::Windows::Forms::FlowLayoutPanel^  messageContainer;















	private: System::Windows::Forms::RichTextBox^  messageBox;



	private: System::Windows::Forms::GroupBox^  todayContainer;
	private: System::Windows::Forms::CheckedListBox^  checkedTaskList;
	private: System::Windows::Forms::DateTimePicker^  chooseDate;








	private: System::Windows::Forms::ListView^  todoListView;
	private: System::Windows::Forms::ColumnHeader^  tIndex;

	private: System::Windows::Forms::ColumnHeader^  tDescription;
	private: System::Windows::Forms::ColumnHeader^  tVenue;
	private: System::Windows::Forms::ColumnHeader^  tTime;
	private: System::Windows::Forms::ColumnHeader^  tDueDate;
	private: System::Windows::Forms::ColumnHeader^  tPriority;
	private: System::Windows::Forms::ListView^  completedListView;
	private: System::Windows::Forms::ColumnHeader^  cIndex;
	private: System::Windows::Forms::ColumnHeader^  cDescription;
	private: System::Windows::Forms::ColumnHeader^  cVenue;
	private: System::Windows::Forms::ColumnHeader^  cTime;
	private: System::Windows::Forms::ColumnHeader^  cDueDate;
	private: System::Windows::Forms::ColumnHeader^  cPriority;






	private: System::Windows::Forms::ListView^  overdueListView;
	private: System::Windows::Forms::ColumnHeader^  oIndex;
	private: System::Windows::Forms::ColumnHeader^  oDescription;
	private: System::Windows::Forms::ColumnHeader^  oVenue;
	private: System::Windows::Forms::ColumnHeader^  oTime;
	private: System::Windows::Forms::ColumnHeader^  oDueDate;
	private: System::Windows::Forms::ColumnHeader^  oPriority;
	private: System::Windows::Forms::NotifyIcon^  notifyIcon1;
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
};
}
