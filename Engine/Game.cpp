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
	tables.emplace_back( Table( { float( rng.NextInt( 0,400 ) ),float( rng.NextInt( 0,400 ) ) } ) );
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

	if( wnd.mouse.LeftIsPressed() && p.Fire() )
	{
		bullets.emplace_back( Bullet( p.GetPos(),{ float( wnd.mouse.GetPosX() ),float( wnd.mouse.GetPosY() ) } ) );
	}

	for( int i = 0; i < bullets.size(); ++i )
	{
		Bullet& b = bullets[i];
		b.Update( dt );
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

		if( !hd )
		{
			hotDogs.erase( hotDogs.begin() + i );
		}
	}
}

void Game::ComposeFrame()
{
	// gfx.DrawRect( 0,0,Graphics::ScreenWidth,Graphics::ScreenHeight,Colors::Cyan );
	for( const HotDog& hd : hotDogs )
	{
		hd.Draw( gfx );
	}

	for( const Table& t : tables )
	{
		t.Draw( gfx );
	}

	p.Draw( gfx );

	for( const Bullet& b : bullets )
	{
		b.Draw( gfx );
	}
}