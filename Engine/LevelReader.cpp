#include "LevelReader.h"

#include <fstream>
#include <string>
#include <cassert>

void LevelReader::ReadLevelIntoArrays( const int nLevel,std::vector<Table>& tables,
	std::vector<HotDog>& hotDogs,
	std::vector<Meatball>& meatballs )
{
	std::ifstream in( "Levels/Level" + std::to_string( nLevel ) + ".lvl" );
	assert( in.good() );
	
	// Line 1 of file is x width, line 2 is y height, rest are actual level.
	std::string xSize;
	std::string ySize;
	std::getline( in,xSize );
	std::getline( in,ySize );
	for( int y = 0; y < std::stoi( ySize ); ++y )
	{
		for( int x = 0; x < std::stoi( xSize ); ++x )
		{
			const char nextChar = in.get();
			if( nextChar == 'T' )
			{
				tables.emplace_back( Table{ { x,y } } );
			}
			else if( nextChar == 'H' )
			{
				hotDogs.emplace_back( HotDog{ { x,y } } );
			}
			else if( nextChar == 'M' )
			{
				meatballs.emplace_back( Meatball{ { x,y } } );
			}
		}
	}
}
