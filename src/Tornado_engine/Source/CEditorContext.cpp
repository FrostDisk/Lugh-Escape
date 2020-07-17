/* ********************************************************************
 * Tornado-Engine : Motor de Videojuegos Tornado                      *
 * =================================================================  *
 *                                                                    *
 * Copyright (c) 2011 por FrostDisk                                   *
 * Correo Electrónico: project-tornado@frostdisk.com                  *
 * Módulo: Codigo Fuente de Clase Contexto de Editor                  *
 * Archivo Fuente: CEditorContext.cpp                                 *
 *                                                                    *
 * Este archivo es propietario y de uso exclusivo por personal de     *
 * FrostDisk. Cualquier distribución, modificación y/o copia no       *
 * autorizada infringe los términos de la licencia para uso y         *
 * distribución de aplicaciones hechas por FrostDisk.                 *
 *                                                                    *
 **********************************************************************/

#include "CEditorContext.h"
#include "CConfig.h"
#include "CVideo.h"
#include "CSceneManager.h"
#include "CGUIEnvironment.h"
#include "CEffects.h"
#include "COutput.h"
#include "CMath.h"

#include "SVideoMode.h"
#include "EGUIEditorControl.h"
#include "EGUIEditorViewportControl.h"

#include <typeinfo.h>

namespace Tornado
{

	/**
	 * \brief Inicializa los recursos del Contexto de Editor
	 */
	bool CEditorContext::InitResources(void)
	{
		irr::gui::IGUIEnvironment *env = GameDevices->GUIEnvironment->GetGUIEnvironment();
		irr::scene::ISceneManager *smgr = GameDevices->SceneManager->GetSceneManager();

		Elements.Global.Font = env->getFont(L"Media/fontlucida.png");

		//Elements.Global.Wire = new CWireEditorSceneNode( smgr->getRootSceneNode() , smgr , 10 );
		//Elements.Global.Wire->setScale(irr::core::vector3df(10.0f,10.0f,10.0f));

		Center = irr::core::vector2df( (irr::f32)Width * 0.5f , (irr::f32)Height * 0.5f );
		return true;
	}

	/**
	 * \brief Dibuja lo ejes coordenados en una posición
	 * \param tmp_Position Posición donde se dibujaran los ejes
	 */
	void CEditorContext::ShowArrowAxis(irr::core::vector3df position)
	{
		irr::gui::IGUIEnvironment *env = GameDevices->GUIEnvironment->GetGUIEnvironment();
		irr::scene::ISceneManager *smgr = GameDevices->SceneManager->GetSceneManager();

		if( !Elements.ArrowAxis.Parent )
		{
			Elements.ArrowAxis.Parent = smgr->addEmptySceneNode();

			Elements.ArrowAxis.XAxi = smgr->addAnimatedMeshSceneNode(	smgr->addArrowMesh(
														L"Red",
														irr::video::SColor(0xFF,0xFF,0x00,0x00),
														irr::video::SColor(0xFF,0xFF,0x00,0x00),
														4,8,3.0,2	),
													Elements.ArrowAxis.Parent);
			Elements.ArrowAxis.XAxi->setMaterialFlag(irr::video::EMF_LIGHTING, false);
			Elements.ArrowAxis.XAxi->setRotation(irr::core::vector3df(0, 0,-90));
			Elements.ArrowAxis.XAxi->setScale(irr::core::vector3df(20,20,20));

			Elements.ArrowAxis.YAxi = smgr->addAnimatedMeshSceneNode(	smgr->addArrowMesh(
														L"Green",
														irr::video::SColor(0xFF,0x00,0xFF,0x00),
														irr::video::SColor(0xFF,0x00,0xFF,0x00),
														4,8,3.0,2	),
													Elements.ArrowAxis.Parent);
			Elements.ArrowAxis.YAxi->setMaterialFlag(irr::video::EMF_LIGHTING, false);
			Elements.ArrowAxis.YAxi->setRotation(irr::core::vector3df(0, 90, 0));
			Elements.ArrowAxis.YAxi->setScale(irr::core::vector3df(20,20,20));

			Elements.ArrowAxis.ZAxi = smgr->addAnimatedMeshSceneNode(	smgr->addArrowMesh(
														L"Blue",
														irr::video::SColor(0xFF,0x00,0x00,0xFF),
														irr::video::SColor(0xFF,0x00,0x00,0xFF),
														4,8,3.0,2	),
													Elements.ArrowAxis.Parent);
			Elements.ArrowAxis.ZAxi->setMaterialFlag(irr::video::EMF_LIGHTING, false);
			Elements.ArrowAxis.ZAxi->setRotation(irr::core::vector3df(90, 0, 0));
			Elements.ArrowAxis.ZAxi->setScale(irr::core::vector3df(20,20,20));
		}

		Elements.ArrowAxis.Parent->setPosition( position );
	}

