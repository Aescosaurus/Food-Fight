#pragma once

#include "Vec2.h"
#include "Surface.h"
#include "Rect.h"

class Table
{
public:
	Table( const Vec2& pos );

	void Draw( class Graphics& gfx ) const;
private:
	static const Surface spr;
	const Vec2 size;
	Vec2 pos;
	Rect hitbox;
};