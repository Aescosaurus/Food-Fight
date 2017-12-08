#include "Player.h"
#include "Keyboard.h"
#include "Graphics.h"
#include <cassert>
#include "Random.h"
#include "Mouse.h"

Player::Player()
	:
	size( 50.0f,50.0f ),
	pos( 0.0f,0.0f ),
	hitbox( pos,pos + size )
{
}

Player::Player( Random& rng )
	:
	Player()
{
	pos.x = float( rng.NextInt( int( size.x / 2.0f ),Graphics::ScreenWidth - int( size.x / 2.0f ) ) );
	pos.y = float( rng.NextInt( int( size.y / 2.0f ),Graphics::ScreenHeight - int( size.y / 2.0f ) ) );
}

Player::Player( const Vec2& pos_in )
	:
	Player()
{
	pos = pos_in - size;
}

void Player::Update( const Keyboard& kbd,const Mouse& ms,float dt )
{
	const float moveTurn = moveSpeed * dt;
	Vec2 moveAmount = Vec2( 0.0f,0.0f );
	if( kbd.KeyIsPressed( int( 'W' ) ) && hitbox.top - moveTurn > 1.0f )
	{
		--moveAmount.y;
	}
	if( kbd.KeyIsPressed( int( 'S' ) ) && hitbox.bottom + moveTurn < float( Graphics::ScreenHeight - 1 ) )
	{
		++moveAmount.y;
	}
	if( kbd.KeyIsPressed( int( 'A' ) ) && hitbox.left - moveTurn > 1.0f )
	{
		--moveAmount.x;
	}
	if( kbd.KeyIsPressed( int( 'D' ) ) && hitbox.right + moveTurn < float( Graphics::ScreenWidth - 1 ) )
	{
		++moveAmount.x;
	}
	pos += moveAmount.GetNormalized() * moveTurn;
	
	hitbox.MoveTo( pos );

	if( shotTimer <= refireTime )
	{
		++shotTimer;
	}
}

void Player::Draw( Graphics& gfx ) const
{
	assert( hitbox.IsContainedBy( Graphics::GetScreenRect() ) );
	gfx.DrawRect( int( pos.x ),int( pos.y ),int( size.x ),int( size.y ),Colors::Red );

	gfx.DrawHitbox( hitbox,{ 255,160,0 },true );
}

bool Player::Fire()
{
	const bool canFire = ( shotTimer >= refireTime );
	if( canFire )
	{
		shotTimer = 0;
	}
	return canFire;
}

const Vec2& Player::GetPos() const
{
	return pos;
}