#include "stdafx.h"
#include "JsonHelper.h"
#include "InvalidInputException.h"
#include "MovieNotFoundException.h"


JsonHelper::JsonHelper()
{
}


JsonHelper::~JsonHelper()
{
}

const rapidjson::Value& JsonHelper::FindMovieByTitle(const std::string& title, rapidjson::GenericValue<rapidjson::UTF8<>>::Array results)
{
	size_t selectedIndex = 0;
	if(results.Size() > 1)
	{
		for (size_t  i = 0; i < results.Size() ; ++i)
		{
			auto movieTitle = results[i]["title"].GetString();
			if(std::strcmp(movieTitle, title.c_str()) == 0)
			{
				selectedIndex = i;
				break;
			}
		}
	}
	return results[selectedIndex];
}

std::string JsonHelper::GetMatchingTitleIdFromMovieList(const std::string& title, const std::string& jsonString)
{
	rapidjson::Document jsonDocument;
	jsonDocument.Parse(jsonString.c_str());
	if (!jsonDocument.IsObject())
	{
		throw InvalidInputException();
	}

	auto results = jsonDocument["results"].GetArray();
	if(results.Size() == 0)
	{
		throw MovieNotFoundException(title);
	}
	const rapidjson::Value& result = FindMovieByTitle(title, results);

	auto id = result["id"].GetInt();

	return std::to_string(id);
}
