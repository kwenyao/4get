#include "ui_display.h"
#include <sstream>
using namespace UIDisplay;
//constructor
UiDisplay::UiDisplay(){
	execute = new Executor;
	converter = new UiConvert;
	listOfTasks = new std::list<Task*>;
	commandKeyword = new string;
	commandKeyword->clear();
	selectedItem = LEAST_INDEX;
	loaded = INITIALISE_BOOLEAN;
	up = INITIALISE_BOOLEAN;
	activeListType = INITIALISE_LIST_TYPE;
	execute->setListType(activeListType);

	InitializeComponent();
	this->printList();
	this->printHelpMessage();
	this->todoListView->AutoResizeColumns(ColumnHeaderAutoResizeStyle::HeaderSize);
	this->overdueListView->AutoResizeColumns(ColumnHeaderAutoResizeStyle::HeaderSize);
	this->completedListView->AutoResizeColumns(ColumnHeaderAutoResizeStyle::HeaderSize);
}

UiDisplay::~UiDisplay(){
	if (components){
		delete components;
	}
}

void UiDisplay::InitializeComponent(void){
	this->components = (gcnew System::ComponentModel::Container());
	System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(UiDisplay::typeid));
	this->tabContainer = (gcnew System::Windows::Forms::TabControl());
	this->tabTodo = (gcnew System::Windows::Forms::TabPage());
	this->todoListView = (gcnew System::Windows::Forms::ListView());
	this->tIndex = (gcnew System::Windows::Forms::ColumnHeader());
	this->tDescription = (gcnew System::Windows::Forms::ColumnHeader());
	this->tStartTime = (gcnew System::Windows::Forms::ColumnHeader());
	this->tDueDate = (gcnew System::Windows::Forms::ColumnHeader());
	this->tabCompleted = (gcnew System::Windows::Forms::TabPage());
	this->completedListView = (gcnew System::Windows::Forms::ListView());
	this->cIndex = (gcnew System::Windows::Forms::ColumnHeader());
	this->cDescription = (gcnew System::Windows::Forms::ColumnHeader());
	this->cStartTime = (gcnew System::Windows::Forms::ColumnHeader());
	this->cDueDate = (gcnew System::Windows::Forms::ColumnHeader());
	this->tabOverdue = (gcnew System::Windows::Forms::TabPage());
	this->overdueListView = (gcnew System::Windows::Forms::ListView());
	this->oIndex = (gcnew System::Windows::Forms::ColumnHeader());
	this->oDescription = (gcnew System::Windows::Forms::ColumnHeader());
	this->oStartTime = (gcnew System::Windows::Forms::ColumnHeader());
	this->oDueDate = (gcnew System::Windows::Forms::ColumnHeader());
	this->textboxInput = (gcnew System::Windows::Forms::TextBox());
	this->notifyIcon1 = (gcnew System::Windows::Forms::NotifyIcon(this->components));
	this->timerRefresh = (gcnew System::Windows::Forms::Timer(this->components));
	this->messageBox = (gcnew System::Windows::Forms::RichTextBox());
	this->labelContainer = (gcnew System::Windows::Forms::GroupBox());
	this->labelTaskType = (gcnew System::Windows::Forms::Label());
	this->labelTaskRepeat = (gcnew System::Windows::Forms::Label());
	this->labelTagTaskType = (gcnew System::Windows::Forms::Label());
	this->labelTagRepeat = (gcnew System::Windows::Forms::Label());
	this->labelTaskPriority = (gcnew System::Windows::Forms::Label());
	this->labelTaskEndTime = (gcnew System::Windows::Forms::Label());
	this->labelTaskStartTime = (gcnew System::Windows::Forms::Label());
	this->labelTaskVenue = (gcnew System::Windows::Forms::Label());
	this->labelTaskDesc = (gcnew System::Windows::Forms::Label());
	this->labelTagPriority = (gcnew System::Windows::Forms::Label());
	this->labelTagEndTime = (gcnew System::Windows::Forms::Label());
	this->labelTagStartTime = (gcnew System::Windows::Forms::Label());
	this->labelTagVenue = (gcnew System::Windows::Forms::Label());
	this->labelTagDesc = (gcnew System::Windows::Forms::Label());
	this->tabContainer->SuspendLayout();
	this->tabTodo->SuspendLayout();
	this->tabCompleted->SuspendLayout();
	this->tabOverdue->SuspendLayout();
	this->labelContainer->SuspendLayout();
	this->SuspendLayout();
	// 
	// UiDisplay
	// 
	this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
	this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
	this->BackColor = System::Drawing::Color::Black;
	this->ClientSize = System::Drawing::Size(1075, 572);
	this->Controls->Add(this->labelContainer);
	this->Controls->Add(this->textboxInput);
	this->Controls->Add(this->messageBox);
	this->Controls->Add(this->tabContainer);
	this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
	this->KeyPreview = true;
	this->MaximizeBox = false;
	this->Name = L"UiDisplay";
	this->Opacity = 0.95;
	this->Text = L"4get";
	this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &UiDisplay::UiDisplay_KeyDown);
	this->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &UiDisplay::UiDisplay_KeyPress);
	this->tabContainer->ResumeLayout(false);
	this->tabTodo->ResumeLayout(false);
	this->tabCompleted->ResumeLayout(false);
	this->tabOverdue->ResumeLayout(false);
	this->labelContainer->ResumeLayout(false);
	this->labelContainer->PerformLayout();
	this->ResumeLayout(false);
	this->PerformLayout();
	// 
	// tabContainer
	// 
	this->tabContainer->Controls->Add(this->tabTodo);
	this->tabContainer->Controls->Add(this->tabCompleted);
	this->tabContainer->Controls->Add(this->tabOverdue);
	this->tabContainer->Location = System::Drawing::Point(392, 34);
	this->tabContainer->Name = L"tabContainer";
	this->tabContainer->SelectedIndex = 0;
	this->tabContainer->Size = System::Drawing::Size(670, 330);
	this->tabContainer->TabIndex = 0;
	this->tabContainer->Selected += gcnew System::Windows::Forms::TabControlEventHandler(this, &UiDisplay::tabContainer_Selected);
	// 
	// tabTodo
	// 
	this->tabTodo->Controls->Add(this->todoListView);
	this->tabTodo->Location = System::Drawing::Point(4, 22);
	this->tabTodo->Name = L"tabTodo";
	this->tabTodo->Padding = System::Windows::Forms::Padding(3);
	this->tabTodo->Size = System::Drawing::Size(662, 304);
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
	this->todoListView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(4) {this->tIndex, this->tDescription, 
		this->tStartTime, this->tDueDate});
	this->todoListView->Font = (gcnew System::Drawing::Font(L"MS Reference Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
		static_cast<System::Byte>(0)));
	this->todoListView->FullRowSelect = true;
	this->todoListView->GridLines = true;
	this->todoListView->LabelEdit = true;
	this->todoListView->Location = System::Drawing::Point(-4, 0);
	this->todoListView->Name = L"todoListView";
	this->todoListView->Size = System::Drawing::Size(670, 308);
	this->todoListView->TabIndex = 1;
	this->todoListView->UseCompatibleStateImageBehavior = false;
	this->todoListView->View = System::Windows::Forms::View::Details;
	this->todoListView->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &UiDisplay::todoListView_MouseClick);
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
	// tStartTime
	// 
	this->tStartTime->Text = L"Start Time";
	this->tStartTime->Width = 25;
	// 
	// tDueDate
	// 
	this->tDueDate->Text = L"Due Date";
	this->tDueDate->Width = 25;
	// 
	// tabCompleted
	// 
	this->tabCompleted->Controls->Add(this->completedListView);
	this->tabCompleted->Location = System::Drawing::Point(4, 22);
	this->tabCompleted->Name = L"tabCompleted";
	this->tabCompleted->Padding = System::Windows::Forms::Padding(3);
	this->tabCompleted->Size = System::Drawing::Size(662, 304);
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
	this->completedListView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(4) {this->cIndex, this->cDescription, 
		this->cStartTime, this->cDueDate});
	this->completedListView->Font = (gcnew System::Drawing::Font(L"MS Reference Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, 
		System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
	this->completedListView->FullRowSelect = true;
	this->completedListView->GridLines = true;
	this->completedListView->LabelEdit = true;
	this->completedListView->Location = System::Drawing::Point(-4, 0);
	this->completedListView->Name = L"completedListView";
	this->completedListView->Size = System::Drawing::Size(677, 303);
	this->completedListView->TabIndex = 2;
	this->completedListView->UseCompatibleStateImageBehavior = false;
	this->completedListView->View = System::Windows::Forms::View::Details;
	this->completedListView->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &UiDisplay::completedListView_MouseClick);
	// 
	// cIndex
	// 
	this->cIndex->Text = L"#";
	this->cIndex->Width = 25;
	// 
	// cDescription
	// 
	this->cDescription->Text = L"Description";
	this->cDescription->Width = 25;
	// 
	// cStartTime
	// 
	this->cStartTime->Text = L"Start Time";
	this->cStartTime->Width = 25;
	// 
	// cDueDate
	// 
	this->cDueDate->Text = L"Due Date";
	this->cDueDate->Width = 25;
	// 
	// tabOverdue
	// 
	this->tabOverdue->Controls->Add(this->overdueListView);
	this->tabOverdue->Location = System::Drawing::Point(4, 22);
	this->tabOverdue->Name = L"tabOverdue";
	this->tabOverdue->Size = System::Drawing::Size(662, 304);
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
	this->overdueListView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(4) {this->oIndex, this->oDescription, 
		this->oStartTime, this->oDueDate});
	this->overdueListView->Font = (gcnew System::Drawing::Font(L"MS Reference Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, 
		System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
	this->overdueListView->FullRowSelect = true;
	this->overdueListView->GridLines = true;
	this->overdueListView->LabelEdit = true;
	this->overdueListView->Location = System::Drawing::Point(-4, 0);
	this->overdueListView->Name = L"overdueListView";
	this->overdueListView->Size = System::Drawing::Size(677, 303);
	this->overdueListView->TabIndex = 2;
	this->overdueListView->UseCompatibleStateImageBehavior = false;
	this->overdueListView->View = System::Windows::Forms::View::Details;
	this->overdueListView->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &UiDisplay::overdueListView_MouseClick);
	// 
	// oIndex
	// 
	this->oIndex->Text = L"#";
	this->oIndex->Width = 25;
	// 
	// oDescription
	// 
	this->oDescription->Text = L"Description";
	this->oDescription->Width = 25;
	// 
	// oStartTime
	// 
	this->oStartTime->Text = L"Start Time";
	this->oStartTime->Width = 25;
	// 
	// oDueDate
	// 
	this->oDueDate->Text = L"Due Date";
	this->oDueDate->Width = 25;
	// 
	// textboxInput
	// 
	this->textboxInput->BackColor = System::Drawing::Color::DarkCyan;
	this->textboxInput->BorderStyle = System::Windows::Forms::BorderStyle::None;
	this->textboxInput->Font = (gcnew System::Drawing::Font(L"MS Reference Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
		static_cast<System::Byte>(0)));
	this->textboxInput->ForeColor = System::Drawing::SystemColors::Info;
	this->textboxInput->Location = System::Drawing::Point(15, 12);
	this->textboxInput->Name = L"textboxInput";
	this->textboxInput->Size = System::Drawing::Size(1047, 16);
	this->textboxInput->TabIndex = 1;
	this->textboxInput->Text = L"Enter Command Here";
	this->textboxInput->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &UiDisplay::textboxInput_MouseClick);
	this->textboxInput->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &UiDisplay::textboxInput_KeyDown);
	this->textboxInput->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &UiDisplay::textboxInput_KeyPress);
	// 
	// notifyIcon1
	// 
	this->notifyIcon1->Text = L"notifyIcon1";
	this->notifyIcon1->Visible = true;
	// 
	// timerRefresh
	// 
	this->timerRefresh->Enabled = true;
	this->timerRefresh->Interval = 60000;
	this->timerRefresh->Tick += gcnew System::EventHandler(this, &UiDisplay::timerRefresh_Tick);
	// 
	// messageBox
	// 
	this->messageBox->BackColor = System::Drawing::Color::IndianRed;
	this->messageBox->BorderStyle = System::Windows::Forms::BorderStyle::None;
	this->messageBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
		static_cast<System::Byte>(0)));
	this->messageBox->Location = System::Drawing::Point(15, 34);
	this->messageBox->Name = L"messageBox";
	this->messageBox->ReadOnly = true;
	this->messageBox->Size = System::Drawing::Size(361, 526);
	this->messageBox->TabIndex = 0;
	this->messageBox->Text = L"";
	// 
	// labelContainer
	// 
	this->labelContainer->Controls->Add(this->labelTaskType);
	this->labelContainer->Controls->Add(this->labelTaskRepeat);
	this->labelContainer->Controls->Add(this->labelTagTaskType);
	this->labelContainer->Controls->Add(this->labelTagRepeat);
	this->labelContainer->Controls->Add(this->labelTaskPriority);
	this->labelContainer->Controls->Add(this->labelTaskEndTime);
	this->labelContainer->Controls->Add(this->labelTaskStartTime);
	this->labelContainer->Controls->Add(this->labelTaskVenue);
	this->labelContainer->Controls->Add(this->labelTaskDesc);
	this->labelContainer->Controls->Add(this->labelTagPriority);
	this->labelContainer->Controls->Add(this->labelTagEndTime);
	this->labelContainer->Controls->Add(this->labelTagStartTime);
	this->labelContainer->Controls->Add(this->labelTagVenue);
	this->labelContainer->Controls->Add(this->labelTagDesc);
	this->labelContainer->ForeColor = System::Drawing::SystemColors::ControlDark;
	this->labelContainer->Location = System::Drawing::Point(392, 370);
	this->labelContainer->Name = L"labelContainer";
	this->labelContainer->Size = System::Drawing::Size(670, 190);
	this->labelContainer->TabIndex = 2;
	this->labelContainer->TabStop = false;
	this->labelContainer->Text = L"Task Details";
	// 
	// labelTaskType
	// 
	this->labelTaskType->AutoSize = true;
	this->labelTaskType->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
		static_cast<System::Byte>(0)));
	this->labelTaskType->ForeColor = System::Drawing::SystemColors::ControlLightLight;
	this->labelTaskType->Location = System::Drawing::Point(483, 122);
	this->labelTaskType->Name = L"labelTaskType";
	this->labelTaskType->Size = System::Drawing::Size(0, 18);
	this->labelTaskType->TabIndex = 13;
	// 
	// labelTaskRepeat
	// 
	this->labelTaskRepeat->AutoSize = true;
	this->labelTaskRepeat->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, 
		System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
	this->labelTaskRepeat->ForeColor = System::Drawing::SystemColors::ControlLightLight;
	this->labelTaskRepeat->Location = System::Drawing::Point(483, 86);
	this->labelTaskRepeat->Name = L"labelTaskRepeat";
	this->labelTaskRepeat->Size = System::Drawing::Size(0, 18);
	this->labelTaskRepeat->TabIndex = 12;
	// 
	// labelTagTaskType
	// 
	this->labelTagTaskType->AutoSize = true;
	this->labelTagTaskType->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
		static_cast<System::Byte>(0)));
	this->labelTagTaskType->ForeColor = System::Drawing::SystemColors::Control;
	this->labelTagTaskType->Location = System::Drawing::Point(386, 122);
	this->labelTagTaskType->Name = L"labelTagTaskType";
	this->labelTagTaskType->Size = System::Drawing::Size(91, 18);
	this->labelTagTaskType->TabIndex = 11;
	this->labelTagTaskType->Text = L"Task Type:";
	// 
	// labelTagRepeat
	// 
	this->labelTagRepeat->AutoSize = true;
	this->labelTagRepeat->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
		static_cast<System::Byte>(0)));
	this->labelTagRepeat->ForeColor = System::Drawing::SystemColors::Control;
	this->labelTagRepeat->Location = System::Drawing::Point(411, 86);
	this->labelTagRepeat->Name = L"labelTagRepeat";
	this->labelTagRepeat->Size = System::Drawing::Size(66, 18);
	this->labelTagRepeat->TabIndex = 10;
	this->labelTagRepeat->Text = L"Repeat:";
	// 
	// labelTaskPriority
	// 
	this->labelTaskPriority->AutoSize = true;
	this->labelTaskPriority->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, 
		System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
	this->labelTaskPriority->ForeColor = System::Drawing::SystemColors::ControlLightLight;
	this->labelTaskPriority->Location = System::Drawing::Point(122, 156);
	this->labelTaskPriority->Name = L"labelTaskPriority";
	this->labelTaskPriority->Size = System::Drawing::Size(0, 18);
	this->labelTaskPriority->TabIndex = 9;
	// 
	// labelTaskEndTime
	// 
	this->labelTaskEndTime->AutoSize = true;
	this->labelTaskEndTime->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, 
		System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
	this->labelTaskEndTime->ForeColor = System::Drawing::SystemColors::ControlLightLight;
	this->labelTaskEndTime->Location = System::Drawing::Point(122, 122);
	this->labelTaskEndTime->Name = L"labelTaskEndTime";
	this->labelTaskEndTime->Size = System::Drawing::Size(0, 18);
	this->labelTaskEndTime->TabIndex = 8;
	// 
	// labelTaskStartTime
	// 
	this->labelTaskStartTime->AutoSize = true;
	this->labelTaskStartTime->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, 
		System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
	this->labelTaskStartTime->ForeColor = System::Drawing::SystemColors::ControlLightLight;
	this->labelTaskStartTime->Location = System::Drawing::Point(122, 86);
	this->labelTaskStartTime->Name = L"labelTaskStartTime";
	this->labelTaskStartTime->Size = System::Drawing::Size(0, 18);
	this->labelTaskStartTime->TabIndex = 7;
	// 
	// labelTaskVenue
	// 
	this->labelTaskVenue->AutoSize = true;
	this->labelTaskVenue->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
		static_cast<System::Byte>(0)));
	this->labelTaskVenue->ForeColor = System::Drawing::SystemColors::ControlLightLight;
	this->labelTaskVenue->Location = System::Drawing::Point(122, 52);
	this->labelTaskVenue->Name = L"labelTaskVenue";
	this->labelTaskVenue->Size = System::Drawing::Size(0, 18);
	this->labelTaskVenue->TabIndex = 6;
	// 
	// labelTaskDesc
	// 
	this->labelTaskDesc->AutoSize = true;
	this->labelTaskDesc->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
		static_cast<System::Byte>(0)));
	this->labelTaskDesc->ForeColor = System::Drawing::SystemColors::ControlLightLight;
	this->labelTaskDesc->Location = System::Drawing::Point(122, 20);
	this->labelTaskDesc->Name = L"labelTaskDesc";
	this->labelTaskDesc->Size = System::Drawing::Size(0, 18);
	this->labelTaskDesc->TabIndex = 5;
	// 
	// labelTagPriority
	// 
	this->labelTagPriority->AutoSize = true;
	this->labelTagPriority->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
		static_cast<System::Byte>(0)));
	this->labelTagPriority->ForeColor = System::Drawing::SystemColors::Control;
	this->labelTagPriority->Location = System::Drawing::Point(49, 156);
	this->labelTagPriority->Name = L"labelTagPriority";
	this->labelTagPriority->Size = System::Drawing::Size(67, 18);
	this->labelTagPriority->TabIndex = 4;
	this->labelTagPriority->Text = L"Priority:";
	// 
	// labelTagEndTime
	// 
	this->labelTagEndTime->AutoSize = true;
	this->labelTagEndTime->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
		static_cast<System::Byte>(0)));
	this->labelTagEndTime->ForeColor = System::Drawing::SystemColors::Control;
	this->labelTagEndTime->Location = System::Drawing::Point(32, 122);
	this->labelTagEndTime->Name = L"labelTagEndTime";
	this->labelTagEndTime->Size = System::Drawing::Size(84, 18);
	this->labelTagEndTime->TabIndex = 3;
	this->labelTagEndTime->Text = L"End Time:";
	// 
	// labelTagStartTime
	// 
	this->labelTagStartTime->AutoSize = true;
	this->labelTagStartTime->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
		static_cast<System::Byte>(0)));
	this->labelTagStartTime->ForeColor = System::Drawing::SystemColors::Control;
	this->labelTagStartTime->Location = System::Drawing::Point(25, 86);
	this->labelTagStartTime->Name = L"labelTagStartTime";
	this->labelTagStartTime->Size = System::Drawing::Size(91, 18);
	this->labelTagStartTime->TabIndex = 2;
	this->labelTagStartTime->Text = L"Start Time:";
	// 
	// labelTagVenue
	// 
	this->labelTagVenue->AutoSize = true;
	this->labelTagVenue->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
		static_cast<System::Byte>(0)));
	this->labelTagVenue->ForeColor = System::Drawing::SystemColors::Control;
	this->labelTagVenue->Location = System::Drawing::Point(57, 52);
	this->labelTagVenue->Name = L"labelTagVenue";
	this->labelTagVenue->Size = System::Drawing::Size(59, 18);
	this->labelTagVenue->TabIndex = 1;
	this->labelTagVenue->Text = L"Venue:";
	// 
	// labelTagDesc
	// 
	this->labelTagDesc->AutoSize = true;
	this->labelTagDesc->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
		static_cast<System::Byte>(0)));
	this->labelTagDesc->ForeColor = System::Drawing::SystemColors::Control;
	this->labelTagDesc->Location = System::Drawing::Point(17, 20);
	this->labelTagDesc->Name = L"labelTagDesc";
	this->labelTagDesc->Size = System::Drawing::Size(99, 18);
	this->labelTagDesc->TabIndex = 0;
	this->labelTagDesc->Text = L"Description:";
	

}

