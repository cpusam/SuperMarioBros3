#include "Player.hpp"
#include <math.h>


PlayerConfig::PlayerConfig (  )
{
	setEnviroment("earth");
}

void PlayerConfig::setEnviroment ( std::string env )
{
	//se é para mudar para ambiente aquático
	if (env == "aquatic")
	{

		return;
	}

	//default
	shootPos["fireflowerLeft"] = Vect(0,0);
	shootPos["fireflowerRight"] = Vect(15,0);

	maxVel.set(3,6);
	minVel.set(0.2,1);
	acc.set(0.05,0.1);
	accJump.set(2,0.1);

	velAdj.set(2,1);

	damp.set(0.95,0.85);

	slide = 0.70;
	gravity = 0.2;
	velOnWall.set(1.2,0);
	velStartJump = -4.5;
	velStartRunJump = -6;
	velStartJumpWall = velStartJump*0.80;

	treeTiles.push_back('t');
	accTree.set(1,1);

	velAnim = 100;
	velMult = 15;
	velAnimDefault["smallmanWalk"] = 100;
}

Player::Player ( SDL_Renderer * renderer, TileMap * level, std::string playerName )
{
	Animation aux;

	dim = (SDL_Rect){0,0,16,16};

	texture = Texturer::add(renderer, "images/Playable/4230.png", (SDL_Color){0,255,255});

	//abaixo são as configs do mario pequeno (com roupa vermelho)
	//idle
	aux.add_frame(texture, (SDL_Rect){252,8,16,16}, dim, 100);//parado
	anim["smallmanIdle"] = aux;
	aux.clear_frames();

	//walk
	aux.add_frame(texture, (SDL_Rect){268,8,16,16}, dim, 100);//andando
	aux.add_frame(texture, (SDL_Rect){252,8,16,16}, dim, 100);//parado
	anim["smallmanWalk"] = aux;
	aux.clear_frames();

	//inverse
	aux.add_frame(texture, (SDL_Rect){286,8,16,16}, dim, 100);//slide
	anim["smallmanInverse"] = aux;
	aux.clear_frames();

	//jump
	aux.add_frame(texture, (SDL_Rect){304,8,16,16}, dim, 100);
	anim["smallmanJump"] = aux;
	aux.clear_frames();

	//fall - o mesmo que jump
	aux.add_frame(texture, (SDL_Rect){304,8,16,16}, dim, 100);
	anim["smallmanFall"] = aux;
	aux.clear_frames();

	//run - fast walk
	aux.add_frame(texture, (SDL_Rect){323,8,16,16}, dim, 80);//primeiro
	aux.add_frame(texture, (SDL_Rect){341,8,16,16}, dim, 80);//segundo
	anim["smallmanRun"] = aux;
	aux.clear_frames();

	//jump- run jump
	aux.add_frame(texture, (SDL_Rect){360,8,16,16}, dim, 100);
	anim["smallmanRunJump"] = aux;
	aux.clear_frames();

	// fall - run fall
	aux.add_frame(texture, (SDL_Rect){360,8,16,16}, dim, 100);
	anim["smallmanRunFall"] = aux;
	aux.clear_frames();

	//slide - slide down
	aux.add_frame(texture, (SDL_Rect){379,8,16,16}, dim, 100);
	anim["smallmanSlideDown"] = aux;
	aux.clear_frames();

	//enter pipe
	aux.add_frame(texture, (SDL_Rect){397,8,16,16}, dim, 100);
	anim["smallmanEnterPipe"] = aux;
	aux.clear_frames();

	//die
	aux.add_frame(texture, (SDL_Rect){416,8,16,16}, dim, 100);
	anim["smallmanDie"] = aux;
	aux.clear_frames();

	//idle hold shell
	aux.add_frame(texture, (SDL_Rect){434,8,16,16}, dim, 100);
	anim["smallmanIdleHoldShell"] = aux;
	aux.clear_frames();

	aux.add_frame(texture, (SDL_Rect){434,8,16,16}, dim, 100);//primeiro
	aux.add_frame(texture, (SDL_Rect){452,8,16,16}, dim, 100);//segundo
	anim["smallmanWalkHoldShell"] = aux;
	aux.clear_frames();

	//kick shell
	aux.add_frame(texture, (SDL_Rect){470,8,16,16}, dim, 200);
	anim["smallmanKickShell"] = aux;
	aux.clear_frames();

	//swim hold shell
	aux.add_frame(texture, (SDL_Rect){489,8,16,16}, dim, 100);
	aux.add_frame(texture, (SDL_Rect){508,9,16,16}, dim, 100);
	anim["smallmanSwimHoldShell"] = aux;
	aux.clear_frames();

	//swim idle
	aux.add_frame(texture, (SDL_Rect){508,8,16,16}, dim, 100);
	aux.add_frame(texture, (SDL_Rect){526,8,16,16}, dim, 100);
	anim["smallmanIdleSwim"] = aux;
	aux.clear_frames();


	aux.add_frame(texture, (SDL_Rect){508,8,16,16}, dim, 100);//normal
	aux.add_frame(texture, (SDL_Rect){526,8,16,16}, dim, 100);//pega impulso
	aux.add_frame(texture, (SDL_Rect){543,8,16,16}, dim, 100);//impulso
	anim["smallmanWalkSwim"] = aux;
	aux.clear_frames();

	//idle/up/down ladder
	aux.add_frame(texture, (SDL_Rect){560,8,16,16}, dim, 100);
	aux.add_frame(texture, (SDL_Rect){577,8,16,16}, dim, 100);
	anim["smallmanMoveLadder"] = aux;
	aux.clear_frames();

	//up/down ladder
	aux.add_frame(texture, (SDL_Rect){560,8,16,16}, dim, 100);
	aux.add_frame(texture, (SDL_Rect){576,8,16,16}, dim, 100);
	anim["smallmanMoveLadder"] = aux;
	aux.clear_frames();

	//idle Ladder
	aux.add_frame(texture, (SDL_Rect){576,8,16,16}, dim, 100);
	//aux.add_frame(texture, (SDL_Rect){640,44,16,31}, dim, 100);
	anim["smallmanIdleLadder"] = aux;
	aux.clear_frames();
/////////////////////////////////////////////////////////////////////////////////
	dim = (SDL_Rect){0,0,16,32};
	///Com powerup cogumelo
	//idle
	aux.add_frame(texture, (SDL_Rect){196,43,16,32}, dim, 100);
	anim["tallmanIdle"] = aux;
	aux.clear_frames();
	//walk
	aux.add_frame(texture, (SDL_Rect){196,43,16,32}, dim, 100);//o mesmo que idle
	dim = (SDL_Rect){0,1,16,31};
	aux.add_frame(texture, (SDL_Rect){214,44,16,31}, dim, 100);
	aux.add_frame(texture, (SDL_Rect){233,44,16,31}, dim, 100);
	anim["tallmanWalk"] = aux;
	aux.clear_frames();

	//inverse
	aux.add_frame(texture, (SDL_Rect){252,44,16,31}, dim, 100);
	anim["tallmanInverse"] = aux;
	aux.clear_frames();
	//jump
	aux.add_frame(texture, (SDL_Rect){271,44,16,31}, dim, 100);
	anim["tallmanJump"] = aux;
	aux.clear_frames();
	//fall o mesmo que jump
	aux.add_frame(texture, (SDL_Rect){271,44,16,31}, dim, 100);
	anim["tallmanFall"] = aux;
	aux.clear_frames();

	//run - TODO:precisa testar essa animação
	dim.w = 19;
	dim.h = 31;
	aux.add_frame(texture, (SDL_Rect){290,44,19,31}, dim, 100);
	aux.add_frame(texture, (SDL_Rect){312,44,19,31}, dim, 100);
	aux.add_frame(texture, (SDL_Rect){335,44,19,31}, dim, 100);
	anim["tallmanRun"] = aux;
	aux.clear_frames();

	//run jump
	aux.add_frame(texture, (SDL_Rect){357,44,19,31}, dim, 100);
	anim["tallmanRunJump"] = aux;
	aux.clear_frames();
	//lower
	dim.w = 16;
	dim.h = 31;
	aux.add_frame(texture, (SDL_Rect){378,44,16,31}, dim, 100);
	anim["tallmanLower"] = aux;
	aux.clear_frames();
	dim.w = 16;
	dim.h = 31;
	//slide
	aux.add_frame(texture, (SDL_Rect){396,44,16,31}, dim, 100);
	anim["tallmanSlide"] = aux;
	aux.clear_frames();

	//enter pipe
	aux.add_frame(texture, (SDL_Rect){415,44,16,31}, dim, 100);
	anim["tallmanEnterPipe"] = aux;
	aux.clear_frames();

	//turn around hold shell
	aux.add_frame(texture, (SDL_Rect){415,44,16,31}, dim, 100);
	anim["tallmanTurnHoldShell"] = aux;
	aux.clear_frames();

	//idle hold shell
	aux.add_frame(texture, (SDL_Rect){433,44,16,31}, dim, 100);
	anim["tallmanIdleHoldShell"] = aux;
	aux.clear_frames();

	//run hold shell
	aux.add_frame(texture, (SDL_Rect){433,44,16,31}, dim, 100);
	aux.add_frame(texture, (SDL_Rect){450,44,16,31}, dim, 100);
	aux.add_frame(texture, (SDL_Rect){469,44,16,31}, dim, 100);
	anim["tallmanRunHoldShell"] = aux;
	aux.clear_frames();
	//jump hold shell
	aux.add_frame(texture, (SDL_Rect){450,44,16,31}, dim, 100);
	anim["tallmanJumpHoldShell"] = aux;
	aux.clear_frames();

	//kick shell
	dim.w = 21;
	dim.h = 31;
	aux.add_frame(texture, (SDL_Rect){488,44,21,31}, dim, 200);
	anim["tallmanKickShell"] = aux;
	aux.clear_frames();

	//idle swim
	dim.w = 19;
	dim.h = 31;
	aux.add_frame(texture, (SDL_Rect){512,44,19,31}, dim, 200);
	aux.add_frame(texture, (SDL_Rect){534,44,19,31}, dim, 200);
	anim["tallmanIdleSwim"] = aux;
	aux.clear_frames();
	//swim
	aux.add_frame(texture, (SDL_Rect){556,44,19,31}, dim, 80);
	aux.add_frame(texture, (SDL_Rect){578,44,19,31}, dim, 80);
	aux.add_frame(texture, (SDL_Rect){599,44,19,31}, dim, 80);
	anim["tallmanSwim"] = aux;
	aux.clear_frames();
	//up/down ladder
	dim.w = 16;
	dim.h = 31;
	aux.add_frame(texture, (SDL_Rect){621,44,16,31}, dim, 100);
	aux.add_frame(texture, (SDL_Rect){640,44,16,31}, dim, 100);
	anim["tallmanMoveLadder"] = aux;
	aux.clear_frames();

	//idle Ladder
	dim.w = 16;
	dim.h = 31;
	aux.add_frame(texture, (SDL_Rect){621,44,16,31}, dim, 100);
	//aux.add_frame(texture, (SDL_Rect){640,44,16,31}, dim, 100);
	anim["tallmanIdleLadder"] = aux;
	aux.clear_frames();
	/*
	aux.add_frame(texture, (SDL_Rect){}, dim, 100);
	anim[""] = aux;
	aux.clear_frames();
	*/
	//addSolid('a');
	addOneWayUp('a');
	setDir(Direction::RIGHT_DIR);
	show(true);
	setName(playerName);
	setGroup("player");

	this->powerup= nullptr;
	this->level = level;

	right = left = false;
	down = up = false;
	shoot = false;
	jump = false;
	holdJump = false;



	setLevel(level);
	//addPowerUp(new TanookiSuit(this));
	//addPowerUp(new PowerUp("mushroom", this));
	size = PlayerSize::TALL;
	collRect.x = -1;
	collRect.y = -1;

	//updateCollRect();
	set_state(PlayerState::IDLE);
	changeAnim("idle");

	controls.insert(std::pair<std::string,Key>("right", Key(SDLK_RIGHT)));
	controls.insert(std::pair<std::string,Key>("left", Key(SDLK_LEFT)));
	controls.insert(std::pair<std::string,Key>("down", Key(SDLK_DOWN)));
	controls.insert(std::pair<std::string,Key>("up", Key(SDLK_UP)));
	controls.insert(std::pair<std::string,Key>("jump", Key(SDLK_x)));
	controls.insert(std::pair<std::string,Key>("shoot", Key(SDLK_c)));
	controls.insert(std::pair<std::string,Key>("grow", Key(SDLK_SPACE)));
}


