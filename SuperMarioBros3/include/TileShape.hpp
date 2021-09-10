#ifndef TILESHAPE_H
#define TILESHAPE_H

#include "Chora.hpp"
#include <vector>
#include <string>


class TileShape: class StateMachine
{
	public:
		std::string getType (  );
		virtual bool isSolid ( int x, int y );
	
	protected:
		void setType ( std::string type );
		
	private:
	std::string type;
	std::vector <int> tile;
};

#endif
