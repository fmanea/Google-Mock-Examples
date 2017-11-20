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
	shared_ptr<FakeLoggerFactory> fakeLoggerFactory;

protected:
	shared_ptr<FakeLogger> fakeLogger;
	MetaDataProcessor* processor;
	FakeMovieMetaDataRepository repository;

	virtual void SetUp()
	{
		fakeLoggerFactory = make_shared<NiceMock<FakeLoggerFactory>>();
		fakeLogger = make_shared<FakeLogger>();
		ON_CALL(*fakeLoggerFactory, CreateLogger()).WillByDefault(Return(fakeLogger));
		
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
	EXPECT_CALL(*fakeLogger, LogError("My Movie")).Times(AtLeast(1));

	processor->ProcessMovies({"My Movie"}, result);

	ASSERT_EQ(0, result.size());
}