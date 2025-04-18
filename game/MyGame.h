#pragma once

class CMyGame : public CGame
{
	// Define sprites and other instance variables here
	CSprite player;	// player sprite
	CSprite startScreen;
    CSprite gameworld;
	CSpriteList jeremyList;
	CSpriteList boltList;
	CSprite krabs;
	CSprite bubble;
	CSpriteList terryList;
	CSpriteList inkList;
	CSoundPlayer inks;
	CSoundPlayer jeremys;
	CSoundPlayer bolts;
	CSprite health;
	CSpriteList GF;
	
	int maxGF = 3;
	int offset = 0;
	int noEnemies = 0;
	int maxenemies = 5;
	int level;
	bool full = false;
	int round = 1;
	int basehealth = 50;
	int maxhealth = 100;
	int basedmg = 10;
	float EdmgMult = 1;
	float PdmgMult = 1;
	bool RoundOver = false;
	bool assigned = false;
	int score = 0;
	bool hardM = false;
	// my own member functions
void PlayerControl();
//upgrade
void Krabs();
void SetupLevel1();
void SetupLevel2();
void hard();
public:
	CMyGame(void);
	~CMyGame(void);

	// Per-Frame Callback Funtions (must be implemented!)
	virtual void OnUpdate();
	virtual void OnDraw(CGraphics* g);

	// Game Life Cycle
	virtual void OnInitialize();
	virtual void OnDisplayMenu();
	virtual void OnStartGame();
	virtual void OnStartLevel(Sint16 nLevel);
	virtual void OnGameOver();
	virtual void OnTerminate();

	 

	// Keyboard Event Handlers
	virtual void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
	virtual void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);

	// Mouse Events Handlers
	virtual void OnMouseMove(Uint16 x,Uint16 y,Sint16 relx,Sint16 rely,bool bLeft,bool bRight,bool bMiddle);
	virtual void OnLButtonDown(Uint16 x,Uint16 y);
	virtual void OnLButtonUp(Uint16 x,Uint16 y);
	virtual void OnRButtonDown(Uint16 x,Uint16 y);
	virtual void OnRButtonUp(Uint16 x,Uint16 y);
	virtual void OnMButtonDown(Uint16 x,Uint16 y);
	virtual void OnMButtonUp(Uint16 x,Uint16 y);
};
