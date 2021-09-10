#ifndef POWERUP_HPP
#define POWERUP_HPP

#include "Chora.hpp"
#include "Player.hpp"

#include <string>

class Player;

class PowerUp: public Entity
{

	public:
		PowerUp ( std::string name, Player * player );

		virtual void fire (  );

	std::string getPlayerName ();

	protected:
		Player * player;
	private:
		std::string playerName;
};

class TanookiSuit: public PowerUp
{
	public:
		enum SuitState
		{
			NORMAL,
			TURN_AROUND,
		};

	public:
		TanookiSuit ( Player * player );

		bool receive ( Entity * sender, std::string mesg );

		void updatePosition();

		void fire ();

		int update ();

	private:
		Vect relativePos;//posição do rabo
};


#endif
