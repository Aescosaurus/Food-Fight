#include "Player.h"
#include <cassert>

const Vec2 Player::size = { 50.0f,50.0f };

Player::Player()
	:
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
	hitbox.MoveTo( pos );
}

void Player::Update( const Keyboard& kbd,const Mouse& ms,float dt )
{
	const float moveTurn = moveSpeed * dt;
	vel = Vec2( 0.0f,0.0f );
	if( kbd.KeyIsPressed( int( 'W' ) ) && hitbox.top - moveTurn > 1.0f )
	{
		--vel.y;
	}
	if( kbd.KeyIsPressed( int( 'S' ) ) && hitbox.bottom + moveTurn < float( Graphics::ScreenHeight - 1 ) )
	{
		++vel.y;
	}
	if( kbd.KeyIsPressed( int( 'A' ) ) && hitbox.left - moveTurn > 1.0f )
	{
		--vel.x;
	}
	if( kbd.KeyIsPressed( int( 'D' ) ) && hitbox.right + moveTurn < float( Graphics::ScreenWidth - 1 ) )
	{
		++vel.x;
	}
	vel = vel.GetNormalized() * moveTurn;
	pos += vel;
	
	hitbox.MoveTo( pos );

	if( shotTimer <= refireTime )
	{
		shotTimer += dt * refireTime * 2.0f;
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
		shotTimer = 0.0f;
	}
	return canFire;
}

void Player::MoveBack()
{
	pos -= vel;
	hitbox.MoveTo( pos );
}

void Player::Hurt( int amount )
{
	hp -= amount;
}

void Player::CheckTableCollision( const Table& t )
{
	if( hitbox.IsOverlappingWith( t.GetRect() ) )
	{
		pos.x -= vel.x;
		hitbox.MoveTo( pos );
	}
	if( hitbox.IsOverlappingWith( t.GetRect() ) )
	{
		pos.x += vel.x;
		pos.y -= vel.y;
		hitbox.MoveTo( pos );
	}
}

const Vec2& Player::GetPos() const
{
	return pos;
}

const Vec2& Player::GetSize()
{
	return size;
}

const Rect& Player::GetRect() const
{
	return hitbox;
}

const Vec2& Player::GetVel() const
{
	return vel;
}
