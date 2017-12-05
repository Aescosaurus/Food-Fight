#include "Enemy.h"
#include "Random.h"
#include "Graphics.h"
#include "Player.h"
#include <cassert>

Enemy::Enemy()
	:
	size( 55.0f,55.0f ),
	hitbox( pos,pos + size ),
	pos( 0.0f,0.0f ),
	vel( 0.0f,0.0f )
{
}

Enemy::Enemy( Random& rng )
	:
	Enemy()
{
	pos.x = float( rng.NextInt( int( size.x ),Graphics::ScreenWidth - int( size.x ) ) );
	pos.y = float( rng.NextInt( int( size.y ),Graphics::ScreenHeight - int( size.y ) ) );
}

Enemy::Enemy( const Vec2& pos )
	:
	Enemy()
{
	this->pos = pos;
}

void Enemy::Update( float dt )
{
	pos += vel * speed * dt;

	hitbox.MoveTo( pos );
}

void Enemy::Draw( Graphics& gfx,const Rect& scrRect ) const
{
	assert( hitbox.IsContainedBy( scrRect ) );
	gfx.DrawRect( int( pos.x ),int( pos.y ),int( size.x ),int( size.y ),Colors::Magenta );
}

void Enemy::SetTarget( const Vec2& target )
{
	vel = -( pos - target );
	vel.Normalize();
}

void Enemy::SetAvoidTarget( const Vec2& antiTarget )
{
	vel = pos - antiTarget;
	vel.Normalize();
}

const Rect& Enemy::GetRect() const
{
	return hitbox;
}

const Vec2& Enemy::GetPos() const
{
	return pos;
}
