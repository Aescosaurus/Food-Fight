#pragma once

#include "Vec2.h"
#include "Rect.h"
#include "Surface.h"

class Food
{
public:
	Food();
	Food( class Random& rng );
	Food( const Vec2& pos );
	Food( const Vec2& pos,const Vec2& size );

	void Update( float dt );
	void Draw( class Graphics& gfx ) const;

	const Vec2& GetPos() const;
	const Rect& GetRect() const;
protected:
	const Vec2 size;
	Vec2 pos;
	Rect hitbox;
	int hitTimer = 0;
	static constexpr int unhitTime = 2;
private:
};

class HotDog : public Food
{
private:
	enum class MoveState
	{
		Moving,
		Waiting,
		Hurt
	};
public:
	HotDog();
	
	HotDog( const HotDog& other );
	HotDog& operator=( const HotDog& other );

	void Update( float dt,class Random& rng );
	void Draw( class Graphics& gfx ) const;

	void Hurt( int amount );
	void Target( const Vec2& targetPos );
	void BounceOffOf( const Vec2& pos );

	operator bool() const;
private:
	static constexpr float speed = 30.5f;
	static const Surface spr;
	Vec2 target;
	MoveState state = MoveState::Waiting;
	static constexpr int maxHP = 10;
	int hp = maxHP;
};

class Meatball : public Food
{
public:
	Meatball( const Vec2& pos );

	void Update( float dt );
	void Draw( class Graphics& gfx ) const;

	void Target( const Vec2& targetPos );
private:
	static constexpr float speed = 50.0f;
	Vec2 target;
};