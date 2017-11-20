#pragma once
#include "gmock/gmock.h"
#include "Logger.h"

class FakeLoggerFactory : public LoggerFactory
{
public:
	MOCK_METHOD0(CreateLogger, std::shared_ptr<Logger>());
};
