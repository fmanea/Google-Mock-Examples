#include "stdafx.h"
#include <gtest/gtest.h>

#include <vector>
#include <gmock/gmock-actions.h>

#include "MetaDataProcessor.h"
#include "FakeLogger.h"
#include "FakeLoggerFactory.h"
#include "FakeMovieMetaDataRepository.h"
#include "MovieNotFoundException.h"

using namespace std;
using namespace testing;

class MetaDataProcessorTests : public Test
{
	shared_ptr<FakeLogger> fakeLogger;
	shared_ptr<FakeLoggerFactory> fakeLoggerFactory;

protected:
	MetaDataProcessor* processor;
	FakeMovieMetaDataRepository repository;

	virtual void SetUp()
	{
		fakeLoggerFactory = make_shared<FakeLoggerFactory>();
		fakeLogger = make_shared<FakeLogger>();
		ON_CALL(*fakeLoggerFactory, CreateLogger()).WillByDefault(testing::Return(fakeLogger));
		
		processor = new MetaDataProcessor(repository, fakeLoggerFactory);
	}

	virtual void TearDown()
	{
		delete processor;
	}
};

TEST_F(MetaDataProcessorTests, ProcessMovies_PassEmptyMovieList_ReturnEmptyResult)
{
	Movies result;
	processor->ProcessMovies({}, result);

	ASSERT_EQ(0, result.size());
}

TEST_F(MetaDataProcessorTests, ProcessMovies_ExceptionThrownDuringProcess_WriteToLog)
{
	Movies result;
	MovieNotFoundException testException("My Movie");
	EXPECT_CALL(repository, FindMovieData(_)).WillRepeatedly(Throw(testException));

	processor->ProcessMovies({"My Movie"}, result);

	ASSERT_EQ(0, result.size());
}