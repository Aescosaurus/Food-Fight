#include "Player.h"
#include "Keyboard.h"
#include "Graphics.h"
#include <cassert>
#include "Random.h"

Player::Player( Random& rng )
	:
	size( 50.0f,50.0f ),
	pos( 0.0f,0.0f ),
	hitbox( pos,size.x,size.y ),
	scrRect( 0.0f,float( Graphics::ScreenWidth ),0.0f,float( Graphics::ScreenHeight ) )
{
	pos.x = float( rng.NextInt( int( size.x / 2.0f ),Graphics::ScreenWidth - int( size.x / 2.0f ) ) );
	pos.y = float( rng.NextInt( int( size.y / 2.0f ),Graphics::ScreenHeight - int( size.y / 2.0f ) ) );
}

Player::Player( const Vec2& pos_in,Random& rng )
	:
	Player( rng )
{
	pos = pos_in - size;
}

void Player::Update( Keyboard& kbd,float dt )
{
	Vec2 moveAmount = Vec2( 0.0f,0.0f );
	if( kbd.KeyIsPressed( int( 'W' ) ) && pos.y - moveSpeed > 0.0f )
	{
		--moveAmount.y;
	}
	if( kbd.KeyIsPressed( int( 'S' ) ) && int( pos.y + size.y + moveSpeed ) < Graphics::ScreenHeight )
	{
		++moveAmount.y;
	}
	if( kbd.KeyIsPressed( int( 'A' ) ) && pos.x - moveSpeed > 0.0f )
	{
		--moveAmount.x;
	}
	if( kbd.KeyIsPressed( int( 'D' ) ) && int( pos.x + size.x + moveSpeed ) < Graphics::ScreenWidth )
	{
		++moveAmount.x;
	}
	moveAmount.Normalize();
	pos += moveAmount * moveSpeed;

	hitbox.MoveTo( pos );
}

void Player::Draw( Graphics& gfx ) const
{
	assert( hitbox.IsContainedBy( scrRect ) );
	gfx.DrawRect( int( pos.x ),int( pos.y ),int( size.x ),int( size.y ),Colors::Red );
}
