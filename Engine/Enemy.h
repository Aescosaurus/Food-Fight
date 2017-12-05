#pragma once

#include "Vec2.h"
#include "Rect.h"
#include <vector>

class Enemy
{
public:
	Enemy();
	Enemy( class Random& rng );
	Enemy( const Vec2& pos );
	void Update( float dt );
	void Draw( class Graphics& gfx,const Rect& scrRect ) const;

	void SetTarget( const Vec2& target );
	void SetAvoidTarget( const Vec2& antiTarget );

	const Rect& GetRect() const;
	const Vec2& GetPos() const;
private:
	static constexpr float speed = 100.0f;
	const Vec2 size;
	Vec2 pos;
	Rect hitbox;
	Vec2 vel;
};