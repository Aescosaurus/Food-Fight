#include "Foods.h"
#include "Graphics.h"
#include "Random.h"

Foods::Cabbage::Cabbage()
	:
	size( 25.0f,25.0f ),
	pos( 0.0f,0.0f ),
	vel( 0.0f,0.0f ),
	hitbox( pos,pos + size )
{
}

Foods::Cabbage::Cabbage( const Vec2& pos )
	:
	Cabbage()
{
	this->pos = pos;
}

Foods::Cabbage::Cabbage( Random& rng )
	:
	Cabbage()
{
	pos.x = float( rng.NextInt( int( size.x ),Graphics::ScreenWidth - int( size.x ) ) );
	pos.y = float( rng.NextInt( int( size.y ),Graphics::ScreenHeight - int( size.y ) ) );
}

void Foods::Cabbage::Update( float dt )
{
	if( Vec2::FindDistSq( pos,target ) < size.x )
	{
		canRetarget = true;
	}
	else
	{
		pos += vel.GetNormalized() * speed * dt;
		canRetarget = false;
	}

	hitbox.MoveTo( pos );
}

void Foods::Cabbage::Draw( Graphics& gfx ) const
{
	gfx.DrawCircle( int( pos.x + size.x / 2 ),int( pos.y + size.y / 2 ),int( size.x ),Colors::MakeRGB( 232,237,193 ) );
}

void Foods::Cabbage::SetDir( const Vec2& target )
{
	if( canRetarget )
	{
		this->target = target;
		vel = target - pos;
	}
}

const Vec2& Foods::Cabbage::GetPos() const
{
	return pos;
}

const Rect& Foods::Cabbage::GetRect() const
{
	return hitbox;
}
