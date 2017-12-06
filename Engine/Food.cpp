#include "Food.h"
#include "Random.h"
#include "Graphics.h"

Food::Food()
	:
	size( 50.0f,50.0f ),
	pos( 0.0f,0.0f ),
	hitbox( pos,pos + size )
{
}

Food::Food( Random& rng )
	:
	Food()
{
	pos.x = float( rng.NextInt( int( size.x ),Graphics::ScreenWidth - int( size.x ) ) );
	pos.y = float( rng.NextInt( int( size.y ),Graphics::ScreenHeight - int( size.y ) ) );
}

Food::Food( const Vec2& pos )
	:
	Food()
{
	this->pos = pos;
}

Food::Food( const Vec2& pos,const Vec2& size )
	:
	size( size ),
	pos( pos ),
	hitbox( pos,pos + size )
{
}

void Food::Update( float dt )
{
	hitbox.MoveTo( pos );
}

void Food::Draw( Graphics& gfx ) const
{
	gfx.DrawRect( int( pos.x ),int( pos.y ),int( size.x ),int( size.y ),Colors::Magenta );
}

const Vec2& Food::GetPos() const
{
	return pos;
}

const Rect& Food::GetRect() const
{
	return hitbox;
}

HotDog::HotDog()
	:
	Food( { 0.0f,0.0f },{ 30.0f,70.0f } )
{
	target = { 0.0f,0.0f };
}

void HotDog::Update( float dt )
{
	const Vec2 diff = target - pos;
	pos += diff.GetNormalized() * speed * dt;

	Food::Update( dt );
}

void HotDog::Draw( Graphics& gfx ) const
{
	gfx.DrawSprite( int( pos.x ),int( pos.y ),spr );
}

void HotDog::Target( const Vec2& targetPos )
{
	target = targetPos;
}
