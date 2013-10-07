//#include "logic_executor.h"
//
//using namespace std;
//
//Executor::Executor(){}
//
//
//bool Executor::receive(string usercommand, vector<string> parameter)
//{
//	Command commandType = determineCommandType(usercommand);
//
//	switch(commandType)
//	{
//	case commandAdd:
//		return true;
//	case commandDelete:
//		return true;
//	default: return false;
//	}
//}
//Enum::Command Executor::determineCommandType (string commandTypeString)
//{
//	if(isEqual(commandTypeString, COMMAND_ADD))
//		return Command::commandAdd;
//	else if(isEqual(commandTypeString, COMMAND_DELETE))
//		return Command::commandDelete;
//	else
//		return Command::commandInvalid;
//}
//bool Executor::adderFunction(vector<string>& vectorOfInputs)
//{
//	_task.setTaskDescription(vectorOfInputs[SLOT_DESCRIPTION]);
//	_task.setTaskLocation(vectorOfInputs[SLOT_LOCATION]);
//
//}
//bool Executor::isEqual(string str1, const string str2)
//{
//	if(str1 == str2)
//		return true;
//	return false;
//}
//string Executor::stringCollector(string task)
//{
//	return task;
//}
//void Executor::loadListOfTasks()
//{
//	tasks.loadListFromFile();	
//}
//int Executor::convertStringToInt(vector<string>& vectorOfInputs)
//{
//	string date = vectorOfInputs[SLOT_TIME];
//	string day, month, year;
//	int dayInt, monthInt, yearInt;
//
//	day += date[0];
//	day += date[1];
//	month += date[3];
//	year += date[5];
//	year += date[6];
//
//	cout << day<< endl;
//	cout << month << endl;
//	cout << year << endl;
//
//	stringstream sd(day);
//	sd >> dayInt;
//	stringstream sm(month);
//	sm >> monthInt;
//	stringstream sy(year);
//	sy >> yearInt;
//}
