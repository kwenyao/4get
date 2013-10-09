#include "ui_display.h"
using namespace UIDisplay;

//constructor
ui_display::ui_display(){
	execute = new Executor;
	converter = new UiConvert;
	listOfTasks = new std::list<Task>;
	loaded = false;

	InitializeComponent();
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
	this->columnHeader1 = (gcnew System::Windows::Forms::ColumnHeader());
	this->columnHeader2 = (gcnew System::Windows::Forms::ColumnHeader());
	this->columnHeader3 = (gcnew System::Windows::Forms::ColumnHeader());
	this->columnHeader4 = (gcnew System::Windows::Forms::ColumnHeader());
	this->columnHeader5 = (gcnew System::Windows::Forms::ColumnHeader());
	this->columnHeader6 = (gcnew System::Windows::Forms::ColumnHeader());
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
	this->floatingListView = (gcnew System::Windows::Forms::ListView());
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
	this->todoListView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(6) {this->columnHeader1, 
		this->columnHeader2, this->columnHeader3, this->columnHeader4, this->columnHeader5, this->columnHeader6});
	this->todoListView->FullRowSelect = true;
	this->todoListView->GridLines = true;
	this->todoListView->Location = System::Drawing::Point(-4, -4);
	this->todoListView->Name = L"todoListView";
	this->todoListView->Size = System::Drawing::Size(440, 259);
	this->todoListView->TabIndex = 2;
	this->todoListView->UseCompatibleStateImageBehavior = false;
	this->todoListView->View = System::Windows::Forms::View::Details;
	// 
	// columnHeader1
	// 
	this->columnHeader1->Text = L"Index No.";
	// 
	// columnHeader2
	// 
	this->columnHeader2->Text = L"Description";
	this->columnHeader2->Width = 127;
	// 
	// columnHeader3
	// 
	this->columnHeader3->Text = L"Venue";
	// 
	// columnHeader4
	// 
	this->columnHeader4->Text = L"Time";
	// 
	// columnHeader5
	// 
	this->columnHeader5->Text = L"Due Date";
	this->columnHeader5->Width = 80;
	// 
	// columnHeader6
	// 
	this->columnHeader6->Text = L"Priority";
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
	this->completedListView->Location = System::Drawing::Point(-4, -4);
	this->completedListView->Name = L"completedListView";
	this->completedListView->Size = System::Drawing::Size(440, 259);
	this->completedListView->TabIndex = 1;
	this->completedListView->UseCompatibleStateImageBehavior = false;
	this->completedListView->View = System::Windows::Forms::View::Details;
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
	this->overdueListView->Size = System::Drawing::Size(440, 259);
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
	this->tabFloat->Controls->Add(this->floatingListView);
	this->tabFloat->Location = System::Drawing::Point(4, 22);
	this->tabFloat->Name = L"tabFloat";
	this->tabFloat->Size = System::Drawing::Size(434, 255);
	this->tabFloat->TabIndex = 3;
	this->tabFloat->Text = L"Floating";
	this->tabFloat->UseVisualStyleBackColor = true;
	// 
	// floatingListView
	// 
	this->floatingListView->Activation = System::Windows::Forms::ItemActivation::OneClick;
	this->floatingListView->AutoArrange = false;
	this->floatingListView->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
	this->floatingListView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(6) {this->fTaskIndex, 
		this->fTaskDescription, this->fTaskVenue, this->fTaskTime, this->fTaskDate, this->fTaskPriority});
	this->floatingListView->FullRowSelect = true;
	this->floatingListView->GridLines = true;
	this->floatingListView->Location = System::Drawing::Point(-4, -4);
	this->floatingListView->Name = L"floatingListView";
	this->floatingListView->Size = System::Drawing::Size(440, 259);
	this->floatingListView->TabIndex = 2;
	this->floatingListView->UseCompatibleStateImageBehavior = false;
	this->floatingListView->View = System::Windows::Forms::View::Details;
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
	this->inputContainer->Size = System::Drawing::Size(800, 30);
	this->inputContainer->TabIndex = 2;
	// 
	// textboxInput
	// 
	this->textboxInput->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
		static_cast<System::Byte>(0)));
	this->textboxInput->Location = System::Drawing::Point(3, 3);
	this->textboxInput->Name = L"textboxInput";
	this->textboxInput->Size = System::Drawing::Size(793, 22);
	this->textboxInput->TabIndex = 1;
	this->textboxInput->Text = L"Enter Command Here";
	this->textboxInput->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &ui_display::textboxInput_MouseClick);
	this->textboxInput->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &ui_display::textboxInput_KeyDown);
	// 
	// messageContainer
	// 
	this->messageContainer->Controls->Add(this->richTextBox1);
	this->messageContainer->Location = System::Drawing::Point(12, 48);
	this->messageContainer->Name = L"messageContainer";
	this->messageContainer->Size = System::Drawing::Size(800, 119);
	this->messageContainer->TabIndex = 3;
	// 
	// richTextBox1
	// 
	this->richTextBox1->BackColor = System::Drawing::SystemColors::InactiveCaption;
	this->richTextBox1->Location = System::Drawing::Point(3, 3);
	this->richTextBox1->Name = L"richTextBox1";
	this->richTextBox1->ReadOnly = true;
	this->richTextBox1->Size = System::Drawing::Size(793, 116);
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
	this->checkedTaskList->Location = System::Drawing::Point(-3, 42);
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

