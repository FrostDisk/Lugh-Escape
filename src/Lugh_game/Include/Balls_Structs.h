#ifndef ___Balls__Structs__H___
#define ___Balls__Structs__H___

#include <tornado.h>

using namespace Tornado;

struct BallsResources
{
	struct BallsMesh
	{
		BallsMesh() :
			LughStand(NULL),
			Lugh(NULL),
			//Maceta(NULL),
			Bbox(NULL),
			Init(NULL),
			End(NULL),
			BossInit(NULL),
			BossJail(NULL),
			BossKey(NULL),
			BordeEsquina(NULL),
			BordePared(NULL),
			Crosshair(NULL),
			Scene(NULL)
		{
		}

		irr::scene::IAnimatedMesh *LughStand; //Mesh de Lugh de Pie
		irr::scene::IAnimatedMesh *Lugh;	// Mesh de Lugh
		irr::scene::IAnimatedMesh *Maceta[7];// Mesh de las Piezas
		irr::scene::IAnimatedMesh *Bbox;// Mesh del suelo

		irr::scene::IAnimatedMesh *Init; // Mesh de Inicio
		irr::scene::IAnimatedMesh *End;// Mesh de Fin

		irr::scene::IAnimatedMesh *BossInit;// Mesh de Inicio Modo-Jefe
		irr::scene::IAnimatedMesh *BossJail; //Mesh de la Jaula
		irr::scene::IAnimatedMesh *BossLughitos;//Mesh de los Lughitos
		irr::scene::IAnimatedMesh *BossKey; //Mesh de la Llave

		irr::scene::IAnimatedMesh *BordeEsquina;//Mesh del Borde-Esquina
		irr::scene::IAnimatedMesh *BordePared;//Mesh del Borde-Pared
		irr::scene::IMesh *Crosshair;//Mesh del Crosshair

		irr::scene::IMesh *Scene;// Mesh de la Escena
	} Mesh;

	struct BallsTexture
	{
		BallsTexture() :
			//SkyBoxBackgroundImage(),
			ScreenHUDImage(NULL),
			ScoreHUDImage(NULL),
			LevelTitleBackgroundImage(NULL),
			//MacetaActualImage(NULL),
			//MacetaNextImage(NULL),
			WinStatusImage(NULL),
			LoseStatusImage(NULL),
			BossWinStatusImage(NULL),
			BossLoseStatusImage(NULL),
			ResultsTitleImage(NULL),
			ResultsDescriptionImage(NULL),
			BombIconNormalImage(NULL),
			BombIconHoverImage(NULL),
			BombIconPressedImage(NULL),
			BombIconPressedHoverImage(NULL),
			ForwardIconNormalImage(NULL),
			ForwardIconHoverImage(NULL),
			ForwardIconPressedImage(NULL),
			ForwardBackgroundImage(NULL),
			CursorImage(NULL),
			ExtraBombImage(NULL),
			RecordTitleImage(NULL),
			RecordWriteYourNameImage(NULL),
			RecordButtonSendNormalImage(NULL),
			RecordButtonSendHoverImage(NULL),
			RecordButtonCancelNormalImage(NULL),
			RecordButtonCancelHoverImage(NULL),
			LoadingBackgroundImage(NULL),
			LoadingTextImage(NULL),
			//LoadingLughImage(NULL),
			AchievementImage(NULL)
		{
		}

		irr::video::ITexture *SkyBoxBackgroundImage[6];//Texturas del Skybox
		irr::video::ITexture *LightBillboardImage;//Textura de una Luz para saber la posició

		irr::video::ITexture *ScreenHUDImage;//Imagen del HUD
		irr::video::ITexture *ScoreHUDImage;//Imagen sólo del puntaje HUD
		irr::video::ITexture *LevelTitleBackgroundImage;//Fondo del Texto de 'Etapa X'
		irr::video::ITexture *BossLevelTitleImage; //Imagen del Texto "Salva a los Lughitos"

