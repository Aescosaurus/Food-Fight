#pragma once

#include "Vec2.h"
#include "Surface.h"
#include "Rect.h"

class Table
{
public:
	Table( const Vec2& pos );

	void Draw( class Graphics& gfx ) const;

	void Move( const Vec2& pushVel );

	const Rect& GetRect() const;
	const Vec2& GetMoveAmount() const;
private:
	static const Surface spr;
	const Vec2 size;
	Vec2 pos;
	Rect hitbox;
	Vec2 moveAmount;
};