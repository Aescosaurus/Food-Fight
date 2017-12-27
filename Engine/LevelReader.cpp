#include "LevelReader.h"

#include <fstream>
#include <string>
#include <cassert>

void LevelReader::ReadLevelIntoArrays( const int nLevel,
	Player& p,
	std::vector<Table>& tables,
	std::vector<HotDog>& hotDogs,
	std::vector<Meatball>& meatballs,
	std::vector<Door>& doors )
{
	std::ifstream in( "Levels/Level" + std::to_string( nLevel ) + ".lvl" );
	assert( in.good() );

	// Line 1 of file is x width, line 2 is y height, line 3 is tile size,
	//  rest are actual level.
	std::string xSize;
	std::string ySize;
	std::string tileSize;
	std::getline( in,xSize );
	std::getline( in,ySize );
	std::getline( in,tileSize );

	const int xs = std::stoi( xSize );
	const int ys = std::stoi( ySize );
	const int ts = std::stoi( tileSize );

	for( int y = 0; y < ys; ++y )
	{
		for( int x = 0; x < xs; ++x )
		{
			const char nextChar = in.get();
			if( nextChar == '\n' )
			{ // Corrects for my mistake of not using std::ios::binary.
				--x;
			}
			else if( nextChar == 'T' )
			{
				tables.emplace_back( Table{ { float( x * ts ),float( y * ts ) } } );
			}
			else if( nextChar == 'H' )
			{
				hotDogs.emplace_back( HotDog{ { float( x * ts ),float( y * ts ) } } );
			}
			else if( nextChar == 'M' )
			{
				meatballs.emplace_back( Meatball{ { float( x * ts ),float( y * ts ) } } );
			}
			else if( nextChar == 'D' )
			{
				doors.emplace_back( Door{ { float( x * ts ),float( y * ts ) } } );
			}
			else if( nextChar == 'P' )
			{
				p.Goto( { float( x * ts ),float( y * ts ) } );
			}
		}
	}

	in.close();
}
