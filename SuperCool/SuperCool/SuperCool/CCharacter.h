#pragma once

#include "CObject.h"

class CCharacter : public CObject
{
public:
	virtual void Init() = 0;
	virtual void Move(float frameTime) = 0;
	virtual void Update(float frameTime) = 0;
	virtual void Render() = 0;

};