#include "CShape.h"

void CShape::Init(OBJTYPE objType, MOVETYPE moveType, Pos pos, DATA_TYPE size)
{
	m_objType = objType;
	m_moveType = moveType;
	m_pos = pos;
	m_size = size;
	m_angle = 0.0f;

}

void CShape::Move()
{

}

void CShape::Update()
{
}

void CShape::Render()
{
	
	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	glTranslatef(m_pos.x, m_pos.y, 0.0f);
	this->Rotate();
	this->ChangeSizeBigger();

	switch (m_objType) {
	case CONE: glutWireCone(1, 1, 5, 5); break;
	case CUBE: glutWireCube(m_size); break;
	case DODECAHEDROPN: glutWireDodecahedron(); break;
	case LCOSAHEDRON: glutWireIcosahedron(); break;
	case OCTAHEDRON: glutWireOctahedron(); break;
	case SPHERE: glutWireSphere(m_size, 5, 5); break;
	case TEAPOT: glutWireTeapot(m_size); break;
	case TETRAHEDRON: glutWireTetrahedron(); break;
	case TORUS: glutWireTorus(m_size, m_size, 5, 5); break;
	default: break;
	}
	glEnd();
	glPopMatrix();
}

