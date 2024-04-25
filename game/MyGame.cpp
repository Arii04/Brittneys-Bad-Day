#include "stdafx.h"
#include "MyGame.h"

CMyGame::CMyGame(void) : 
	startScreen(400,300,"startScreen.bmp",0)
	// to initialise more sprites here use a comma-separated list
{
	// TODO: add initialisation here
}

CMyGame::~CMyGame(void)
{
	// TODO: add destruction code here
}

/////////////////////////////////////////////////////
// Per-Frame Callback Funtions (must be implemented!)

void CMyGame::OnUpdate()
{
	// do not run game logic when in menu mode
	if (IsMenuMode()) return;

	Uint32 t = GetTime();

	// TODO: add the game update code here
	player.Update(t);
	
	krabs.Update(t);

	for (CSprite* aterry : terryList)
	{

		aterry->SetRotation(player.GetX() - aterry->GetX() , player.GetY() - aterry->GetY());
		
		if (rand() % 60 == 0 && IsGameOver() == false)
		{
			CSprite* aink = new CSprite(aterry->GetX(), aterry->GetY(), "ink.bmp", CColor::White(), GetTime());
				
			aink->SetDirection(player.GetX() - aterry->GetX(), player.GetX() - aterry->GetY());
		
			aink->AddImage("ink.bmp","ink", 2, 1, 0, 0, 1, 0, CColor::Black());
			aink->SetAnimation("ink", 2);
			aink->SetSpeed(rand()% 600 +100);
			aink->SetRotation(aterry->GetRotation() );
			inkList.push_back(aink);
			inks.Play("ink.wav");
		}
		
			

	aterry->Update(t);
	}
		

	
	
	for (CSprite* aGF : GF)
	{
		aGF->Update(t);
	}



	for (CSprite* aink : inkList) aink->Update(t);
	//bolt update
	for (CSprite* abolt : boltList) abolt->Update(t);
	//jeremy enemy updates
	for (CSprite* ajeremy : jeremyList)
	{
		CVector playerVector = CVector(0.0f, 0.0f);
		playerVector.SetX(player.GetX() - ajeremy->GetX());
		playerVector.SetY(player.GetY() - ajeremy->GetY());
		playerVector = (rand() % 2 + 1) * Normalise(playerVector);
		ajeremy->Accelerate(playerVector);
		ajeremy->SetOmega(800);
		ajeremy->Update(t);
	}

	
	
	
	krabs.Update(t);
	 
	bubble.Update(t);

	health.Update(t);



	//colision detection
	for (CSprite* abolt : boltList)
	{
		for (CSprite* ajeremy : jeremyList)
		{
			if (abolt->HitTest(ajeremy))
			{
				abolt->Delete();
				score = score + 10;
				ajeremy->SetHealth(ajeremy->GetHealth() - basedmg*PdmgMult) ;
				if (ajeremy->GetHealth() <= 0)
				{
					ajeremy->Delete();
					score = score + 20;
					noEnemies -= 1;
				}
				
			}
			

		}
		for (CSprite* aterry : terryList)
		{
			if (abolt->HitTest(aterry))
			{
				abolt->Delete();
				score = score + 10;
				aterry->SetHealth(aterry->GetHealth() - basedmg * PdmgMult);
				if (aterry->GetHealth() <= 0)
				{
					aterry->Delete();
					score = score + 20;
					noEnemies -= 1;
				}

			}


		}

	}
	//delete if out of bounds
	for (CSprite* abolt : boltList)
	{
		if ((abolt->GetX() > 1920) || (abolt->GetX() < 0) || (abolt->GetY() > 1080) || (abolt->GetY() < 0))
		{
			abolt->Delete();
		}
	}
	if (hardM == false)
	{
		for (CSprite* aink : inkList)
		{
			if ((aink->GetX() > 1920) || (aink->GetX() < 0) || (aink->GetY() > 1080) || (aink->GetY() < 0))
			{
			aink->Delete();
			}
		}
	}
	
	
	for (CSprite* aGF : GF)
	{
		if (player.HitTest(aGF))
		{
			
			player.SetX(rand()%1600 - 200);
			player.SetY(rand()%1200 - 200);
			
		}
		for (CSprite* ajeremy : jeremyList)
		{
			if (ajeremy->HitTest(aGF))
			{
				ajeremy->SetY(rand() % 1200 - 200);
				ajeremy->SetX(rand() % 1600 - 200);

			}
		}

	}


	//player collison
	for (CSprite* ajeremy : jeremyList)
	{
		if (player.HitTest(ajeremy))
		{
			player.SetHealth(max(0,player.GetHealth() - basedmg*EdmgMult));
			ajeremy->Delete();
			noEnemies -= 1;
		}
		
		if (player.GetHealth() <= 0)
		{
			GameOver();
		}
			
	}
	for (CSprite* aterry : terryList)
	{
		if (player.HitTest(aterry))
		{
			player.SetHealth(player.GetHealth() - basedmg * EdmgMult);
			aterry->Delete();
			noEnemies -= 1;
		}

		if (player.GetHealth() <= 0)
		{
			GameOver();
		}

	}
	for (CSprite* aink : inkList)
	{
		if (player.HitTest(aink))
		{
			player.SetHealth(player.GetHealth() - basedmg * EdmgMult);
			aink->Delete();
			
		}

		if (player.GetHealth() <= 0)
		{
			GameOver();
		}

	}
	//delteters
	boltList.delete_if(deleted);
	jeremyList.delete_if(deleted);
	inkList.delete_if(deleted);
	terryList.delete_if(deleted);
	GF.delete_if(deleted);
	//spawner
	
	
	if ((noEnemies <= maxenemies) && (full == false)&& RoundOver == false)
	{
		
		int x = rand() % 2 + 1 ;
		if (x == 1)
		{
		CSprite* ajeremy = new CSprite(rand() % 1600 + 200, rand() % 900 + 300, "jeremy.bmp", CColor::White(), GetTime());
			ajeremy->SetHealth(basehealth /2 + (round+EdmgMult));
			jeremyList.push_back(ajeremy);
			noEnemies += 1;
			jeremys.Play("jeremy.wav", -1);
		}
		else if(x== 2)
		{
			CSprite* aterry = new CSprite(rand() % 1500 + 200, rand() % 800 + 300, "terry.bmp", CColor::White(), GetTime());
			aterry->AddImage("terry.bmp", "t", 2, 1, 0, 0, 1, 0, CColor::White());
			aterry->SetAnimation("t", 3);
			aterry->SetHealth(basehealth + (round + EdmgMult));
			terryList.push_back(aterry);
			noEnemies += 1;
		}
		
		
		
		
	}


	if (noEnemies == maxenemies)
	{
			full = true;
	}
	
	if ((noEnemies == 0) && (full == true))
	{
			full = false;
			GF.delete_all();
			maxenemies += 2;
			round += 1;
			EdmgMult = EdmgMult + ((rand() % 3 + 1)/10);
			score = score + 100;
			if (IsGameOver() == false) Krabs();
			for (int i = 0; i < maxGF; i++) 
			{
			CSprite* aGF = new CSprite(rand() % 1400 + 200, rand() % 700 + 300, 0, 0, GetTime());
			aGF->AddImage("Gravitational Field.bmp", "GF", 4, 1, 0, 0, 2, 0, CColor::White());
			aGF->SetAnimation("GF", 7);
			aGF->SetOmega(800);
			GF.push_back(aGF);
			}
	}

	//sound
	if (jeremyList.empty() == true || noEnemies ==0)
	{
		jeremys.Stop();
	}
	
	if (IsGameOver() == true)
	{
		jeremys.Stop();
	}
				
		
	//player wrap around
	if (player.GetX() < 0) player.SetX(1600);
	if (player.GetX() > 1600) player.SetX(50);
	if (player.GetY() < 0) player.SetY(1050);
	if (player.GetY() > 1050) player.SetY(50);
	
	for (CSprite* ajeremy : jeremyList)
	{
		if (ajeremy->GetX() < 50) ajeremy->SetX(1600);
		if (ajeremy->GetX() > 1600) ajeremy->SetX(50);
		if (ajeremy->GetY() < 0) ajeremy->SetY(1050);
		if (ajeremy->GetY() > 1050) ajeremy->SetY(0);
	}

	if (hardM == true)
	{
		hard();
	}








	PlayerControl();
}