bool Player::receive ( Entity * sender, std::string mesg )
{
	return false;
}

void Player::changeSize() {

	if (size == PlayerSize::SMALL) {
		addPowerUp(new PowerUp("mushroom", this));
		size = PlayerSize::TALL;
		pos.y = pos.y - collRect.h - 3;
	}
	else {
		pos.y = pos.y - collRect.h - 3;
		addPowerUp(nullptr);
		size = PlayerSize::SMALL;
	}
}

void Player::addPowerUp(PowerUp * p)
{
	if (powerup)
	{
		Elements::remove(powerup->getId());
		delete powerup;
	}

	powerup = p;
	updateCollRect();
}

//atualiza retanmgulos de colisão
void Player::updateCollRect (  )
{
	if (powerup)
	{
		if (powerup->getName() == "mushroom")
		{
			if (vel.x == -config.maxVel.x || vel.x == config.maxVel.x)
			{
				collRect.w = 16;
				collRect.x = 0;
			}
			else
			{
				collRect.w = 8;
				collRect.x = 8/2;
			}
			collRect.h = 24;

			if ((isGround() || get_state() == PlayerState::JUMP || get_state() == PlayerState::FALL) && down)
			{
				collRect.h = 14;
			}
			collRect.y = 32 - collRect.h - 1;
		}
	}
	else
	{
		collRect.x = 4/2;
		collRect.w = 12;
		collRect.h= 16;
		collRect.y = -1;
	}

	setSides(collRect, collPoints);
}

