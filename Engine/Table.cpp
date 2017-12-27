#include "Table.h"

const Surface Table::sprites[4] =
{
	Surface( "Images/Table1.bmp" ),
	Surface( "Images/Table2.bmp" ),
	Surface( "Images/Table3.bmp" ),
	Surface( "Images/Table4.bmp" )
};
const Surface Table::tableAngles[nAngles] =
{
	Surface{ "Images/Table/Table1.bmp" },
	Surface{ "Images/Table/Table2.bmp" },
	Surface{ "Images/Table/Table3.bmp" },
	Surface{ "Images/Table/Table4.bmp" },
	Surface{ "Images/Table/Table5.bmp" },
	Surface{ "Images/Table/Table6.bmp" },
	Surface{ "Images/Table/Table7.bmp" },
	Surface{ "Images/Table/Table8.bmp" },
	Surface{ "Images/Table/Table9.bmp" }
};
const Vec2 Table::size = { 50.0f,50.0f };

Table::Table( const Vec2& pos )
	:
	pos( pos ),
	hitbox( pos,pos + size )
{
	while( pos.x + size.x > Graphics::ScreenWidth )
	{
		--this->pos.x;
	}
	while( pos.y + size.y > Graphics::ScreenHeight )
	{
		--this->pos.y;
	}
	hitbox.MoveTo( pos );
}

void Table::Update( Random& rng,float dt )
{
	if( s != State::Broken )
	{
		++hitTimer;
		// if( rng.NextInt( 0,10 ) > 5 )
		if( hitTimer > unhitTime )
		{
			hitTimer = 0;
			s = State::Normal;
		}
	}
}

void Table::Draw( Graphics& gfx ) const
{
	// if( s == State::Hurt )
	// {
	// 	gfx.DrawSprite( int( pos.x ),int( pos.y ),sprites[int( sprIndex )],Colors::White,Colors::Magenta );
	// }
	// else
	// {
	// 	gfx.DrawSprite( int( pos.x ),int( pos.y ),sprites[int( sprIndex )] );
	// }

	// if( int( sprIndex ) < nSprites - 1 )
	// {
	// 	gfx.DrawHitbox( hitbox,{ 255,160,0 },true );
	// }

	gfx.DrawSpriteExpanded( int( pos.x ),int( pos.y ),tableAngles[0],6,Colors::Magenta,false );

	if( s == State::Normal )
	{
		
	}
	else if( s == State::Hurt )
	{
		// Draw with that funny white overlay to signal damage has been taken.
	}

	if( s != State::Broken )
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
		s = State::Broken;
	}
	else
	{
		s = State::Hurt;
	}
}

void Table::CheckBulletCollision( Bullet& b )
{
	if( hitbox.IsOverlappingWith( b.GetRect() ) )
	{
		Hurt( 0.3f );
		b.Kill();
	}
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