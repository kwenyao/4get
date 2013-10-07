#include <gtest\gtest.h>
#include "logic_tester.h"


TEST_F(ParserTest, MethodReturnsFirstItem)
{
	vector<string> inputBits(SLOT_SIZE);
	TaskDeadline Dtask(id, description, location, reminderTime, priority, status, repeat, endTime);

	parser.parseInput(input1,inputBits);





}
