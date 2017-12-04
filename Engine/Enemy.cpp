#include "Enemy.h"
#include "Random.h"
#include "Graphics.h"

Enemy::Enemy( Random& rng )
	:
	size( 55.0f,55.0f )
{
	pos.x = float( rng.NextInt( size.x,Graphics::ScreenWidth - size.x ) );
	pos.y = float( rng.NextInt( size.y,Graphics::ScreenHeight - size.y ) );
}

void Enemy::Draw( Graphics& gfx ) const
{
	gfx.DrawRect( pos.x,pos.y,size.x,size.y,Colors::Magenta );
}
