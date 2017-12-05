#pragma once

class Vec2
{
public:
	Vec2() = default;
	Vec2( float x_in,float y_in );

	Vec2 operator+( const Vec2& rhs ) const;
	Vec2& operator+=( const Vec2& rhs );
	Vec2 operator*( float rhs ) const;
	Vec2& operator*=( float rhs );
	Vec2 operator-( const Vec2& rhs ) const;
	Vec2& operator-=( const Vec2& rhs );
	bool operator==( const Vec2& rhs ) const;
	bool operator!=( const Vec2& rhs ) const;
	Vec2& operator-();

	float GetLength() const;
	float GetLengthSq() const;
	static float FindDistSq( const Vec2& vec1,const Vec2& vec2 );

	Vec2& Normalize();
	Vec2 GetNormalized() const;
public:
	float x;
	float y;
};