#include "ui_display.h"
using namespace UIDisplay;

//constructor
ui_display::ui_display(){
	execute = new Executor;
	converter = new UiConvert;
	listOfTasks = new std::list<Task*>;
	commandKeyword = new string;
	loaded = false;
	activeListType = listToDo;
	execute->setListType(activeListType);
	
	InitializeComponent();
	this->printList();
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
	this->tIndex = (gcnew System::Windows::Forms::ColumnHeader());
	this->tDescription = (gcnew System::Windows::Forms::ColumnHeader());
	this->tVenue = (gcnew System::Windows::Forms::ColumnHeader());
	this->tTime = (gcnew System::Windows::Forms::ColumnHeader());
	this->tDueDate = (gcnew System::Windows::Forms::ColumnHeader());
	this->tPriority = (gcnew System::Windows::Forms::ColumnHeader());
	this->tabCompleted = (gcnew System::Windows::Forms::TabPage());
	this->completedListView = (gcnew System::Windows::Forms::ListView());
	this->cIndex = (gcnew System::Windows::Forms::ColumnHeader());
	this->cDescription = (gcnew System::Windows::Forms::ColumnHeader());
	this->cVenue = (gcnew System::Windows::Forms::ColumnHeader());
	this->cTime = (gcnew System::Windows::Forms::ColumnHeader());
	this->cDueDate = (gcnew System::Windows::Forms::ColumnHeader());
	this->cPriority = (gcnew System::Windows::Forms::ColumnHeader());
	this->tabOverdue = (gcnew System::Windows::Forms::TabPage());
	this->overdueListView = (gcnew System::Windows::Forms::ListView());
	this->oIndex = (gcnew System::Windows::Forms::ColumnHeader());
	this->oDescription = (gcnew System::Windows::Forms::ColumnHeader());
	this->oVenue = (gcnew System::Windows::Forms::ColumnHeader());
	this->oTime = (gcnew System::Windows::Forms::ColumnHeader());
	this->oDueDate = (gcnew System::Windows::Forms::ColumnHeader());
	this->oPriority = (gcnew System::Windows::Forms::ColumnHeader());
	this->inputContainer = (gcnew System::Windows::Forms::FlowLayoutPanel());
	this->textboxInput = (gcnew System::Windows::Forms::TextBox());
	this->messageContainer = (gcnew System::Windows::Forms::FlowLayoutPanel());
	this->messageBox = (gcnew System::Windows::Forms::RichTextBox());
	this->todayContainer = (gcnew System::Windows::Forms::GroupBox());
	this->checkedTaskList = (gcnew System::Windows::Forms::CheckedListBox());
	this->chooseDate = (gcnew System::Windows::Forms::DateTimePicker());
	this->tabContainer->SuspendLayout();
	this->tabTodo->SuspendLayout();
	this->tabCompleted->SuspendLayout();
	this->tabOverdue->SuspendLayout();
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
	this->tabContainer->Location = System::Drawing::Point(370, 195);
	this->tabContainer->Name = L"tabContainer";
	this->tabContainer->SelectedIndex = 0;
	this->tabContainer->Size = System::Drawing::Size(442, 250);
	this->tabContainer->TabIndex = 0;
	this->tabContainer->Selected += gcnew System::Windows::Forms::TabControlEventHandler(this, &ui_display::tabContainer_Selected);
	// 
	// tabTodo
	// 
	this->tabTodo->Controls->Add(this->todoListView);
	this->tabTodo->Location = System::Drawing::Point(4, 22);
	this->tabTodo->Name = L"tabTodo";
	this->tabTodo->Padding = System::Windows::Forms::Padding(3);
	this->tabTodo->Size = System::Drawing::Size(434, 224);
	this->tabTodo->TabIndex = 0;
	this->tabTodo->Text = L"To Do";
	this->tabTodo->UseVisualStyleBackColor = true;
	// 
	// todoListView
	// 
	this->todoListView->Activation = System::Windows::Forms::ItemActivation::OneClick;
	this->todoListView->AutoArrange = false;
	this->todoListView->BackColor = System::Drawing::Color::SandyBrown;
	this->todoListView->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
	this->todoListView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(6) {this->tIndex, this->tDescription, 
		this->tVenue, this->tTime, this->tDueDate, this->tPriority});
	this->todoListView->Font = (gcnew System::Drawing::Font(L"MS Reference Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
		static_cast<System::Byte>(0)));
	this->todoListView->FullRowSelect = true;
	this->todoListView->GridLines = true;
	this->todoListView->LabelEdit = true;
	this->todoListView->Location = System::Drawing::Point(-4, -4);
	this->todoListView->Name = L"todoListView";
	this->todoListView->Size = System::Drawing::Size(440, 259);
	this->todoListView->TabIndex = 1;
	this->todoListView->UseCompatibleStateImageBehavior = false;
	this->todoListView->View = System::Windows::Forms::View::Details;
	// 
	// tIndex
	// 
	this->tIndex->Text = L"#";
	this->tIndex->Width = 29;
	// 
	// tDescription
	// 
	this->tDescription->Text = L"Description";
	this->tDescription->Width = 139;
	// 
	// tVenue
	// 
	this->tVenue->Text = L"Venue";
	this->tVenue->Width = 79;
	// 
	// tTime
	// 
	this->tTime->Text = L"Time";
	this->tTime->Width = 68;
	// 
	// tDueDate
	// 
	this->tDueDate->Text = L"Due Date";
	this->tDueDate->Width = 62;
	// 
	// tPriority
	// 
	this->tPriority->Text = L"Priority";
	// 
	// tabCompleted
	// 
	this->tabCompleted->Controls->Add(this->completedListView);
	this->tabCompleted->Location = System::Drawing::Point(4, 22);
	this->tabCompleted->Name = L"tabCompleted";
	this->tabCompleted->Padding = System::Windows::Forms::Padding(3);
	this->tabCompleted->Size = System::Drawing::Size(434, 224);
	this->tabCompleted->TabIndex = 1;
	this->tabCompleted->Text = L"Completed";
	this->tabCompleted->UseVisualStyleBackColor = true;
	// 
	// completedListView
	// 
	this->completedListView->Activation = System::Windows::Forms::ItemActivation::OneClick;
	this->completedListView->AutoArrange = false;
	this->completedListView->BackColor = System::Drawing::Color::SandyBrown;
	this->completedListView->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
	this->completedListView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(6) {this->cIndex, this->cDescription, 
		this->cVenue, this->cTime, this->cDueDate, this->cPriority});
	this->completedListView->Font = (gcnew System::Drawing::Font(L"MS Reference Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, 
		System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
	this->completedListView->FullRowSelect = true;
	this->completedListView->GridLines = true;
	this->completedListView->LabelEdit = true;
	this->completedListView->Location = System::Drawing::Point(-4, -4);
	this->completedListView->Name = L"completedListView";
	this->completedListView->Size = System::Drawing::Size(440, 259);
	this->completedListView->TabIndex = 2;
	this->completedListView->UseCompatibleStateImageBehavior = false;
	this->completedListView->View = System::Windows::Forms::View::Details;
	// 
	// cIndex
	// 
	this->cIndex->Text = L"#";
	this->cIndex->Width = 29;
	// 
	// cDescription
	// 
	this->cDescription->Text = L"Description";
	this->cDescription->Width = 139;
	// 
	// cVenue
	// 
	this->cVenue->Text = L"Venue";
	this->cVenue->Width = 79;
	// 
	// cTime
	// 
	this->cTime->Text = L"Time";
	this->cTime->Width = 68;
	// 
	// cDueDate
	// 
	this->cDueDate->Text = L"Due Date";
	this->cDueDate->Width = 62;
	// 
	// cPriority
	// 
	this->cPriority->Text = L"Priority";
	// 
	// tabOverdue
	// 
	this->tabOverdue->Controls->Add(this->overdueListView);
	this->tabOverdue->Location = System::Drawing::Point(4, 22);
	this->tabOverdue->Name = L"tabOverdue";
	this->tabOverdue->Size = System::Drawing::Size(434, 224);
	this->tabOverdue->TabIndex = 2;
	this->tabOverdue->Text = L"Overdue";
	this->tabOverdue->UseVisualStyleBackColor = true;
	// 
	// overdueListView
	// 
	this->overdueListView->Activation = System::Windows::Forms::ItemActivation::OneClick;
	this->overdueListView->AutoArrange = false;
	this->overdueListView->BackColor = System::Drawing::Color::SandyBrown;
	this->overdueListView->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
	this->overdueListView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(6) {this->oIndex, this->oDescription, 
		this->oVenue, this->oTime, this->oDueDate, this->oPriority});
	this->overdueListView->Font = (gcnew System::Drawing::Font(L"MS Reference Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, 
		System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
	this->overdueListView->FullRowSelect = true;
	this->overdueListView->GridLines = true;
	this->overdueListView->LabelEdit = true;
	this->overdueListView->Location = System::Drawing::Point(-4, -4);
	this->overdueListView->Name = L"overdueListView";
	this->overdueListView->Size = System::Drawing::Size(440, 259);
	this->overdueListView->TabIndex = 2;
	this->overdueListView->UseCompatibleStateImageBehavior = false;
	this->overdueListView->View = System::Windows::Forms::View::Details;
	// 
	// oIndex
	// 
	this->oIndex->Text = L"#";
	this->oIndex->Width = 29;
	// 
	// oDescription
	// 
	this->oDescription->Text = L"Description";
	this->oDescription->Width = 139;
	// 
	// oVenue
	// 
	this->oVenue->Text = L"Venue";
	this->oVenue->Width = 79;
	// 
	// oTime
	// 
	this->oTime->Text = L"Time";
	this->oTime->Width = 68;
	// 
	// oDueDate
	// 
	this->oDueDate->Text = L"Due Date";
	this->oDueDate->Width = 62;
	// 
	// oPriority
	// 
	this->oPriority->Text = L"Priority";
	// 
	// inputContainer
	// 
	this->inputContainer->Anchor = System::Windows::Forms::AnchorStyles::Left;
	this->inputContainer->Controls->Add(this->textboxInput);
	this->inputContainer->Location = System::Drawing::Point(12, 12);
	this->inputContainer->Name = L"inputContainer";
	this->inputContainer->Size = System::Drawing::Size(800, 22);
	this->inputContainer->TabIndex = 2;
	// 
	// textboxInput
	// 
	this->textboxInput->BackColor = System::Drawing::Color::DarkCyan;
	this->textboxInput->BorderStyle = System::Windows::Forms::BorderStyle::None;
	this->textboxInput->Font = (gcnew System::Drawing::Font(L"MS Reference Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
		static_cast<System::Byte>(0)));
	this->textboxInput->ForeColor = System::Drawing::SystemColors::Info;
	this->textboxInput->Location = System::Drawing::Point(3, 3);
	this->textboxInput->Name = L"textboxInput";
	this->textboxInput->Size = System::Drawing::Size(793, 16);
	this->textboxInput->TabIndex = 1;
	this->textboxInput->Text = L"Enter Command Here";
	this->textboxInput->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &ui_display::textboxInput_MouseClick);
	this->textboxInput->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &ui_display::textboxInput_KeyDown);
	this->textboxInput->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &ui_display::textboxInput_KeyPress);
	// 
	// messageContainer
	// 
	this->messageContainer->Controls->Add(this->messageBox);
	this->messageContainer->Location = System::Drawing::Point(12, 40);
	this->messageContainer->Name = L"messageContainer";
	this->messageContainer->Size = System::Drawing::Size(800, 127);
	this->messageContainer->TabIndex = 3;
	// 
	// messageBox
	// 
	this->messageBox->BackColor = System::Drawing::Color::IndianRed;
	this->messageBox->Location = System::Drawing::Point(3, 3);
	this->messageBox->Name = L"messageBox";
	this->messageBox->ReadOnly = true;
	this->messageBox->Size = System::Drawing::Size(793, 124);
	this->messageBox->TabIndex = 0;
	this->messageBox->Text = L"";
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
	this->checkedTaskList->Location = System::Drawing::Point(-3, 42);
	this->checkedTaskList->Name = L"checkedTaskList";
	this->checkedTaskList->Size = System::Drawing::Size(352, 139);
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
	this->BackColor = System::Drawing::SystemColors::InactiveCaptionText;
	this->ClientSize = System::Drawing::Size(824, 466);
	this->Controls->Add(this->todayContainer);
	this->Controls->Add(this->messageContainer);
	this->Controls->Add(this->inputContainer);
	this->Controls->Add(this->tabContainer);
	this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
	this->KeyPreview = true;
	this->Name = L"ui_display";
	this->Text = L"4get";
	this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &ui_display::ui_display_KeyDown);
	this->tabContainer->ResumeLayout(false);
	this->tabTodo->ResumeLayout(false);
	this->tabCompleted->ResumeLayout(false);
	this->tabOverdue->ResumeLayout(false);
	this->inputContainer->ResumeLayout(false);
	this->inputContainer->PerformLayout();
	this->messageContainer->ResumeLayout(false);
	this->todayContainer->ResumeLayout(false);
	this->ResumeLayout(false);

}