//verifica se em cima é sólido
bool Player::isTopSolid (  )
{
	for (auto & p: upSide)
		if (isSolid(p))
			return true;

	return false;
}

bool Player::isMiddleTopSolid (  )
{
	Vect p = upSide.at(int(upSide.size()/2));
	p.y -= 1;
	return isSolid(p);
}

bool Player::isTree (  )
{
	SDL_Rect rect = getCollRect();
	for (auto tile: config.treeTiles)
	{
		if (tile == level->get_tile(rect.x + rect.w/2, rect.y + rect.h/2))
			return true;
	}

	return false;
}

void Player::catchTree (  )
{
	if (isTree() == false)
		return;

	SDL_Rect rect = getCollRect();
	Vect center = Vect(rect.x + rect.w/2, rect.y + rect.w/2);

	Vect pos = Vect((center.x/level->get_tilesize())*level->get_tilesize(),(center.y/level->get_tilesize())*level->get_tilesize());

	pos -= center;

	set_pos(get_pos() + pos);
}

void Player::reset (  )
{

}

bool Player::touchPowerUp (  )
{
	return false;
}
// se foi atingido por algum inimigo do grupo objGroup
bool Player::wasHitBy ( std::string objGroup )
{
	return false;
}

bool Player::inLadder (  )
{
	return false;
}

