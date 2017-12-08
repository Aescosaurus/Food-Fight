#pragma once

#include "Vec2.h"
#include "Rect.h"
#include "Bullet.h"
#include <vector>

class Player
{
public:
	Player();
	Player( class Random& rng );
	Player( const Vec2& pos );

	void Update( const class Keyboard& kbd,const class Mouse& ms,float dt );
	void Draw( class Graphics& gfx ) const;

	bool Fire();
	void Move( const Vec2& pushAmount );

	const Vec2& GetPos() const;
	static const Vec2& GetSize();
	const Rect& GetRect() const;
	const Vec2& GetVel() const;
private:
	static constexpr float moveSpeed = 170.0f;
	static const Vec2 size;
	Vec2 pos;
	Rect hitbox;
	Vec2 vel;
	int shotTimer = 0;
	static constexpr int refireTime = 15;
};