	/**
	 * \brief Crea la GUI por defecto
	 */
	void CEditorContext::PrepareGUI(void)
	{

		GameDevices->Video->SetCursorVisibility(true);
		irr::video::IVideoDriver* driver = GameDevices->Video->GetVideoDevice()->getVideoDriver();;
		irr::gui::IGUISkin *skin = GameDevices->GUIEnvironment->GetGUISkin();
		irr::gui::IGUIEnvironment *env = GameDevices->GUIEnvironment->GetGUIEnvironment();
		irr::scene::ISceneManager *smgr = GameDevices->SceneManager->GetSceneManager();

		if( Elements.Global.Font )
		{
			skin->setFont( Elements.Global.Font );
		}

		Elements.Windows.Properties = env->addWindow( irr::core::rect<irr::s32>( Width-200,60,Width-10,Height-10) , false );
		irr::core::rect<irr::s32> areawin = Elements.Windows.Properties->getAbsolutePosition();
		Elements.Windows.Properties->setDrawTitlebar(false);
		Elements.Windows.Properties->setDraggable(false);
		Elements.Windows.Properties->getCloseButton()->remove();
		
		/*
		env->addButton( irr::core::rect<irr::s32>( 10,areawin.getHeight()-110,180,areawin.getHeight()-90 ),Elements.Windows.Properties,-1,L"Todo");
		env->addButton( irr::core::rect<irr::s32>( 10,areawin.getHeight()-90,180,areawin.getHeight()-70 ),Elements.Windows.Properties,-1,L"Mapeado");
		env->addButton( irr::core::rect<irr::s32>( 10,areawin.getHeight()-70,180,areawin.getHeight()-50 ),Elements.Windows.Properties,-1,L"Entidades");
		env->addButton( irr::core::rect<irr::s32>( 10,areawin.getHeight()-50,180,areawin.getHeight()-30 ),Elements.Windows.Properties,-1,L"Camaras");
		env->addButton( irr::core::rect<irr::s32>( 10,areawin.getHeight()-30,180,areawin.getHeight()-10 ),Elements.Windows.Properties,-1,L"Triggers");
		*/

		// Ventana de información
		/*
		GUIEditorInfoElements.Window = env->addWindow( irr::core::rect<irr::s32>( 10,100,144,228 ) , false );
		env->addStaticText( L"Position" , irr::core::rect<irr::s32>(8,19,135,32),false,false,GUIEditorInfoElements.Window);
		env->addStaticText( L"Scale" , irr::core::rect<irr::s32>(8,54,135,67),false,false,GUIEditorInfoElements.Window);
		env->addStaticText( L"Rotation" , irr::core::rect<irr::s32>(8,89,135,102),false,false,GUIEditorInfoElements.Window);

		GUIEditorInfoElements.Pos.X = env->addEditBox( L"" , irr::core::rect<irr::s32>(5,33,45,53),true,GUIEditorInfoElements.Window);
		GUIEditorInfoElements.Pos.X = env->addEditBox( L"" , irr::core::rect<irr::s32>(47,33,87,53),true,GUIEditorInfoElements.Window);
		GUIEditorInfoElements.Pos.Z = env->addEditBox( L"" , irr::core::rect<irr::s32>(89,33,129,53),true,GUIEditorInfoElements.Window);

		GUIEditorInfoElements.Sca.X = env->addEditBox( L"" , irr::core::rect<irr::s32>(5,68,45,88),true,GUIEditorInfoElements.Window);
		GUIEditorInfoElements.Sca.Y = env->addEditBox( L"" , irr::core::rect<irr::s32>(47,68,87,88),true,GUIEditorInfoElements.Window);
		GUIEditorInfoElements.Sca.Z = env->addEditBox( L"" , irr::core::rect<irr::s32>(89,68,129,88),true,GUIEditorInfoElements.Window);

		GUIEditorInfoElements.Rot.X = env->addEditBox( L"" , irr::core::rect<irr::s32>(5,103,45,123),true,GUIEditorInfoElements.Window);
		GUIEditorInfoElements.Rot.Y = env->addEditBox( L"" , irr::core::rect<irr::s32>(47,103,87,123),true,GUIEditorInfoElements.Window);
		GUIEditorInfoElements.Rot.Z = env->addEditBox( L"" , irr::core::rect<irr::s32>(89,103,129,123),true,GUIEditorInfoElements.Window);

		GUIEditorInfoElements.Window->setVisible(false);
		GUIEditorInfoElements.Window->getCloseButton()->remove();
		GUIEditorInfoElements.VisibleWindow = false;
		*/

		// Creando los elementos de la ventana de Viewport
		// No funciona por ahora
		/*GUIEditorViewportElements.Window = env->addWindow( irr::core::rect<irr::s32>( 10,Height-110,110,Height-10 ), false );
		GUIEditorViewportElements.Up = env->addButton( irr::core::rect<irr::s32>(  2,22,48,58 ), GUIEditorViewportElements.Window,EGEVC_ID_BUTTON_UP,L"Up");
		GUIEditorViewportElements.Front = env->addButton( irr::core::rect<irr::s32>(  2,62,48,98 ), GUIEditorViewportElements.Window,EGEVC_ID_BUTTON_FRONT,L"Front");
		GUIEditorViewportElements.Side = env->addButton( irr::core::rect<irr::s32>( 52,22,98,58 ), GUIEditorViewportElements.Window,EGEVC_ID_BUTTON_SIDE,L"Side");
		GUIEditorViewportElements.Persp = env->addButton( irr::core::rect<irr::s32>( 52,62,98,98 ), GUIEditorViewportElements.Window,EGEVC_ID_BUTTON_PERSP,L"Persp");
		GUIEditorViewportElements.Ortho = env->addButton( irr::core::rect<irr::s32>( 52,62,98,98 ), GUIEditorViewportElements.Window,EGEVC_ID_BUTTON_ORTHO,L"Ortho");
		GUIEditorViewportElements.Ortho->setVisible(false);*/


		// Aqui se crea la cámara
		//Camera = smgr->addCameraSceneNode();
		Elements.Global.Camera = smgr->addCameraSceneNodeMaya();
		//Camera->setTarget(irr::core::vector3df(-50,20,-60));
		Elements.Global.Camera->setPosition(irr::core::vector3df(-500,550,-500));
		Elements.Global.Camera->setFarValue(42000.0f);



		// Dibujar los ejes
		ShowArrowAxis( irr::core::vector3df(0.0f,0.0f,0.0f) );

		

		irr::gui::IGUIContextMenu *menu = env->addMenu();

		menu->addItem(L"Context",-1,true,true);
		menu->addItem(L"Edit",-1,true,true);
		menu->addItem(L"Insert",-1,true,true);
		menu->addItem(L"Object",-1,false,true);
		menu->addItem(L"Tools",-1,true,true);
		menu->addItem(L"View",-1,true,true);
		menu->addItem(L"Help",-1,true,true);

		irr::gui::IGUIContextMenu* submenu;

		// Contexto
		submenu = menu->getSubMenu(0);
		submenu->addItem(L"New",EGEC_ID_MENU_CONTEXT_NEW,true,false);
		submenu->addItem(L"Open...",EGEC_ID_MENU_CONTEXT_OPEN,true,false);
		submenu->addSeparator();
		submenu->addItem(L"Save",EGEC_ID_MENU_CONTEXT_SAVE,true,false);
		submenu->addItem(L"Save as...",EGEC_ID_MENU_CONTEXT_SAVEAS,true,false);
		submenu->addSeparator();
		submenu->addItem(L"Import",-1,true,true);
		submenu->addSeparator();
		submenu->addItem(L"Exit",EGEC_ID_MENU_CONTEXT_CLOSEEDITOR,true,false);

		// Contexto -> Importar desde
		submenu = menu->getSubMenu(0)->getSubMenu(6);
		submenu->addItem(L".irr file",EGEC_ID_MENU_CONTEXT_IMPORT_IRRFILE,true,false);

		// Edición
		submenu = menu->getSubMenu(1);
		submenu->addItem(L"Undo",EGEC_ID_MENU_EDIT_UNDO,true,false);
		submenu->addItem(L"Redo",EGEC_ID_MENU_EDIT_REDO,true,false);
		submenu->addSeparator();
		submenu->addItem(L"Clone",EGEC_ID_MENU_EDIT_CLONE,true,false);
		submenu->addItem(L"Remove",EGEC_ID_MENU_EDIT_DELETE,true,false);

		// Insertar
		submenu = menu->getSubMenu(2);
		submenu->addItem(L"Object",-1,true,true);
		submenu->addItem(L"Bbox",-1,true,true);
		submenu->addItem(L"Light",EGEC_ID_MENU_INSERT_LIGHT,true,false);

		// Insertar -> Objeto
		submenu = menu->getSubMenu(2)->getSubMenu(0);
		submenu->addItem(L"Cube",EGEC_ID_MENU_INSERT_OBJECT_CUBE,true,false);
		submenu->addItem(L"Sphere",EGEC_ID_MENU_INSERT_OBJECT_SPHERE,true,false);
		submenu->addItem(L"Terrain",EGEC_ID_MENU_INSERT_OBJECT_TERRAIN,true,false);
		submenu->addItem(L"SkyBox",EGEC_ID_MENU_INSERT_OBJECT_SKYBOX,true,false);
		submenu->addItem(L"OctTree",EGEC_ID_MENU_INSERT_OBJECT_OCTREE,true,false);
		submenu->addItem(L"Mesh",EGEC_ID_MENU_INSERT_OBJECT_MESH,true,false);
		submenu->addItem(L"Light",EGEC_ID_MENU_INSERT_OBJECT_LIGHT,true,false);
		submenu->addItem(L"Empty SceneNode",EGEC_ID_MENU_INSERT_OBJECT_EMPTYSCENENODE,true,false);
		submenu->addItem(L"Camera",EGEC_ID_MENU_INSERT_OBJECT_CAMERA,true,false);
		submenu->addItem(L"Billboard",EGEC_ID_MENU_INSERT_OBJECT_BILLBOARD,true,false);
		submenu->addItem(L"Animated Mesh",EGEC_ID_MENU_INSERT_OBJECT_ANIMATEDMESH,true,false);
		submenu->addItem(L"Particle System",EGEC_ID_MENU_INSERT_OBJECT_PARTICLESYSTEM,true,false);

		// Insertar -> Bbox
		submenu = menu->getSubMenu(2)->getSubMenu(1);
		submenu->addItem(L"Sphere",EGEC_ID_MENU_INSERT_BBOX_SPHERE,true,false);
		submenu->addItem(L"Box",EGEC_ID_MENU_INSERT_BBOX_BOX,true,false);
		submenu->addItem(L"Capsule",EGEC_ID_MENU_INSERT_BBOX_CAPSULE,true,false);
		submenu->addItem(L"Cylinder",EGEC_ID_MENU_INSERT_BBOX_CYLINDER,true,false);
		submenu->addItem(L"Cone",EGEC_ID_MENU_INSERT_BBOX_CONE,true,false);
		submenu->addItem(L"Chamfer Cylinder",EGEC_ID_MENU_INSERT_BBOX_CHAMFERCYLINDER,true,false);
		submenu->addItem(L"Null",EGEC_ID_MENU_INSERT_BBOX_NULL,true,false);
		submenu->addItem(L"Compound",EGEC_ID_MENU_INSERT_BBOX_COMPOUND,false,false);
		submenu->addItem(L"Convex Hull",EGEC_ID_MENU_INSERT_BBOX_CONVEXHULL,false,false);


		// Herramientas
		submenu = menu->getSubMenu(4);
		submenu->addItem(L"Preferences...",EGEC_ID_MENU_TOOLS_PREFERENCES,true,false);

		// Vista
		submenu = menu->getSubMenu(5);
		submenu->addItem(L"Toolbar",EGEC_ID_MENU_VIEW_SHOWTOOLS,true,false,true);
		submenu->addItem(L"Update GUI",EGEC_ID_MENU_VIEW_UPDATEGUI,true,false);

		// Ayuda
		submenu = menu->getSubMenu(6);
		submenu->addItem(L"About",-1,true,false);


		/*irr::gui::IGUIToolBar* toolbar = env->addToolBar();

		irr::video::ITexture* image = driver->getTexture("Media/editor/blank.png");

		toolbar->addButton(-1, 0,L"",image,0,false,true);
		toolbar->addButton(-1, 0,L"",image,0,false,true);
		toolbar->addButton(-1, 0,L"",image,0,false,true);
		toolbar->addButton(-1, 0,L"",image,0,false,true);
		toolbar->addButton(-1, 0,L"",image,0,false,true);
		toolbar->addButton(-1, 0,L"",image,0,false,true);
		toolbar->addButton(-1, 0,L"",image,0,false,true);
		toolbar->addButton(-1, 0,L"",image,0,false,true);
		toolbar->addButton(-1, 0,L"",image,0,false,true);
		toolbar->addButton(-1, 0,L"",image,0,false,true);
		toolbar->addButton(-1, 0,L"",image,0,false,true);
		toolbar->addButton(-1, 0,L"",image,0,false,true);
		toolbar->addButton(-1, 0,L"",image,0,false,true);
		toolbar->addButton(-1, 0,L"",image,0,false,true);
		toolbar->addButton(-1, 0,L"",image,0,false,true);
		toolbar->addButton(-1, 0,L"",image,0,false,true);*/
	}