void ui_display::loadList(){
	this->printList();
}

void ui_display::printError(string error){
	String ^ error_sys_string=gcnew String(error.c_str());
	array<String ^> ^ errorLines = {error_sys_string};
	array<String ^> ^  emptyLines ={};
	this->messageBox->Lines=emptyLines;
	this->messageBox->Lines = errorLines;
}

void ui_display::passUserInput(){
	string stdCommand;
	converter->stringSysToStdConversion(this->textboxInput->Text, stdCommand);
	execute->stringCollector(stdCommand);	
}

Void ui_display::textboxInput_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e){

	if(e->KeyCode == Keys::Enter){
		commandKeyword->clear();
		array<String ^> ^  helpLines = {
			"type \"add\" to add a task",
			"type \"del\" to delete a task",
			"type \"mod\" to modify a task",
			"type \"mark\" to change the status of a task"
		};
		this->messageBox->Lines = helpLines;
		this->passUserInput();
		this->textboxInput->Clear();
		list<Task*> taskList;
		taskList = execute->getUpdatedList(activeListType);
		*listOfTasks = taskList;
		printList();

	}
}

void ui_display::printList(){
	try{
		switch(activeListType){
		case listCompleted:
			printCompletedList();
			break;
		case listOverdue:
			printOverdueList();
			break;
		case listToDo:
			printToDoList();
			break;
		default:
			throw MESSAGE_ERROR_INVALID_LIST;
		}
	}
	catch(string error){
		this->printError(error);
	}
}
void ui_display::printToDoList(){
	try{
		int size = listOfTasks->size();

		int j=0;
		array<ListViewItem^>^ temp;
		Array::Resize(temp, size);
		if(loaded)
		{
			this->todoListView->Items->Clear();
		}
		if(size==0){
			throw MESSAGE_ERROR_LIST_EMPTY;
		}
		this->Cursor = Cursors::WaitCursor;

		this->todoListView->BeginUpdate();

		for (int i=0; i<size; i++)
		{
			ListViewItem^ item = gcnew ListViewItem;
			converter->printItem(item, listOfTasks, i+1);
			temp[j] = item;
			j++;
		}
		this->todoListView->Items->AddRange(temp);
		loaded = true;
		this->Cursor = Cursors::Default;
		this->todoListView->EndUpdate();
	}
	catch(string error){
		this->printError(error);
	}

}
void ui_display::printCompletedList(){
	try{
		int size = listOfTasks->size();

		int j=0;
		array<ListViewItem^>^ temp;
		Array::Resize(temp, size);

		if(loaded)
		{
			this->completedListView->Items->Clear();
		}
		if(size==0){
			throw MESSAGE_ERROR_LIST_EMPTY;
		}
		this->Cursor = Cursors::WaitCursor;

		this->completedListView->BeginUpdate();


		for (int i=0; i<size; i++)
		{
			MessageBox::Show("In print loop");
			ListViewItem^ item = gcnew ListViewItem;
			converter->printItem(item, listOfTasks, i+1);
			temp[j] = item;
			j++;
		}
		this->completedListView->Items->AddRange(temp);
		loaded = true;
		this->Cursor = Cursors::Default;
		this->completedListView->EndUpdate();
	}
	catch(string error){
		this->printError(error);
	}

}
void ui_display::printOverdueList(){
	try{
		int size = listOfTasks->size();

		int j=0;
		array<ListViewItem^>^ temp;
		Array::Resize(temp, size);

		if(loaded)
		{
			this->overdueListView->Items->Clear();
		}
		if(size==0){
			throw MESSAGE_ERROR_LIST_EMPTY;
		}
		this->Cursor = Cursors::WaitCursor;

		this->overdueListView->BeginUpdate();


		for (int i=0; i<size; i++)
		{
			ListViewItem^ item = gcnew ListViewItem;
			converter->printItem(item, listOfTasks, i+1);
			temp[j] = item;
			j++;
		}
		this->overdueListView->Items->AddRange(temp);
		loaded = true;
		this->Cursor = Cursors::Default;
		this->overdueListView->EndUpdate();
	}
	catch(string error){
		this->printError(error);
	}

}

