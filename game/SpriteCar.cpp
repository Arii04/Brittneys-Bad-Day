#include "stdafx.h"
#include "SpriteCar.h"

CSpriteCar::CSpriteCar(Sint16 x, Sint16 y, Uint32 time)
	: CSprite(x, y, 100, 100, "car.gif", time)
{
	turn = 0;
	gear = 0;
	brakes = false;
}

CSpriteCar::~CSpriteCar()
{
}

void CSpriteCar::OnUpdate(Uint32 time, Uint32 deltaTime)
{
    // Retrieve current speed
    float v = GetSpeed();

    // TODO: Calculate acceleration based on gear
    float forwardAcceleration = 2.5; // Example value, adjust as needed
    float reverseAcceleration = 0.03f; // Example value, lower for reverse
    float neutralAcceleration = 0.0f; // Neutral gear

    float acceleration = 0.0f;
    if (gear == 1)
        acceleration = forwardAcceleration;
    else if (gear == -1)
        acceleration = -reverseAcceleration;
    else
        acceleration = neutralAcceleration;

    v += acceleration * deltaTime;

    float airResistance = 0.0001f * v * v;
    float rollingResistance = 0.001f;
    float brakeResistance = brakes ? 0.01f : 0.0f;

    v -= (airResistance + rollingResistance + brakeResistance) * deltaTime;

    if (v < 0.0f)
        v = 0.0f;

    float turnFactor = 1.0f; 
    if (v > 0.0f) {
        if (turn == -1)
            SetDirection(GetDirection() - turnFactor);
        else if (turn == 1)
            SetDirection(GetDirection() + turnFactor);
    }
    SetRotation(GetDirection());

    SetSpeed(v);

    CSprite::OnUpdate(time, deltaTime);
}

