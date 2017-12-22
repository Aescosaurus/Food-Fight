#include "Door.h"

const Surface Door::spr = { "Images/Door.bmp" };

Door::Door( const Vec2& pos )
	:
	pos( pos ),
	hitbox( spr.GetRect() )
{
	hitbox.MoveTo( pos );
}

void Door::Draw( Graphics& gfx ) const
{
	gfx.DrawSprite( int( pos.x ),int( pos.y ),spr,Colors::Magenta,false );

	gfx.DrawHitbox( hitbox,{ 255,160,0 },true );
}

const Rect& Door::GetRect() const
{
	return hitbox;
}