	/**
	 * \brief Selecciona el nodo que está tocando el cursor del Mouse
	 * \param tmp_X posición X del cursor del mouse
	 * \param tmp_Y posición Y del cursor del mouse
	 */
	void CEditorContext::SceneNodeMousePick(irr::s32 mouseRx,irr::s32 mouseRy)
	{
		irr::scene::ISceneManager *smgr = GameDevices->SceneManager->GetSceneManager();
		irr::scene::ISceneCollisionManager* collMan = smgr->getSceneCollisionManager(); //Colision Manager

		//Declaro una linea de intersección
		irr::core::line3d<irr::f32> ray;
		//Con esto creo una linea en 3D usando las coordenadas del mouse y la camara activa
		ray = collMan->getRayFromScreenCoordinates(irr::core::position2d<irr::s32>(mouseRx,mouseRy));

		//No se si se utilizara esto...
		// Tracks the current intersection point with the level or a mesh
		irr::core::vector3df intersection;

		// Used to show with triangle has been hit
		irr::core::triangle3df hitTriangle;

		//irr::scene::ISceneNode *ActiveSceneNode = SelectedSceneNode;

		//Deselecciono lo que selecione previamente
		if(SelectedSceneNode)
		{
			SelectedSceneNode->setDebugDataVisible(irr::scene::EDS_OFF);
		}
		/*if(SelectedLight)
		{
			SelectedLight->Target->setVisible(false);
		}*/

		//Chequeo colision
		SelectedSceneNode = collMan->getSceneNodeAndCollisionPointFromRay(
				ray,
				intersection, // This will be the position of the collision
				hitTriangle, // This will be the triangle hit in the collision
				EMPF_PICKABLE, // This ensures that only nodes that we have
				// set up to be pickable are considered
				0); // Check the entire scene (this is actually the implicit default)

		//Seleccionar lo que seleccione
		if(SelectedSceneNode)
		{
			/*if( GUIEditorInfoElements.VisibleWindow ){
				GUIEditorInfoElements.Window->setEnabled(true);
			}*/
			SelectedSceneNode->setDebugDataVisible(irr::scene::EDS_BBOX);
			Mode = EGEM_MESH_PICKED;

			irr::s32 Id = SelectedSceneNode->getID();
			if( (Id&EMPF_LIGHT) || (Id&EMPF_TARGET) )
			{
				COutput::Wprintf(L"Toque una luz\n");
				std::list<SGUIEditorLightElement *>::iterator it;
				for( it=Lights.begin() ; it!=Lights.end() ; it++)
				{
					if( (*it)->Node == SelectedSceneNode || (*it)->Target == SelectedSceneNode )
					{
						SelectedLight = (*it);
						SelectedLight->Target->setVisible(true);
						break;
					}
				}
			}
		}
		else
		{
			//GUIEditorInfoElements.Window->setEnabled(false);
			Mode = EGEM_DEFAULT;
		}
	}

