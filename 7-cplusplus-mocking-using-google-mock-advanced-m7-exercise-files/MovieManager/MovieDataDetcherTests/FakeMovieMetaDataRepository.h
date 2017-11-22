#pragma once

#include "gmock/gmock.h"
#include "MovieMetaDataRepository.h"

class FakeMovieMetaDataRepository : public MovieMetaDataRepository
{
public:
	MOCK_METHOD1(FindMovieData, std::shared_ptr<MovieData>(const std::string& movieName));
};