void ui_display::loadList(){
	/*list = execute->load();*/
	this->printList();
}

void ui_display::passUserInput(){
	string stdCommand;
	converter->stringSysToStdConversion(this->textboxInput->Text, stdCommand);
	execute->stringCollector(stdCommand);

}

Void ui_display::textboxInput_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e){
	if(e->KeyCode == Keys::Enter)
	{
		this->passUserInput();
		this->textboxInput->Text->Replace(this->textboxInput->Text,"Enter Command Here:");
		MessageBox::Show("Enter pressed");
		listOfTasks = execute->getUpdatedList();
		MessageBox::Show(System::Convert::ToString(1));
		printList();
	}
}

void ui_display::printList(){
	int size = listOfTasks->size();
	int j=0;
	array<ListViewItem^>^ temp;
	Array::Resize(temp, 1000000);

	if(size==0){
		MessageBox::Show("List is empty");
		return;
	}
	this->Cursor = Cursors::WaitCursor;

	this->todoListView->BeginUpdate();
	if(loaded)
	{
		this->todoListView->Items->Clear();
	}

	for (int i=0; i<size; i++)
	{
		MessageBox::Show("In print loop");
		ListViewItem^item = gcnew ListViewItem;
		converter->printItem(item, listOfTasks);
		temp[j] = item;
		j++;
	}
	this->todoListView->Items->AddRange(temp);
	loaded = true;
	this->Cursor = Cursors::Default;
	this->todoListView->EndUpdate();

}

Void ui_display::textboxInput_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e){
	if(e->KeyChar.ToString() == Keys::F1.ToString() )
	{
		MessageBox::Show("Alt pressed");
		array<ListViewItem^>^ temp;

		this->Cursor = Cursors::WaitCursor;

		this->todoListView->BeginUpdate();
		if(loaded)
		{
			this->todoListView->Items->Clear();
		}
		System::Windows::Forms::ListViewItem^ item;
		System::String^ sys_index = "1";
		System::String^ sys_desc = "description";
		System::String^ sys_venue = "location";
		System::String^ sys_time = "1200"; //time
		System::String^ sys_due = "05-10-2013"; //due
		System::String^ sys_priority = "high"; //priority
		item->BeginEdit();

		//item->SubItems[0]->Text = sys_index;

		//creating item for listview
		item->SubItems->Add(sys_index);
		item->SubItems->Add(sys_desc); //add description
		item->SubItems->Add(sys_venue); //add venue	 
		item->SubItems->Add(sys_time); //add time
		item->SubItems->Add(sys_due); //add due
		item->SubItems->Add(sys_priority); //add priority

		temp[0] = item;
		this->todoListView->Items->AddRange(temp);
		loaded = true;
		this->Cursor = Cursors::Default;
		this->todoListView->EndUpdate();
	}
}

Void ui_display::textboxInput_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e){
	this->textboxInput->Clear();
}