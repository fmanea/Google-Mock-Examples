#include "stdafx.h"
#include <iostream>

#include "MetaDataProcessor.h"
#include "TheMovieDbRepository.h"
#include "../MovieDataDetcherTests/ApiKey.h"
#include "TheMovieDbDataFactory.h"

int main()
{
	TheMovieDbDataFactory dataFactory;
	TheMovieDbRepository repository(MY_API_KEY, dataFactory);
	MetaDataProcessor processor(repository);

	Movies result;
	processor.ProcessMovies({ "Doctor Strange", "Dr. Strangelove" }, result);

	for (auto movie : result)
	{
		std::cout << "Title: " << movie->GetTitle() << std::endl;
		std::cout << "IMDB Id: " << movie->GetImdbId() << std::endl << std::endl;
		std::cout << movie->GetPlot() << std::endl << std::endl;
		std::cout << "Length (min.) " << movie->GetLengthMin() << std::endl << std::endl;
		std::cout << "----------------------------------------" << std::endl;
	}

	return 0;
}