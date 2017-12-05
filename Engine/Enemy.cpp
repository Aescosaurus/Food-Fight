#include "Enemy.h"
#include "Random.h"
#include "Graphics.h"
#include "Player.h"

Enemy::Enemy( Random& rng,const std::vector<Enemy>& others )
	:
	size( 55.0f,55.0f ),
	hitbox( pos,pos + size )
{
	bool isTouching = false;
	do
	{
		pos.x = float( rng.NextInt( int( size.x ),Graphics::ScreenWidth - int( size.x ) ) );
		pos.y = float( rng.NextInt( int( size.y ),Graphics::ScreenHeight - int( size.y ) ) );
		hitbox.MoveTo( pos );

		for( const Enemy& e : others )
		{
			if( e.GetRect().IsOverlappingWith( hitbox ) )
			{
				isTouching = true;
			}
		}
	} while( isTouching );
}

void Enemy::Update( const Player& p,const std::vector<Enemy>& others,float dt )
{
	Vec2 posToAvoid;
	MoveState nextState = MoveState::Moving;
	for( const Enemy& e : others )
	{
		if( e.GetRect().IsOverlappingWith( hitbox ) && &e != &( *this ) )
		{
			nextState = MoveState::Avoiding;
			posToAvoid = e.GetPos();
			break;
		}
	}
	state = nextState;

	if( state == MoveState::Moving )
	{
		const Vec2 diff = pos - p.GetPos();
		pos -= diff.GetNormalized() * speed * dt;
	}
	else if( state == MoveState::Avoiding )
	{
		const Vec2 diff = pos - posToAvoid;
		pos += diff.GetNormalized() * speed * dt;
	}

	hitbox.MoveTo( pos );
}

void Enemy::Update( float dt )
{
	pos += vel * speed * dt;

	hitbox.MoveTo( pos );
}

void Enemy::Draw( Graphics& gfx ) const
{
	gfx.DrawRect( int( pos.x ),int( pos.y ),int( size.x ),int( size.y ),Colors::Magenta );
}

void Enemy::SetTarget( const Vec2& target )
{
	vel = Vec2( 0.0f,0.0f ) - ( pos - target );
	vel.Normalize();
}

void Enemy::SetAvoidTarget( const Vec2& antiTarget )
{
	vel = Vec2( 0.0f,0.0f ) + ( pos - antiTarget );
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
