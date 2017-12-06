#pragma once

#include "Vec2.h"

class Rect
{
public:
	Rect() = default;
	Rect( float left_in,float right_in,float top_in,float bottom_in );
	Rect( const Vec2& topLeft,const Vec2& bottomRight );
	Rect( const Vec2& topLeft,float width,float height );
	bool IsOverlappingWith( const Rect& other ) const;
	bool IsContainedBy( const Rect& other ) const;
	static Rect FromCenter( const Vec2& center,float halfWidth,float halfHeight );
	void MoveBy( const Vec2& amount );
	void MoveTo( const Vec2& pos );
	Rect GetExpanded( float offset ) const;
	Vec2 GetCenter() const;
	float GetWidth() const;
	float GetHeight() const;
public:
	float left;
	float right;
	float top;
	float bottom;
};