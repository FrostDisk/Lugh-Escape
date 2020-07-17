#include "Balls_Scoreboard.h"


BallsScoreboard::BallsScoreboard( const uint16 maxScoreElements ) :
										MaxElements( maxScoreElements ),
										ScoreList(),
										ScoreIterator(),
										MinScore(100000)
{
}

// Ingresa un nuevo elemento a la lista de puntajes
bool BallsScoreboard::AddScoreData(	const wchar_t *userName,
									const uint32 userScore,
									const uint16 userLastLevel )
{
	std::list<BallsScoreData *>::iterator it;

	for( it=ScoreList.begin() ; it!=ScoreList.end() ; it++ )
	{
		if( (*it)->Score > userScore )
		{
			if( userScore < MinScore )
			{
				MinScore = userScore;
			}

			BallsScoreData *ScoreData = new BallsScoreData;

			#if defined(_DEBUG)
			COutput::Wprintf( L"Agregando: name=%ls score=%d level=%d\n",userName,userScore,userLastLevel);
			#endif

			COutput::Wsprintf( ScoreData->Name , userName );
			ScoreData->Score = userScore;
			ScoreData->Level = userLastLevel;

			ScoreList.insert( it , ScoreData );

			if( ScoreList.size() > MaxElements )
			{
				ScoreList.pop_back();
			}
			return true;
		}
	}

	if( ScoreList.size() <= MaxElements )
	{
		BallsScoreData *ScoreData = new BallsScoreData;

		#if defined(_DEBUG)
		COutput::Wprintf( L"Agregando: name=%ls score=%d level=%d\n",userName,userScore,userLastLevel);
		#endif

		COutput::Wsprintf( ScoreData->Name , userName );
		ScoreData->Score = userScore;
		ScoreData->Level = userLastLevel;

		ScoreList.push_back( ScoreData );
		return true;
	}

	return false;
}

// Genera el archivo XML con los puntajes
bool BallsScoreboard::SaveScoreboard(void)
{
	char FileName[ __TORNADO_PATH_LENGTH ];
	COutput::WcsToMbs( FileName , __TORNADO_PATH_LENGTH , ScoreFilename , __TORNADO_PATH_LENGTH );

	//char Data[ BUFFER_SIZE ];

	FILE *Stream = NULL;
	//int opened = COutput::Wfopen( Stream , ScoreFilename , L"w" );
	fopen_s( &Stream , FileName , "wt" );

	if( Stream != NULL )
	{
		//sprintf_s( Data , BUFFER_SIZE , "<?xml version=\"1.0\"?>\n<scoreboard>\n" );
		fprintf( Stream , "<?xml version=\"1.0\"?>\n<scoreboard>\n" );

		std::list<BallsScoreData *>::iterator it;

		for( it=ScoreList.begin() ; it!=ScoreList.end() ; it++ )
		{
			char Name[ BUFFER_SIZE ];
			COutput::WcsToMbs( Name , BUFFER_SIZE , (*it)->Name , BUFFER_SIZE );
			fprintf( Stream , "\t<element name=\"%s\" score=\"%d\" level=\"%d\" />\n",Name,(*it)->Score,(*it)->Level);
		}

		fprintf( Stream , "</scoreboard>\n" );

		COutput::Fclose( Stream );
		return true;
	}
	return false;
}


// Lee el archivo XML con los puntajes
bool BallsScoreboard::LoadScoreboard(void)
{
	char FileName[ __TORNADO_PATH_LENGTH ];
	COutput::WcsToMbs( FileName , __TORNADO_PATH_LENGTH , ScoreFilename , __TORNADO_PATH_LENGTH );

	// create the reader using one of the factory functions
	irr::io::IrrXMLReader* xml = irr::io::createIrrXMLReader( FileName );

	if (xml == 0)
	{
		return false; // file could not be opened
	}

	ScoreList.clear();

	BallsScoreData *Data = NULL;
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
					wchar_t Name[ BUFFER_SIZE ],Score[ BUFFER_SIZE ],Level[ BUFFER_SIZE ];
					COutput::MbsToWcs( Name , BUFFER_SIZE , xml->getAttributeValue("name") , BUFFER_SIZE );
					COutput::MbsToWcs( Score , BUFFER_SIZE , xml->getAttributeValue("score") , BUFFER_SIZE );
					COutput::MbsToWcs( Level , BUFFER_SIZE , xml->getAttributeValue("level") , BUFFER_SIZE );

					COutput::Wprintf( L"Leyendo name=\"%ls\" score=\"%ls\" level=\"%ls\"\n", Name , Score , Level );
					AddScoreData( Name , CMath::Wtoi( Score ) , CMath::Wtoi( Level ) );
				}
				break;
			}
		}
	}

	// delete the xml parser after usage
	delete xml;

	return true;
}

bool BallsScoreboard::GetItem( wchar_t *itemName , uint16 *itemScore , uint16 *itemLevel )
{
	if( ScoreIterator != ScoreList.rend() )
	{
		COutput::Wcscpy( itemName , BUFFER_SIZE , (*ScoreIterator)->Name );
		*itemScore = (*ScoreIterator)->Score;
		*itemLevel = (*ScoreIterator)->Level;
		ScoreIterator++;
		return true;
	}
	else 
	{
		return false;
	}
}