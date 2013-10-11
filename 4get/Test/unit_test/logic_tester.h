#include <gtest\gtest.h>
#include <gtest\gtest.h>
#include "logic_parser.h"
#include "logic_task.h"
#include "logic_task_deadline.h"
#include "logic_task_floating.h"
#include "logic_task_timed.h"
#include <time.h>

//#include "logic_task_list.h"



class ParserTest : public ::testing::Test {
protected:
  // You can remove any or all of the following functions if its body
  // is empty.

	Parser parser;
	string input1, input2, input3, input4;

	int id;
	string description;
	string location;
	tm *reminderTime;
	Priority priority;
	Status status;
	RepeatType repeat;
	tm *endTime;
 
  ParserTest() {
    // You can do set-up work for each test here.
  }
 
  virtual ~ParserTest() {
    // You can do clean-up work that doesn't throw exceptions here.
  }
 
  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:
 
  virtual void SetUp() {
    // Code here will be called immediately after the constructor (right
    // before each test).
	input1 = "Add HomeWork from EE2020 ,at com1 ,repeat weekly ,From Monday 2PM to Saturday 4PM ,!";
	input2 = "delete 2" + LIST_TO_DO;
	input3 = "mark 3 Undone" + LIST_TO_DO;
	input4 = "modify 2 ,from 2000 to 1900 ,at com2" + LIST_TO_DO;


	time_t rawtime;
	time ( &rawtime );
	reminderTime = localtime ( &rawtime );
	endTime = localtime( &rawtime);
	id = 1;
	description = "HomeWork from EE2020";
	location = "com1";

	reminderTime->tm_hour = 20;
	reminderTime->tm_min = 00;
	reminderTime->tm_wday = 5;

	mktime ( reminderTime );

	priority = high;
	status = incomplete;
	repeat = none;

	endTime->tm_hour = 23;
	endTime->tm_min = 59;
	endTime->tm_wday = 0;

	mktime ( endTime );

  }
 
  virtual void TearDown() {
    // Code here will be called immediately after each test (right
    // before the destructor).
  }
 
  // Objects declared here can be used by all tests in the test case for Foo.
};
