#include "Table.h"
#include "Graphics.h"
#include "Random.h"

const Surface Table::sprites[4] =
{
	Surface( "Images/Table1.bmp" ),
	Surface( "Images/Table2.bmp" ),
	Surface( "Images/Table3.bmp" ),
	Surface( "Images/Table4.bmp" )
};
const Vec2 Table::size = { float( sprites[0].GetWidth() ),float( sprites[0].GetHeight() ) };

Table::Table( const Vec2& pos )
	:
	pos( pos ),
	hitbox( sprites[0].GetRect() )
{
	hitbox.MoveTo( pos );
}

void Table::Update( Random& rng,float dt )
{
	++hitTimer;
	// if( rng.NextInt( 0,10 ) > 5 )
	if( hitTimer > unhitTime )
	{
		hitTimer = 0;
		s = State::Normal;
	}
}

void Table::Draw( Graphics& gfx ) const
{
	if( s == State::Hurt )
	{
		gfx.DrawSprite( int( pos.x ),int( pos.y ),sprites[int( sprIndex )],Colors::White,Colors::Magenta );
	}
	else
	{
		gfx.DrawSprite( int( pos.x ),int( pos.y ),sprites[int( sprIndex )] );
	}

	if( int( sprIndex ) < nSprites - 1 )
	{
		gfx.DrawHitbox( hitbox,{ 255,160,0 },true );
	}
}

void Table::Hurt( float damage )
{
	sprIndex += damage;
	if( int( sprIndex ) > nSprites - 1 )
	{
		hitbox.MoveTo( { float( Graphics::ScreenWidth ),float( Graphics::ScreenHeight ) } );
	}
	s = State::Hurt;
}

const Vec2& Table::GetPos() const
{
	return pos;
}

const Rect& Table::GetRect() const
{
	return hitbox;
}

Table::operator bool() const
{
	return int( sprIndex ) < nSprites - 1;
}