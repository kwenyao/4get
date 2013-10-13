#pragma once

#include "ui_convert.h"
#include "logic_executor.h"
#include "logic_task.h"
#include "common_message.h"
#include <string>
#include <list>
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
	private: list<Task>* listOfTasks;

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







	
	private: System::Windows::Forms::ListView^  overdueListView;
	private: System::Windows::Forms::ColumnHeader^  oTaskIndex;
	private: System::Windows::Forms::ColumnHeader^  oTaskDescription;
	private: System::Windows::Forms::ColumnHeader^  oTaskVenue;
	private: System::Windows::Forms::ColumnHeader^  oTaskTime;
	private: System::Windows::Forms::ColumnHeader^  oTaskDate;
	private: System::Windows::Forms::ColumnHeader^  oTaskPriority;


	private: System::Windows::Forms::RichTextBox^  richTextBox1;
	private: System::Windows::Forms::GroupBox^  todayContainer;
	private: System::Windows::Forms::CheckedListBox^  checkedTaskList;
	private: System::Windows::Forms::DateTimePicker^  chooseDate;








	private: System::Windows::Forms::ListView^  todoListView;
	private: System::Windows::Forms::ColumnHeader^  tIndexNo;
	private: System::Windows::Forms::ColumnHeader^  tDescription;
	private: System::Windows::Forms::ColumnHeader^  tVenue;
	private: System::Windows::Forms::ColumnHeader^  tTime;
	private: System::Windows::Forms::ColumnHeader^  tDueDate;
	private: System::Windows::Forms::ColumnHeader^  tPriority;








	private: System::Windows::Forms::ListView^  completedListView;
	private: System::Windows::Forms::ColumnHeader^  cIndexNo;
	private: System::Windows::Forms::ColumnHeader^  cDescription;
	private: System::Windows::Forms::ColumnHeader^  cVenue;
	private: System::Windows::Forms::ColumnHeader^  cPriority;





	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void);
#pragma endregion

	private: void loadList();
	private: void printList();
	private: void printToDoList();
	private: void printCompletedList();
	private: void printOverdueList();
	private: void passUserInput();          
	public: System::Void textboxInput_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);
	private: System::Void textboxInput_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
	private: System::Void completedListView_ItemActivate(System::Object^  sender, System::EventArgs^  e);
	private: System::Void overdueListView_ItemActivate(System::Object^  sender, System::EventArgs^  e);
	private: System::Void textboxInput_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
};
}
