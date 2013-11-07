#include "ui_display.h"
#include <sstream>
using namespace UIDisplay;

//constructor
ui_display::ui_display(){
	execute = new Executor;
	converter = new UiConvert;
	listOfTasks = new std::list<Task*>;
	commandKeyword = new string;
	commandKeyword->clear();
	selectedItem = 0;
	loaded = false;
	up = false;
	activeListType = listToDo;
	execute->setListType(activeListType);

	InitializeComponent();
	this->printList();
	this->printHelpMessage();
}

ui_display::~ui_display(){
	if (components){
		delete components;
	}
}

void ui_display::InitializeComponent(void){
	this->components = (gcnew System::ComponentModel::Container());
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
	this->notifyIcon1 = (gcnew System::Windows::Forms::NotifyIcon(this->components));
	this->timerRefresh = (gcnew System::Windows::Forms::Timer(this->components));
	this->itemDisplayLabel = (gcnew System::Windows::Forms::Label());
	this->tabContainer->SuspendLayout();
	this->tabTodo->SuspendLayout();
	this->tabCompleted->SuspendLayout();
	this->tabOverdue->SuspendLayout();
	this->inputContainer->SuspendLayout();
	this->messageContainer->SuspendLayout();
	this->SuspendLayout();
	// 
	// tabContainer
	// 
	this->tabContainer->Controls->Add(this->tabTodo);
	this->tabContainer->Controls->Add(this->tabCompleted);
	this->tabContainer->Controls->Add(this->tabOverdue);
	this->tabContainer->Location = System::Drawing::Point(382, 173);
	this->tabContainer->Name = L"tabContainer";
	this->tabContainer->SelectedIndex = 0;
	this->tabContainer->Size = System::Drawing::Size(677, 358);
	this->tabContainer->TabIndex = 0;
	this->tabContainer->Selected += gcnew System::Windows::Forms::TabControlEventHandler(this, &ui_display::tabContainer_Selected);
	// 
	// tabTodo
	// 
	this->tabTodo->Controls->Add(this->todoListView);
	this->tabTodo->Location = System::Drawing::Point(4, 22);
	this->tabTodo->Name = L"tabTodo";
	this->tabTodo->Padding = System::Windows::Forms::Padding(3);
	this->tabTodo->Size = System::Drawing::Size(669, 332);
	this->tabTodo->TabIndex = 0;
	this->tabTodo->Text = L"To Do";
	this->tabTodo->UseVisualStyleBackColor = true;
	// 
	// todoListView
	// 
	this->todoListView->Activation = System::Windows::Forms::ItemActivation::OneClick;
	this->todoListView->AutoArrange = false;
	this->todoListView->BackColor = System::Drawing::Color::SandyBrown;
	this->todoListView->BorderStyle = System::Windows::Forms::BorderStyle::None;
	this->todoListView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(6) {this->tIndex, this->tDescription, 
		this->tVenue, this->tTime, this->tDueDate, this->tPriority});
	this->todoListView->Font = (gcnew System::Drawing::Font(L"MS Reference Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
		static_cast<System::Byte>(0)));
	this->todoListView->FullRowSelect = true;
	this->todoListView->GridLines = true;
	this->todoListView->LabelEdit = true;
	this->todoListView->Location = System::Drawing::Point(-4, 0);
	this->todoListView->Name = L"todoListView";
	this->todoListView->Size = System::Drawing::Size(677, 336);
	this->todoListView->TabIndex = 1;
	this->todoListView->UseCompatibleStateImageBehavior = false;
	this->todoListView->View = System::Windows::Forms::View::Details;
	
	// 
	// tIndex
	// 
	this->tIndex->Text = L"#";
	this->tIndex->Width = 25;
	// 
	// tDescription
	// 
	this->tDescription->Text = L"Description";
	this->tDescription->Width = 25;
	// 
	// tVenue
	// 
	this->tVenue->Text = L"Venue";
	this->tVenue->Width = 25;
	// 
	// tTime
	// 
	this->tTime->Text = L"Time";
	this->tTime->Width = 25;
	// 
	// tDueDate
	// 
	this->tDueDate->Text = L"Due Date";
	this->tDueDate->Width = 25;
	// 
	// tPriority
	// 
	this->tPriority->Text = L"Priority";
	this->tPriority->Width = 552;
	// 
	// tabCompleted
	// 
	this->tabCompleted->Controls->Add(this->completedListView);
	this->tabCompleted->Location = System::Drawing::Point(4, 22);
	this->tabCompleted->Name = L"tabCompleted";
	this->tabCompleted->Padding = System::Windows::Forms::Padding(3);
	this->tabCompleted->Size = System::Drawing::Size(669, 332);
	this->tabCompleted->TabIndex = 1;
	this->tabCompleted->Text = L"Completed";
	this->tabCompleted->UseVisualStyleBackColor = true;
	// 
	// completedListView
	// 
	this->completedListView->Activation = System::Windows::Forms::ItemActivation::OneClick;
	this->completedListView->AutoArrange = false;
	this->completedListView->BackColor = System::Drawing::Color::SandyBrown;
	this->completedListView->BorderStyle = System::Windows::Forms::BorderStyle::None;
	this->completedListView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(6) {this->cIndex, this->cDescription, 
		this->cVenue, this->cTime, this->cDueDate, this->cPriority});
	this->completedListView->Font = (gcnew System::Drawing::Font(L"MS Reference Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, 
		System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
	this->completedListView->FullRowSelect = true;
	this->completedListView->GridLines = true;
	this->completedListView->LabelEdit = true;
	this->completedListView->Location = System::Drawing::Point(-4, 0);
	this->completedListView->Name = L"completedListView";
	this->completedListView->Size = System::Drawing::Size(677, 336);
	this->completedListView->TabIndex = 2;
	this->completedListView->UseCompatibleStateImageBehavior = false;
	this->completedListView->View = System::Windows::Forms::View::Details;
	
	// 
	// cIndex
	// 
	this->cIndex->Text = L"#";
	this->cIndex->Width = 25;
	// 
	// cDescription
	// 
	this->cDescription->Text = L"Description";
	this->cDescription->Width = 160;
	// 
	// cVenue
	// 
	this->cVenue->Text = L"Venue";
	this->cVenue->Width = 79;
	// 
	// cTime
	// 
	this->cTime->Text = L"Time";
	this->cTime->Width = 172;
	// 
	// cDueDate
	// 
	this->cDueDate->Text = L"Due Date";
	this->cDueDate->Width = 171;
	// 
	// cPriority
	// 
	this->cPriority->Text = L"Priority";
	this->cPriority->Width = 81;
	// 
	// tabOverdue
	// 
	this->tabOverdue->Controls->Add(this->overdueListView);
	this->tabOverdue->Location = System::Drawing::Point(4, 22);
	this->tabOverdue->Name = L"tabOverdue";
	this->tabOverdue->Size = System::Drawing::Size(669, 332);
	this->tabOverdue->TabIndex = 2;
	this->tabOverdue->Text = L"Overdue";
	this->tabOverdue->UseVisualStyleBackColor = true;
	// 
	// overdueListView
	// 
	this->overdueListView->Activation = System::Windows::Forms::ItemActivation::OneClick;
	this->overdueListView->AutoArrange = false;
	this->overdueListView->BackColor = System::Drawing::Color::SandyBrown;
	this->overdueListView->BorderStyle = System::Windows::Forms::BorderStyle::None;
	this->overdueListView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(6) {this->oIndex, this->oDescription, 
		this->oVenue, this->oTime, this->oDueDate, this->oPriority});
	this->overdueListView->Font = (gcnew System::Drawing::Font(L"MS Reference Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, 
		System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
	this->overdueListView->FullRowSelect = true;
	this->overdueListView->GridLines = true;
	this->overdueListView->LabelEdit = true;
	this->overdueListView->Location = System::Drawing::Point(-4, 0);
	this->overdueListView->Name = L"overdueListView";
	this->overdueListView->Size = System::Drawing::Size(677, 336);
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
	this->oDescription->Width = 160;
	// 
	// oVenue
	// 
	this->oVenue->Text = L"Venue";
	this->oVenue->Width = 79;
	// 
	// oTime
	// 
	this->oTime->Text = L"Time";
	this->oTime->Width = 172;
	// 
	// oDueDate
	// 
	this->oDueDate->Text = L"Due Date";
	this->oDueDate->Width = 171;
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
	this->inputContainer->Size = System::Drawing::Size(1047, 24);
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
	this->textboxInput->Size = System::Drawing::Size(1047, 16);
	this->textboxInput->TabIndex = 1;
	this->textboxInput->Text = L"Enter Command Here";
	this->textboxInput->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &ui_display::textboxInput_MouseClick);
	this->textboxInput->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &ui_display::textboxInput_KeyDown);
	this->textboxInput->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &ui_display::textboxInput_KeyPress);
	// 
	// messageContainer
	// 
	this->messageContainer->Controls->Add(this->messageBox);
	this->messageContainer->Location = System::Drawing::Point(12, 42);
	this->messageContainer->Name = L"messageContainer";
	this->messageContainer->Size = System::Drawing::Size(1047, 125);
	this->messageContainer->TabIndex = 3;
	// 
	// messageBox
	// 
	this->messageBox->BackColor = System::Drawing::Color::IndianRed;
	this->messageBox->BorderStyle = System::Windows::Forms::BorderStyle::None;
	this->messageBox->Location = System::Drawing::Point(3, 3);
	this->messageBox->Name = L"messageBox";
	this->messageBox->ReadOnly = true;
	this->messageBox->Size = System::Drawing::Size(1044, 122);
	this->messageBox->TabIndex = 0;
	this->messageBox->Text = L"";
	// 
	// notifyIcon1
	// 
	this->notifyIcon1->Text = L"notifyIcon1";
	this->notifyIcon1->Visible = true;
	this->notifyIcon1->DoubleClick += gcnew System::EventHandler(this, &ui_display::notifyIcon1_DoubleClick);
	this->notifyIcon1->Icon = gcnew System::Drawing::Icon("favicon.ico");
	// 
	// timerRefresh
	// 
	this->timerRefresh->Enabled = true;
	this->timerRefresh->Interval = 60000;
	this->timerRefresh->Tick += gcnew System::EventHandler(this, &ui_display::timerRefresh_Tick);
	// 
	// itemDisplayLabel
	// 
	this->itemDisplayLabel->AutoSize = true;
	this->itemDisplayLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, 
		System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
	this->itemDisplayLabel->ForeColor = System::Drawing::SystemColors::ControlLightLight;
	this->itemDisplayLabel->Location = System::Drawing::Point(27, 195);
	this->itemDisplayLabel->Name = L"itemDisplayLabel";
	this->itemDisplayLabel->Size = System::Drawing::Size(0, 24);
	this->itemDisplayLabel->TabIndex = 4;
	// 
	// ui_display
	// 
	this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
	this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
	this->BackColor = System::Drawing::Color::Black;
	this->ClientSize = System::Drawing::Size(1075, 543);
	this->Controls->Add(this->itemDisplayLabel);
	this->Controls->Add(this->messageContainer);
	this->Controls->Add(this->inputContainer);
	this->Controls->Add(this->tabContainer);
	this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
	this->KeyPreview = true;
	this->MaximizeBox = false;
	this->Name = L"ui_display";
	this->Opacity = 0.95;
	this->Text = L"4get";
	this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &ui_display::ui_display_KeyDown);
	this->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &ui_display::ui_display_KeyPress);
	this->Resize += gcnew System::EventHandler(this, &ui_display::ui_display_Resize);
	this->tabContainer->ResumeLayout(false);
	this->tabTodo->ResumeLayout(false);
	this->tabCompleted->ResumeLayout(false);
	this->tabOverdue->ResumeLayout(false);
	this->inputContainer->ResumeLayout(false);
	this->inputContainer->PerformLayout();
	this->messageContainer->ResumeLayout(false);
	this->ResumeLayout(false);
	this->PerformLayout();

}