		irr::video::ITexture *MacetaActualImage[7];//Imagenes del bloque siguiente
		irr::video::ITexture *MacetaNextImage[7];// Imagenes chicas del bloque siguiente

		irr::video::ITexture *WinStatusImage;// Imagen de "Ganaste"
		irr::video::ITexture *LoseStatusImage; // Imagen de "Perdiste"
		irr::video::ITexture *BossWinStatusImage; // Imagen de "Ganaste" modo-jefe
		irr::video::ITexture *BossLoseStatusImage; // Imagen de "perdiste" modo-jefe


		irr::video::ITexture *ResultsTitleImage;// Imagen de "¡Felicidades!"
		irr::video::ITexture *ResultsDescriptionImage;// Imagen de detalles de puntaje

		irr::video::ITexture *BombIconNormalImage;//Imagen de la "bomba"
		irr::video::ITexture *BombIconHoverImage;// Imagen de la "bomba" hover
		irr::video::ITexture *BombIconPressedImage;// Imagen de la "bomba" presionada
		irr::video::ITexture *BombIconPressedHoverImage;// Imágen de la "bomba" presionada-hover

		irr::video::ITexture *ForwardIconNormalImage;//Imagen del Avanzar
		irr::video::ITexture *ForwardIconHoverImage;//Imagen del Avanzar hover
		irr::video::ITexture *ForwardIconPressedImage;//Imagen del Avanzar presionada
		irr::video::ITexture *ForwardBackgroundImage;//Fondo del Avanzar

		irr::video::ITexture *CursorImage;//Cursor del mouse
		irr::video::ITexture *ExtraBombImage;//Imagen de Bomba Extra

		irr::video::ITexture *RecordTitleImage;// Imagen de "nuevo record"
		irr::video::ITexture *RecordWriteYourNameImage;// Imagen de "escriba su nombre"

		irr::video::ITexture *RecordButtonSendNormalImage;// Imagen de "enviar"
		irr::video::ITexture *RecordButtonSendHoverImage;// Imagen hover de "enviar"
		irr::video::ITexture *RecordButtonCancelNormalImage;//Imagen de "Cancelar"
		irr::video::ITexture *RecordButtonCancelHoverImage;//Imagen hover de "Cancelar"

		irr::video::ITexture *LoadingBackgroundImage;// Imagen de Fondo del Tiempo de Carga
		irr::video::ITexture *LoadingTextImage;// Imagen de "Cargando"
		irr::video::ITexture *LoadingLughImage[24];// Imagenes del Chanchito girando

		irr::video::ITexture *AchievementImage; // Imagen de "Logro Desbloqueado"

	} Texture;

	struct BallsFont
	{
		BallsFont() :
			HUD(NULL),
			StageTitle(NULL),
			ResultsTotalScore(NULL),
			NameEditBox(NULL),
			Text(NULL)
		{
		}

		irr::gui::IGUIFont* HUD;// Fuente usada para la HUD
		irr::gui::IGUIFont* StageTitle;// Fuente usada para el nivel
		irr::gui::IGUIFont* ResultsTotalScore; // Fuente usada para el puntaje final
		irr::gui::IGUIFont* NameEditBox;// Fuente usada para el ingreso de nombre en el scoreboard
		irr::gui::IGUIFont* Text;//Fuente usada para las ventanas de aviso

	} Font;

	struct BallsMusic
	{
		BallsMusic() :
			Normal(NULL),
			Fast(NULL),
			GameOver(NULL),
			Victory(NULL),
			NewRecord(NULL),
			Boss(NULL),
			BossDefeated(NULL)
		{
		}

		audiere::OutputStreamPtr Normal;// Música Normal
		audiere::OutputStreamPtr Fast;// Música 'rápida'
		audiere::OutputStreamPtr GameOver;// Música para Game Over
		audiere::OutputStreamPtr Victory;// Música para Victoria
		audiere::OutputStreamPtr NewRecord;// Música para nuevo record
		audiere::OutputStreamPtr Boss;//Musica para el Jefe
		audiere::OutputStreamPtr BossDefeated;//Música para derrotar Jefe

	} Music;

