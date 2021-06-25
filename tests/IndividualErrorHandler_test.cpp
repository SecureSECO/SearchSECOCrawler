#include "pch.h"
#include "IndividualErrorHandler.h"

TEST(TestExecute, TestThrowWarning)
{
	LogThrowHandler l = LogThrowHandler("", LogLevel::WARN, 0);
	EXPECT_THROW(l.execute("", 0), int);
}

TEST(TestExecute, TestThrowFatal)
{
	LogThrowHandler l = LogThrowHandler("", LogLevel::ERROR, 0);
	EXPECT_THROW(l.execute("", 0), int);
}