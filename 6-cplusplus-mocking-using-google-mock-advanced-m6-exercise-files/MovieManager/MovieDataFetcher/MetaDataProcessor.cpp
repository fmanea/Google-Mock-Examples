#include "stdafx.h"
#include "MetaDataProcessor.h"
#include "MovieData.h"
#include <fstream>

MetaDataProcessor::MetaDataProcessor(MovieMetaDataRepository& repository) : 
	MetaDataProcessor(repository, std::make_shared<LoggerFactory>())
{
}

MetaDataProcessor::MetaDataProcessor(MovieMetaDataRepository& respository, std::shared_ptr<LoggerFactory> loggerFactory)
	: m_repository(respository), m_loggerFactory(loggerFactory)
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
		}
		catch(...)
		{
			auto logger = m_loggerFactory->CreateLogger();

			logger->LogError(movieName);
		}
	}
}