	struct BallsSound
	{
		BallsSound() :
			MacetaPut(NULL),
			BombExplosion(NULL),
			MenuHover(NULL),
			MenuPressed(NULL),
			ScoreDetail(NULL),
			ScoreFinal(NULL),
			Achievement(NULL)
		{
		}

		audiere::OutputStreamPtr MacetaPut;//Se colocó una Pieza
		audiere::OutputStreamPtr BombExplosion;//Explosióm Bomba
		
		audiere::OutputStreamPtr MenuHover;//Seleccionada una Opción
		audiere::OutputStreamPtr MenuPressed;//Clic sobre una Opción

		audiere::OutputStreamPtr ScoreDetail;//Aparición de Puntaje
		audiere::OutputStreamPtr ScoreFinal;//Aparición de Puntaje Final

		audiere::OutputStreamPtr Achievement;//Sonido de Logro Desbloqueado
	} Sound;

	/*BallsResources() :
		BallsMesh(),
		BallsTexture(),
		BallsFont() {}*/
};


struct BallsNodes
{

	struct BallsBoard
	{

		BallsBoard() :
			Parent(NULL),
			Lugh(NULL),
			Maceta(NULL),
			SelectedMaceta(NULL),
			AnimationTargetNode(NULL),
			AnimationInitTargetPoint(),
			Jail(NULL),
			Key(NULL),
			Lughitos(NULL),
			Crosshair(NULL),
			Scene(NULL)
		{
		}

		irr::scene::ISceneNode *Parent;//Nodo padre de la Pelota (para aplicar rotaciones y movimiento)
		irr::scene::IAnimatedMeshSceneNode *LughStand; // Nodo de Lugh parado
		irr::scene::IAnimatedMeshSceneNode *Lugh;// Nodo de Lugh
		irr::scene::ISceneNode *Maceta;// Nodo del bloque transparente
		irr::scene::ISceneNode *SelectedMaceta;// Nodo seleccionado con el mouse

		//irr::scene::IAnimatedMeshSceneNode *ActualMacetaNode;//Nodo Maceta actual
		//irr::scene::IAnimatedMeshSceneNode *NextMacetaNode;//Nodo Maceta siguiente

		irr::scene::ISceneNode *AnimationTargetNode;//Punto de inicio animación (objetivo) de camara
		irr::core::vector3df AnimationInitTargetPoint;//Punto de inicio animación (objetivo) de camara
		//irr::core::vector3df AnimationEndTargetPoint;//Punto de termino animación (objetivo) de camara
		//irr::core::vector3df AnimationEndPositionPoint;//Punto de término animación (posición) de camara

		irr::scene::ISceneNode *Jail; //Nodo de la Jaula
		irr::scene::ISceneNode *Key;//Nodo de la Llave
		irr::scene::ISceneNode *Lughitos;//Nodo de los Lughitos

		irr::scene::ISceneNode *Crosshair;//Nodo del Crosshair

		irr::scene::ISceneNode *Scene;// Nodo de Escenario
	} Board;

	struct BallsCamera
	{

		BallsCamera() :
			FPS(NULL),
			Node(NULL),
			Position(),
			Target()
		{
		}

		irr::scene::ICameraSceneNode* FPS;// Camara FPS
		irr::scene::ICameraSceneNode* Node; // Camara
		irr::core::vector3df Position;// Posicion de la Camara
		irr::core::vector3df Target;// Objetivo de la Camara

	} Camera;

