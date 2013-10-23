#include <gtest\gtest.h>
#include "logic_tester.h"


TEST_F(ParserTest, MethodReturnsFirstItem)
{
	vector<string> inputBits1(SLOT_SIZE);
	parser.parseInput(input1,inputBits1);
	EXPECT_EQ("add",parser.getCommand());
}

TEST_F(ParserTest, TestDelete)
{
	vector<string> inputBits2(SLOT_SIZE);
	parser.parseInput(input2, inputBits2);
	EXPECT_EQ("delete",parser.getCommand());
}

TEST_F(ParserTest, TestMark)
{
	vector<string> inputBits3(SLOT_SIZE);
	parser.parseInput(input3, inputBits3);
	EXPECT_EQ("mark",parser.getCommand());
}

TEST_F(ParserTest, TestModify)
{
	vector<string> inputBits4(SLOT_SIZE);
	parser.parseInput(input4, inputBits4);
	EXPECT_EQ("modify",parser.getCommand());
}

TEST_F(LogTest, TestLog)
{
	//this is a test for different types of log.
	logging(inputMessage, type, status);
	logging(inputMessage2, type2, status2);
}
TEST_F(ExecutorTest, TestExecutorAdd){
	EXPECT_EQ(true,ExecutorTester.stringCollector(taskAdd));
}

