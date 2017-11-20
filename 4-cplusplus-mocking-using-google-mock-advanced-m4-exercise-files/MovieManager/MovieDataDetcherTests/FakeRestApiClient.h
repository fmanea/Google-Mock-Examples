#pragma once

#include "RestApiClient.h"
#include "gmock/gmock.h"
class FakeRestApiClient : public RestApiClient
{
public:
	MOCK_METHOD1(HttpGet, std::string(std::string&));
};