	struct BallsHUD
	{
		BallsHUD() :
			StageTitleTextPosition(),
			ClockTextPosition(),
			ScoreTextPosition(),
			BombsTextPosition(),
			ScreenHUDPosition(),
			ScoreHUDPosition(),
			LevelTitleBackgroundPosition(),
			MacetaActualPosition(),
			MacetaNextPosition(),
			ExtraBombPosition(),
			VictoryStatusPosition(),
			GameOverStatusPosition(),
			ResultsTitlePosition(),
			ResultsDescriptionPosition(),
			BombsIconPosition(),
			ForwardIconPosition(),
			ForwardBackgroundPosition(),
			RecordTitlePosition(),
			RecordWriteYourNamePosition(),
			RecordButtonSendPosition(),
			RecordButtonCancelPosition(),
			RecordNameEditBoxPosition(),
			ScreenHUD(NULL),
			ScoreHUD(NULL),
			LevelTitleBackground(NULL),
			BossLevelTitle(NULL),
			ExtraBomb(NULL),
			//MaceActual(NULL),
			//MacetaNext(NULL,
			WinStatus(NULL),
			LoseStatus(NULL),
			ResultsTitle(NULL),
			ResultsDescription(NULL),
			BombIconNormal(NULL),
			BombIconHover(NULL),
			BombIconPressed(NULL),
			BombIconPressedHover(NULL),
			ForwardIconNormal(NULL),
			ForwardIconHover(NULL),
			ForwardIconPressed(NULL),
			ForwardBackground(NULL),
			RecordTitle(NULL),
			RecordWriteYourName(NULL),
			RecordButtonSendNormal(NULL),
			RecordButtonSendHover(NULL),
			RecordButtonCancelNormal(NULL),
			RecordButtonCancelHover(NULL),
			RecordNameEditBox(NULL)
		{
		}


		irr::core::rect<irr::s32> StageTitleTextPosition;// Posición de la imágen "Level 1"
		irr::core::rect<irr::s32> ClockTextPosition;// Posicion del reloj
		irr::core::rect<irr::s32> ScoreTextPosition;// Posicion del puntaje
		irr::core::rect<irr::s32> BombsTextPosition;// Posicion del contador de bombas
		
		irr::core::vector2d<irr::s32> ScreenHUDPosition; // Posición pre-calculada de la imágen de HUD
		irr::core::vector2d<irr::s32> ScoreHUDPosition; // Posición pre-calculada del puntaje de HUD
		irr::core::vector2d<irr::s32> LevelTitleBackgroundPosition; // Posición pre-calculada del fondo del texto de 'etapa x'
		irr::core::vector2d<irr::s32> BossLevelTitlePosition; //Posición pre-calculada de la imágen del texto de 'salva a los lughitos'

		irr::core::vector2d<irr::s32> MacetaActualPosition;// Posicion del bloque siguiente
		irr::core::vector2d<irr::s32> MacetaNextPosition;// Posición del bloque pequeño siguiente
		irr::core::vector2d<irr::s32> ExtraBombPosition;//Posición de la imágen de 'Bomba Extra'

		irr::core::vector2d<irr::s32> VictoryStatusPosition; // Posicion pre-calculada de la imagen de victoria
		irr::core::vector2d<irr::s32> GameOverStatusPosition; // Posicion pre-calculada de la imagen de derrota
		irr::core::vector2d<irr::s32> BossVictoryStatusPosition; // Posicion pre-calculada de la imagen de victoria modo-jefe
		irr::core::vector2d<irr::s32> BossGameOverStatusPosition; // Posicion pre-calculada de la imagen de derrota modo-jefe
		irr::core::vector2d<irr::s32> ResultsTitlePosition;// Posicion pre-calculada de la imágen del título de descripción de puntaje
		irr::core::vector2d<irr::s32> ResultsDescriptionPosition;// Posición pre-calculada de la imagen de descripción de puntaje

		irr::core::vector2d<irr::s32> BombsIconPosition; // Posición del icono de Bomba
		irr::core::vector2d<irr::s32> ForwardIconPosition; //Posición del icono de Avanzar
		irr::core::vector2d<irr::s32> ForwardBackgroundPosition;//Posición del fondo de la Bomba
		irr::core::vector2d<irr::s32> RecordTitlePosition;// Posición de la imagen "has hecho un record"
		irr::core::vector2d<irr::s32> RecordWriteYourNamePosition;// Posicion de la imágen "escribe tu nombre"
		irr::core::vector2d<irr::s32> RecordButtonSendPosition;// Posicion de la imágen "enviar"
		irr::core::vector2d<irr::s32> RecordButtonCancelPosition;// Posición de la imagen "cancelar"
		
