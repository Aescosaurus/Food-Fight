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
	Enemy( class Random& rng );
	void Update( const class Player& p,const std::vector<Enemy>& others,float dt );
	void Update( float dt );
	void Draw( class Graphics& gfx ) const;

	void SetTarget( const Vec2& target );
	void SetAvoidTarget( const Vec2& antiTarget );

	const Rect& GetRect() const;
	const Vec2& GetPos() const;
private:
	static constexpr float speed = 100.0f;
	const Vec2 size = { 0.0f,0.0f };
	Vec2 pos = { 0.0f,0.0f };
	Rect hitbox = { 0.0f,0.0f,0.0f,0.0f };
	Vec2 vel = { 0.0f,0.0f };
	MoveState state = MoveState::Idle;
};