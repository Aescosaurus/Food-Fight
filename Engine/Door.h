#pragma once

#include "Vec2.h"
#include "Rect.h"
#include "Surface.h"
#include "Graphics.h"

class Door
{
public:
	Door( const Vec2& pos );

	void Draw( Graphics& gfx ) const;

	const Rect& GetRect() const;
private:
	static const Surface spr;
	const Vec2 pos;
	Rect hitbox;
};