		irr::core::rect<irr::s32> RecordNameEditBoxPosition; // Posicion de la caja de texto "nombre"

		irr::core::vector2d<irr::s32> AchievementPosition; // Posición de la imágen "Logro desbloqueado"

		irr::gui::IGUIImage *ScreenHUD; // Imagen del HUD
		irr::gui::IGUIImage *ScoreHUD; // Imágen del Puntaje
		irr::gui::IGUIImage *LevelTitleBackground; // Imágen de fondo del 'etapa x'
		irr::gui::IGUIImage *BossLevelTitle;//Imagen de "Salva a los Lughitos"
		irr::gui::IGUIImage *ExtraBomb; //Imagen de 'extra bomba'

		irr::gui::IGUIImage *MacetaActual[7];// Imagen del bloque siguiente
		irr::gui::IGUIImage *MacetaNext[7];// Imagen pequeña del bloque siguiente

		irr::gui::IGUIImage *WinStatus;// Imagen de "Ganaste"
		irr::gui::IGUIImage *LoseStatus;// Imagen de "Perdiste"

		irr::gui::IGUIImage *ResultsTitle;//Imagen de "¡Felicidades!"
		irr::gui::IGUIImage *ResultsDescription;// Imagen de descripción de puntaje

		// Iconos de Bomba
		irr::gui::IGUIImage *BombIconNormal;
		irr::gui::IGUIImage *BombIconHover;
		irr::gui::IGUIImage *BombIconPressed;
		irr::gui::IGUIImage *BombIconPressedHover;

		// Iconos de Avanzar
		irr::gui::IGUIImage *ForwardIconNormal;
		irr::gui::IGUIImage *ForwardIconHover;
		irr::gui::IGUIImage *ForwardIconPressed;
		irr::gui::IGUIImage *ForwardBackground;

		irr::gui::IGUIImage *RecordTitle;// Imagen de "¡Has hecho un record!"
		irr::gui::IGUIImage *RecordWriteYourName; // Imagen de "Escribe tu nombre"

		irr::gui::IGUIImage *RecordButtonSendNormal;// Imagen de "enviar"
		irr::gui::IGUIImage *RecordButtonSendHover;// Imagen hover de "enviar"
		irr::gui::IGUIImage *RecordButtonCancelNormal;//Imagen de "Cancelar"
		irr::gui::IGUIImage *RecordButtonCancelHover;//Imagen hover de "Cancelar"

		irr::gui::IGUIEditBox *RecordNameEditBox;// Campo de Texto para el nombre

		irr::gui::IGUIImage *Achievement;

	} HUD;

	struct BallsLoading
	{
		BallsLoading() :
			BgRect(),
			BgPosition(),
			PigRect(),
			PigPosition(),
			TextRect(),
			TextPosition()
		{
		}

		irr::core::rect<irr::s32> BgRect;
		irr::core::vector2d<irr::s32> BgPosition;

		irr::core::rect<irr::s32> PigRect;
		irr::core::vector2d<irr::s32> PigPosition;

		irr::core::rect<irr::s32> TextRect;
		irr::core::vector2d<irr::s32> TextPosition;

	} Loading;

	struct BallsLights
	{
		BallsLights() :
			TestLight()
		{
		}

		irr::scene::ISceneNode* TestLight;
	} Lights;

	/*BallsNodes() :
		BallsBoard(),
		BallsCamera(),
		BallsHUD() {}*/
};

struct BallsVariables
{
	struct BallsMatrix
	{
		BallsMatrix() :
			Cols(0),
			Rows(0) {}

