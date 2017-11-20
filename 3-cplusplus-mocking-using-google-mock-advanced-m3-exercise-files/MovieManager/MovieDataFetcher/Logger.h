#pragma once
#include <string>
#include <fstream>
#include <memory>

class Logger 
{
public:
	virtual void LogError(std::string message) = 0;
};

class FileLogger : public Logger
{
public:
	void LogError(std::string message) override
	{
		std::ofstream myfile;
		myfile.open("errors.txt");

		myfile << message << std::endl;
		myfile.close();
	}
};

class LoggerFactory 
{
public:
	virtual std::shared_ptr<Logger> CreateLogger() 
	{
		return std::make_shared<FileLogger>();
	}
};