#include "stdafx.h"
#include "TheMovieDbDataFactory.h"
#include "SettableMovieData.h"
#include "rapidjson/document.h"
#include "ErrorParsingMovieDataException.h"


TheMovieDbDataFactory::TheMovieDbDataFactory()
{
}


TheMovieDbDataFactory::~TheMovieDbDataFactory()
{
}

void TheMovieDbDataFactory::GetActors(const std::string& jsonString, std::vector<std::string>& result) const
{
	rapidjson::Document jsonDocument;
	jsonDocument.Parse(jsonString.c_str());
	if (!jsonDocument.IsObject())
	{
		throw ErrorParsingMovieDataException();
	}

	try
	{
		auto cast = jsonDocument["cast"].GetArray();
		for (auto& actor : cast)
		{
			auto name = actor["name"].GetString();
			result.push_back(name);
		}
	}
	catch (...)
	{
		throw ErrorParsingMovieDataException();
	}
}

std::shared_ptr<MovieData> TheMovieDbDataFactory::CreateFromJson(const std::string& jsonString) const
{
	rapidjson::Document jsonDocument;
	jsonDocument.Parse(jsonString.c_str());
	if (!jsonDocument.IsObject())
	{
		throw ErrorParsingMovieDataException();
	}

	try
	{
		auto imdbId = jsonDocument["imdb_id"].GetString();
		auto title = jsonDocument["title"].GetString();
		auto plot = jsonDocument["overview"].GetString();
		auto lengthMin = jsonDocument["runtime"].GetUint();

		auto result = std::make_shared<SettableMovieData>();
		result->SetImdbId(imdbId);
		result->SetTitle(title);
		result->SetPlot(plot);
		result->SetLengthMin(lengthMin);

		return result;
	}
	catch (...)
	{
		throw ErrorParsingMovieDataException();
	}
}