#include "gtest/gtest.h"
#include "TheMovieDbRepository.h"
#include "TheMovieDbDataFactory.h"
#include "MovieNotFoundException.h"
#include "FakeRestApiClient.h"

TEST(TheMovieDbRepositoryTests, FindMovieData_ApiReturnsEmptyString_ThrowException)
{
	TheMovieDbDataFactory factory;
	FakeRestApiClient fakeClient;

	TheMovieDbRepository repository("api-key", factory, fakeClient);

	ASSERT_THROW(
		repository.FindMovieData("movie name"), MovieNotFoundException);
}

TEST(TheMovieDbRepositoryTests, FindMovieData_ApiReturnsStringWithoutMovie_ThrowException)
{
	TheMovieDbDataFactory factory;
	FakeRestApiClient fakeClient;

	TheMovieDbRepository repository("api-key", factory, fakeClient);

	ASSERT_THROW(
		repository.FindMovieData("movie name"), MovieNotFoundException);
}