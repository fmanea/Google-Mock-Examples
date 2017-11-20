#pragma once
#include <string>
#include <vector>
#include "MovieData.h"

class SettableMovieData : public MovieData
{
public:

	void SetImdbId(std::string id) override;
	void SetTitle(std::string title) override;
	void SetLengthMin(unsigned length) override;
	void SetActors(std::vector<std::string> actors) override;
	void SetPlot(std::string plot) override;
};

inline void SettableMovieData::SetImdbId(std::string id)
{
	MovieData::SetImdbId(id);
}

inline void SettableMovieData::SetTitle(std::string title)
{
	MovieData::SetTitle(title);
}

inline void SettableMovieData::SetLengthMin(unsigned length)
{
	MovieData::SetLengthMin(length);
}

inline void SettableMovieData::SetActors(std::vector<std::string> actors)
{
	MovieData::SetActors(actors);
}

inline void SettableMovieData::SetPlot(std::string plot)
{
	MovieData::SetPlot(plot);
}
