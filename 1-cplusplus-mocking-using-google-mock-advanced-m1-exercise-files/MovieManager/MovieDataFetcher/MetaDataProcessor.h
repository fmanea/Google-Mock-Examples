#pragma once

#include <vector>
#include <string>

class MovieData;

typedef std::vector<MovieData> Movies;

class MetaDataProcessor
{
public:
	MetaDataProcessor();
	~MetaDataProcessor();

	void ProcessMovies(const std::vector<std::string>& fileNames, Movies& result);
};

