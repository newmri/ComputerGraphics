#pragma once
#include "CObject.h"

typedef struct {
	// Life
	bool alive;	// is the particle alive?
	float life;	// particle lifespan
	float fade; // decay
				// color
	float red;
	float green;
	float blue;
	// Position/direction
	float xpos;
	float ypos;
	float zpos;
	// Velocity/Direction, only goes down in y dir
	float vel;
	// Gravity
	float gravity;
	
	float size;
}particles;

const int MAX_PARTICLES = 2000;

class CParticle : public CObject
{
public:
	virtual void Init();
	virtual void Update();
	virtual void Render();

public:
	void InitParticle(int i);

private:
	// Paticle System
	particles par_sys[MAX_PARTICLES];
};