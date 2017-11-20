#include "gtest/gtest.h"
#include "TheMovieDbRepository.h"
#include "TheMovieDbDataFactory.h"
#include "MovieNotFoundException.h"
#include "FakeRestApiClient.h"

using namespace testing;
const std::string fictiveApiKey = "1234";

TEST(TheMovieDbRepositoryTests, FindMovieData_ApiReturnsEmptyString_ThrowException)
{
	TheMovieDbDataFactory factory;
	FakeRestApiClient fakeClient;
	EXPECT_CALL(fakeClient, HttpGet(_)).WillOnce(Return(""));

	TheMovieDbRepository repository(fictiveApiKey, factory, fakeClient);

	ASSERT_THROW(
		repository.FindMovieData("movie name"), MovieNotFoundException);
}

TEST(TheMovieDbRepositoryTests, FindMovieData_ApiReturnsStringWithoutMovie_ThrowException)
{
	TheMovieDbDataFactory factory;
	FakeRestApiClient fakeClient;
	EXPECT_CALL(fakeClient, HttpGet(_)).WillOnce(Return("{\"results\":[]}"));

	TheMovieDbRepository repository(fictiveApiKey, factory, fakeClient);

	ASSERT_THROW(
		repository.FindMovieData("movie name"), MovieNotFoundException);
}

TEST(TheMovieDbRepositoryTests, FindMovieData_ApiReturnsValidData_ReturnMovieResult)
{
	const char* movieList = "{\"page\":1,\"results\":[{\"id\":123,\"title\":\"my movie title\"}],\"total_results\":1,\"total_pages\":1}";
	const char* movieMeta = "{\"imdb_id\":\"myId\",\"title\":\"my movie title\",\"overview\":\"this is a plot\",\"runtime\":180}";

	std::string firstQuery = "http://api.themoviedb.org/3/search/movie?api_key=1234&page=1&query=my%2fmovie%2ftitle";
	std::string secondQuery = "http://api.themoviedb.org/3/movie/123?api_key=1234";
	TheMovieDbDataFactory factory;
	FakeRestApiClient fakeClient;

	EXPECT_CALL(fakeClient, HttpGet(_)).WillOnce(Return(movieList)).WillOnce(Return(movieMeta));

	TheMovieDbRepository repository(fictiveApiKey, factory, fakeClient);

	auto result = repository.FindMovieData("my movie title");

	EXPECT_EQ(result->GetImdbId(), "myId");
}