Void ui_display::textboxInput_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e){
	this->textboxInput->Enabled = true;
	this->textboxInput->Clear();
}
Void ui_display::tabContainer_Selected(System::Object^  sender, System::Windows::Forms::TabControlEventArgs^  e){
	try{
		if(this->tabContainer->SelectedIndex==1)
			activeListType=listCompleted;
		else if(this->tabContainer->SelectedIndex==2)
			activeListType=listOverdue;
		else if(this->tabContainer->SelectedIndex==0)
			activeListType=listToDo;
		else
			throw MESSAGE_ERROR_INVALID_LIST;
		execute->setListType(activeListType);
		*listOfTasks = execute->getUpdatedList(activeListType);
		this->printList();
	}
	catch(string error){
		this->printError(error);
	}
}
Void ui_display::textboxInput_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e){

	if(commandKeyword->size() < 3){
		switch(e->KeyChar){
		case 'a':
			*commandKeyword += 'a';
			break;
		case 'd':
			*commandKeyword += 'd';
			break;
		case 'e':
			*commandKeyword += 'e';
			break;
		case 'l':
			*commandKeyword += 'l';
			break;
		case 'm':
			*commandKeyword += 'm';
			break;
		case 'o':
			*commandKeyword += 'o';
			break;
		case 'r':
			*commandKeyword += 'r';
			break;
		};
	}

	if(commandKeyword->size()==3){
		array<String ^> ^  addLines ={
			"add <task description>",
			",at <venue>",
			",from <start time of timed task>",
			",to <end time of timed task>",
			",by <due time>",
			",remind on <reminder time>",
			",repeat <daily, weekly or monthly>",
			",!"
		};
		array<String ^> ^  delLines ={
			"del <task index>"
		};
		array<String ^> ^  modLines ={
			"mod <taskindex> <task description>",
			",at <venue>",
			",from <start time of timed task>",
			",to <end time of timed task>",
			",by <due time>",
			",remind on <reminder time>",
			",repeat <daily, weekly or monthly>",
			",!"
		};
		array<String ^> ^  markLines ={
			"mark <taskindex> <status>",
			" ",
			"statuses available:",
			"	done / completed",
			"	undone / incomplete"
		};
		array<String ^> ^  emptyLines ={};
		this->messageBox->Lines=emptyLines;
		if(*commandKeyword == "add"){
			this->messageBox->Lines= addLines;
		}
		else if(*commandKeyword == "del"){
			this->messageBox->Lines= delLines;
		}
		else if(*commandKeyword == "mod"){
			this->messageBox->Lines= modLines;
		}
		else if(*commandKeyword == "mar"){
			this->messageBox->Lines= markLines;
		}
	}
}
Void ui_display::ui_display_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
	if(e->Control && e->KeyCode==Keys::Tab){
		int nextPage = (this->tabContainer->SelectedIndex + 1) % 3;
		this->tabContainer->SelectedIndex = nextPage;
	}
	else if(e->KeyCode==Keys::Enter){
		this->textboxInput->Enabled = true;
	}
}