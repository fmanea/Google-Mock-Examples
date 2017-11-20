#include "stdafx.h"
#include "MetaDataProcessor.h"
#include "MovieData.h"

MetaDataProcessor::MetaDataProcessor()
{
}


MetaDataProcessor::~MetaDataProcessor()
{
}

void MetaDataProcessor::ProcessMovies(const std::vector<std::string>& fileNames, Movies& result)
{
	if(fileNames.size() == 0)
	{
		return;
	}
}