Void UiDisplay::timerRefresh_Tick(System::Object^  sender, System::EventArgs^  e){
	try{
		if(todoListView->Items->Count!=EMPTY_LIST_COUNT){
			execute->refreshAll();
			this->printList();
		}
	}
	catch(string &error){
		this->printError(error);
	}
}

void UiDisplay::printError(string error){
	String ^ error_sys_string;
	converter->stringStdToSysConversion(error_sys_string, error);
	array<String ^> ^ errorLines = {error_sys_string};
	this->messageBox->Lines = errorLines;
}
void UiDisplay::checkIfExit(String^ userInput){
	userInput = userInput->ToLower();
	if(userInput == COMMAND_EXIT || userInput == COMMAND_QUIT){
		Application::Exit();
	}
}
void UiDisplay::passUserInput(){
	try{
		string stdCommand;
		this->checkIfExit(this->textboxInput->Text);
		converter->stringSysToStdConversion(this->textboxInput->Text, stdCommand);
		if(!execute->processInput(stdCommand)){
			throw MESSAGE_ERROR_COMMAND_QUERY;
		}
	}
	catch(string error){
		this->printError(error);
	}
}

void UiDisplay::printList(){
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
		}
	}
	catch(string error){
		printError(error);
	}
}
void UiDisplay::printToDoList(){
	try{
		int size = listOfTasks->size();
		int j = INITIALISE_INT_ZERO;
		array<ListViewItem^>^ temp;
		Array::Resize(temp, size);
		if(loaded)
		{
			this->todoListView->Items->Clear();
		}
		if(size==EMPTY_LIST_COUNT){
			return;
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
void UiDisplay::printCompletedList(){
	try{
		int size = listOfTasks->size();

		int j=INITIALISE_INT_ZERO;
		array<ListViewItem^>^ temp;
		Array::Resize(temp, size);

		if(loaded)
		{
			this->completedListView->Items->Clear();
		}
		if(size==EMPTY_LIST_COUNT){
			return;
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
void UiDisplay::printOverdueList(){
	try{
		int size = listOfTasks->size();

		int j=INITIALISE_INT_ZERO;
		array<ListViewItem^>^ temp;
		Array::Resize(temp, size);

		if(loaded)
		{
			this->overdueListView->Items->Clear();
		}
		if(size==EMPTY_LIST_COUNT){
			return;
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

Void UiDisplay::UiDisplay_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
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
Void UiDisplay::UiDisplay_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e){
	if(SetFocus(textboxInput)){
		this->textboxInput->Text = System::Convert::ToString(e->KeyChar);
		this->textboxInput->SelectionStart = POSITION_AFTER_FIRST_CHAR;
		converter->stringSysToStdConversion(this->textboxInput->Text, *commandKeyword); 
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

void UiDisplay::changeLabelColour(String^ priority){
	if(priority == HIGH_PRIORITY_NAME){
		this->labelTaskDesc->ForeColor = Color::OrangeRed;
		this->labelTaskVenue->ForeColor = Color::OrangeRed;
		this->labelTaskStartTime->ForeColor = Color::OrangeRed;
		this->labelTaskEndTime->ForeColor = Color::OrangeRed;
		this->labelTaskPriority->ForeColor = Color::OrangeRed;
		this->labelTaskRepeat->ForeColor = Color::OrangeRed;
		this->labelTaskType->ForeColor = Color::OrangeRed;
	}
	else{
		this->labelTaskDesc->ForeColor = Color::White;
		this->labelTaskVenue->ForeColor = Color::White;
		this->labelTaskStartTime->ForeColor = Color::White;
		this->labelTaskEndTime->ForeColor = Color::White;
		this->labelTaskPriority->ForeColor = Color::White;
		this->labelTaskRepeat->ForeColor = Color::White;
		this->labelTaskType->ForeColor = Color::White;
	}
}

void UiDisplay::printLabel(ListViewItem^ item){
	changeLabelColour(item->SubItems[ITEM_PRIORITY_SLOT]->Text);
	//display selected item in product details
	this->labelTaskDesc->Text = item->SubItems[ITEM_DESCRIPTION_SLOT]->Text;

	this->labelTaskVenue->Text = item->SubItems[ITEM_LOCATION_SLOT]->Text;

	this->labelTaskStartTime->Text = item->SubItems[ITEM_STARTTIME_SLOT]->Text;

	this->labelTaskEndTime->Text = item->SubItems[ITEM_ENDTIME_SLOT]->Text;

	this->labelTaskPriority->Text = item->SubItems[ITEM_PRIORITY_SLOT]->Text;

	this->labelTaskRepeat->Text = item->SubItems[ITEM_REPEAT_SLOT]->Text;

	this->labelTaskType->Text = item->SubItems[ITEM_TASKTYPE_SLOT]->Text;
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

bool UiDisplay::SetFocus(Control ^ control){
	if(!(control->Focused)){
		selectedItem = LEAST_INDEX;
		control->Focus();
		return true;
	}
	return false;
}
void UiDisplay::focusList(ListType activeListType){
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
	if(list->Items->Count == EMPTY_LIST_COUNT)
		return;
	else if(!(list->Focused))
		this->SetFocus(list);
	else if (selectedItem == LEAST_INDEX && up || selectedItem == list->Items->Count - 1 && !up)
		return;
	else if (selectedItem < list->Items->Count - 1 && !up || selectedItem < list->Items->Count && up){
		if(up)
			--selectedItem;
		else
			++selectedItem;
	}
	this->printLabel(list->Items[selectedItem]);
}

Void UiDisplay::textboxInput_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e){
	this->textboxInput->Enabled = true;
	this->textboxInput->Clear();
}
Void UiDisplay::tabContainer_Selected(System::Object^  sender, System::Windows::Forms::TabControlEventArgs^  e){
	try{
		selectedItem=LEAST_INDEX;
		if(this->tabContainer->SelectedIndex==TAB_INDEX_COMPLETED){
			activeListType=listCompleted;
		}
		else if(this->tabContainer->SelectedIndex==TAB_INDEX_OVERDUE){
			activeListType=listOverdue;
		}
		else if(this->tabContainer->SelectedIndex==TAB_INDEX_TODO){
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
Void UiDisplay::textboxInput_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e){
	if(commandKeyword->size() < INPUT_LENGTH_SHOW_HELP_INFO ){
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
Void UiDisplay::textboxInput_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e){

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

			if(this->textboxInput->Text->Length <= MAX_EMPTY_TEXTBOX_LENGTH){
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
	}
	catch(string &error){
		this->printError(error);
	}
}
Void UiDisplay::todoListView_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e){
	if(todoListView->Items->Count != 0){
		ListView::SelectedListViewItemCollection^ tasks = this->todoListView->SelectedItems;
		ListViewItem^ item = tasks[MOST_RECENT_SELECTED_ITEM];
		selectedItem = converter->stringSysToIntConversion(item->SubItems[ITEM_INDEX_SLOT]->Text) - 1;
		this->printLabel(item);
	}
	else
		return;
}
Void UiDisplay::completedListView_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e){
	if(completedListView->Items->Count != 0){
		ListView::SelectedListViewItemCollection^ tasks = this->completedListView->SelectedItems;
		ListViewItem^ item = tasks[MOST_RECENT_SELECTED_ITEM];
		selectedItem = converter->stringSysToIntConversion(item->SubItems[0]->Text) - 1;
		this->printLabel(item);
	}
	else
		return;
}
Void UiDisplay::overdueListView_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e){
	if(overdueListView->Items->Count != 0){
		ListView::SelectedListViewItemCollection^ tasks = this->overdueListView->SelectedItems;
		ListViewItem^ item = tasks[MOST_RECENT_SELECTED_ITEM];
		selectedItem = converter->stringSysToIntConversion(item->SubItems[0]->Text) - 1;
		this->printLabel(item);
	}
	else
		return;
}

Void UiDisplay::checkInput(){
	if(commandKeyword->size()==INPUT_LENGTH_SHOW_HELP_INFO){
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
		else if(*commandKeyword == "sea"){
			this->printSearchMessage();
		}
	}
	else return;
}
Void UiDisplay::printAddMessage(){
	array<String ^> ^  addLines ={
		COMMAND_ADD_HELP,
		COMMAND_ADD_HELP_LOCATION,
		COMMAND_ADD_HELP_TIMED,
		COMMAND_ADD_HELP_DUE,
		COMMAND_ADD_HELP_REPEAT,
		COMMAND_ADD_HELP_PRIORITY,
		NEWLINE,
		COMMAND_ADD_HELP_TIME_DATE,
		COMMAND_ADD_HELP_TIME_DAY,
		COMMAND_ADD_HELP_TIME_TIME,
		NEWLINE,
		COMMAND_ADD_FLOATING_EXAMPLE,
		COMMAND_ADD_DEADLINE_EXAMPLE,
		COMMAND_ADD_TIMED_EXAMPLE
	};
	this->messageBox->Lines= addLines;
}
Void UiDisplay::printDelMessage(){
	array<String ^> ^  delLines ={
		COMMAND_DEL_HELP,
		COMMAND_DEL_HELP_MULTIPLE,
		NEWLINE,
		COMMAND_DEL_HELP_EXAMPLE,
		COMMAND_DEL_HELP_MULTIPLE_EXAMPLE
	};
	this->messageBox->Lines= delLines;
}
Void UiDisplay::printModMessage(){
	array<String ^> ^  modLines ={
		COMMAND_MOD_HELP,
		COMMAND_MOD_HELP_LOCATION,
		COMMAND_MOD_HELP_START,
		COMMAND_MOD_HELP_END,
		COMMAND_MOD_HELP_PRIORITY,
		COMMAND_MOD_HELP_PRIORITY_STATES,
		NEWLINE,
		COMMAND_MOD_HELP_EXAMPLE1,
		NEWLINE,
		COMMAND_MOD_HELP_EXAMPLE2,
		NEWLINE,
		COMMAND_MOD_HELP_EXAMPLE3
	};
	this->messageBox->Lines= modLines;
}
Void UiDisplay::printMarMessage(){
	array<String ^> ^  markLines ={
		COMMAND_MARK_HELP,
		COMMAND_MARK_HELP_MULTIPLE,
		NEWLINE,
		COMMAND_MARK_HELP_EXAMPLE,
		COMMAND_MARK_HELP_MULTIPLE_EXAMPLE
	};
	this->messageBox->Lines = markLines;
}
Void UiDisplay::printSearchMessage(){
	array<String ^> ^  searchLines ={
		COMMAND_SEARCH_HELP_INSTRUCTIONS,
		NEWLINE,
		COMMAND_SEARCH_HELP,
		COMMAND_SEARCH_HELP_LOCATION,
		COMMAND_SEARCH_HELP_START,
		COMMAND_SEARCH_HELP_END,
		COMMAND_SEARCH_HELP_PRIORITY,
		COMMAND_SEARCH_HELP_PRIORITY_STATES
	};
	this->messageBox->Lines = searchLines;
}
Void UiDisplay::printHelpMessage(){
	array<String ^> ^  helpLines = {
		MESSAGE_HELP_INSTRUCTIONS,
		NEWLINE,
		MESSAGE_HELP_ADD,
		MESSAGE_HELP_DEL,
		MESSAGE_HELP_MOD,
		MESSAGE_HELP_MARK,
		MESSAGE_HELP_SEARCH
	};
	this->messageBox->Lines = helpLines;
}
