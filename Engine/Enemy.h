#pragma once

#include "Vec2.h"
#include "Rect.h"
#include <vector>

class Enemy
{
private:
	enum class MoveState
	{
		Moving,
		Avoiding,
		Idle
	};
public:
	Enemy( class Random& rng,const std::vector<Enemy>& others );
	void Update( const class Player& p,const std::vector<Enemy>& others,float dt );
	void Draw( class Graphics& gfx ) const;

	const Rect& GetRect() const;
private:
	static constexpr float speed = 2.5f;
	const Vec2 size;
	Vec2 pos;
	Rect hitbox;
	Vec2 vel;
	MoveState state = MoveState::Idle;
};