		uint16 Cols;// Número de columnas de la matriz
		uint16 Rows;// Número de filas de la matriz

	} Matrix;

	struct BallsGlobal
	{
		BallsGlobal() :
			LevelsPerBoss(0),
			KeyHeight(0.0f),
			BallHeight(0.0f),
			CrosshairHeight(0.0f),
			IndexShowElement(0),
			InitBallSpeed(0),
			InitBallRotationSpeed(0.0f),
			KeyRotationSpeed(0.0f),
			FactorSpeedInc(0.0f)
		{
		}

		uint16 LevelsPerBoss; // Numero de Etapas por Jefe
		real KeyHeight;//Altura de la Llave
		real BallHeight;//Altura de la Pelota
		real CrosshairHeight;//Altura del Crosshair
		uint16 IndexShowElement;// Indicador de si se muestra una variables
		irr::s32 InitBallSpeed;// Velocidad inicial de la pelota
		real InitBallRotationSpeed;// Velocidad inicial de rotacion de la pelota
		real KeyRotationSpeed;

		real FactorSpeedInc;// Factor de incremento de la velocidad de la pelota por nivel

	} Global;

	struct BallsScore
	{
		BallsScore() :
			FactorLevelScore(0.0f),
			FactorPasses(0),
			FactorUnpasses(0),
			FactorBonusTime(0),
			FactorBonusBombs(0),
			BossFactorPasses(0),
			BossFactorUnpasses(0),
			BonusBossDefeated(0),
			MaxUnpassesBlocks(0)
		{
		}

		real FactorLevelScore;// Factor de multiplicacion al puntaje por cada nivel
		real FactorBossScore;//Factor de multiplicación al puntaje por cada jefe

		uint16 FactorPasses;//Factor puntaje bloques pasados
		uint16 FactorUnpasses;//Factor puntaje bloques no-pasados
		uint16 FactorBonusTime;//Factor puntaje tiempo
		uint16 FactorBonusBombs;//Factor puntaje bombas

		uint16 BossFactorPasses;//Factor Puntaje bloques pasados Jefe
		uint16 BossFactorUnpasses;//Factor puntaje bloques no-pasados Jefe
		uint16 BonusBossDefeated;//Bonus derrotar Jefe

		uint16 MaxUnpassesBlocks;// Numero maximo de bloques que pueden sobrar

	} Score;

	struct BallsLoading
	{
		BallsLoading() :
			ActualPig( 0 )
		{
		}

		uint16 ActualPig;
	} Loading;

	struct BallsSwitch
	{
		BallsSwitch() :
			InsertMacetaMode(true),
			StartBallMoving(false),
			ForwardButtonPressed(false)
		{
		}

		bool InsertMacetaMode; //TRUE si esta en modo colocar, FALSE si está en modo borrar
		bool StartBallMoving; // Indicador de si la pelota comienza a moverse
		bool ForwardButtonPressed; // Indicador de si se presiono el boton de Avanzar

		bool ScoreShowElement[5];

	} Switch;

	struct BallsRandom
	{
		BallsRandom() :
			NroMeshes(0),
			RandomMesh(0),
			RandomMeshNext(0),
			RandomProbability(0)
		{
		}

		uint16 NroMeshes;//Numero de meshes
		uint16 RandomMesh;//Numero Azar
		uint16 RandomMeshNext;//Numero Azar Siguiente
		uint16 RandomProbability;// Probabilidad de que el nuevo bloque sea diferente al anterior

	} Random;

	struct BallsString
	{
		//BallsString() {}

		wchar_t PuntajePiezas[12];
		wchar_t PuntajeSobras[12];
		wchar_t PuntajeBonus[12];
		wchar_t PuntajeTotal[12];
		wchar_t Puntaje[12];//Texto Puntaje

		wchar_t RemainingBombs[5];

	} String;

	/*BallsVariables() :
		BallsMatrix(),
		BallsGlobal(),
		BallsSwitch(),
		BallsRandom() {}*/
};

#endif
