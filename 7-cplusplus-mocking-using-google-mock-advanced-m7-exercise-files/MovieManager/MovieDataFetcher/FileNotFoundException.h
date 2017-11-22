#pragma once
#include <exception>

class FileNotFoundException : public std::exception
{
public:
	FileNotFoundException() {}
};
