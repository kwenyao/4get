#include "ui_convert.h"
#include "msclr\marshal_cppstd.h"

using namespace System;
using namespace msclr::interop;

bool UiConvert::stringSysToStdConversion(String^ source, string& result){
	result = marshal_as<string>(source);
	return true;
}

bool UiConvert::stringStdToSysConversion(String^ result, string& source){
	result = marshal_as<String^>(source);
	return true;
}