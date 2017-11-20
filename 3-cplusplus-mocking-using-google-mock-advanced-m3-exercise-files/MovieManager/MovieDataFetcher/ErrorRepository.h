#pragma once
#include <string>

class ErrorRepository
{
public:
	virtual ~ErrorRepository() = default;

	virtual void LogBadMovie(std::string movieName) = 0;
};