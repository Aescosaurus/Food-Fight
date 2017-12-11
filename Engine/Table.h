#pragma once

#include "Vec2.h"
#include "Surface.h"
#include "Rect.h"

class Table
{
public:
	Table( const Vec2& pos );

	void Draw( class Graphics& gfx ) const;

	void Hurt( float damage );

	const Vec2& GetPos() const;
	const Rect& GetRect() const;
	operator bool() const;
private:
	static constexpr int nSprites = 4;
	static const Surface sprites[nSprites];
	static const Vec2 size;
	Vec2 pos;
	Rect hitbox;
	float sprIndex = 0;
};