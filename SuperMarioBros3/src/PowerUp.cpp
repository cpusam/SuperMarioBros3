#include "PowerUp.hpp"


PowerUp::PowerUp ( std::string name, Player * player )
{
	this->playerName = player->getName();
	setName(name);
	setGroup("powerup");

	this->player = player;
  if (!this->player)
    throw Exception("PowerUp::Não foi definido corretamente player");
}

void PowerUp::fire (  )
{
}

std::string PowerUp::getPlayerName ()
{
  return playerName;
}

TanookiSuit::TanookiSuit ( Player * player ): PowerUp("tanooki", player)
{
	set_state(SuitState::NORMAL);
	dim = (SDL_Rect){0,0,32,32};
}

bool TanookiSuit::receive ( Entity * sender, std::string mesg )
{
	if (sender == player && mesg == "changeDir")
	{
		updatePosition();
	}

	return false;
}

void TanookiSuit::updatePosition()
{
	SDL_Rect rect = player->getCollRect();
	this->changeDir(player->getDir());

	if (player->getDir() == Direction::RIGHT_DIR)
	{
		relativePos.x = rect.x;
	}
	else if (player->getDir() == Direction::LEFT_DIR)
	{
		relativePos.x = rect.x + rect.w;
	}


	relativePos.y = rect.h - dim.h;
	pos += relativePos;//muda a posição do sprite
}

void TanookiSuit::fire ()
{
	if (player->get_state() != Player::WALK || player->get_state() != Player::IDLE ||
      player->get_state() != Player::JUMP || player->get_state() != Player::FALL)
	{
		if (player->getControlKey("shoot").get_state() == Key::PRESS)
		{
			set_state(SuitState::TURN_AROUND);

		}
	}
}

int TanookiSuit::update ()
{
	switch (get_state())
	{
		case SuitState::NORMAL:
		case SuitState::TURN_AROUND:
			updatePosition();

			break;
	}

	return get_state();
}