void Player::catchLadder (  )
{
}

Key Player::getControlKey ( std::string keyName )
{
	return controls[keyName];
}


// controles - interface

void Player::doShoot (  )
{
	if (powerup)
	{
		shoot = (powerup->getName() == "fireflower" || powerup->getName() == "hammer");
	}
}

void Player::doJump (  )
{
	jump = get_state() == PlayerState::IDLE || get_state() == PlayerState::WALK || get_state() == PlayerState::RUN || get_state() == PlayerState::LOWER || get_state() == PlayerState::UP_LADDER || get_state() == PlayerState::IDLE_LADDER || get_state() == PlayerState::IDLE_TREE || get_state() == PlayerState::MOVE_TREE;
}

void Player::changeDir ( Direction d )
{
	Entity::changeDir(d);
}



void Player::updateControls (  )
{
	for (auto & key: controls)
		key.second.update();

	right = controls["right"].get_state() == Key::HOLD;
	left = controls["left"].get_state() == Key::HOLD;
	down = controls["down"].get_state() == Key::HOLD;
	up = controls["up"].get_state() == Key::PRESS;

	if (controls["jump"].get_state() == Key::PRESS)
		doJump();
	else
		jump = false;

	if (controls["shoot"].get_state() == Key::PRESS)
		doShoot();
	else
		shoot = false;


	if (down == false && get_state() == PlayerState::IDLE)
	{
		if (controls["left"].get_state() == Key::HOLD)
		{
			left = true;
		}

		if (controls["right"].get_state() == Key::HOLD)
		{
			right = true;
		}
	}

	if (down == true && (get_state() == PlayerState::FALL || get_state() == PlayerState::JUMP))
	{
		if (controls["left"].get_state() == Key::HOLD)
		{
			left = true;
		}

		if (controls["right"].get_state() == Key::HOLD)
		{
			right = true;
		}
	}

	if (isTree()) {
		up = controls["up"].get_state() == Key::HOLD || controls["up"].get_state() == Key::PRESS;
	}

	if (controls["grow"].get_state() == Key::PRESS) {
		changeSize();
	}
}

bool Player::collisionHor (  )
{
	SDL_Rect boundary = level->get_dimension();
	SDL_Rect rect = {int(pos.x) + collRect.x, int(pos.y) + collRect.y, 8, collRect.h};

	if (rect.x < boundary.x)
	{
		vel.x = 0;
		pos.x = boundary.x;
		pos.x -= collRect.x + 1;//+1 para evitar tremores
		return true;
	}

	if (rect.x + rect.w > boundary.x + boundary.w)
	{
		vel.x = 0;
		rect.x = boundary.x + boundary.w - (collRect.x + rect.w);
		pos.x  = rect.x - 2;
		return true;
	}

	return Entity::collisionHor();
}

void Player::updateAnim (  )
{
	if (currAnim)
	{
		if (currAnim == &anim[getAnimName("walk")] || currAnim == &anim[getAnimName("run")])
		{

			//int(fabs(vel.x))*config.velMult tem que ser positivo e menor que config.velAnim
			int diff = config.velAnim - int(fabs(vel.x*config.velMult));
			if (diff > 0)
				currAnim->set_frames_delay(diff);
		}

		currAnim->update();
	}
}

void Player::changeAnim ( std::string animName, bool reset )
{
	#ifdef _DEBUG_
	std::cout<<"animName = "<<animName<<std::endl;
	std::cout<<"anim.size  = "<<anim.size()<<std::endl;
	std::cout<<"anim = "<<getAnimName(animName)<<std::endl;
	#endif

	if (anim.size() > 0)
		//if (anim.find(getAnimName(animName)) != anim.end())
			currAnim = &anim[getAnimName(animName)];

	if (reset)
		currAnim->reset();
}

