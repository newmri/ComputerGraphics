#include "Define.h"
#include "Objects.h"

void CParticle::Init()
{
	// Initialize particles
	for (int i  = 0; i < MAX_PARTICLES; ++i) {
		par_sys[i].alive = true;
		par_sys[i].life = 1.0;
		par_sys[i].fade = float(rand() % 100) / 1000.0f + 0.003f;

		par_sys[i].xpos = (float)(rand() % (int)(FLOOR_SCALE.x * FLOOR_SIZE)) - (int)(FLOOR_SCALE.x * FLOOR_SIZE) / 2;
		par_sys[i].ypos = m_pos.y;
		par_sys[i].zpos = (float)(rand() % 21) - 10;

		par_sys[i].red = 0.5;
		par_sys[i].green = 0.5;
		par_sys[i].blue = 1.0;

		par_sys[i].vel = 0.0;
		par_sys[i].gravity = -0.8;//-0.8;
	}
}

void CParticle::InitParticle(int i)
{
	par_sys[i].alive = true;
	par_sys[i].life = 1.0;
	par_sys[i].fade = float(rand() % 100) / 1000.0f + 0.003f;

	par_sys[i].xpos = (float)(rand() % (int)(FLOOR_SCALE.x * FLOOR_SIZE)) - (int)(FLOOR_SCALE.x * FLOOR_SIZE) / 2;
	par_sys[i].ypos = m_pos.y;
	par_sys[i].zpos = (float)(rand() % 21) - 10;

	par_sys[i].red = 0.5;
	par_sys[i].green = 0.5;
	par_sys[i].blue = 1.0;

	par_sys[i].vel = 0.0;
	par_sys[i].gravity = -0.8;//-0.8;
}

void CParticle::Update()
{
	
}

void CParticle::Render()
{

	glPushMatrix();
	float x, y, z;
	float slowdown = 0.1;
	float zoom = 0;
	for (int i  = 0; i < MAX_PARTICLES; i = i + 2) {
		if (par_sys[i].alive == true) {
			x = par_sys[i].xpos;
			y = par_sys[i].ypos;
			z = par_sys[i].zpos + zoom;

			// Draw particles
			glColor3f(1.0, 1.0, 1.0);
			glPushMatrix();
			glTranslatef(x, y, z);
			glutSolidSphere(m_size, 16, 16);
			glPopMatrix();

			// Update values
			//Move
			par_sys[i].ypos += par_sys[i].vel / (slowdown * 1000);
			par_sys[i].vel += par_sys[i].gravity;
			// Decay
			par_sys[i].life -= par_sys[i].fade;

			if (par_sys[i].ypos <= 0) {

				par_sys[i].life = -1.0;
			}

			//Revive
			if (par_sys[i].life < 0.0) {
				this->InitParticle(i);
			}
		}
	}

	glPopMatrix();
}