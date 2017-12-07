#pragma once

#include "Vec2.h"
#include "Surface.h"

class Table
{
public:
	Table( const Vec2& pos );

	void Draw( class Graphics& gfx ) const;
private:
	Vec2 pos;
	const Vec2 size;
	const Surface spr = { "Images/Table1.bmp" };
};