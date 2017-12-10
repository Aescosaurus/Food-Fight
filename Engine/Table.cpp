#include "Table.h"
#include "Graphics.h"

const Surface Table::spr = { "Images/Table1.bmp" };
const Surface Table::broken = { "Images/Table2.bmp" };

Table::Table( const Vec2& pos )
	:
	size( float( spr.GetWidth() ),float( spr.GetHeight() ) ),
	pos( pos ),
	hitbox( spr.GetRect() )
{
	hitbox.MoveTo( pos );
}

void Table::Draw( Graphics& gfx ) const
{
	if( !isBroken )
	{
		gfx.DrawSprite( int( pos.x ),int( pos.y ),spr );
		gfx.DrawHitbox( hitbox,{ 255,160,0 },true );
	}
	else
	{
		gfx.DrawSprite( int( pos.x ),int( pos.y ),broken );
	}
}

void Table::Break()
{
	hitbox.MoveTo( { float( Graphics::ScreenWidth ),float( Graphics::ScreenHeight ) } );
	isBroken = true;
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

const Vec2 Table::GetClosestTarget( const Vec2& pos,int num )
{
	Vec2 possibleTargets[numTargets];
	// Copy targets over to possibleTargets.
	for( int i = 0; i < numTargets; ++i )
	{
		possibleTargets[i] = targets[i];
	}
	SortByHighest( possibleTargets,numTargets );

	return possibleTargets[num];
}

void Table::SortByHighest( Vec2* start,int max )
{
	Vec2* newList = new Vec2[max];
	for( int i = 0; i < max; ++i )
	{
		newList[i] = start[i];
	}

	for( int i = 0; i < max; ++i )
	{
		for( int j = 0; j < max; ++j )
		{
			if( newList[j].GetLengthSq() > newList[i].GetLengthSq() )
			{
				std::swap( newList[i],newList[j] );
			}
		}
	}

	for( int i = 0; i < max; ++i )
	{
		start[i] = newList[i];
	}

	delete[] newList;
}
