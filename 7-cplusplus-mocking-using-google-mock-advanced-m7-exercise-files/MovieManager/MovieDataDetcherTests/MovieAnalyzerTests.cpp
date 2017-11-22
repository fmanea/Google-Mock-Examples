#include "MovieAnalyzer.h"
#include <gtest/gtest.h>
#include <memory>
#include "FakeMovieMetaDataRepository.h"
#include "FakeLogger.h"
#include "SettableMovieData.h"

using namespace testing;

class FakeStream
{
public:
	MOCK_METHOD1(open, void(std::string));
	MOCK_CONST_METHOD0(is_open, bool());
	MOCK_METHOD0(getstring, std::string());
	MOCK_METHOD0(close, void());
	MOCK_METHOD0(eof, bool());

	void getline(char *output, size_t size)
	{
		memcpy(output, getstring().c_str(), size);
	}

};

class fakeDataLayer : public DataLayer
{
public:
	MOCK_METHOD1(MovieExist, bool(const std::string&));
	MOCK_METHOD1(Create, void(std::shared_ptr<MovieData>));
	MOCK_METHOD1(Update, void(std::shared_ptr<MovieData>));
};

TEST(MovieAnalyzerTests, ProcessFromFile_FileIsEmpty_DoNotCallDB)
{
	FakeMovieMetaDataRepository fakeRepository;
	fakeDataLayer fakeDataLayer;
	EXPECT_CALL(fakeDataLayer, Create(_)).Times(0);
	EXPECT_CALL(fakeDataLayer, Update(_)).Times(0);

	MovieAnalyzer<FakeStream> analyzer(fakeRepository, fakeDataLayer);

	NiceMock<FakeStream> fakeStream;
	EXPECT_CALL(fakeStream, is_open()).WillRepeatedly(Return(true));
	EXPECT_CALL(fakeStream, eof()).WillRepeatedly(Return(true));

	analyzer.ProcessFromFile(fakeStream);
}

class MovieAnalyzerForTests : public MovieAnalyzer<FakeStream>
{
public:
	MovieAnalyzerForTests(MovieMetaDataRepository& repository, DataLayer& dal) :
		MovieAnalyzer<FakeStream>(repository, dal) {};

	MOCK_METHOD0(CreateLogger, std::shared_ptr<Logger>());
};

TEST(MovieAnalyzerTests, ProcessFromFile_FileHaveOneExistingMovie_LogWarnning)
{
	auto movieData = std::make_shared<SettableMovieData>();
	FakeMovieMetaDataRepository fakeRepository;
	EXPECT_CALL(fakeRepository, FindMovieData(_)).WillRepeatedly(Return(movieData));

	fakeDataLayer fakeDataLayer;
	EXPECT_CALL(fakeDataLayer, MovieExist(_)).WillRepeatedly(Return(true));

	MovieAnalyzerForTests analyzer(fakeRepository, fakeDataLayer);
	
	auto fakeLogger = std::make_shared<FakeLogger>();
	EXPECT_CALL(*fakeLogger, LogWarning("Movie already exist in DB")).Times(1);
	EXPECT_CALL(analyzer, CreateLogger()).WillRepeatedly(Return(fakeLogger));

	NiceMock<FakeStream> fakeStream;
	EXPECT_CALL(fakeStream, is_open()).WillRepeatedly(Return(true));
	EXPECT_CALL(fakeStream, eof()).WillOnce(Return(false)).WillOnce(Return(true));
	EXPECT_CALL(fakeStream, getstring()).WillOnce(Return("My movie title"));

	analyzer.ProcessFromFile(fakeStream);
}