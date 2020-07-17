#ifndef ___Balls__Scoreboard__H___
#define ___Balls__Scoreboard__H___

#include <Tornado.h>
#include <list>

#include "Balls_ScoreData.h"

using namespace Tornado;

class BallsScoreboard
{

private:

	uint16 MaxElements;

	wchar_t ScoreFilename[ __TORNADO_PATH_LENGTH ];

	std::list<BallsScoreData *> ScoreList;

	std::list<BallsScoreData *>::reverse_iterator ScoreIterator;

	uint32 MinScore;

protected:
public:
	BallsScoreboard(const uint16 MaxElements);

	bool AddScoreData(const wchar_t *Name,const uint32 Score,const uint16 Level);

	inline void SetFilename(const wchar_t *Name){
		COutput::Wsprintf( ScoreFilename , Name );
	}

	bool SaveScoreboard(void);
	bool LoadScoreboard(void);

	inline bool VerifyScore(uint16 Score)
	{
		return ScoreList.size()==0 || ScoreList.size() <= MaxElements || MinScore < Score ? true : false;
	}

	inline void BeginFetch(void)
	{
		ScoreIterator = ScoreList.rbegin();
	}

	bool GetItem(wchar_t *Name,uint16 *Score,uint16 *Level);

};

#endif
