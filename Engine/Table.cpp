#include "Table.h"
#include "Graphics.h"

const Surface Table::spr = { "Images/Table1.bmp" };

Table::Table( const Vec2& pos )
	:
	size( 64.0f,32.0f ),
	pos( pos ),
	hitbox( spr.GetRect() )
{
	hitbox.MoveTo( pos );
}

void Table::Draw( Graphics& gfx ) const
{
	gfx.DrawSprite( int( pos.x ),int( pos.y ),spr );

	gfx.DrawHitbox( hitbox,{ 255,160,0 },true );
}

const Rect& Table::GetRect() const
{
	return hitbox;
}

int Table::CountTargets() const
{
	return numTargets;
}

const Vec2& Table::GetTarget( int num ) const
{
	return targets[num];
}

