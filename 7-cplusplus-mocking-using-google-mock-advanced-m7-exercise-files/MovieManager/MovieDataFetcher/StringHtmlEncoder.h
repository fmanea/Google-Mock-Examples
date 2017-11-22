#pragma once

#include <string>

class StringHtmlEncoder
{
public: 
	static std::string Encode(const std::string& input)
	{
		std::string encodedResult;

		int start = 0;
		for (size_t i = 0; i < input.length(); i++)
		{
			if (input[i] == ' ')
			{
				encodedResult.append(input, start, i - start);
				encodedResult += "%2f";
				start = i + 1;
			}
		}

		encodedResult.append(input, start, input.length());

		return encodedResult;
	}
};