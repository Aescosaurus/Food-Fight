#pragma once

#include "Vec2.h"
#include "Rect.h"

class Player
{
public:
	Player( class Random& rng );
	Player( const Vec2& pos,class Random& rng );
	void Update( class Keyboard& kbd,float dt );
	void Draw( class Graphics& gfx ) const;
private:
	static constexpr float moveSpeed = 3.5f;
	const Vec2 size;
	Vec2 pos;
	Rect hitbox;
	const Rect scrRect;
};