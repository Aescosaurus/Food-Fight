/******************************************************************************************
*	Chili DirectX Framework Version 16.07.20											  *
*	Game.cpp																			  *
*	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
*																						  *
*	This file is part of The Chili DirectX Framework.									  *
*																						  *
*	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
*	it under the terms of the GNU General Public License as published by				  *
*	the Free Software Foundation, either version 3 of the License, or					  *
*	(at your option) any later version.													  *
*																						  *
*	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
*	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
*	GNU General Public License for more details.										  *
*																						  *
*	You should have received a copy of the GNU General Public License					  *
*	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	p( { Graphics::ScreenWidth / 2,Graphics::ScreenHeight / 2 } )
{
	hotDogs.emplace_back( HotDog() );
	tables.emplace_back( Table( { 400.0f,400.0f } ) );
}

void Game::Go()
{
	gfx.BeginFrame();
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	const float dt = ft.Mark();

	p.Update( wnd.kbd,wnd.mouse,dt );
	for( Table& t : tables )
	{
		if( t.GetRect().IsOverlappingWith( p.GetRect() ) )
		{
			p.MoveBack();
		}
	}

	if( wnd.mouse.LeftIsPressed() && p.Fire() )
	{
		bullets.emplace_back( Bullet( p.GetPos() + Player::GetSize() / 2 - Bullet::GetSize() / 2,
			{ float( wnd.mouse.GetPosX() ),float( wnd.mouse.GetPosY() ) } ) );
	}

	for( int i = 0; i < bullets.size(); ++i )
	{
		Bullet& b = bullets[i];
		b.Update( dt );

		for( const Table& t : tables )
		{
			if( t.GetRect().IsOverlappingWith( b.GetRect() ) )
			{
				b.Kill();
			}
		}

		if( !b )
		{
			bullets.erase( bullets.begin() + i );
		}
	}

	for( int i = 0; i < hotDogs.size(); ++i )
	{
		HotDog& hd = hotDogs[i];
		hd.Update( dt,rng );

		hd.Target( p.GetPos() );

		for( Bullet& b : bullets )
		{
			if( hd.GetRect().IsOverlappingWith( b.GetRect() ) )
			{
				b.Kill();
				hd.Hurt( 1 );
			}
		}

		for( Table& t : tables )
		{
			// int nextTarget = 0;
			// do
			// {
			// 	hd.Target( t.GetTarget( nextTarget ) );
			// }
			// while( !t.GetRect().Covers( hd.GetPos(),hd.GetTarget(),Graphics::GetScreenRect() ) &&
			// 	nextTarget <= t.CountTargets() );

			// for( int i = 0; i < t.CountTargets(); ++i )
			// {
			// 	if( t.GetRect().Covers( hd.GetPos(),hd.GetTarget(),Graphics::GetScreenRect() ) )
			// 	{
			// 		hd.Target( t.GetTarget( i ) );
			// 	}
			// }

			// if( t.GetRect().Covers( hd.GetPos(),hd.GetTarget(),Graphics::GetScreenRect() ) )
			// {
			// 	float distFromPlayer = 0.0f;
			// 	int closest = 0;
			// 	for( int i = 0; i < t.CountTargets(); ++i )
			// 	{
			// 		const Vec2 diff = { p.GetPos() - t.GetTarget( i ) };
			// 		if( diff.GetLengthSq() > distFromPlayer )
			// 		{
			// 			distFromPlayer = diff.GetLengthSq();
			// 			closest = i;
			// 		}
			// 	}
			// 
			// 	hd.Target( t.GetTarget( i ) );
			// }

			// TODO: Find closest targetable table corner and go to it.
			// int nTarget = 0;
			// hd.Target( p.GetPos() );
			// while( t.GetRect().Covers( hd.GetPos(),p.GetPos(),Graphics::GetScreenRect() ) )
			// {
			// 	++nTarget;
			// 	hd.Target( t.GetClosestTarget( p.GetPos(),nTarget ) );
			// }

			if( t && t.GetRect().IsOverlappingWith( hd.GetRect() ) )
			{
				t.Break();
				hd.MoveAwayFrom( t.GetPos() );
			}
		}

		if( !hd )
		{
			hotDogs.erase( hotDogs.begin() + i );
		}
	}
}

bool Game::TestLine( const Vec2& pos1,const Vec2& pos2 )
{
	const Vec2 delta = Vec2( pos2 - pos1 ).Normalize();
	Vec2 curPos = pos1;
	while( Graphics::GetScreenRect().Contains( curPos ) )
	{
		curPos += delta;
		gfx.PutPixelSafe( int( curPos.x ),int( curPos.y ),Colors::Red );

		if( curPos.x > pos2.x && curPos.y > pos2.y )
		{
			return false;
		}
		if( tables[0].GetRect().Contains( curPos ) )
		{
			return true;
		}
	}

	return false;
}

void Game::ComposeFrame()
{
	// gfx.DrawRect( 0,0,Graphics::ScreenWidth,Graphics::ScreenHeight,Colors::Cyan );

	for( const Table& t : tables )
	{
		t.Draw( gfx );
	}

	for( const HotDog& hd : hotDogs )
	{
		hd.Draw( gfx );
		gfx.DrawLine( int( hd.GetPos().x ),int( hd.GetPos().y ),int( hd.GetTarget().x ),int( hd.GetTarget().y ),Colors::Cyan );
	}

	p.Draw( gfx );

	for( const Bullet& b : bullets )
	{
		b.Draw( gfx );
	}
}