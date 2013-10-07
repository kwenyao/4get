#include "ui_display.h"
using namespace UIDisplay;

//constructor
ui_display::ui_display(void){
	InitializeComponent();
	//
	//TODO: Add the constructor code here
	//
}

ui_display::~ui_display(){
	if (components){
		delete components;
	}
}

void ui_display::InitializeComponent(void){
	this->tabContainer = (gcnew System::Windows::Forms::TabControl());
	this->tabTodo = (gcnew System::Windows::Forms::TabPage());
	this->todoListView = (gcnew System::Windows::Forms::ListView());
	this->taskIndex = (gcnew System::Windows::Forms::ColumnHeader());
	this->taskDescription = (gcnew System::Windows::Forms::ColumnHeader());
	this->taskLocation = (gcnew System::Windows::Forms::ColumnHeader());
	this->taskTime = (gcnew System::Windows::Forms::ColumnHeader());
	this->taskDueDate = (gcnew System::Windows::Forms::ColumnHeader());
	this->taskPriority = (gcnew System::Windows::Forms::ColumnHeader());
	this->tabCompleted = (gcnew System::Windows::Forms::TabPage());
	this->completedListView = (gcnew System::Windows::Forms::ListView());
	this->cTaskIndex = (gcnew System::Windows::Forms::ColumnHeader());
	this->cTaskDescription = (gcnew System::Windows::Forms::ColumnHeader());
	this->cTaskVenue = (gcnew System::Windows::Forms::ColumnHeader());
	this->cTaskTime = (gcnew System::Windows::Forms::ColumnHeader());
	this->cTaskDate = (gcnew System::Windows::Forms::ColumnHeader());
	this->cTaskPriority = (gcnew System::Windows::Forms::ColumnHeader());
	this->tabOverdue = (gcnew System::Windows::Forms::TabPage());
	this->overdueListView = (gcnew System::Windows::Forms::ListView());
	this->oTaskIndex = (gcnew System::Windows::Forms::ColumnHeader());
	this->oTaskDescription = (gcnew System::Windows::Forms::ColumnHeader());
	this->oTaskVenue = (gcnew System::Windows::Forms::ColumnHeader());
	this->oTaskTime = (gcnew System::Windows::Forms::ColumnHeader());
	this->oTaskDate = (gcnew System::Windows::Forms::ColumnHeader());
	this->oTaskPriority = (gcnew System::Windows::Forms::ColumnHeader());
	this->tabFloat = (gcnew System::Windows::Forms::TabPage());
	this->listView1 = (gcnew System::Windows::Forms::ListView());
	this->fTaskIndex = (gcnew System::Windows::Forms::ColumnHeader());
	this->fTaskDescription = (gcnew System::Windows::Forms::ColumnHeader());
	this->fTaskVenue = (gcnew System::Windows::Forms::ColumnHeader());
	this->fTaskTime = (gcnew System::Windows::Forms::ColumnHeader());
	this->fTaskDate = (gcnew System::Windows::Forms::ColumnHeader());
	this->fTaskPriority = (gcnew System::Windows::Forms::ColumnHeader());
	this->inputContainer = (gcnew System::Windows::Forms::FlowLayoutPanel());
	this->textboxInput = (gcnew System::Windows::Forms::TextBox());
	this->messageContainer = (gcnew System::Windows::Forms::FlowLayoutPanel());
	this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
	this->todayContainer = (gcnew System::Windows::Forms::GroupBox());
	this->checkedTaskList = (gcnew System::Windows::Forms::CheckedListBox());
	this->chooseDate = (gcnew System::Windows::Forms::DateTimePicker());
	this->tabContainer->SuspendLayout();
	this->tabTodo->SuspendLayout();
	this->tabCompleted->SuspendLayout();
	this->tabOverdue->SuspendLayout();
	this->tabFloat->SuspendLayout();
	this->inputContainer->SuspendLayout();
	this->messageContainer->SuspendLayout();
	this->todayContainer->SuspendLayout();
	this->SuspendLayout();
	// 
	// tabContainer
	// 
	this->tabContainer->Controls->Add(this->tabTodo);
	this->tabContainer->Controls->Add(this->tabCompleted);
	this->tabContainer->Controls->Add(this->tabOverdue);
	this->tabContainer->Controls->Add(this->tabFloat);
	this->tabContainer->Location = System::Drawing::Point(370, 173);
	this->tabContainer->Name = L"tabContainer";
	this->tabContainer->SelectedIndex = 0;
	this->tabContainer->Size = System::Drawing::Size(442, 281);
	this->tabContainer->TabIndex = 0;
	// 
	// tabTodo
	// 
	this->tabTodo->Controls->Add(this->todoListView);
	this->tabTodo->Location = System::Drawing::Point(4, 22);
	this->tabTodo->Name = L"tabTodo";
	this->tabTodo->Padding = System::Windows::Forms::Padding(3);
	this->tabTodo->Size = System::Drawing::Size(434, 255);
	this->tabTodo->TabIndex = 0;
	this->tabTodo->Text = L"To Do";
	this->tabTodo->UseVisualStyleBackColor = true;
	// 
	// todoListView
	// 
	this->todoListView->Activation = System::Windows::Forms::ItemActivation::OneClick;
	this->todoListView->AutoArrange = false;
	this->todoListView->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
	this->todoListView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(6) {this->taskIndex, this->taskDescription, 
		this->taskLocation, this->taskTime, this->taskDueDate, this->taskPriority});
	this->todoListView->FullRowSelect = true;
	this->todoListView->GridLines = true;
	this->todoListView->Location = System::Drawing::Point(-4, -4);
	this->todoListView->Name = L"todoListView";
	this->todoListView->Size = System::Drawing::Size(440, 259);
	this->todoListView->TabIndex = 0;
	this->todoListView->UseCompatibleStateImageBehavior = false;
	this->todoListView->View = System::Windows::Forms::View::Details;
	this->todoListView->VirtualMode = true;
	// 
	// taskIndex
	// 
	this->taskIndex->Text = L"Index No.";
	// 
	// taskDescription
	// 
	this->taskDescription->Text = L"Description";
	this->taskDescription->Width = 118;
	// 
	// taskLocation
	// 
	this->taskLocation->Text = L"Venue";
	// 
	// taskTime
	// 
	this->taskTime->Text = L"Time";
	// 
	// taskDueDate
	// 
	this->taskDueDate->Text = L"Due Date";
	this->taskDueDate->Width = 80;
	// 
	// taskPriority
	// 
	this->taskPriority->Text = L"Priority";
	// 
	// tabCompleted
	// 
	this->tabCompleted->Controls->Add(this->completedListView);
	this->tabCompleted->Location = System::Drawing::Point(4, 22);
	this->tabCompleted->Name = L"tabCompleted";
	this->tabCompleted->Padding = System::Windows::Forms::Padding(3);
	this->tabCompleted->Size = System::Drawing::Size(434, 255);
	this->tabCompleted->TabIndex = 1;
	this->tabCompleted->Text = L"Completed";
	this->tabCompleted->UseVisualStyleBackColor = true;
	// 
	// completedListView
	// 
	this->completedListView->Activation = System::Windows::Forms::ItemActivation::OneClick;
	this->completedListView->AutoArrange = false;
	this->completedListView->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
	this->completedListView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(6) {this->cTaskIndex, 
		this->cTaskDescription, this->cTaskVenue, this->cTaskTime, this->cTaskDate, this->cTaskPriority});
	this->completedListView->FullRowSelect = true;
	this->completedListView->GridLines = true;
	this->completedListView->Location = System::Drawing::Point(-7, -2);
	this->completedListView->Name = L"completedListView";
	this->completedListView->Size = System::Drawing::Size(526, 259);
	this->completedListView->TabIndex = 1;
	this->completedListView->UseCompatibleStateImageBehavior = false;
	this->completedListView->View = System::Windows::Forms::View::Details;
	this->completedListView->SelectedIndexChanged += gcnew System::EventHandler(this, &ui_display::completedListView_SelectedIndexChanged);
	// 
	// cTaskIndex
	// 
	this->cTaskIndex->Text = L"Index No.";
	// 
	// cTaskDescription
	// 
	this->cTaskDescription->Text = L"Description";
	this->cTaskDescription->Width = 127;
	// 
	// cTaskVenue
	// 
	this->cTaskVenue->Text = L"Venue";
	// 
	// cTaskTime
	// 
	this->cTaskTime->Text = L"Time";
	// 
	// cTaskDate
	// 
	this->cTaskDate->Text = L"Due Date";
	this->cTaskDate->Width = 80;
	// 
	// cTaskPriority
	// 
	this->cTaskPriority->Text = L"Priority";
	// 
	// tabOverdue
	// 
	this->tabOverdue->Controls->Add(this->overdueListView);
	this->tabOverdue->Location = System::Drawing::Point(4, 22);
	this->tabOverdue->Name = L"tabOverdue";
	this->tabOverdue->Size = System::Drawing::Size(434, 255);
	this->tabOverdue->TabIndex = 2;
	this->tabOverdue->Text = L"Overdue";
	this->tabOverdue->UseVisualStyleBackColor = true;
	// 
	// overdueListView
	// 
	this->overdueListView->Activation = System::Windows::Forms::ItemActivation::OneClick;
	this->overdueListView->AutoArrange = false;
	this->overdueListView->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
	this->overdueListView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(6) {this->oTaskIndex, 
		this->oTaskDescription, this->oTaskVenue, this->oTaskTime, this->oTaskDate, this->oTaskPriority});
	this->overdueListView->FullRowSelect = true;
	this->overdueListView->GridLines = true;
	this->overdueListView->Location = System::Drawing::Point(-4, -4);
	this->overdueListView->Name = L"overdueListView";
	this->overdueListView->Size = System::Drawing::Size(442, 259);
	this->overdueListView->TabIndex = 1;
	this->overdueListView->UseCompatibleStateImageBehavior = false;
	this->overdueListView->View = System::Windows::Forms::View::Details;
	// 
	// oTaskIndex
	// 
	this->oTaskIndex->Text = L"Index No.";
	// 
	// oTaskDescription
	// 
	this->oTaskDescription->Text = L"Description";
	this->oTaskDescription->Width = 127;
	// 
	// oTaskVenue
	// 
	this->oTaskVenue->Text = L"Venue";
	// 
	// oTaskTime
	// 
	this->oTaskTime->Text = L"Time";
	// 
	// oTaskDate
	// 
	this->oTaskDate->Text = L"Due Date";
	this->oTaskDate->Width = 80;
	// 
	// oTaskPriority
	// 
	this->oTaskPriority->Text = L"Priority";
	// 
	// tabFloat
	// 
	this->tabFloat->Controls->Add(this->listView1);
	this->tabFloat->Location = System::Drawing::Point(4, 22);
	this->tabFloat->Name = L"tabFloat";
	this->tabFloat->Size = System::Drawing::Size(434, 255);
	this->tabFloat->TabIndex = 3;
	this->tabFloat->Text = L"Floating";
	this->tabFloat->UseVisualStyleBackColor = true;
	// 
	// listView1
	// 
	this->listView1->Activation = System::Windows::Forms::ItemActivation::OneClick;
	this->listView1->AutoArrange = false;
	this->listView1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
	this->listView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(6) {this->fTaskIndex, this->fTaskDescription, 
		this->fTaskVenue, this->fTaskTime, this->fTaskDate, this->fTaskPriority});
	this->listView1->FullRowSelect = true;
	this->listView1->GridLines = true;
	this->listView1->Location = System::Drawing::Point(-4, -4);
	this->listView1->Name = L"listView1";
	this->listView1->Size = System::Drawing::Size(442, 259);
	this->listView1->TabIndex = 2;
	this->listView1->UseCompatibleStateImageBehavior = false;
	this->listView1->View = System::Windows::Forms::View::Details;
	// 
	// fTaskIndex
	// 
	this->fTaskIndex->Text = L"Index No.";
	// 
	// fTaskDescription
	// 
	this->fTaskDescription->Text = L"Description";
	this->fTaskDescription->Width = 127;
	// 
	// fTaskVenue
	// 
	this->fTaskVenue->Text = L"Venue";
	// 
	// fTaskTime
	// 
	this->fTaskTime->Text = L"Time";
	// 
	// fTaskDate
	// 
	this->fTaskDate->Text = L"Due Date";
	this->fTaskDate->Width = 80;
	// 
	// fTaskPriority
	// 
	this->fTaskPriority->Text = L"Priority";
	// 
	// inputContainer
	// 
	this->inputContainer->Anchor = System::Windows::Forms::AnchorStyles::Left;
	this->inputContainer->Controls->Add(this->textboxInput);
	this->inputContainer->Location = System::Drawing::Point(12, 12);
	this->inputContainer->Name = L"inputContainer";
	this->inputContainer->Size = System::Drawing::Size(800, 49);
	this->inputContainer->TabIndex = 2;
	// 
	// textboxInput
	// 
	this->textboxInput->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
		static_cast<System::Byte>(0)));
	this->textboxInput->Location = System::Drawing::Point(3, 3);
	this->textboxInput->Multiline = true;
	this->textboxInput->Name = L"textboxInput";
	this->textboxInput->Size = System::Drawing::Size(793, 42);
	this->textboxInput->TabIndex = 1;
	this->textboxInput->Text = L"Enter Command Here";
	// 
	// messageContainer
	// 
	this->messageContainer->Controls->Add(this->richTextBox1);
	this->messageContainer->Location = System::Drawing::Point(12, 67);
	this->messageContainer->Name = L"messageContainer";
	this->messageContainer->Size = System::Drawing::Size(800, 100);
	this->messageContainer->TabIndex = 3;
	// 
	// richTextBox1
	// 
	this->richTextBox1->BackColor = System::Drawing::SystemColors::InactiveCaption;
	this->richTextBox1->Location = System::Drawing::Point(3, 3);
	this->richTextBox1->Name = L"richTextBox1";
	this->richTextBox1->ReadOnly = true;
	this->richTextBox1->Size = System::Drawing::Size(793, 94);
	this->richTextBox1->TabIndex = 0;
	this->richTextBox1->Text = L"";
	// 
	// todayContainer
	// 
	this->todayContainer->Controls->Add(this->checkedTaskList);
	this->todayContainer->Controls->Add(this->chooseDate);
	this->todayContainer->Location = System::Drawing::Point(15, 218);
	this->todayContainer->Name = L"todayContainer";
	this->todayContainer->Size = System::Drawing::Size(349, 194);
	this->todayContainer->TabIndex = 4;
	this->todayContainer->TabStop = false;
	this->todayContainer->Text = L"Tasks For";
	// 
	// checkedTaskList
	// 
	this->checkedTaskList->FormattingEnabled = true;
	this->checkedTaskList->Location = System::Drawing::Point(0, 40);
	this->checkedTaskList->Name = L"checkedTaskList";
	this->checkedTaskList->Size = System::Drawing::Size(349, 139);
	this->checkedTaskList->TabIndex = 1;
	// 
	// chooseDate
	// 
	this->chooseDate->Location = System::Drawing::Point(0, 16);
	this->chooseDate->Name = L"chooseDate";
	this->chooseDate->Size = System::Drawing::Size(349, 20);
	this->chooseDate->TabIndex = 0;
	// 
	// ui_display
	// 
	this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
	this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
	this->ClientSize = System::Drawing::Size(824, 466);
	this->Controls->Add(this->todayContainer);
	this->Controls->Add(this->messageContainer);
	this->Controls->Add(this->inputContainer);
	this->Controls->Add(this->tabContainer);
	this->Name = L"ui_display";
	this->Text = L"ui_display";
	this->tabContainer->ResumeLayout(false);
	this->tabTodo->ResumeLayout(false);
	this->tabCompleted->ResumeLayout(false);
	this->tabOverdue->ResumeLayout(false);
	this->tabFloat->ResumeLayout(false);
	this->inputContainer->ResumeLayout(false);
	this->inputContainer->PerformLayout();
	this->messageContainer->ResumeLayout(false);
	this->todayContainer->ResumeLayout(false);
	this->ResumeLayout(false);
}