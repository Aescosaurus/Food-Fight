#include "Bullet.h"
#include "Graphics.h"
#include <cassert>

const Surface Bullet::spr = Surface( "Images/Bullet.bmp" );
const Vec2 Bullet::size = Vec2( 10.0f,10.0f );

Bullet::Bullet( const Vec2& origin,const Vec2& target )
	:
	pos( origin ),
	hitbox( pos,pos + size )
{
	vel = ( target - pos ).Normalize();
}

void Bullet::Update( float dt )
{
	pos += vel * speed * dt;

	hitbox.MoveTo( pos );
	if( !hitbox.IsContainedBy( Graphics::GetScreenRect() ) )
	{
		willDestroy = true;
	}
}

void Bullet::Draw( Graphics& gfx ) const
{
	assert( hitbox.IsContainedBy( Graphics::GetScreenRect() ) || willDestroy );
	gfx.DrawCircle( int( pos.x + size.x / 2 ),int( pos.y + size.y / 2 ),int( size.x / 2 ),Colors::Blue );
}

Bullet::operator bool() const
{
	return !willDestroy;
}
