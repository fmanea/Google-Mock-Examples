#pragma once
#include "MovieDataFactory.h"

class TheMovieDbDataFactory : public MovieDataFactory
{
public:
	TheMovieDbDataFactory();
	~TheMovieDbDataFactory();

	void GetActors(const std::string& jsonString, std::vector<std::string>& result) const override;
	std::shared_ptr<MovieData> CreateFromJson(const std::string& jsonString) const override;
};

