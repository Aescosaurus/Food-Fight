#pragma once

#include "Vec2.h"
#include "Surface.h"
#include "Rect.h"
#include "Bullet.h"
#include "Random.h"
#include "Graphics.h"

class Table
{
private:
	enum class State
	{
		Normal,
		Hurt,
		Broken
	};
public:
	Table( const Vec2& pos );

	void Update( Random& rng,float dt );
	void Draw( Graphics& gfx ) const;

	void Hurt( float damage );

	void CheckBulletCollision( Bullet& b );

	const Vec2& GetPos() const;
	const Rect& GetRect() const;
	operator bool() const;
private:
	static constexpr int nSprites = 4;
	static const Surface sprites[nSprites];
	static constexpr int nAngles = 9;
	static const Surface tableAngles[nAngles];
	static const Vec2 size;
	Vec2 pos;
	Rect hitbox;
	float sprIndex = 0;
	State s = State::Normal;
	int hitTimer = 0;
	static constexpr int unhitTime = 2;
};