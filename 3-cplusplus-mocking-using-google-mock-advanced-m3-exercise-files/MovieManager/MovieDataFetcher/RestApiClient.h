#pragma once
#include <string>

class RestApiClient
{
public:
	RestApiClient();
	virtual ~RestApiClient();

	virtual std::string HttpGet(std::string& url);
};
