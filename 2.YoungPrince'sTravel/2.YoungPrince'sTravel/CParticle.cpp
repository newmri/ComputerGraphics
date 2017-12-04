#include "Define.h"
#include "Objects.h"

void CParticle::Init()
{
	// Initialize particles
	for (int i  = 0; i < MAX_PARTICLES; ++i) {
		par_sys[i].alive = true;
		par_sys[i].life = 1.0;
		par_sys[i].fade = float(rand() % 100) / 1000.0f + 0.003f;

		par_sys[i].xpos = (float)(rand() % (int)WINDOW_WIDTH - (int) WINDOW_WIDTH / 2);
		par_sys[i].ypos = (float)(rand() % (int)WINDOW_HEIGHT - (int)WINDOW_HEIGHT / 2);
		par_sys[i].zpos = (float)(rand() % 21) - 10;

		par_sys[i].red = 0.5;
		par_sys[i].green = 0.5;
		par_sys[i].blue = 1.0;

		par_sys[i].vel = 0.0;
		par_sys[i].gravity = -0.8;//-0.8;
		switch (rand() % 3) {
		case 0: par_sys[i].size = m_size;
		case 1: par_sys[i].size = m_size - 0.1f;
		case 2: par_sys[i].size = m_size - 0.2f;
		}
	}
}

void CParticle::InitParticle(int i)
{
	par_sys[i].alive = true;
	par_sys[i].life = 1.0;
	par_sys[i].fade = float(rand() % 100) / 1000.0f + 0.003f;

	par_sys[i].xpos = (float)(rand() % (int)WINDOW_WIDTH - (int)WINDOW_WIDTH / 2);
	par_sys[i].ypos = (float)(rand() % (int)WINDOW_HEIGHT - (int)WINDOW_HEIGHT / 2);
	par_sys[i].zpos = (float)(rand() % 21) - 10;

	
	par_sys[i].red = rand() * 1 / (float)RAND_MAX;
	par_sys[i].green = rand() * 1 / (float)RAND_MAX;
	par_sys[i].blue = rand() * 1 / (float)RAND_MAX;

	par_sys[i].vel = 0.0;
	par_sys[i].gravity = -0.8;//-0.8;
	switch (rand() % 3) {
	case 0: par_sys[i].size = m_size;
	case 1: par_sys[i].size = m_size - 0.1f;
	case 2: par_sys[i].size = m_size - 0.2f;
	}
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
			glColor3f(par_sys[i].red, par_sys[i].green, par_sys[i].blue);
			glPushMatrix();
			glTranslatef(x, y, z);
			glutSolidSphere(par_sys[i].size, 16, 16);
			glPopMatrix();

			// Update values

			par_sys[i].life -= par_sys[i].fade;
			par_sys[i].red = rand() * 1 / (float)RAND_MAX;
			par_sys[i].green = rand() * 1 / (float)RAND_MAX;
			par_sys[i].blue = rand() * 1 / (float)RAND_MAX;
			//Revive
			if (par_sys[i].life < 0.0) {
				this->InitParticle(i);
			}
			
		}
	}

	glPopMatrix();
}