Void ui_display::timerRefresh_Tick(System::Object^  sender, System::EventArgs^  e){
	try{
		if(todoListView->Items->Count!=0){
			execute->refreshAll();
			this->printList();
		}
	}
	catch(string &error){
		this->printError(error);
	}
}

Void ui_display::notifyIcon1_DoubleClick(System::Object^  sender, System::EventArgs^  e){
	this->Show();
	this->WindowState = FormWindowState::Normal;
}
Void ui_display::ui_display_Resize(System::Object^  sender, System::EventArgs^  e){
	if(this->WindowState == FormWindowState::Minimized){
		this->notifyIcon1->Visible =true;
		this->notifyIcon1->ShowBalloonTip(500);
		this->Hide();
	}
	else if (this->WindowState == FormWindowState::Normal){
		notifyIcon1->Visible = false;
	}
}

void ui_display::printError(string error){
	String ^ error_sys_string=gcnew String(error.c_str());
	array<String ^> ^ errorLines = {error_sys_string};
	array<String ^> ^  emptyLines ={};
	this->messageBox->Lines=emptyLines;
	this->messageBox->Lines = errorLines;
}

void ui_display::passUserInput(){
	try{
		string stdCommand;
		converter->stringSysToStdConversion(this->textboxInput->Text, stdCommand);
		if(!execute->stringCollector(stdCommand)){
			throw MESSAGE_ERROR_COMMAND_QUERY;
		}
	}
	catch(string error){
		this->printError(error);
	}
}