void CMyGame::OnDraw(CGraphics* g)
{
	




	// draw menu when in menu mode
	if (IsMenuMode())
	{
		startScreen.Draw(g);
		return;
	}
	
	
	
	// ----- scrolling -------------------------------
	
    // game world image is of size 1600x1200
	int leftScreenLimit = 400;  // half of the window width
	int rightScreenLimit = 1600 - 400;

	int bottomScreenLimit = 300;  // half of the window height
	int topScreenLimit = 1200 - 300;

	CVector scrollpos;  // the amount by which the game world is scrolled
	
	// do not scroll if left to the left limit
	if (player.GetX() < leftScreenLimit)
	{
		scrollpos.SetX(0);
	}
	// do not scroll if below the bottom limit
	if (player.GetY() < bottomScreenLimit)
	{
		scrollpos.SetY(0);
	}

    // we scroll the whole game world according to the player position
	// unless we reached the left/bottom or right/top screen limits
	if (player.GetX() >= leftScreenLimit && player.GetX() <= rightScreenLimit)
	{
		scrollpos.SetX(leftScreenLimit - player.GetX());
	}
	if (player.GetY() >= bottomScreenLimit && player.GetY() <= topScreenLimit)
	{
		scrollpos.SetY(bottomScreenLimit - player.GetY());
	}


	// we stop scrolling with the player once we have reached the right/top limit
	// and remain in that fixed scrolling position
	if (player.GetX() > rightScreenLimit)
	{
		scrollpos.SetX(leftScreenLimit - rightScreenLimit); //-800
	}
	if (player.GetY() > topScreenLimit)
	{
		scrollpos.SetY(bottomScreenLimit - topScreenLimit); //-600
	}

	// set global scroll position
	g->SetScrollPos(scrollpos);
	
	gameworld.Draw(g);
   //draw Gravitaional Fields
	for (CSprite* aGF : GF) aGF->Draw(g); 
	player.Draw(g);

	 //draw bolts
	for (CSprite* abolt : boltList) abolt->Draw(g);
	//draw jeremy enemy
	for (CSprite* ajeremy : jeremyList) ajeremy->Draw(g);

	// draw terry enemy
	for (CSprite* aterry : terryList)aterry->Draw(g);
	//draw ink
	for (CSprite* aink : inkList) aink->Draw(g);
	
	 // don't scroll anything drawn thereafter
	 g->SetScrollPos(0, 0);

	 if (RoundOver !=true)
	 {
		 
		 
		 
		
		*g << font(28) << color(CColor::Blue()) << xy(10, 505) << "score " << score;
		*g << font(28) << color(CColor::Blue()) << xy(650, 570) << "round: " << (int)round;
		*g << font(28) << color(CColor::Blue()) << xy(10, 460) << "enemies: " << (int)noEnemies;
	 }
	 
	health.SetPosition(30, 570);
		health.Draw(g);
	 *g << font(28) << color(CColor::Red()) << xy(65, 570) << ": " << player.GetHealth();
	 if (IsGameOverMode())  *g << font(40) << color(CColor::Red()) << xy(150, 300) << "The Invasion was Withheld for now";
	 if (IsGameOverMode())  *g << font(40) << color(CColor::Magenta()) << xy(150, 250) << "Final score is :" << score;
	 if (IsGameOverMode() && hardM== true)  *g << font(40) << color(CColor::Blue()) << xy(150, 220) << "Final Defense Mode was active";
	 if (IsGameOverMode())  *g << font(40) << color(CColor::Green()) << xy(150, 150) << "Press F2 to begin the invasion once more " ;
	
	 
	 //draw when round over
	 if (RoundOver == true && player.GetHealth() > 0 )
	 {
		 inkList.delete_all();
		 while (assigned == false)
		 {
			 int ktype = (rand() % 3 + 1);
			 assigned = true;


			 if (ktype == 1)
			 {
				 krabs.SetImage("p1");
				 assigned = true;
			 }
			 else if (ktype == 2)
			 {
				 krabs.SetImage("p2");
				 assigned = true;
			 }
			 else if (ktype == 3)
			 {
				 krabs.SetImage("p3");
				 assigned = true;
			 }
			
		 }
		
		krabs.SetPosition(300, 300);
		krabs.Draw(g);
		bubble.SetPosition(400, 400);
		bubble.Draw(g);
		
		







	 }
}

