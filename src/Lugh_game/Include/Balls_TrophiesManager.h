#ifndef ___Balls__TrophiesManager__H___
#define ___Balls__TrophiesManager__H___

#include <Tornado.h>

#include "Balls_Achievement.h"
#include "Balls_TrophyType.h"

using namespace Tornado;

class BallsTrophiesManager
{

private:
	uint16 NroElements;

	wchar_t TrophiesFilename[ __TORNADO_PATH_LENGTH ];

	std::list<BallsAchievement *> TrophiesList;

protected:
public:
	BallsTrophiesManager();

	void InitTrophies(void);

	inline void SetFilename(const wchar_t *Name){
		COutput::Wsprintf( TrophiesFilename , Name );
	}

	bool SaveTrophies(void);
	bool LoadTrophies(void);
	void VerifyTrophy(const wchar_t *Key,const wchar_t *Hash);
	void AddTrophy(uint16 Id,const wchar_t *Key,const wchar_t *Hash);
	bool UnlockTrophy(uint16 Id);
	bool IsUnlockedTrophy(uint16 Id);
	int GetUnlockedNumber(void);
};

#endif