void ui_display::printList(){
	try{
		list<Task*> taskList;
		taskList = execute->getUpdatedList(activeListType);
		*listOfTasks = taskList;
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
	catch(string &error){
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
	catch(string &error){
		this->printError(error);
	}
	this->todoListView->AutoResizeColumns(ColumnHeaderAutoResizeStyle::HeaderSize);
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
	catch(string &error){
		this->printError(error);
	}
	this->completedListView->AutoResizeColumns(ColumnHeaderAutoResizeStyle::HeaderSize);
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

	catch(string &error){
		this->printError(error);
	}
	this->overdueListView->AutoResizeColumns(ColumnHeaderAutoResizeStyle::HeaderSize);
}

Void ui_display::ui_display_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
	if(e->Control && e->KeyCode==Keys::Tab){
		int nextPage = (this->tabContainer->SelectedIndex + 1) % 3;
		this->tabContainer->SelectedIndex = nextPage;

	}
	else if(e->KeyCode == Keys::Down){
		this->focusList(activeListType);
	}
	else if(e->KeyCode == Keys::Up){
		up = true;
		this->focusList(activeListType);
		up = false;
	}
	else if(e->Alt && e->KeyCode==Keys::D4){
		if(this->WindowState == FormWindowState::Normal){
			this->WindowState = FormWindowState::Minimized;
			this->Hide();
			this->notifyIcon1->Visible = true;
		}
		else if (this->WindowState == FormWindowState::Minimized){
			this->WindowState = FormWindowState::Normal;
			this->Show();
			this->notifyIcon1->Visible = false;
		}
	}
}
Void ui_display::ui_display_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e){
	if(SetFocus(textboxInput)){
		this->textboxInput->Text = System::Convert::ToString(e->KeyChar);
		this->textboxInput->SelectionStart = 1;
		converter->stringSysToStdConversion(System::Convert::ToString(e->KeyChar), *commandKeyword); 
	}
}