void CMyGame::PlayerControl()
{

	float hwalkSpeed = 425; // horizontal walking speed
	float vwalkSpeed = 400; // vertical walking speed


	enum animation_state { NONE, STANDLEFT, STANDRIGHT, WALKLEFT, WALKRIGHT };
	/* 
	  player status variable is used to indicate which state the player is in

	  0: None
	  1: standing left looking
	  2: standing right looking
	  3: walking left
	  4: walking right
	*/

	// preserving the current status
    int old_animation_status = player.GetStatus();
    
	// resetting the player to standing each time and then
	// changing this according to state and keyboard input
    player.SetMotion(0, 0);
	if (player.GetStatus()==WALKLEFT) player.SetStatus(STANDLEFT);
	if (player.GetStatus()==WALKRIGHT) player.SetStatus(STANDRIGHT);
	
	// setting the speeds and animation status according to the keyboard controls
	if (IsKeyDown(SDLK_d)) { player.SetXVelocity(hwalkSpeed); player.SetStatus(WALKRIGHT);}
	if (IsKeyDown(SDLK_a)) { player.SetXVelocity(-hwalkSpeed); player.SetStatus(WALKLEFT); }
	if (IsKeyDown(SDLK_w))
	{
		if (player.GetStatus() == STANDLEFT) player.SetStatus(WALKLEFT);
		if (player.GetStatus() == STANDRIGHT) player.SetStatus(WALKRIGHT);
		player.SetYVelocity(vwalkSpeed);
	}
	if (IsKeyDown(SDLK_s))
	{
		if (player.GetStatus() == STANDLEFT) player.SetStatus(WALKLEFT);
		if (player.GetStatus() == STANDRIGHT) player.SetStatus(WALKRIGHT);
		player.SetYVelocity(-vwalkSpeed);
	}

	// changing animation sequences if different from previous status
	if (player.GetStatus() != old_animation_status)
	{
		if (player.GetStatus() == WALKLEFT) player.SetAnimation("walkleft", 10);
		if (player.GetStatus() == WALKRIGHT) player.SetAnimation("walkright", 10);
		if (player.GetStatus() == STANDRIGHT) player.SetImage("standright");
		if (player.GetStatus() == STANDLEFT) player.SetImage("standleft");
	}


	player.Update(GetTime());


}

