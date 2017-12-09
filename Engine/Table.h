#pragma once

#include "Vec2.h"
#include "Surface.h"
#include "Rect.h"

class Table
{
public:
	Table( const Vec2& pos );

	void Draw( class Graphics& gfx ) const;

	const Rect& GetRect() const;
	int CountTargets() const;
	const Vec2& GetTarget( int num ) const;
private:
	static const Surface spr;
	const Vec2 size;
	Vec2 pos;
	Rect hitbox;
	static constexpr int numTargets = 4;
	const Vec2 targets[numTargets] =
	{
		Vec2( pos.x - 30.0f,pos.y - 30.0f ), // Upper left.
		Vec2( pos.x + size.x + 30.0f,pos.y - 30.0f ), // Upper right.
		Vec2( pos.x + size.x + 30.0f,pos.y + size.y + 30.0f ), // Bottom right.
		Vec2( pos.x - 30.0f,pos.y + size.y + 30.0f ) // Bottom left.
	};
};