	/**
	 * \brief Constructor de Clase
	 * \param tmp_id ID de Contexto
	 * \param tmp_haveloading Indicador de si el Contexto tiene Tiempo de Carga
	 */
	CEditorContext::CEditorContext(	uint16 contextId,
									bool haveLoading ) :
										CContext(contextId,haveLoading),
										LastNodeId(0),
										LastLightId(0),
										SelectedSceneNode(NULL),
										SelectedLight(NULL),
										Nodes(),
										Lights(),
										Mode(EGEM_DEFAULT),
										Function(EGEF_DEFAULT),
										Transform(EGET_NONE)
	{
	}

	/**
	 * \brief Destructor de Clase
	 */
	CEditorContext::~CEditorContext()
	{
		#if defined(_DEBUG)
		COutput::Wprintf(L"Destruyendo CEditorContext(%d)\n",GetId());
		#endif
	}

	/**
	 * \brief Inicializa las variables del Contexto
	 */
	bool CEditorContext::Init(void)
	{
		return true;
	}

	/**
	 * \brief Prepara la GUI de Inicio
	 */
	void CEditorContext::Prepare(void)
	{
	}

	/**
	 * \brief Calcula el siguiente cuadro
	 */
	void CEditorContext::Next(real delta)
	{
	}

	/**
	 * \brief Dibuja la GUI
	 */
	void CEditorContext::Draw(void)
	{
		irr::video::IVideoDriver* driver = GameDevices->Video->GetVideoDevice()->getVideoDriver();;

		GameDevices->SceneManager->DrawScene( driver );
		GameDevices->GUIEnvironment->DrawGUI( driver );

	}

	/**
	 * \brief Termina el Contexto (se llama durante el cambio de Contexto)
	 */
	void CEditorContext::End(void)
	{
	}

	/**
	 * \brief Prepara la escena de Tiempo de Carga
	 */
	bool CEditorContext::LoadingInit(void)
	{
		return true;
	}

	/**
	 * \brief Prepara la escena de Tiempo de Carga
	 */
	void CEditorContext::LoadingPrepare(void)
	{
	}

	/**
	 * \brief Calcula el siguiente cuadro del Tiempo de Carga
	 */
	void CEditorContext::LoadingNext(real delta)
	{
	}

	/**
	 * \brief Dibuja la escena de Tiempo de Carga
	 */
	void CEditorContext::LoadingDraw(void)
	{
	}

	/**
	 * \brief Se termina el Tiempo de Carga
	 */
	void CEditorContext::LoadingEnd(void)
	{
	}

	/**
	 * \brief Cierra el contexto (cuando se termina el programa)
	 */
	void CEditorContext::Close(void)
	{
	}

