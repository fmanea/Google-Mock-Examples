#include "stdafx.h"
#include "DAL.h"
#include "NotImplementedException.h"


DAL::DAL()
{
}


DAL::~DAL()
{
}

bool DAL::MovieExist(const std::string& cs)
{
	throw NotImplementedException();
}

void DAL::Create(std::shared_ptr<MovieData> movie)
{
	throw NotImplementedException();
}

void DAL::Update(std::shared_ptr<MovieData> movie)
{
	throw NotImplementedException();
}
