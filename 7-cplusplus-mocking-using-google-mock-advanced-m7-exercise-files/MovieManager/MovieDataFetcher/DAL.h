#pragma once
#include <string>
#include "MovieData.h"
#include <memory>

class DAL
{
public:
	DAL();
	~DAL();

	static bool MovieExist(const std::string& movieName);
	static void Create(std::shared_ptr<MovieData> movie);
	static void Update(std::shared_ptr<MovieData> movie);
};

class DataLayer 
{
public:
	virtual bool MovieExist(const std::string& movieName)
	{
		return DAL::MovieExist(movieName);
	}

	virtual void Create(std::shared_ptr<MovieData> movie)
	{
		DAL::Create(movie);
	}

	virtual void Update(std::shared_ptr<MovieData> movie)
	{
		DAL::Update(movie);
	}
};