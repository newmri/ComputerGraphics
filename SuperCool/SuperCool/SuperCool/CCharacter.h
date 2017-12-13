#pragma once

#include "CObject.h"

class CCharacter : public CObject
{
public:
	virtual void Init() = 0;
	virtual void Move() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;

};