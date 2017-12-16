#include "Food.h"
#include "Random.h"
#include "Graphics.h"
#include <cassert>
#include "Table.h"

const Surface HotDog::spr = Surface( "Images/HotDog.bmp" );

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

void Food::RandomizeState( Random& rng )
{
	if( rng.NextInt( 0,10 ) > 5 )
	{
		state = MoveState::Moving;
	}
	else
	{
		state = MoveState::Waiting;
	}
}

HotDog::HotDog()
	:
	Food( { 0.0f,0.0f },{ 30.0f,70.0f } )
{
	target = { 0.0f,0.0f };
	hitbox = spr.GetRect();
	hitbox.MoveTo( pos );
}

HotDog::HotDog( const HotDog& other )
{
	*this = other;
}

HotDog& HotDog::operator=( const HotDog& other )
{
	pos = other.pos;
	target = other.target;
	hitbox = other.hitbox;
	hp = other.hp;

	return *this;
}

void HotDog::Update( Random& rng,float dt )
{
	// const int rngNum = rng.NextInt( 0,10 );
	// if( rngNum > 6 )
	// {
	// 	state = MoveState::Waiting;
	// }
	// else if( rngNum > 4 )
	// {
	// 	state = MoveState::Moving;
	// }
	// else
	// {
	// 	// State is still being hurt.
	// }

	++hitTimer;
	if( hitTimer > unhitTime )
	{
		hitTimer = 0;
		RandomizeState( rng );
	}

	if( state == MoveState::Moving )
	{
		const Vec2 diff = target - pos;
		pos += diff.GetNormalized() * speed * dt;
	}

	Food::Update( dt );
}

void HotDog::Draw( Graphics& gfx ) const
{
	assert( hitbox.IsContainedBy( Graphics::GetScreenRect() ) );
	// if( state != MoveState::Hurt )
	// {
	// 	if( target.x < pos.x )
	// 	{
	// 		gfx.DrawSprite( int( pos.x ),int( pos.y ),spr,Colors::Magenta,true );
	// 	}
	// 	else
	// 	{
	// 		gfx.DrawSprite( int( pos.x ),int( pos.y ),spr,Colors::Magenta,false );
	// 	}
	// }
	// else
	// {
	// 	gfx.DrawSprite( int( pos.x ),int( pos.y ),spr,Colors::White,Colors::Magenta );
	// }

	if( state != MoveState::Hurting )
	{
		gfx.DrawSprite( int( pos.x ),int( pos.y ),spr,Colors::Magenta,( target.x < pos.x ) );
	}
	else
	{
		gfx.DrawSprite( int( pos.x ),int( pos.y ),spr,Colors::White,Colors::Magenta,( target.x < pos.x ) );
	}

	gfx.DrawHitbox( hitbox,{ 255,160,0 },true );
	gfx.DrawLine( int( pos.x ),int( pos.y ),int( target.x ),int( target.y ),Colors::Cyan );
}

void HotDog::Hurt( int amount )
{
	hp -= amount;
	state = MoveState::Hurting;
}

void HotDog::Target( const Vec2& targetPos )
{
	target = targetPos;
}

void HotDog::BounceOffOf( const Vec2& pos_in )
{
	state = MoveState::Hurting;
	const Vec2 moveAwayDir = ( pos_in - pos ).Normalize();
	pos -= moveAwayDir * speed;
}

HotDog::operator bool() const
{
	return hp > 0;
}

Meatball::Meatball( const Vec2& pos )
	:
	Food( pos,{ 55.0f,55.0f } ),
	target( pos ),
	vel( speed,speed )
{
}

Meatball::Meatball( const Meatball& other )
{
	*this = other;
}

Meatball& Meatball::operator=( const Meatball& other )
{
	pos = other.pos;
	target = other.target;
	hitbox = other.hitbox;
	hp = other.hp;

	return *this;
}

void Meatball::Update( Random& rng,float dt )
{
	++hitTimer;
	if( hitTimer > unhitTime )
	{
		hitTimer = 0;
		// state = MoveState::Moving;
	}

	// if( Vec2{ target - pos }.GetLengthSq() < vel.GetLengthSq() )
	// {
	// 	state = MoveState::Waiting;
	// }

	const Vec2 lastMoveAmount = vel.GetNormalized() * speed * dt;
	pos += lastMoveAmount;

	if( hitbox.GetExpanded( 5.0f ).IsContainedBy( Graphics::GetScreenRect() ) )
	{
		canRetarget = false;
	}
	else
	{
		canRetarget = true;
		pos -= lastMoveAmount * 20.0f;
		vel = -vel;
	}

	Food::Update( dt );
}

void Meatball::Draw( Graphics& gfx ) const
{
	assert( hitbox.IsContainedBy( Graphics::GetScreenRect() ) );
	if( state == MoveState::Hurting )
	{
		gfx.DrawRect( int( pos.x ),int( pos.y ),int( size.x ),int( size.y ),Colors::White );
	}
	else
	{
		gfx.DrawRect( int( pos.x ),int( pos.y ),int( size.x ),int( size.y ),Colors::Red );
	}

	gfx.DrawHitbox( hitbox,Colors::MakeRGB( 255,160,0 ),true );
	gfx.DrawLine( int( pos.x ),int( pos.y ),int( target.x ),int( target.y ),Colors::Cyan );
}

void Meatball::Target( const Vec2& targetPos )
{
	// if( Vec2{ target - pos }.GetLengthSq() < vel.GetLengthSq() )
	// if( state == MoveState::Waiting )
	{
		// ++moveTimer;
		// if( moveTimer > waitTime )
		if( canRetarget )
		{
			// moveTimer = 0;
			target = targetPos;
			vel = target - pos;
		}
	}
}

void Meatball::Hurt( int damage )
{
	hp -= damage;
	state = MoveState::Hurting;
}

bool Meatball::IsAlive() const
{
	return hp > 0;
}