//void ui_display::focusItem(){
//	switch(activeListType){
//	case listCompleted:
//		focusCompletedItem();
//		break;
//	case listOverdue:
//		focusOverdueItem();
//		break;
//	case listToDo:
//		focusToDoItem();
//		break;
//	default:
//		throw MESSAGE_ERROR_INVALID_LIST;
//	}
//}
//void ui_display::focusCompletedItem(){
//	/*if(completedListView->Items->Count > 0){
//	SetFocus(completedListView);
//	completedListView->Items[0]->Selected = true;
//	}*/
//
//	System::Object^ sender;
//	System::EventArgs^ e;
//	if(completedListView->Items->Count > 0){
//		SetFocus(completedListView);
//		if(selectedItem >= completedListView->Items->Count){
//			selectedItem--;
//		}
//		else if(selectedItem < 0){
//			selectedItem++;
//		}
//		/*stringstream ss;
//		ss << selectedItem;
//		string selectedItemstring = ss.str();
//		MessageBox::Show( gcnew System::String(selectedItemstring.c_str()));*/
//		this->completedListView->Items[selectedItem]->Selected = true;
//		this->completedListView_ItemActivate(sender, e);
//	}
//}
//void ui_display::focusOverdueItem(){
//	/*if(overdueListView->Items->Count > 0){
//	SetFocus(overdueListView);
//	overdueListView->Items[0]->Selected = true;
//	}*/
//
//	System::Object^ sender;
//	System::EventArgs^ e;
//	if(overdueListView->Items->Count > 0){
//		SetFocus(overdueListView);
//		if(selectedItem >= overdueListView->Items->Count){
//			selectedItem--;
//		}
//		else if(selectedItem < 0){
//			selectedItem++;
//		}
//		/*stringstream ss;
//		ss << selectedItem;
//		string selectedItemstring = ss.str();
//		MessageBox::Show( gcnew System::String(selectedItemstring.c_str()));*/
//		this->overdueListView->Items[selectedItem]->Selected = true;
//		this->overdueListView_ItemActivate(sender, e);
//	}
//}
//void ui_display::focusToDoItem(){
//
//
//	System::Object^ sender;
//	System::EventArgs^ e;
//	if(todoListView->Items->Count > 0){
//		SetFocus(todoListView);
//		if(selectedItem >= todoListView->Items->Count){
//			selectedItem--;
//		}
//		else if(selectedItem < 0){
//			selectedItem++;
//		}
//		/*stringstream ss;
//		ss << selectedItem;
//		string selectedItemstring = ss.str();
//		MessageBox::Show( gcnew System::String(selectedItemstring.c_str()));*/
//		this->todoListView->Items[selectedItem]->Selected = true;
//		this->todoListView_ItemActivate(sender, e);
//
//	}
//}

