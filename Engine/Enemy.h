#pragma once

#include "Vec2.h"

class Enemy
{
public:
	Enemy( class Random& rng );
	void Draw( class Graphics& gfx ) const;
private:
	const Vec2 size;
	Vec2 pos;
};