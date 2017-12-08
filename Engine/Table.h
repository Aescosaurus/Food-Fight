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
		pos - Vec2( 10.0f,10.0f ), // Upper left.
		pos + Vec2( size.x + 10.0f,-10.0f ), // Upper right.
		pos + size + Vec2( 10.0f,10.0f ), // Bottom right.
		pos + Vec2( -10.0f,size.y + 10.0f ) // Bottom left.
	};
};