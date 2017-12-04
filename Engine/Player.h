#pragma once

#include "Vec2.h"
#include "Rect.h"
#include "Random.h"

class Player
{
public:
	Player();
	Player( const Vec2& pos );
	void Update( class Keyboard& kbd,float dt );
	void Draw( class Graphics& gfx ) const;
private:
	static constexpr float moveSpeed = 3.5f;
	const Vec2 size;
	Vec2 pos;
	Rect hitbox;
	Random rng;
	const Rect scrRect;
};