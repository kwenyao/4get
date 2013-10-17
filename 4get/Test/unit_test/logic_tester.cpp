#include <gtest\gtest.h>
#include "logic_tester.h"


TEST_F(ParserTest, MethodReturnsFirstItem)
{
	vector<string> inputBits1(SLOT_SIZE);
	vector<string> inputBits2(SLOT_SIZE);
	vector<string> inputBits3(SLOT_SIZE);
	vector<string> inputBits4(SLOT_SIZE);

	TaskTimed Ttask(id, description, location, reminderTime, priority, status, repeat, startTime, endTime);

	parser.parseInput(input1,inputBits1);
	parser.parseReset();
	cout << Ttask.getTaskDescription() << endl;

	parser.parseInput(input2, inputBits2);
	parser.parseReset();
	parser.parseInput(input3, inputBits3);
	parser.parseReset();
	parser.parseInput(input4, inputBits4);
	parser.parseReset();

	time_t timer;
	time(&timer);
}
