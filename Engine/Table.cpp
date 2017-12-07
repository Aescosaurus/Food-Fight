#include "Table.h"
#include "Graphics.h"

Table::Table( const Vec2& pos )
	:
	size( 64.0f,32.0f ),
	pos( pos )
{
}

void Table::Draw( Graphics& gfx ) const
{
	gfx.DrawSprite( int( pos.x ),int( pos.y ),spr );
}
