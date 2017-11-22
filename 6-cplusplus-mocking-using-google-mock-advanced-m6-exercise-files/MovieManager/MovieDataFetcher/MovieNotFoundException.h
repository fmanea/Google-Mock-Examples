#pragma once
#include <exception>

class MovieNotFoundException : public std::exception
{
	const std::string m_movieName;

public:
	MovieNotFoundException(const std::string& movieName): m_movieName(movieName){}
	std::string GetMovieName() const{ return m_movieName; }
};