#pragma once

#include "Vec2.h"
#include "Surface.h"
#include "Rect.h"

class Table
{
public:
	Table( const Vec2& pos );

	void Draw( class Graphics& gfx ) const;

	void Break();

	const Rect& GetRect() const;
	const Vec2& GetPos() const;
	operator bool() const;

	int CountTargets() const;
	const Vec2& GetTarget( int num ) const;
	// Finds closest target to pos, and returns offset num of list of that order.
	const Vec2 GetClosestTarget( const Vec2& pos,int num );
private:
	void SortByHighest( Vec2* start,int max );
private:
	static const Surface spr;
	static const Surface broken;
	static constexpr int nSprites = 3;
	static const Surface sprites[nSprites];
	const Vec2 size;
	Vec2 pos;
	Rect hitbox;
	bool isBroken = false;
	int sprIndex = 0;
	static constexpr int numTargets = 4;
	const Vec2 targets[numTargets] =
	{
		Vec2( pos.x - 30.0f,pos.y - 30.0f ), // Upper left.
		Vec2( pos.x + size.x + 30.0f,pos.y - 30.0f ), // Upper right.
		Vec2( pos.x + size.x + 30.0f,pos.y + size.y + 30.0f ), // Bottom right.
		Vec2( pos.x - 30.0f,pos.y + size.y + 30.0f ) // Bottom left.
	};
};