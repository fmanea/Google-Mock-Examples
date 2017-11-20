#pragma once

#include <vector>
#include <iostream>
class MovieData
{
	std::string m_id;
	std::string m_title;
	std::string m_posterUrl;
	unsigned m_length;
	std::vector<std::string> m_actors;
	std::string m_plot;
protected:
	virtual void SetImdbId(std::string id) { m_id = id; }
	virtual void SetTitle(std::string title) { m_title = title; }
	virtual void SetLengthMin(unsigned length) { m_length = length; }
	virtual void SetActors(std::vector<std::string> actors) { m_actors = actors; }
	virtual void SetPlot(std::string plot) { m_plot = plot; }

	MovieData();
public:
	virtual ~MovieData();

	std::string GetImdbId()const { return m_id; }
	std::string GetTitle()const { return m_title; }
	unsigned GetLengthMin()const { return m_length; }
	std::vector<std::string> GetActors()const { return m_actors; }
	std::string GetPlot()const { return m_plot; }
};

