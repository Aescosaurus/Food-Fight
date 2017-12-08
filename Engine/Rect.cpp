#include "Rect.h"
#include <cmath>

Rect::Rect( float left_in,float right_in,float top_in,float bottom_in )
	:
	left( left_in ),
	right( right_in ),
	top( top_in ),
	bottom( bottom_in )
{
}

Rect::Rect( const Vec2& topLeft,const Vec2 & bottomRight )
	:
	Rect( topLeft.x,bottomRight.x,topLeft.y,bottomRight.y )
{
}

Rect::Rect( const Vec2& topLeft,float width,float height )
	:
	Rect( topLeft,topLeft + Vec2( width,height ) )
{
}

bool Rect::IsOverlappingWith( const Rect& other ) const
{
	return right > other.left && left < other.right
		&& bottom > other.top && top < other.bottom;
}

bool Rect::Covers( const Vec2& pos1,const Vec2& pos2,const Rect& scrRect ) const
{
	const Vec2 delta = pos2 - pos1;
	if( delta.x == 0.0f || delta.y == 0.0f )
	{
		return false;
	}
	Vec2 testPoint = pos1;
	while( scrRect.Contains( testPoint ) )
	{
		testPoint += delta;
		if( this->Contains( delta ) )
		{
			return true;
		}
	}

	return false;
}

bool Rect::IsContainedBy( const Rect& other ) const
{
	return left >= other.left && right <= other.right &&
		top >= other.top && bottom <= other.bottom;
}

bool Rect::Contains( const Vec2& point ) const
{
	return( point.x > left && point.x < right &&
		point.y > top && point.y < bottom );
}

Rect Rect::FromCenter( const Vec2 & center,float halfWidth,float halfHeight )
{
	const Vec2 half( halfWidth,halfHeight );
	return Rect( center - half,center + half );
}

void Rect::MoveBy( const Vec2& amount )
{
	left += amount.x;
	right += amount.x;
	top += amount.y;
	bottom += amount.y;
}

void Rect::MoveTo( const Vec2& pos )
{
	right += pos.x - left;
	bottom += pos.y - top;
	left = pos.x;
	top = pos.y;
}

Rect Rect::GetExpanded( float offset ) const
{
	return Rect( left - offset,right + offset,top - offset,bottom + offset );
}

Vec2 Rect::GetCenter() const
{
	return Vec2( ( left + right ) / 2.0f,( top + bottom ) / 2.0f );
}

float Rect::GetWidth() const
{
	return right - left;
}

float Rect::GetHeight() const
{
	return bottom - top;
}