void ui_display::printLabel(ListViewItem^ item){
	if(item->SubItems[5]->Text == "high"){
		this->itemDisplayLabel->ForeColor = Color::OrangeRed;
	}
	else{
		this->itemDisplayLabel->ForeColor = Color::White;
	}
	//display selected item in product details
	this->itemDisplayLabel->Text = TAG_NAME;
	this->itemDisplayLabel->Text +=item->SubItems[1]->Text->ToString();
	this->itemDisplayLabel->Text += NEWLINE;
	this->itemDisplayLabel->Text += TAG_LOCATION;
	this->itemDisplayLabel->Text +=item->SubItems[2]->Text->ToString();
	this->itemDisplayLabel->Text += NEWLINE;
	this->itemDisplayLabel->Text += TAG_START_TIME;
	this->itemDisplayLabel->Text +=item->SubItems[3]->Text->ToString();
	this->itemDisplayLabel->Text += NEWLINE;
	this->itemDisplayLabel->Text += TAG_END_TIME;
	this->itemDisplayLabel->Text +=item->SubItems[4]->Text->ToString();
	this->itemDisplayLabel->Text += NEWLINE;
	this->itemDisplayLabel->Text += TAG_PRIORITY;
	this->itemDisplayLabel->Text +=item->SubItems[5]->Text->ToString();
	//}
}

//Void ui_display::todoListView_ItemActivate(System::Object^  sender, System::EventArgs^  e){
//	MessageBox::Show("todo item activate");
//	ListView::SelectedListViewItemCollection^ tasksSelected = this->todoListView->SelectedItems;
//	this->printLabel(tasksSelected[0]);
//}
//Void ui_display::completedListView_ItemActivate(System::Object^  sender, System::EventArgs^  e){
//	ListView::SelectedListViewItemCollection^ tasksSelected = this->completedListView->SelectedItems;
//	this->printLabel(tasksSelected[0]);
//}
//Void ui_display::overdueListView_ItemActivate(System::Object^  sender, System::EventArgs^  e){
//	ListView::SelectedListViewItemCollection^ tasksSelected = this->overdueListView->SelectedItems;
//	this->printLabel(tasksSelected[0]);
//}

bool ui_display::SetFocus(Control ^ control){
	if(!(control->Focused)){
		control->Focus();
		return true;
	}
	return false;
}
void ui_display::focusList(ListType activeListType){
	ListView^ list;
	switch(activeListType){
	case listToDo:
		list = todoListView;
		break;
	case listCompleted:
		list = completedListView;
		break;
	case listOverdue:
		list = overdueListView;
		break;
	}
	if(list->Items->Count == 0)
		return;
	else if(!(list->Focused))
		this->SetFocus(list);
	else if (selectedItem == 0 && up || selectedItem == list->Items->Count - 1 && !up)
		return;
	else if (selectedItem < list->Items->Count - 1 && !up || selectedItem < list->Items->Count && up){
		if(up)
			--selectedItem;
		else
			++selectedItem;
	}
	this->printLabel(list->Items[selectedItem]);
}

