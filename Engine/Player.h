#pragma once

#include "Vec2.h"
#include "Rect.h"
#include "Bullet.h"
#include <vector>
#include "Table.h"

class Player
{
public:
	Player();
	Player( class Random& rng );
	Player( const Vec2& pos );

	void Update( const class Keyboard& kbd,const class Mouse& ms,float dt );
	void Draw( class Graphics& gfx ) const;

	bool Fire();
	void MoveBack();
	void Hurt( int amount );

	void CheckTableCollision( const Table& t );

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
	float shotTimer = 0.0f;
	static constexpr float refireTime = 15.0f;
	static constexpr int maxHP = 10;
	int hp = maxHP;
};