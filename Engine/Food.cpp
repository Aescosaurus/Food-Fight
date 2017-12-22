#include "Food.h"
#include "Random.h"
#include "Graphics.h"
#include <cassert>
#include "Table.h"

const Surface HotDog::spr = Surface( "Images/HotDog.bmp" );
const Surface Meatball::spr = Surface{ "Images/Meatball.bmp" };

Food::Food()
	:
	pos( 0.0f,0.0f )
{
}

Food::Food( const Vec2& pos )
	:
	Food()
{
	this->pos = pos;
}

void Food::Update( float dt )
{
	hitbox.MoveTo( pos );
}

void Food::Draw( Graphics& gfx ) const
{
	gfx.DrawRect( int( pos.x ),int( pos.y ),50,50,Colors::Magenta );
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
	Food( { 0.0f,0.0f } )
{
	target = { 0.0f,0.0f };
	hitbox = spr.GetRect();
	hitbox.MoveTo( pos );
}

HotDog::HotDog( const Vec2& startPos )
	:
	Food( startPos )
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

void HotDog::CheckBulletCollision( Bullet& b )
{
	if( hitbox.IsOverlappingWith( b.GetRect() ) )
	{
		Hurt( 1 );
		b.Kill();
	}
}

void HotDog::CheckTableCollision( Table& t )
{
	if( hitbox.IsOverlappingWith( t.GetRect() ) )
	{
		t.Hurt( 1.0f );
		BounceOffOf( t.GetPos() );
	}
}

void HotDog::CheckPlayerCollision( Player& p )
{
	if( hitbox.IsOverlappingWith( p.GetRect() ) )
	{
		p.Hurt( 1 );
		Hurt( 1 );
		BounceOffOf( p.GetPos() );
	}
}

HotDog::operator bool() const
{
	return hp > 0;
}

Meatball::Meatball( const Vec2& pos )
	:
	Food( pos ),
	target( pos ),
	vel( speed,speed )
{
	hitbox = spr.GetRect();
	hitbox.MoveTo( pos );
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
		state = MoveState::Moving;
	}

	const Vec2 lastMoveAmount = vel.GetNormalized() * speed * dt;
	pos += lastMoveAmount;
	hitbox.MoveTo( pos );

	if( hitbox.GetExpanded( 1.5f ).IsContainedBy( Graphics::GetScreenRect() ) )
	{
		canRetarget = false;
	}
	else
	{
		canRetarget = true;
		pos -= lastMoveAmount * 1.5f;
		vel = -vel;
	}

	Food::Update( dt );
}

void Meatball::Draw( Graphics& gfx ) const
{
	assert( hitbox.IsContainedBy( Graphics::GetScreenRect() ) );

	if( state == MoveState::Hurting )
	{
		gfx.DrawSprite( int( pos.x ),int( pos.y ),spr,Colors::White,Colors::Magenta,( vel.x < 0.0f ) );
	}
	else
	{
		gfx.DrawSprite( int( pos.x ),int( pos.y ),spr,Colors::Magenta,( vel.x < 0.0f ) );
	}

	gfx.DrawHitbox( hitbox,Colors::MakeRGB( 255,160,0 ),true );
	gfx.DrawLine( int( pos.x ),int( pos.y ),int( target.x ),int( target.y ),Colors::Cyan );
}

void Meatball::Target( const Vec2& targetPos )
{
	if( canRetarget )
	{
		target = targetPos;
		vel = target - pos;
	}
}

void Meatball::Hurt( int damage )
{
	hp -= damage;
	state = MoveState::Hurting;
}

void Meatball::CheckBulletCollision( Bullet& b )
{
	if( hitbox.IsOverlappingWith( b.GetRect() ) )
	{
		Hurt( 1 );
		b.Kill();
	}
}

Meatball::operator bool() const
{
	return( hp > 0 );
}