	/**
	 * \brief Evento de GUI
	 * \param Caller Elemento que llamó el evento
	 * \param Element Si el Evento tiene que ver con otro elemento, será este puntero
	 * \param EventType Tipo de Evento
	 * \return FALSE
	 */
	bool CEditorContext::OnGUIEvent(	irr::gui::IGUIElement *caller,
										irr::gui::IGUIElement *element,
										const uint16 &eventType )
	{

		irr::gui::IGUIEnvironment *env = GameDevices->GUIEnvironment->GetGUIEnvironment();
		irr::scene::ISceneManager *smgr = GameDevices->SceneManager->GetSceneManager();
		#if defined(ENABLE_DYNAMIC_LIGHTS)
		XEffects::EffectHandler* effects = GameDevices->Effects->GetEffects();
		#endif
		irr::video::IVideoDriver* driver = GameDevices->Video->GetVideoDevice()->getVideoDriver();
		irr::IrrlichtDevice* device = GameDevices->Video->GetVideoDevice();

		// Presionar un Boton de la GUI
		switch(eventType)
		{
			// Ventana de Selección de Archivo
			case irr::gui::EGET_FILE_SELECTED:
			{

				irr::gui::IGUIFileOpenDialog *dialog = (irr::gui::IGUIFileOpenDialog*)caller;
				//COutput::Wprintf(L"Abrir algun archivo: '%ls'\n",dialog->getFileName());
				irr::s32 id = dialog->getID();

				switch(id)
				{

					case EGEC_ID_WINDOW_IMPORT_IRRFILE:
					{
						smgr->loadScene( dialog->getFileName() );
						break;
					};

					case EGEC_ID_WINDOW_INSERT_OBJECT_MESH:
					{
						smgr->addMeshSceneNode( smgr->getMesh( dialog->getFileName() ) );
						break;
					}

					case EGEC_ID_WINDOW_INSERT_OBJECT_ANIMATEDMESH:
					{
						smgr->addAnimatedMeshSceneNode( smgr->getMesh( dialog->getFileName() ) );
						break;
					}

					default:
					{
						break;
					}
				} //-- Fin switch(id)
				break;

			} //-- Fin Ventana Selección de Archivo

			// Opción de Menú seleccionada
			case irr::gui::EGET_MENU_ITEM_SELECTED:
			{

				irr::gui::IGUIContextMenu* menu = (irr::gui::IGUIContextMenu*)caller;
				irr::s32 id = menu->getItemCommandId( menu->getSelectedItem() );

				switch(id)
				{

					case EGEC_ID_MENU_CONTEXT_IMPORT_IRRFILE:
					{
						env->addFileOpenDialog(L"Seleccione el archivo .irr",true,0,EGEC_ID_WINDOW_IMPORT_IRRFILE);
						break;
					}

                    //Se agregaron las demas ventanas

					case EGEC_ID_MENU_INSERT_OBJECT_CUBE:
					{
						irr::scene::IMeshSceneNode *cube = smgr->addCubeSceneNode();
						cube->setMaterialTexture(0, driver->getTexture("resources/editor/t351sml.jpg"));
						cube->setScale(irr::core::vector3df(10.0f,10.0f,10.0f));
						cube->setMaterialFlag(irr::video::EMF_LIGHTING, false);

						LastNodeId += 1;
						cube->setID(LastNodeId);

						CreateAndSetTriangleSelector( cube->getMesh() , cube );
						if( SelectedSceneNode )
						{
							SelectedSceneNode->setDebugDataVisible(irr::scene::EDS_OFF);
						}
						SelectedSceneNode = cube;
						SelectedSceneNode->setDebugDataVisible(irr::scene::EDS_BBOX);
						Mode = EGEM_MESH_PICKED;
						Nodes.push_back( cube );
						#if defined(ENABLE_DYNAMIC_LIGHTS)
						if( effects )
						{
							effects->addShadowToNode( cube );
						}
						#endif
						break;
					}

					case EGEC_ID_MENU_INSERT_OBJECT_SPHERE:
					{
						irr::scene::IMeshSceneNode *sphere = smgr->addSphereSceneNode();
						CreateAndSetTriangleSelector( sphere->getMesh() , sphere );
						sphere->setMaterialTexture(0,driver->getTexture("resources/editor/wall.bmp"));
						sphere->setScale(irr::core::vector3df(10.0f,10.0f,10.0f));
						sphere->setMaterialFlag(irr::video::EMF_LIGHTING, false);

						LastNodeId += 1;
						sphere->setID(LastNodeId);

						CreateAndSetTriangleSelector( sphere->getMesh() , sphere );
						if( SelectedSceneNode )
						{
							SelectedSceneNode->setDebugDataVisible(irr::scene::EDS_OFF);
						}
						SelectedSceneNode = sphere;
						SelectedSceneNode->setDebugDataVisible(irr::scene::EDS_BBOX);
						Mode = EGEM_MESH_PICKED;
						Nodes.push_back( sphere );
						#if defined(ENABLE_DYNAMIC_LIGHTS)
						if( effects )
						{
							effects->addShadowToNode( sphere );
						}
						#endif
						break;
					}

					case EGEC_ID_MENU_INSERT_OBJECT_TERRAIN:
					{
						irr::scene::ITerrainSceneNode *terrain = smgr->addTerrainSceneNode(
																	"resources/editor/terrain-heightmap.bmp",
																	0,											// parent node
																	-1,											// node id
																	irr::core::vector3df(0.f, 0.f, 0.f),        // position
																	irr::core::vector3df(0.f, 0.f, 0.f),        // rotation
																	irr::core::vector3df(10.f, 1.1f, 10.f),     // scale
																	irr::video::SColor ( 255, 255, 255, 255 ),  // vertexColor
																	5,											// maxLOD
																	irr::scene::ETPS_17,						// patchSize
																	4											// smoothFactor
																	);

						terrain->setMaterialFlag(irr::video::EMF_LIGHTING, false);
						terrain->setMaterialTexture(0,driver->getTexture("resources/editor/terrain-texture.jpg"));
						terrain->setMaterialTexture(1,driver->getTexture("resources/editor/detailmap3.jpg"));
						terrain->setMaterialType(irr::video::EMT_DETAIL_MAP);
						terrain->scaleTexture(1.0f, 20.0f);

						LastNodeId += 1;
						terrain->setID(LastNodeId);

						CreateAndSetTerrainTriangleSelector( terrain );
						if( SelectedSceneNode )
						{
							SelectedSceneNode->setDebugDataVisible(irr::scene::EDS_OFF);
						}
						SelectedSceneNode = terrain;
						SelectedSceneNode->setDebugDataVisible(irr::scene::EDS_BBOX);
						Mode = EGEM_MESH_PICKED;
						Nodes.push_back( terrain );
						#if defined(ENABLE_DYNAMIC_LIGHTS)
						if( effects )
						{
							effects->addShadowToNode( terrain );
						}
						#endif
						break;
					}

				    case EGEC_ID_MENU_INSERT_OBJECT_MESH:
					{
						env->addFileOpenDialog(L"Seleccione archivo Mesh",true,0,EGEC_ID_WINDOW_INSERT_OBJECT_MESH);
						break;
					}

					case EGEC_ID_MENU_INSERT_OBJECT_ANIMATEDMESH:
					{
						env->addFileOpenDialog(L"Seleccione archivo Mesh",true,0,EGEC_ID_WINDOW_INSERT_OBJECT_ANIMATEDMESH);
						break;
					}


					case EGEC_ID_MENU_INSERT_LIGHT:
					{
						irr::scene::ISceneNode* node = 0;
						node = smgr->addBillboardSceneNode(0, irr::core::dimension2d<irr::f32>(32, 32));
						node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
						node->setMaterialType(irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL_REF);
						node->setMaterialTexture(0, driver->getTexture("resources/editor/ampolleta.png"));
						node->setPosition(irr::core::vector3df(0.0f,100.0,0.0f));

						LastNodeId += 1;
						node->setID(LastNodeId);

						irr::scene::ISceneNode* target = 0;
						target = smgr->addBillboardSceneNode(0, irr::core::dimension2d<irr::f32>(32, 32));
						target->setMaterialFlag(irr::video::EMF_LIGHTING, false);
						target->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
						target->setMaterialTexture(0, driver->getTexture("resources/editor/particlewhite.bmp"));
						target->setPosition(irr::core::vector3df(0.0f,0.0f,0.0f));
						//target->setVisible(false);

						LastNodeId += 1;
						target->setID(LastNodeId);

						CreateAndSetLightTriangleSelector( node , target );
						if( SelectedSceneNode )
						{
							SelectedSceneNode->setDebugDataVisible(irr::scene::EDS_OFF);
						}

						LastLightId += 1;

						#if defined(ENABLE_DYNAMIC_LIGHTS)
						XEffects::SShadowLight *light = 
							new XEffects::SShadowLight(	
										LastLightId ,
										512,
										irr::core::vector3df(0.0f,100.0f,0.0f),
										irr::core::vector3df(0.0f,0.0f,0.0f),
										irr::video::SColor(0xFF, 0xFF, 0xFF, 0xFF),
										10.0f,
										100.0f,
										(irr::f32)(90.0f * irr::core::DEGTORAD64),
										true );
						#endif

						SGUIEditorLightElement *element = new SGUIEditorLightElement();
						element->Id = LastLightId;
						element->Node = node;
						element->Target = target;
						#if defined(ENABLE_DYNAMIC_LIGHTS)
						element->Light = light;
						#endif
						//Nodes.push_back( node );

						#if defined(ENABLE_DYNAMIC_LIGHTS)
						effects->addShadowLight( *light );
						#endif
						Lights.push_back( element );
						break;
					}
		            //
					default:
					{
						//env->addWindow( irr::core::rect<irr::s32>(Width/2-100,Height/2-50,Width/2+100,Height/2+50), true , L"No implementado todavía");
						break;
					}
				} //-- Fin switch(id)

				break;

			} //-- Fin Opción de Menú seleccionada

			// Botón presionado
			case irr::gui::EGET_BUTTON_CLICKED:
			{

				/*
				irr::s32 id = Caller->getID();
				switch(id)
				{
					default:
					{
						break;
					}
				} //-- Fin switch(id)
				*/
			} //-- Fin Botón presionado

			default:
			{
				//env->addWindow( irr::core::rect<irr::s32>(Width/2-100,Height/2-50,Width/2+100,Height/2+50), true , L"No implementado todavía");
				break;
			}
		} //-- Fin presionar botón de GUI

		return false;
	}

