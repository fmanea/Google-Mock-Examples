#pragma once

#include "gmock/gmock.h"
#include "Logger.h"

class FakeLogger : public Logger
{
public:
	MOCK_METHOD1(LogError, void(std::string));
};