Void ui_display::textboxInput_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e){
	this->textboxInput->Enabled = true;
	this->textboxInput->Clear();
}
Void ui_display::tabContainer_Selected(System::Object^  sender, System::Windows::Forms::TabControlEventArgs^  e){
	try{
		selectedItem=0;
		if(this->tabContainer->SelectedIndex==1){
			activeListType=listCompleted;
		}
		else if(this->tabContainer->SelectedIndex==2){
			activeListType=listOverdue;
		}
		else if(this->tabContainer->SelectedIndex==0){
			activeListType=listToDo;
		}
		else
			throw MESSAGE_ERROR_INVALID_LIST;
		execute->setListType(activeListType);
		*listOfTasks = execute->getUpdatedList(activeListType);
		this->printList();
		this->focusList(activeListType);
	}
	catch(string &error){
		this->printError(error);
	}
}
Void ui_display::textboxInput_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e){
	if(commandKeyword->size() < 3 ){
		//MessageBox::Show("keypress inside");
		commandKeyword->clear();
		converter->stringSysToStdConversion(this->textboxInput->Text, *commandKeyword);
		if(iswalpha(e->KeyChar)){
			commandKeyword->push_back((char)e->KeyChar);
			//MessageBox::Show("alpha keypress");
		}
	}
	this->checkInput();
}
Void ui_display::textboxInput_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e){

	try{
		if(e->KeyCode == Keys::Enter){
			commandKeyword->clear();
			this->printHelpMessage();
			//if(!this->textboxInput->Text->Empty)
			this->passUserInput();
			this->textboxInput->Clear();
			this->printList();
		}
		else if(e->KeyCode == Keys::Back){

			if(this->textboxInput->Text->Length <= 1){
				this->printHelpMessage();

			}
			else{
				commandKeyword->clear();
				converter->stringSysToStdConversion(this->textboxInput->Text, *commandKeyword);
				if(commandKeyword->empty()){
					throw MESSAGE_ERROR_EMPTY_INPUT;
				}
				commandKeyword->pop_back();
				this->checkInput();
			}

		}
		/*else if(e->KeyCode == Keys::Down || e->KeyCode == Keys::Up){
		focusItem();
		}*/
	}
	catch(string &error){
		this->printError(error);
	}
}

Void ui_display::checkInput(){
	if(commandKeyword->size()==3){
		/*array<String ^> ^  emptyLines ={};
		this->messageBox->Lines=emptyLines;*/
		//MessageBox::Show("check input");
		if(*commandKeyword == "add" || *commandKeyword == "cre"){
			this->printAddMessage();
		}
		else if(*commandKeyword == "del" || *commandKeyword == "rem"){
			this->printDelMessage();
		}
		else if(*commandKeyword == "mod"){
			this->printModMessage();
		}
		else if(*commandKeyword == "mar"){
			this->printMarMessage();
		}
	}
	else return;
}
Void ui_display::printAddMessage(){
	array<String ^> ^  addLines ={
		COMMAND_ADD_HELP,
		COMMAND_ADD_HELP_LOCATION,
		COMMAND_ADD_HELP_START,
		COMMAND_ADD_HELP_END,
		COMMAND_ADD_HELP_DUE,
		COMMAND_ADD_HELP_REMIND,
		COMMAND_ADD_HELP_PRIORITY
	};
	this->messageBox->Lines= addLines;
}
Void ui_display::printDelMessage(){
	array<String ^> ^  delLines ={
		COMMAND_DEL_HELP,
		COMMAND_DEL_HELP_MULTIPLE
	};
	this->messageBox->Lines= delLines;
}
Void ui_display::printModMessage(){
	array<String ^> ^  modLines ={
		COMMAND_MOD_HELP,
		COMMAND_MOD_HELP_LOCATION,
		COMMAND_MOD_HELP_START,
		COMMAND_MOD_HELP_END,
		COMMAND_MOD_HELP_DUE,
		COMMAND_MOD_HELP_REMIND,
		COMMAND_MOD_HELP_PRIORITY
	};
	this->messageBox->Lines= modLines;
}
Void ui_display::printMarMessage(){
	array<String ^> ^  markLines ={
		COMMAND_MARK_HELP,
		COMMAND_MARK_HELP_MULTIPLE
	};
	this->messageBox->Lines = markLines;
}
Void ui_display::printHelpMessage(){
	array<String ^> ^  helpLines = {
		MESSAGE_HELP_ADD,
		MESSAGE_HELP_DEL,
		MESSAGE_HELP_MOD,
		MESSAGE_HELP_MARK,
		MESSAGE_HELP_SEARCH
	};
	this->messageBox->Lines = helpLines;
}
