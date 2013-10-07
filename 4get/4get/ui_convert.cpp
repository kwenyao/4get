#include "ui_convert.h"
#include "logic_task.h"
#include "msclr\marshal_cppstd.h"

using namespace System;
using namespace msclr::interop;

UiConvert::UiConvert(){};

bool UiConvert::stringSysToStdConversion(String^ source, string& result){
	result = marshal_as<string>(source);
	return true;
}

bool UiConvert::stringStdToSysConversion(String^ result, string& source){
	result = marshal_as<String^>(source);
	return true;
}

//void UiConvert::printItem(System::Windows::Forms::ListViewItem^ item)
//{
//	Task t1 = print();
//	//convert to system string
//	System::String^ sys_name = gcnew System::String(p1.getName().c_str()); //name
//	System::String^ sys_bar = System::Convert::ToString(p1.getBarcode()); //barcode
//	System::String^ sys_price = System::Convert::ToString(p1.getPrice()); //price
//	System::String^ sys_manu = gcnew System::String(p1.getManufacturer().c_str()); //manufacturer
//	System::String^ sys_instock = System::Convert::ToString(p1.getInstock()); //number in stock
//	System::String^ sys_cat = gcnew System::String(p1.getCategory().c_str()); //category
//	System::String^ sys_nosold = System::Convert::ToString(p1.getNosold()); //number sold
//
//	item->BeginEdit();
//
//	item->SubItems[0]->Text = sys_name;
//
//	//creating item for listview
//	item->SubItems->Add(sys_bar); //add barcode
//	item->SubItems->Add(sys_cat); //add category	 
//	item->SubItems->Add(sys_manu); //add manu
//	item->SubItems->Add(sys_price); //add price
//	item->SubItems->Add(sys_nosold); //add number sold
//	item->SubItems->Add(sys_instock); //add number in stock
//}