std::string Player::getAnimName ( std::string animName )
{
	std::cout<<"animName getANimName = "<<animName<<std::endl;
	std::string powername = "";
	if (powerup)
		powername = powerup->getName();
std::cout<<"powerup name = "<<powername<<std::endl;
	if (animName == "idle")
	{
			if (powerup)
			{

				if (powername == "mushroom")
					return "tallmanIdle";

				if (powername == "fireflower")
				{
					if (shoot)
						return "firemanShoot";

					return "firemanIdle";
				}

				if (powername == "hammer")
				{
					if (shoot)
						return "hammerShoot";

					return "hammerIdle";
				}
			}

			return "smallmanIdle";
	}

	if (animName == "walk")
	{
			if (powerup)
			{
				if (powername == "mushroom")
					return "tallmanWalk";


				if (powername == "fireflower")
				{
					if (shoot)
						return "firemanShoot";

					return "firemanWalk";
				}

				if (powername == "hammer")
				{
					if (shoot)
						return "hammerShoot";

					return "hammerWalk";
				}
			}

			return "smallmanWalk";
	}

	if (animName == "run")
	{
		if (powerup)
		{
			if (powername == "mushroom" && (vel.x == config.maxVel.x || vel.x == -config.maxVel.x))
				return "tallmanRun";
		}

		return "smallmanRun";
	}

	if (animName == "jump")
	{
		if (powerup)
		{

			if (powername == "mushroom")
			{
				if (vel.x == -config.maxVel.x || vel.x == config.maxVel.x)
					return "tallmanRunJump";

				return "tallmanJump";
			}
		}

		return "smallmanJump";
	}

	if (animName == "inverse")
	{
		if (powerup)
		{

			if (powername == "mushroom")
				return "tallmanInverse";
		}

		return "smallmanInverse";
	}

	if (animName == "lower")
	{
		if (powerup)
		{

			if (powername == "mushroom")
				return "tallmanLower";
		}
		return "smallmanIdle";
	}

	if (animName == "fall")
	{
		if (powerup)
		{

			if (powername == "mushroom")
			{
				if (down)
					return "tallmanLower";
				else
					return "tallmanFall";
			}
		}

		return "smallmanFall";
	}

	if (animName == "moveTree")
	{
		if (powerup)
		{

			if (powername == "mushroom")
			{
				return "tallmanMoveLadder";
			}
		}

		return "smallmanMoveLadder";
	}

	if (animName == "idleTree")
	{
		if (powerup)
		{

			if (powername == "mushroom")
			{
				return "tallmanIdleLadder";
			}
		}

		return "smallmanIdleLadder";
	}

	if (animName == "wallJump")
	{
		if (powerup)
		{
			if (powername == "mushroom")
			{
				return "tallmanJump";
			}
		}
		return "smallmanIdleLadder";
	}

	std::cout<<"Erro ao pegar nova animação, pegando smallmanIdle\n";
	return "smallmanIdle";//padrão
}



void Player::input ( SDL_Event & event )
{
	for (auto & key: controls)
		key.second.input(event);
}

void Player::draw ( SDL_Renderer * renderer, Camera * camera )
{
	if (currAnim)
	{
		currAnim->draw(renderer, camera, round(pos.x), round(pos.y));
		//#ifdef _DEBUG_
		//drawSides(renderer, camera);
		//#endif
		//SDL_Rect rect = getCollRect();
		//SDL_Rect d = {rect.x + (rect.w-5)/2, rect.y + (rect.h-5)/2,5,5};

	}
}

