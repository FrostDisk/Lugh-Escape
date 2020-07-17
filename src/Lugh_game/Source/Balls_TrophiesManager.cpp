#include "Balls_TrophiesManager.h"

BallsTrophiesManager::BallsTrophiesManager() : NroElements(0)
{
}

void BallsTrophiesManager::InitTrophies(void)
{
	AddTrophy(TROPHY_LUGH,L"ACA6536535B495CCB339664D775E872C",L"4A6B9484047F7724CA7BB5387E78DE177709795A765EF11639C369B60940956C");
	AddTrophy(TROPHY_JOE,L"FA2D45843F7ED1C05200F1680CF96630",L"BA16CBA5571BAE757D78CBFA9747036BB69C8C30E513FFCABA1BBADA960934B2");
	AddTrophy(TROPHY_RETRO,L"117CF7BC821A26CD362D83C1927D856E",L"95C4D0EAC64A0583D1526F2AC8AEA143537CABCE2557007F656C9D0553D59D50");
	AddTrophy(TROPHY_BALL,L"6231AAAE8A79EB5C3C3ECB3634007B27",L"AD1C0BA51D391A3CBA499474228CE89AAE4930AB95EF994B95673260CB494FD1");
	AddTrophy(TROPHY_SARGE,L"3CD20AEDB86F8B2F640BE767FB5649C6",L"CC4EA14484B2DEFEFC559F50607FB510AA21A5C4C1E0DABA56F5CB05BFA917D1");
	AddTrophy(TROPHY_MASHI,L"8B0E748FC0A4BFF0D612BC5F605212B7",L"A20791343F7B74A8FB3A2F898AD0A4789BACA7D93FB2CD0E5F79ECD7633C9C89");
}

bool BallsTrophiesManager::SaveTrophies(void)
{
	char FileName[ __TORNADO_PATH_LENGTH ];
	COutput::WcsToMbs( FileName , __TORNADO_PATH_LENGTH , TrophiesFilename , __TORNADO_PATH_LENGTH );

	//char Data[ BUFFER_SIZE ];

	FILE *Stream = NULL;
	//int opened = COutput::Wfopen( Stream , ScoreFilename , L"w" );
	fopen_s( &Stream , FileName , "wt" );

	if( Stream != NULL )
	{
		//sprintf_s( Data , BUFFER_SIZE , "<?xml version=\"1.0\"?>\n<trophies>\n" );
		fprintf( Stream , "<?xml version=\"1.0\"?>\n<trophies>\n" );

		std::list<BallsAchievement *>::iterator it;

		for( it=TrophiesList.begin() ; it!=TrophiesList.end() ; it++ )
		{
			if( (*it)->Unlocked )
			{
				char Key[ KEY_SIZE ];
				char Hash[ HASH_SIZE ];
				COutput::WcsToMbs( Key , KEY_SIZE , (*it)->Key , KEY_SIZE );
				COutput::WcsToMbs( Hash , HASH_SIZE , (*it)->Hash , HASH_SIZE );
				fprintf( Stream , "\t<element key=\"%s\" hash=\"%s\" />\n",Key,Hash);
			}
		}

		fprintf( Stream , "</trophies>\n" );

		COutput::Fclose( Stream );
		return true;
	}
	return false;
}

bool BallsTrophiesManager::LoadTrophies(void)
{
	char FileName[ __TORNADO_PATH_LENGTH ];
	COutput::WcsToMbs( FileName , __TORNADO_PATH_LENGTH , TrophiesFilename , __TORNADO_PATH_LENGTH );

	// create the reader using one of the factory functions
	irr::io::IrrXMLReader* xml = irr::io::createIrrXMLReader( FileName );

	if (xml == 0)
	{
		return false; // file could not be opened
	}

	bool BeginReading = false;

	// parse the file until end reached
	while(xml->read())
	{
		// based on xml->getNodeType(), do something.
		switch(xml->getNodeType())
		{
			// Leo <element>
			case irr::io::EXN_ELEMENT:
			{
				wchar_t NodeName[ BUFFER_SIZE ];
				COutput::MbsToWcs( NodeName , BUFFER_SIZE , xml->getNodeName() , BUFFER_SIZE );

				if( !COutput::Wstrcmp( L"element" , NodeName ) )
				{
					wchar_t Key[ BUFFER_SIZE ],Hash[ BUFFER_SIZE ];
					COutput::MbsToWcs( Key , BUFFER_SIZE , xml->getAttributeValue("key") , BUFFER_SIZE );
					COutput::MbsToWcs( Hash , BUFFER_SIZE , xml->getAttributeValue("hash") , BUFFER_SIZE );

					COutput::Wprintf( L"Verificando key=\"%ls\" hash=\"%ls\"\n", Key , Hash );
					VerifyTrophy( Key , Hash );
				}
				break;
			}
		}
	}

	// delete the xml parser after usage
	delete xml;

	return true;
}

void BallsTrophiesManager::VerifyTrophy(	const wchar_t *trophieKey,
											const wchar_t *trophieHash)
{
	std::list<BallsAchievement *>::iterator it;

	for( it=TrophiesList.begin() ; it!=TrophiesList.end() ; it++ )
	{
		int checkKey = COutput::Wstrcmp( (*it)->Key , trophieKey );
		int checkHash = COutput::Wstrcmp( (*it)->Hash , trophieHash );

		if( !checkKey && !checkHash )
		{
			(*it)->Unlocked = true;
			return;
		}
	}
}

void BallsTrophiesManager::AddTrophy(	uint16 trophyId,
										const wchar_t *trophyKey,
										const wchar_t *trophyHash )
{
	BallsAchievement *TrophyData = new BallsAchievement;

	#if defined(_DEBUG)
	COutput::Wprintf( L"Registrando: id=%d key=%ls hash=%ls\n",trophyId,trophyKey,trophyHash);
	#endif

	COutput::Wsprintf(TrophyData->Key,trophyKey);
	COutput::Wsprintf(TrophyData->Hash,trophyHash);
	TrophyData->Id = trophyId;
	TrophyData->Unlocked = false;
	NroElements += 1;

	TrophiesList.push_back( TrophyData );
}

bool BallsTrophiesManager::UnlockTrophy(uint16 trophyId)
{
	std::list<BallsAchievement *>::iterator it;

	for( it=TrophiesList.begin() ; it!=TrophiesList.end() ; it++ )
	{
		if( (*it)->Id == trophyId )
		{
			(*it)->Unlocked = true;
			return true;
		}
	}
	return false;
}

bool BallsTrophiesManager::IsUnlockedTrophy(uint16 trophyId)
{
	std::list<BallsAchievement *>::iterator it;

	for( it=TrophiesList.begin() ; it!=TrophiesList.end() ; it++ )
	{
		if( (*it)->Id == trophyId )
		{
			return (*it)->Unlocked;
		}
	}
	return false;
}

int BallsTrophiesManager::GetUnlockedNumber(void)
{
	int Counter = 0;
	std::list<BallsAchievement *>::iterator it;

	for( it=TrophiesList.begin() ; it!=TrophiesList.end() ; it++ )
	{
		if( (*it)->Unlocked )
		{
			Counter += 1;
		}
	}
	return Counter;
}
