#pragma once

class CSpriteCar : public CSprite
{
	int turn;		// Steering Wheel: turn < 0 is left;  turn == 0 is straight on;  turn > 0 is right
	int gear;		// Gear:  gear > 0 is gear; gear < 0 is reverse; gear == 0 is neutral
	bool brakes;	// Brakes
public:
	CSpriteCar(Sint16 x, Sint16 y, Uint32 time);
	~CSpriteCar(void);

// User Steering

	void CSpriteCar::Turn(int n)	{ turn = n; }
	void SetGear(int n)				{ gear = n; }
	void SetBrake(bool b)			{ brakes = b; }

	int GetTurn() { return turn; }
	int GetGear() { return gear; }
	bool GetBrake() { return brakes; }

// Called 60 times every second to update the position of the car
	virtual void OnUpdate(Uint32 time, Uint32 deltaTime);
};