int Player::update (  )
{
	if (powerup)
		powerup->update();

	updateControls();

	//printf("State = %d\n", get_state());
	switch (get_state())
	{
		case PlayerState::IDLE:
			if (isGround() == false)
			{
				set_state(PlayerState::FALL);
				changeAnim("fall");
				break;
			}

			if (right)
			{
				if (isDir(Direction::LEFT_DIR))
					changeDir(Direction::RIGHT_DIR);
				set_state(PlayerState::WALK);
				changeAnim("walk");
				break;
			}
			else if (left)
			{
				if (isDir(Direction::RIGHT_DIR))
					changeDir(Direction::LEFT_DIR);
				set_state(PlayerState::WALK);
				changeAnim("walk");
				break;
			}

			if (down && powerup)
			{
				set_state(PlayerState::LOWER);
				changeAnim("lower");
				break;
			}

			if (isTree())
			{
				if (up)
				{
					catchTree();
					if (right || left)
					{
						changeAnim("moveTree");
						set_state(PlayerState::MOVE_TREE);
					}
					else
					{
						changeAnim("idleTree");
						set_state(PlayerState::IDLE_TREE);
					}
					break;
				}
			}

			if (jump)
			{
				vel.y = config.velStartJump;
				pos.y += vel.y;
				updateCollRect();
				collisionVer();
				set_state(PlayerState::JUMP);
				if (down && size == PlayerSize::TALL)
					changeAnim("lower");
				else
					changeAnim("jump");
				break;
			}

			if (shoot)
			{
				if (powerup)
				{
					if (powerup->getName() == "fireflower")
					{
						changeAnim("shoot");
						powerup->fire();
					}
					else if (powerup->getName() == "hammer")
					{
						changeAnim("shoot");
						powerup->fire();
					}
					else if (powerup->getName() == "tanooki")
					{
						changeAnim("tanooki");
						powerup->fire();
					}
				}
			}

			updateCollRect();

			updateAnim();
			break;

		case PlayerState::RUN:
		case PlayerState::WALK:
			if (isGround() == false)
			{
				vel.y = 0;
				set_state(PlayerState::FALL);
				if (down)
				{
					changeAnim("lower");
				}
				else if (get_state() == PlayerState::RUN)
				{
					changeAnim("run");
				}
				else
				{
					changeAnim("fall");
				}
				break;
			}
			/*
			//aperta dois botões juntos, impossivel numa tela de celular
			if (left && right)
			{
				changeAnim("walk");
				acc.x = 0;
				vel.x *= config.damp.x;
				if (vel.x == 0)
				{
					acc.zero();
					set_state(PlayerState::IDLE);
					changeAnim("idle");
					break;
				}
			}
			else */
			if (right)
			{
				//se estava indo para esquerda
				if (vel.x < 0)
				{
					changeAnim("inverse");

					acc.x = 0;
					vel.x *= config.damp.x;
					if (vel.x > -config.minVel.x && vel.x < config.minVel.x)
					{
						acc.zero();
						vel.zero();
						set_state(PlayerState::IDLE);
						changeAnim("idle");
						break;
					}
					else if (isSolidSide("right"))
					{
						acc.x = config.acc.x;
						vel.x = 0;
					}
				}
				else
				{
					changeDir(Direction::RIGHT_DIR);
					changeAnim("walk");
					//abaixo serve para evitar tremores quando encosta num sólido
					if (isSolidSide("right"))
					{
						acc.x = 0;
						vel.x = 0;
					}
					else
						acc.x = config.acc.x;
				}
			}
			else if (left)
			{
				// se estava indo para direita
				if (vel.x > 0)
				{
					changeAnim("inverse");

					acc.x = 0;
					vel.x *= config.damp.x;
					if (vel.x > -config.minVel.x && vel.x < config.minVel.x)
					{
						acc.zero();
						vel.zero();
						set_state(PlayerState::IDLE);
						changeAnim("idle");
						break;
					}
					else if (isSolidSide("left"))
					{
						acc.x = -config.acc.x;
						vel.x = 0;
					}
				}
				else
				{
					changeDir(Direction::LEFT_DIR);
					changeAnim("walk");
					//abaixo serve para evitar tremores quando encosta num sólido
					if (isSolidSide("left"))
					{
						acc.x = 0;
						vel.x = 0;
					}
					else
						acc.x = -config.acc.x;
				}
			}
			else
			{
				acc.x = 0;
				// diminui a velocidade
				vel.x *= config.damp.x;
				if (vel.x > -config.minVel.x && vel.x < config.minVel.x)
				{
					acc.zero();
					vel.zero();
					set_state(PlayerState::IDLE);
					changeAnim("idle");
					break;
				}
			}

			if (down && size == PlayerSize::TALL)
			{
				//desativa movimento
				right = left = false;
				//deslizando abaixado
				set_state(PlayerState::LOWER);
				changeAnim("lower");
				break;
			}

			if (isTree())
			{
				if (up)
				{
					catchTree();
					if (right || left)
					{
						changeAnim("moveTree");
						set_state(PlayerState::MOVE_TREE);
					}
					else
					{
						changeAnim("idleTree");
						set_state(PlayerState::IDLE_TREE);
					}
					break;
				}
			}

			if (jump)
			{
				if (vel.x == -config.maxVel.x || vel.x == config.maxVel.x)
					vel.y = config.velStartRunJump;
				else
					vel.y = config.velStartJump;
				pos.y += vel.y;
				updateCollRect();
				collisionVer();
				set_state(PlayerState::JUMP);
				if (down && size == PlayerSize::TALL)
					changeAnim("lower");
				else
					changeAnim("jump");
				//if (get_state() == PlayerState::RUN)
				//	throw 1;
				break;
			}

			vel.x += acc.x;//*double(FPSManager::instance()->get_delta());

			if (vel.x > config.maxVel.x)
			{
				vel.x = config.maxVel.x;
				set_state(PlayerState::RUN);
				changeAnim("run");
			}
			else if (vel.x < -config.maxVel.x)
			{
				vel.x = -config.maxVel.x;
				set_state(PlayerState::RUN);
				changeAnim("run");
			}

			if ((left == true && right == false && vel.x < config.minVel.x && vel.x > 0) || (left == false && right == true && vel.x > -config.minVel.x && vel.x < 0))
			{
				vel.x = 0;
				set_state(PlayerState::IDLE);
				changeAnim("idle");
				break;
			}

			pos.x += vel.x;
			updateCollRect();
			if (collisionHor())
			{
				vel.x = 0;
				acc.x = 0;
			}

			if (shoot)
			{
				if (powerup)
				{
					if (powerup->getName() == "fireflower")
					{
						changeAnim("shoot");
						powerup->fire();
					}
					else if (powerup->getName() == "hammer")
					{
						changeAnim("shoot");
						powerup->fire();
					}
					else if (powerup->getName() == "tanooki")
					{
						changeAnim("tanooki");
						powerup->fire();
					}
				}
			}

			updateAnim();
			break;

		case PlayerState::LOWER:
			if (down == false)
			{
				if (isGround() == false)
				{
					acc.zero();
					vel.zero();
					set_state(PlayerState::FALL);
					changeAnim("fall");
					break;
				}
				else
				{
					updateCollRect();
					if (isTopSolid() && size == PlayerSize::TALL)
					{
						vel.zero();
						acc.zero();
						set_state(PlayerState::MOVE_OUT_TILE);
						changeAnim("idle");
						break;
					}
					else
					{
						if (right || left)
						{
							set_state(PlayerState::WALK);
							changeAnim("walk");
							break;
						}
						else
						{
							set_state(PlayerState::IDLE);
							changeAnim("idle");
							break;
						}
					}
				}
			}

			if (isGround())
			{
				if (jump)
				{
					vel.y = config.velStartJump;
					pos.y += vel.y;
					updateCollRect();
					collisionVer();

					set_state(PlayerState::JUMP);
					if (down == true)
						changeAnim("lower");
					else
						changeAnim("jump");
					break;
				}
			}
			else
			{
				vel.y = 0;
				set_state(PlayerState::FALL);
				if (down== true)
					changeAnim("lower");
				else
					changeAnim("fall");
				break;
			}

			vel.x *= config.damp.x;
			if (vel.x > -config.minVel.x && vel.x < config.minVel.x)
				vel.x = 0;

			pos.x += vel.x;
			updateCollRect();
			if (collisionHor())
			{
				vel.x = 0;
				acc.x = 0;
			}

			updateAnim();
			break;

		case PlayerState::FALL:
		case PlayerState::JUMP:
			{
				if (isGround())
				{
					if (vel.x != 0)
					{
						if (down == true)
						{
							set_state(PlayerState::LOWER);
							changeAnim("lower");
							break;
						}
						else
						{
							set_state(PlayerState::WALK);
							changeAnim("walk");
							break;
						}
					}
					else
					{
						if (down)
						{
							set_state(PlayerState::LOWER);
							changeAnim("lower");
							break;
						}
						else
						{
							set_state(PlayerState::IDLE);
							changeAnim("idle");
							break;
						}
					}
				}


				bool pressedJump = false;
				if (down == false)
				{
					if (get_state() == PlayerState::FALL)
						changeAnim("fall");
					else
						changeAnim("jump");
				}
				else
				{
					if (controls["jump"].get_state() == Key::HOLD)
					{
						changeAnim("lower");
					}
				}

				if (controls["jump"].get_state() == Key::PRESS)
				{
					pressedJump = true;
				}

				float damping = 0;
				if (right)
				{
					acc.x = config.acc.x;

					if (isSolidSide("right"))
					{
						damping = -config.gravity/2.0;
						changeDir(Direction::LEFT_DIR);
						changeAnim("wallJump");
					}
					else if (dir == Direction::LEFT_DIR)
						changeDir(Direction::RIGHT_DIR);

					if (vel.x > -config.minVel.x && vel.x < config.minVel.x)
						acc.x = config.accJump.x;
					else if (vel.x < -config.minVel.x)
					{
						changeDir(Direction::RIGHT_DIR);
						vel.x = -config.minVel.x;
					}
				}
				else if (left)
				{
					acc.x = -config.acc.x;

					if (isSolidSide("left"))
					{
						vel.x = 0;

						printf("tocou left em %u %s\n",SDL_GetTicks(), (pressedJump)?"pulou":"Não pulou");
						if (pressedJump)
						{
							vel.y= config.velStartJumpWall;
							pos.y += vel.y;
							collisionVer();
							/*vel.x = 4;//config.velOnWall.x;
							pos.x += vel.x;
							collisionHor();
							*/
							pressedJump = false;
						}

						damping = -config.gravity/2.0;
						changeDir(Direction::RIGHT_DIR);
						changeAnim("wallJump");

					}
					else if (dir == Direction::RIGHT_DIR)
					{
						changeDir(Direction::LEFT_DIR);
						printf("Player::mudar anim para jump/fall\n");
					}

					if (vel.x > -config.minVel.x && vel.x < config.minVel.x)
						acc.x = -config.accJump.x;
					else if (vel.x > config.minVel.x)
					{
						changeDir(Direction::LEFT_DIR);
						vel.x = config.minVel.x;
					}
				}
				else
				{
					acc.x = 0;
					// diminui a velocidade
					vel.x *= config.damp.x;
				}


				if (isTree())
				{
					if (up)
					{
						catchTree();
						if (right || left)
						{
							changeAnim("moveTree");
							set_state(PlayerState::MOVE_TREE);
						}
						else
						{
							changeAnim("idleTree");
							set_state(PlayerState::IDLE_TREE);
						}
						break;
					}
				}

				if (shoot)
				{
					if (powerup)
					{
						if (powerup->getName() == "fireflower")
						{
							changeAnim("shootfire");
							powerup->fire();
						}
						else if (powerup->getName() == "hammer")
						{
							changeAnim("shoothammer");
							powerup->fire();
						}
						else if (powerup->getName() == "tanooki")
						{
							changeAnim("tanooki");
							powerup->fire();
						}
					}
				}


				vel.x += acc.x;

				if (vel.x > config.maxVel.x)
				{
					vel.x = config.maxVel.x;
				}
				else if (vel.x < -config.maxVel.x)
				{
					vel.x = -config.maxVel.x;
				}


				if (((left == false && right == false) || (left == true && right == true)) && vel.x > -config.minVel.x && vel.x < config.minVel.x)
				{
					vel.x = 0;
				}

				pos.x += vel.x;
				updateCollRect();
				collisionHor();

				vel.y += config.gravity + damping;
				//se soltou o botão de jump então perde força
				if (vel.y < 0 && get_state() == PlayerState::JUMP && (controls["jump"].get_state() == Key::RELEASE || controls["jump"].get_state() == Key::FREE))
					vel.y *= config.damp.y;

				if (vel.y > config.maxVel.y)
				{
					vel.y = config.maxVel.y;
				}
				else if (vel.y < -config.maxVel.y)
				{
					vel.y = -config.maxVel.y;
				}

				pos.y += vel.y;
				updateCollRect();
				if (collisionVer())
				{
					vel.zero();
					acc.zero();
					changeAnim("idle", true);
					set_state(PlayerState::IDLE);
					break;
				}
				//se bateu com o meio da cabeça no tile
				if (isMiddleTopSolid())
				{
					vel.y = 0;
				}
				else
				{
					if (isSolidSide("up", 0) && isSolidSide("up", upSide.size()-1) == false)
						pos.x += config.velAdj.x;
					else if (isSolidSide("up", 0) == false && isSolidSide("up", upSide.size()-1))
						pos.x += -config.velAdj.x;
				}

				updateAnim();
			}
			break;

		case PlayerState::IDLE_SWIM:
			updateAnim();
			break;

		case PlayerState::SWIM:
			updateAnim();
			break;

		case PlayerState::SHOOT:
			updateAnim();
			break;

		case PlayerState::IDLE_LADDER:
			updateAnim();
			break;

		case PlayerState::UP_LADDER:
			updateAnim();
			break;

		case PlayerState::DOWN_LADDER:
			updateAnim();
			break;

		case PlayerState::WATER_JUMP:
			updateAnim();
			break;

		case PlayerState::TALL_TO_SMALL:
			updateAnim();
			break;

		case PlayerState::MOVE_OUT_TILE:
			//congela os controles
			down = shoot = jump = left = right = false;

			if (dir == Direction::LEFT_DIR)
				vel.x = config.maxVel.x;

			if (dir == Direction::RIGHT_DIR)
				vel.x = -config.maxVel.x;

			pos.x += vel.x;
			updateCollRect();

			if (isTopSolid() == false)
			{
				vel.zero();
				acc.zero();
				set_state(PlayerState::IDLE);
				changeAnim("idle");
				break;
			}

			updateAnim();
			break;

		case PlayerState::IDLE_TREE:
			if (right || left || up || down)
			{
				if (right)
					changeDir(Direction::RIGHT_DIR);
				else
					changeDir(Direction::LEFT_DIR);
				set_state(PlayerState::MOVE_TREE);
				changeAnim("moveTree");
				break;
			}

			if (!isTree()) {
				acc.zero();
				set_state(PlayerState::FALL);
				break;
			}

			//updateAnim();
			break;
		case PlayerState::MOVE_TREE:
			{
				if (isTree())
				{
					if (right)
					{
						acc.x = config.accTree.x;
						changeDir(Direction::RIGHT_DIR);
					}
					else if (left)
					{
						acc.x = -config.accTree.x;
						changeDir(Direction::LEFT_DIR);
					}
					else
					{
						acc.x = 0;
					}

					if (up)
					{
						acc.y = -config.accTree.y;
					}
					else if (down)
					{
						acc.y = config.accTree.y;
					}
					else
					{
						acc.y = 0;
					}

					if (acc.x == 0 && acc.y == 0)
					{
						acc.zero();
						//changeAnim("idleTree");
						set_state(PlayerState::IDLE_TREE);
					}
				}
				else
				{
					acc.zero();
					set_state(PlayerState::FALL);
					break;
				}
				vel.x = acc.x;
				pos.x += vel.x;
				collisionHor();

				float before = pos.y;
				vel.y = acc.y;
				pos.y += vel.y;
				collisionVer();

				if (isTree() == false && up)
				{
					pos.y = before;
				}

				updateAnim();
			}
			break;

		default:
			break;
	}

	return get_state();
}
