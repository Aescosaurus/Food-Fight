#include "Bullet.h"
#include "Graphics.h"
#include <cassert>

const Surface Bullet::spr = Surface( "Images/Bullet.bmp" );
const Vec2 Bullet::size = Vec2( 10.0f,10.0f );

Bullet::Bullet( const Vec2& origin,const Vec2& target )
	:
	pos( origin ),
	hitbox( spr.GetRect() )
{
	vel = ( target - pos ).Normalize();
	hitbox.MoveTo( pos );
}

void Bullet::Update( float dt )
{
	pos += vel * speed * dt;

	hitbox.MoveTo( pos );
	// Needs to be expanded because DrawHitbox sometimes goes like
	//  0.01 opacity pixel 1 outside the screen.
	if( !hitbox.GetExpanded( 1 ).IsContainedBy( Graphics::GetScreenRect() ) )
	{
		willDestroy = true;
	}
}

void Bullet::Draw( Graphics& gfx ) const
{
	assert( hitbox.IsContainedBy( Graphics::GetScreenRect() ) || willDestroy );
	// gfx.DrawCircle( int( pos.x + size.x / 2 ),int( pos.y + size.y / 2 ),int( size.x / 2 ),Colors::Blue );
	gfx.DrawSprite( int( pos.x ),int( pos.y ),spr );

	gfx.DrawHitbox( hitbox,{ 255,160,0 },true );
}

void Bullet::Kill()
{
	willDestroy = true;
}

Bullet::operator bool() const
{
	return !willDestroy;
}

const Rect& Bullet::GetRect() const
{
	return hitbox;
}