/////////////////////////////////////////////////////
// Game Life Cycle

// one time initialisation
void CMyGame::OnInitialize()
{   
	// loading the game map
	gameworld.LoadImage("background.bmp", "map1");
	gameworld.SetImage("map1"); gameworld.SetPosition(400, 300);

	// configuring the animations for the player sprite
	player.LoadImage("brittney.bmp", "standright", 6, 1, 2, 0);
	player.AddImage("brittney.bmp", "walkright", 6, 1, 0, 0, 2, 0);
	player.LoadImage("brittney.bmp", "standleft", 6, 1, 5, 0);
	player.AddImage("brittney.bmp", "walkleft", 6, 1, 3, 0, 5, 0);
	player.SetHealth(basehealth);
	player.SetImage("standright");
	player.SetStatus(2);
	//upgrades
	krabs.LoadImage("Dr.Krabs.bmp", "p1", CSprite::Sheet(3, 1).Tile(0, 0), CColor::Magenta());
	krabs.LoadImage("Dr.Krabs.bmp", "p2", CSprite::Sheet(3, 1).Tile(1, 0), CColor::Magenta());
	krabs.LoadImage("Dr.Krabs.bmp", "p3", CSprite::Sheet(3, 1).Tile(2, 0), CColor::Magenta());
	//speech bubble
	bubble.AddImage("bubble.bmp", "sbu", 2, 1, 0, 0, 1, 0, CColor::Magenta);
	bubble.SetAnimation("sbu", 2);
	health.AddImage("health.bmp", "hp", 2, 1, 0, 0, 1, 0, CColor::White());
	health.SetAnimation("hp", 2);
}

// called when a new game is requested (e.g. when F2 pressed)
// use this function to prepare a menu or a welcome screen
void CMyGame::OnDisplayMenu()
{   

	SetupLevel1();
}


void CMyGame::SetupLevel1()
{



}

// setting up a level 
void CMyGame::SetupLevel2()
{
	

}

