#pragma once

#include "Vec2.h"
#include "Rect.h"
#include "Surface.h"

class Bullet
{
public:
	Bullet() = default;
	Bullet( const Vec2& origin,const Vec2& target );

	void Update( float dt );
	void Draw( class Graphics& gfx ) const;

	operator bool() const;
private:
	static constexpr float speed = 150.5f;
	static const Surface spr;
	static const Vec2 size;
	Vec2 pos;
	Vec2 vel;
	Rect hitbox;
	bool willDestroy = false;
};