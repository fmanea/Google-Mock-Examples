#pragma once
#include <string>

class RestApiClient
{
public:
	RestApiClient();
	~RestApiClient();

	std::string HttpGet(std::string& url);
};