// called when a new game is started
// as a second phase after a menu or a welcome screen
void CMyGame::OnStartGame()
{
    player.SetPosition(100, 50);
	player.SetMotion(0, 0);
	player.SetImage("standright");
	player.SetStatus(2);

	gameworld.SetPosition(800, 600);
	
}

// called when a new level started - first call for nLevel = 1
void CMyGame::OnStartLevel(Sint16 nLevel)
{	

}

// called when the game is over
void CMyGame::OnGameOver()
{
}

// one time termination code
void CMyGame::OnTerminate()
{
}

/////////////////////////////////////////////////////
// Keyboard Event Handlers

void CMyGame::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{
	if (sym == SDLK_F4 && (mod & (KMOD_LALT | KMOD_RALT)))
		StopGame();
	if (sym == SDLK_SPACE)
		PauseGame();
	if (sym == SDLK_F2)
	{ 
		EdmgMult = 1;
		PdmgMult = 1;
		RoundOver = false;
		assigned = false;
		score = 0;
		full = false;
		round = 1;
		maxenemies = 5;
		noEnemies = 0;
		jeremyList.delete_all();
		boltList.delete_all();
		player.SetHealth(basehealth);
		terryList.delete_all();
		inkList.delete_all();
		jeremys.Stop();
		hardM = false;
		NewGame();
	}

	//upgrades
	if (sym == SDLK_1 && RoundOver == true)
	{
		player.SetHealth(maxhealth);
		RoundOver = false;
		assigned = false;
	}
	if (sym == SDLK_2 && RoundOver == true)
	{
		maxhealth = maxhealth + (maxhealth / 10);
		player.SetHealth(player.GetHealth() + (player.GetHealth() / 10));
		RoundOver = false;
		assigned = false;
	}
	if (sym == SDLK_3 && RoundOver == true)
	{
		PdmgMult = PdmgMult + (PdmgMult / 10);
		RoundOver = false;
		assigned = false;
	}
	//difficulty modifier
	if (sym == SDLK_7 && IsMenuMode())
	{
		hardM = true;
		player.SetHealth(200);
		PdmgMult = 4;
		maxenemies = 16;
	}
		
}

void CMyGame::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode)
{
}


/////////////////////////////////////////////////////
// Mouse Events Handlers

void CMyGame::OnMouseMove(Uint16 x,Uint16 y,Sint16 relx,Sint16 rely,bool bLeft,bool bRight,bool bMiddle)
{
}

void CMyGame::OnLButtonDown(Uint16 x,Uint16 y)
{
	// start game with a left mouse button click
	if (IsMenuMode()) StartGame();

	if (IsGameOver() == false) 
	{
		
		CSprite* abolt = new CSprite(player.GetX(), player.GetY(), 0, 0, GetTime());
		abolt->AddImage("lightning.bmp", "bolt", 3, 1, 0, 0, 2, 0, CColor::Blue());
		abolt->SetAnimation("bolt", 7);
		if (player.GetStatus() == 2 || player.GetStatus() == 4)
			{
		abolt->SetDirection(90);
			}
		else if (player.GetStatus() == 1 || player.GetStatus() == 3)
			{
		abolt->SetDirection(270);
			}
		abolt->SetSpeed(500);
		bolts.Play("bolt.wav");
		boltList.push_back(abolt);
	}
	


	
	
}

void CMyGame::OnLButtonUp(Uint16 x,Uint16 y)
{
}

void CMyGame::OnRButtonDown(Uint16 x,Uint16 y)
{
}

void CMyGame::OnRButtonUp(Uint16 x,Uint16 y)
{
}

void CMyGame::OnMButtonDown(Uint16 x,Uint16 y)
{
}

void CMyGame::OnMButtonUp(Uint16 x,Uint16 y)
{
}



void CMyGame::Krabs()
{
	
	RoundOver = true;
	assigned = false;

}

void CMyGame::hard()
{
	maxGF = maxGF + round;
	for (CSprite* aink : inkList)
	{
		if (aink->GetX() < 0) aink->SetX(1920);
		if (aink->GetX() > 1920) aink->SetX(0);
		if (aink->GetY() < 0) aink->SetY(1080);
		if (aink->GetY() > 1080) aink->SetY(0);
	}

}