	/**
	 * \brief Evento de Teclado
	 * \param tmp_Key Tecla presionada
	 * \param tmp_Char Código de tecla presionada
	 * \param tmp_isCtrl Si se presionó la tecla Ctrl
	 * \param tmp_isShift Si se presionó la tecla Shift
	 * \param tmp_isPressedDown Si se presionó o se soltó la tecla
	 * \return TRUE
	 */
	bool CEditorContext::OnKeyInput(	const uint16 &key,
										const wchar_t &keyChar,
										const bool isCtrl,
										const bool isShift,
										const bool isPressedDown )
	{
		irr::gui::IGUIEnvironment *env = GameDevices->GUIEnvironment->GetGUIEnvironment();
		irr::scene::ISceneManager *smgr = GameDevices->SceneManager->GetSceneManager();
		irr::video::IVideoDriver* driver = GameDevices->Video->GetVideoDevice()->getVideoDriver();
		irr::IrrlichtDevice* device = GameDevices->Video->GetVideoDevice();

		if( isPressedDown )
		{
			switch( Mode )
			{
				case EGEM_DEFAULT:
				{
					break;
				}

				case EGEM_MESH_PICKED:
				{
					switch( key )
					{
						/*
						case irr::KEY_KEY_M:
						{
							if( tmp_isPressedDown )
							{
								if( GUIEditorInfoElements.Window->isVisible() )
								{
									GUIEditorInfoElements.Window->setVisible(false);
									GUIEditorInfoElements.VisibleWindow = false;
								}
								else
								{
									GUIEditorInfoElements.Window->setVisible(true);
									GUIEditorInfoElements.VisibleWindow = true;
								}
							}
							break;
						}
						*/

						case irr::KEY_KEY_R:
						{
							if( Function != EGEF_SCALE )
							{
								Function = EGEF_SCALE ;
								#if defined(_DEBUG)
								COutput::Wprintf(L"Modo Escalado Activado\n");
								#endif
								if( SelectedSceneNode )
								{
									SavedVector = SelectedSceneNode->getScale();
								}
							}
							else
							{
								Function = EGEF_DEFAULT ;
								#if defined(_DEBUG)
								COutput::Wprintf(L"Modo Escalado Desactivado\n");
								#endif
								if( SelectedSceneNode )
								{
									SelectedSceneNode->setScale( SavedVector );
								}
							}
							break;
						}

						case irr::KEY_KEY_E:
						{
							if( Function != EGEF_ROTATE )
							{
								Function = EGEF_ROTATE ;
								#if defined(_DEBUG)
								COutput::Wprintf(L"Modo Rotación Activado\n");
								#endif
								if( SelectedSceneNode )
								{
									SavedVector = SelectedSceneNode->getRotation();
								}
							}
							else
							{
								Function = EGEF_DEFAULT ;
								#if defined(_DEBUG)
								COutput::Wprintf(L"Modo Rotación Desactivado\n");
								#endif
								if( SelectedSceneNode )
								{
									SelectedSceneNode->setRotation( SavedVector );
								}
							}
							break;
						}

						case irr::KEY_KEY_W:
						{
							if( Function != EGEF_MOVE )
							{
								Function = EGEF_MOVE ;
								#if defined(_DEBUG)
								COutput::Wprintf(L"Modo Desplazamiento Activado\n");
								#endif
								if( SelectedSceneNode )
								{
									SavedVector = SelectedSceneNode->getPosition();
								}
							}
							else
							{
								Function = EGEF_DEFAULT ;
								#if defined(_DEBUG)
								COutput::Wprintf(L"Modo Desplazamiento Desactivado\n");
								#endif
								if( SelectedSceneNode )
								{
									SelectedSceneNode->setPosition( SavedVector );
								}
							}
							break;
						}

						case irr::KEY_KEY_X:
						{
							if( Transform != EGET_X )
							{
								TransformVector = irr::core::vector3df(1.0f,0.0f,0.0f);
								Transform = EGET_X; 
								#if defined(_DEBUG)
								COutput::Wprintf(L"Eje-X Activado\n");
								#endif
							}
							else 
							{
								TransformVector = irr::core::vector3df(0.0f,0.0f,0.0f);
								Transform = EGET_NONE; 
								#if defined(_DEBUG)
								COutput::Wprintf(L"Eje-X Desactivado\n");
								#endif
							}
							break;
						}

						case irr::KEY_KEY_Y:
						{
							if( Transform != EGET_Y )
							{
								TransformVector = irr::core::vector3df(0.0f,1.0f,0.0f);
								Transform = EGET_Y; 
								#if defined(_DEBUG)
								COutput::Wprintf(L"Eje-Y Activado\n");
								#endif
							}
							else 
							{
								TransformVector = irr::core::vector3df(0.0f,0.0f,0.0f);
								Transform = EGET_NONE; 
								#if defined(_DEBUG)
								COutput::Wprintf(L"Eje-Y Desactivado\n");
								#endif
							}
							break;
						}

						case irr::KEY_KEY_Z:
						{
							if( Transform != EGET_Z )
							{
								TransformVector = irr::core::vector3df(0.0f,0.0f,1.0f);
								Transform = EGET_Z; 
								#if defined(_DEBUG)
								COutput::Wprintf(L"Eje-Z Activado\n");
								#endif
							}
							else 
							{
								TransformVector = irr::core::vector3df(0.0f,0.0f,0.0f);
								Transform = EGET_NONE; 
								#if defined(_DEBUG)
								COutput::Wprintf(L"Eje-Z Desactivado\n");
								#endif
							}
							break;
						}

						default:
						{
							break;
						}
					}
					break;
				}

				default:
				{
					break;
				}
			}
		}
		return false;
	}

