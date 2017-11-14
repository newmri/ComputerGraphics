#include "CObject.h"

void CObject::Init(float(*arr)[3])
{
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 3; ++j) m_ctrlPoints[i][j] = arr[i][j];
	}

}

void CObject::Update()
{

}

void CObject::Render()
{
	
	
}