#ifndef ___Balls__ContextMain__H___
#define ___Balls__ContextMain__H___

#include <Tornado.h>

#include "Balls_Structs.h"
#include "Balls_Matrix.h"
#include "Balls_Scoreboard.h"
#include "Balls_TrophiesManager.h"

using namespace Tornado;

class BallsContextMain : public CContext
{

private:

	static uint16 Level;// Nivel Actual
	static uint16 BossLevel;//Nivel de Jefe
	static uint32 Puntaje;// Puntaje
	static uint16 RemainingBombs;//Bombas Restantes
	static real RemainingTime;// Tiempo Restante
	static irr::s32 BallSpeed; // Velocidad de la pelota
	static irr::f32 BallRotationSpeed; // Velocidad de rotación de la pelota
	static bool IsBossTime;//Indicador de si es hora del Jefe

	bool AchievementUnlocked;

	uint16 GameStatus;//Estado del juego

	BallsResources Resources;
	BallsNodes Nodes;
	BallsVariables Variables;
	BallsMatrix Matrix;
	BallsScoreboard Scoreboard;
	BallsTrophiesManager TrophiesManager;

	CClock Clock; // Reloj
	CClock TrophyClock; // Reloj para Logros
	CClock LoadingClock; // Reloj para Loading

	irr::core::vector2di MousePosition;// Posicion del Mouse

	#if defined(DEBUG_MODE)
	bool DebugFPSMode; // Indicador de camara FPS
	real DebugDesp;
	irr::scene::ISceneNode *DebugNode;
	#endif
	//irr::core::vector3df CameraLookNew;

	
	

	//irr::scene::ITextSceneNode *Time;// Texto del Tiempo en pantalla


	//irr::s32 Width; // Ancho de la ventana
	//irr::s32 Height;// Alto de la ventana

protected:
public:
	BallsContextMain(uint16 Id,bool HaveLoading);
	~BallsContextMain();

	bool Init(void);
	void Prepare(void);
	void Next(real Delta);
	void Draw(void);
	void End(void);

	bool LoadingInit(void);
	void LoadingPrepare(void);
	void LoadingNext(real Delta);
	void LoadingDraw(void);
	void LoadingEnd(void);

	void Close(void);


	bool OnGUIEvent(irr::gui::IGUIElement *Caller,irr::gui::IGUIElement *Element,const uint16 &EventType);
	//bool OnJoystickEvent(const irr::SEvent::SJoystickEvent &Event);
	bool OnKeyInput(const uint16 &Key,const wchar_t &Char,const bool isCtrl,const bool isShift,const bool isPressedDown);
	bool OnMouseInput(const uint16 &EventType,const sint32 &X,const sint32 &Y,const real &Wheel,const bool isLeft,const bool isMiddle,const bool isRight,const bool isCtrl,const bool isShift);
	//bool OnUserEvent(const sint32 &UserData1,const sint32 &UserData2);

	void CreateRandomMaceta(bool Both = false);
	void StartBallAnimation(void);
	void MoveBall(bool Save=false);
	void SelectEmptyMacetaNode(const sint32 &tmp_X,const sint32 &tmp_Y);
	void SelectPutMacetaNode(const sint32 &tmp_X,const sint32 &tmp_Y);
	bool DeleteMacetaNode(void);
	bool PutMacetaNode(void);
	void CreateMacetaNode(uint16 id);
	void UnlockTrophy(uint16 Id);
};

#endif