	/**
	 * \brief Evento de Mouse
	 * \param tmp_EventType Evento
	 * \param tmp_X Posición X del Cursor
	 * \param tmp_Y Posición Y del Cursor
	 * \param tmp_Wheel Movimiento de la rueda
	 * \param tmp_isLeft Si se presionó el botón izquierdo
	 * \param tmp_isMiddle Si se presionó el botón central
	 * \param tmp_isRight Si se presionó el botón derecho
	 * \param tmp_isCtrl Si se presionó la tecla Ctrl
	 * \param tmp_isShift Si se presionó la tecla Shift
	 * \bug <b>[leve]</b> Cuando se hace clic sobre un elemento de la GUI, el foco del mesh seleccionado se pierde.
	 * \return TRUE
	 */
	bool CEditorContext::OnMouseInput(	const uint16 &eventType,
										const sint32 &mouseX,
										const sint32 &mouseY,
										const real &wheel,
										const bool isLeft,
										const bool isMiddle,
										const bool isRight,
										const bool isCtrl,
										const bool isShift )
	{

		irr::gui::IGUIEnvironment *env = GameDevices->GUIEnvironment->GetGUIEnvironment();
		irr::scene::ISceneManager *smgr = GameDevices->SceneManager->GetSceneManager();

		#if defined(ENABLE_DYNAMIC_LIGHTS)
		XEffects::EffectHandler *effect = GameDevices->Effects->GetEffects();
		#endif

		Elements.Mouse.Xrel = mouseX - Elements.Mouse.Xold;
		Elements.Mouse.Yrel = mouseY - Elements.Mouse.Yold;
		Elements.Mouse.Xold = mouseX;
		Elements.Mouse.Yold = mouseY;

		switch( Mode )
		{
			case EGEM_MESH_PICKED:
			{
				switch( eventType )
				{
					case irr::EMIE_MOUSE_MOVED:
					{
						if( SelectedSceneNode )
						{
							switch( Function )
							{
								case EGEF_SCALE:
								{
									switch( Transform )
									{
										case EGET_X:
										case EGET_Y:
										case EGET_Z:
										{
											if( SelectedSceneNode )
											{
												irr::core::vector2df Mouse = irr::core::vector2df((irr::f32)mouseX,(irr::f32)mouseY);
												irr::f32 Sign = (Mouse.X - Center.X)/CMath::Fabs(Mouse.X - Center.X);
												irr::f32 dist = Mouse.getDistanceFrom( Center );
												SelectedSceneNode->setScale( SavedVector + TransformVector * dist * Sign);
												#if defined(_DEBUG)
												COutput::Wprintf(L"Distance=%f from=(%f,%f)\n",dist,Center.X,Center.Y);
												#endif
											}
											break;
										}

										default:
										{
											break;
										}
									}
									break;
								} //-- fin case EGEF_SCALE

								case EGEF_ROTATE:
								{
									switch( Transform )
									{
										case EGET_X:
										case EGET_Y:
										case EGET_Z:
										{
											if( SelectedSceneNode )
											{
												irr::core::vector2df Mouse = irr::core::vector2df((irr::f32)mouseX,(irr::f32)mouseY);
												irr::f32 Sign = (Mouse.X - Center.X)/CMath::Fabs(Mouse.X - Center.X);
												irr::f32 dist = Mouse.getDistanceFrom( Center );
												SelectedSceneNode->setRotation( SavedVector + TransformVector * dist * Sign);
												#if defined(_DEBUG)
												COutput::Wprintf(L"Distance=%f from=(%f,%f)\n",dist,Center.X,Center.Y);
												#endif
											}
											break;
										}

										default:
										{
											break;
										}
									}
									break;
								} //-- fin case EGEF_ROTATE

								case EGEF_MOVE:
								{
									switch( Transform )
									{
										case EGET_X:
										case EGET_Y:
										case EGET_Z:
										{
											if( SelectedSceneNode )
											{
												irr::core::vector2df Mouse = irr::core::vector2df((irr::f32)mouseX,(irr::f32)mouseY);
												irr::f32 Sign = (Mouse.X - Center.X)/CMath::Fabs(Mouse.X - Center.X);
												irr::f32 dist = Mouse.getDistanceFrom( Center );
												SelectedSceneNode->setPosition( SavedVector + TransformVector * dist * Sign);
												#if defined(_DEBUG)
												COutput::Wprintf(L"Distance=%f from=(%f,%f)\n",dist,Center.X,Center.Y);
												#endif
											}
											if( SelectedLight )
											{
												#if defined(ENABLE_DYNAMIC_LIGHTS)
												XEffects::SShadowLight *light = effect->getShadowLightById( SelectedLight->Id );
												if( light != NULL )
												{
													light->setPosition( SelectedLight->Node->getPosition() );
													light->setTarget( SelectedLight->Target->getPosition() );
													#if defined(_DEBUG)
													irr::core::vector3df pos = light->getPosition();
													irr::core::vector3df tar = light->getTarget();
													COutput::Wprintf(L"Luz[%d] Posicion=(%f,%f,%f) Target=(%f,%f,%f)\n",SelectedLight->Id,pos.X,pos.Y,pos.Z,tar.X,tar.Y,tar.Z);
													#endif
												}
												#endif
											}
											break;
										}

										default:
										{
											break;
										}
									}
									break;
								} //-- fin case EGEF_MOVE

								default:
								{
									break;
								}
							} //-- fin switch( Function )
						} //-- fin if(SelectedSceneNode)
						break;
					} //-- fin case irr::EMIE_MOUSE_MOVED

					case irr::EMIE_LMOUSE_PRESSED_DOWN:
					{
						if( SelectedSceneNode )
						{
							switch( Function )
							{
								case EGEF_SCALE:
								{
									SavedVector = SelectedSceneNode->getScale();
									Function = EGEF_DEFAULT;
									Transform = EGET_NONE;
									Mode = EGEM_DEFAULT;
									SceneNodeMousePick(mouseX,mouseY);
									break;
								} //-- fin case EGEF_SCALE

								case EGEF_ROTATE:
								{
									SavedVector = SelectedSceneNode->getRotation();
									Function = EGEF_DEFAULT;
									Transform = EGET_NONE;
									Mode = EGEM_DEFAULT;
									SceneNodeMousePick(mouseX,mouseY);
									break;
								} //-- fin case EGEF_ROTATE

								case EGEF_MOVE:
								{
									SavedVector = SelectedSceneNode->getPosition();
									Function = EGEF_DEFAULT;
									Transform = EGET_NONE;
									Mode = EGEM_DEFAULT;
									SceneNodeMousePick(mouseX,mouseY);
									break;
								} //-- fin case EGEF_MOVE

								default:
								{
									SceneNodeMousePick(mouseX,mouseY);
									break;
								}
							} //-- fin switch( Function )
						} //-- fin if(SelectedSceneNode)
						break;
					} //-- fin case irr::EMIE_LMOUSE_PRESSED_DOWN
				} //-- fin switch( tmp_EventType )
			} //-- fin case EGEM_MESH_PICKED
			break;
		
			default:
			{
				switch( eventType )
				{
					case irr::EMIE_LMOUSE_PRESSED_DOWN:
					{
						SceneNodeMousePick(mouseX,mouseY);
						break;
					} //-- fin case irr::EMIE_LMOUSE_PRESSED_DOWN

					case irr::EMIE_RMOUSE_DOUBLE_CLICK:
					{

						irr::gui::IGUIContextMenu *menu = env->addContextMenu( irr::core::rect<irr::s32>(mouseX,mouseY,0,0) );
						menu->addItem(L"Opcion 1");
						menu->addItem(L"Opcion 2",-1,false);
						menu->addItem(L"Opcion 3",-1,true,false,true);
						menu->addItem(L"Opcion 4",-1,true,true);
						irr::gui::IGUIContextMenu *submenu = menu->getSubMenu(3);
						submenu->addItem(L"Sub-opcion 1");
						submenu->addItem(L"Sub-opcion 2");
						break;
					} //-- case irr::EMIE_RMOUSE_DOUBLE_CLICK
					break;
				} //-- switch( tmp_EventType )
			} //-- fin default
		} //-- fin switch(Mode)
		return false;
	}
	
