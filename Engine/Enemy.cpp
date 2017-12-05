#include "Enemy.h"
#include "Random.h"
#include "Graphics.h"
#include "Player.h"

Enemy::Enemy( Random& rng,const std::vector<Enemy>& others )
	:
	size( 55.0f,55.0f )
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
	const Vec2 diff = pos - p.GetPos();
	pos -= diff.GetNormalized() * speed;

	hitbox.MoveTo( pos );

	MoveState nextState = MoveState::Moving;
	for( const Enemy& e : others )
	{
		if( e.GetRect().IsOverlappingWith( hitbox ) )
		{
			nextState = MoveState::Avoiding;
		}
	}
	state = nextState;
}

void Enemy::Draw( Graphics& gfx ) const
{
	gfx.DrawRect( int( pos.x ),int( pos.y ),int( size.x ),int( size.y ),Colors::Magenta );
}

const Rect& Enemy::GetRect() const
{
	return hitbox;
}
