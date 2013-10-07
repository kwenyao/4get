#include <gtest\gtest.h>
#include <gtest\gtest.h>
#include "logic_parser.h"
#include "logic_task.h"
#include "logic_task_deadline.h"
#include "logic_task_floating.h"
#include "logic_task_timed.h"
#include "logic_task_repeat.h"
#include "logic_task_list.h"



class ParserTest : public ::testing::Test {
protected:
  // You can remove any or all of the following functions if its body
  // is empty.

	Parser parser;
	string input1;
 
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
	input1 = "Add HomeWork EE2020 ,by Thursday ,Repeat Weekly ,!"; 
	
  }
 
  virtual void TearDown() {
    // Code here will be called immediately after each test (right
    // before the destructor).
  }
 
  // Objects declared here can be used by all tests in the test case for Foo.
};
