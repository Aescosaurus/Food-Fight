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
	const Surface spr = { "Images/Table1.bmp" }; // TODO: Make this static. :)
	const Vec2 size;
	Vec2 pos;
	Rect hitbox;
};