	/**
     * \brief Crea y Establece un Triangle Selector para el IMeshSceneNode
	 * \param tmp_Mesh Mesh que será utilizado para la colisión
     * \param tmp_Node Node al que se le agregará el Selector
     */
	void CEditorContext::CreateAndSetTriangleSelector(	irr::scene::IMesh *mesh,
														irr::scene::ISceneNode *node )
	{
		irr::scene::ISceneManager *smgr = GameDevices->SceneManager->GetSceneManager();

        //Defino el selector
        irr::scene::ITriangleSelector* selector;

        //Tengo que hacerlo "Pickable"
        irr::s32 flags = node->getID();
        flags = EMPF_MESH | flags;

        node->setID(flags);
        //creo un selector y se lo agrego al nodo (esto suele repetirse para cada mesh)
		
		selector = smgr->createTriangleSelector(mesh,node); //Crearlo segun el mesh	  
        node->setTriangleSelector(selector); //agregarlo al nodo
        selector->drop(); //No lo usare mas y lo dropeo
    }


    /**
     * \brief Crea y Establece un Triangle Selector para el IMeshSceneNode
	 * \param tmp_Node Nodo de Luz que se le agregará el Selector
     * \param tmp_Target Objetivo de Luz que se le agregará el Selector
     */
	void CEditorContext::CreateAndSetLightTriangleSelector(	irr::scene::ISceneNode *node,
															irr::scene::ISceneNode *target )
	{
		irr::scene::ISceneManager *smgr = GameDevices->SceneManager->GetSceneManager();

        //Defino el selector
        

        //Tengo que hacerlo "Pickable"
        irr::s32 flags = node->getID();
        flags = EMPF_LIGHT | flags;
        node->setID(flags);

        flags = target->getID();
        flags = EMPF_TARGET | flags;
        target->setID(flags);

		irr::scene::IMeshSceneNode *cube = smgr->addCubeSceneNode();
        //creo un selector y se lo agrego al nodo (esto suele repetirse para cada mesh)
		
		irr::scene::ITriangleSelector* selector;

		selector = smgr->createTriangleSelector(cube->getMesh(),node);
		node->setTriangleSelector(selector);
        selector->drop();

		selector = smgr->createTriangleSelector(cube->getMesh(),target);
		target->setTriangleSelector(selector);
		selector->drop();

		cube->remove();
    }

	/**
     * \brief Crea y Establece un Triangle Selector para el ITerrainSceneNode
	 *
	 * \param tmp_Terrain ITerrainSceneNode establecer un TriangleSelector
     * \author egyware
     */
	void CEditorContext::CreateAndSetTerrainTriangleSelector(irr::scene::ITerrainSceneNode *terrain )
	{
		irr::scene::ISceneManager *smgr = GameDevices->SceneManager->GetSceneManager();

        //Defino el selector
        irr::scene::ITriangleSelector* selector;

        //Tengo que hacerlo "Pickable"
        irr::s32 flags = terrain->getID();
        flags = EMPF_TERRAIN | flags;

        terrain->setID(flags);
        //creo un selector y se lo agrego al nodo (esto suele repetirse para cada mesh)
		
		selector = smgr->createTerrainTriangleSelector(terrain);
		
        terrain->setTriangleSelector(selector); //agregarlo al nodo
        selector->drop(); //No lo usare mas y lo dropeo
    }
};

