#pragma once

#include "Vec2.h"
#include "Rect.h"

class Foods
{
public:
	class Cabbage
	{
	public:
		Cabbage();
		Cabbage( const Vec2& pos );
		Cabbage( class Random& rng );

		void Update( float dt );
		void Draw( class Graphics& gfx ) const;

		void SetDir( const Vec2& target );

		const Vec2& GetPos() const;
		const Rect& GetRect() const;
	private:
		static constexpr float speed = 50.0f;
		const Vec2 size;
		Vec2 pos;
		Vec2 vel;
		Rect hitbox;
	};
public:
private:
};