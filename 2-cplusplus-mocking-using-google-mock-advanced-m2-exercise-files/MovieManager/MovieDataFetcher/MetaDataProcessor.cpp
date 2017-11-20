#include "stdafx.h"
#include "MetaDataProcessor.h"
#include "MovieData.h"

MetaDataProcessor::MetaDataProcessor(MovieMetaDataRepository& jsonClient) : m_repository(jsonClient)
{
}


MetaDataProcessor::~MetaDataProcessor()
{
}

void MetaDataProcessor::ProcessMovies(const std::vector<std::string>& movieNames, Movies& result)
{
	if(movieNames.size() == 0)
	{
		return;
	}

	for (auto movieName : movieNames)
	{
		try
		{
			std::shared_ptr<MovieData> movieData = m_repository.FindMovieData(movieName);

			result.push_back(movieData);
		}catch(...)
		{
			// TODO: error handling
		}
	}
}
