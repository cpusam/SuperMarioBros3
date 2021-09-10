#include "JumperTile.hpp"
#include "Exception.hpp"

	Vect dump;//o quanto tirar da velocidade
	Vect acc;//aceleração
	Vect velMax;//velocidade máxima
	float gravity;//gravidade
	float velStartJump;//velocidade inicial ao pular
	
JumperTileConfig::JumperTileConfig (  )
{
	dump.set(0, 0.80);
	acc.set(0,0.05);
	velMax.set(0,3);
	velStartJump = -velMax.y;
	gravity = 0.5;
}



JumperTile::JumperTile (  )
{
	show(false);
	jump = false;
}

void JumperTile::setJump ( bool jump )
{
	this->jump = jump;
}

void JumperTile::setTile ( TileMapView * level, int x, int y, int newTile, int bgTile )
{
	this->level = level;
	pos.x = start.x = int(x / level->get_tilesize()) * level->get_tilesize();
	pos.y = start.y = int(y / level->get_tilesize()) * level->get_tilesize();
	
	this->bgTile = bgTile;
	this->newTile = newTile;
	
	show(false);
	jump = false;
	
	this->level = level;
	int tile = level->get_tile(start.x,start.y);
	
	if (level->is_animated(tile))
	{
		CAnimatedTile aux = level->get_animation(tile);
		if (aux.get_tile() != tile)
		{
			std::cout<<"Tile ANIM "<<tile<<" passado no construtor não é animado\n";
			throw Exception("Tile não é animado");
		}
		anim["tile"] = aux;
	}
	else
	{
		Animation aux;
		
		SDL_Rect src = level->get_source(tile);
		if (src.w <= 0 || src.h <= 0)
		{
			std::cout<<"Tile SRC " <<tile<<" Inexistente\n";
			throw Exception("Jumper erro ao criar tile, não existe o tile passado no construtor");
		}
		
		aux.add_frame(level->texture, src, (SDL_Rect){0,0,level->get_tilesize(),level->get_tilesize()}, 100);
		anim["tile"] = aux;
	}
	
	currAnim = &anim["tile"];
	printf("currAnim.delay = %d\n", currAnim->get_curr_frame().get_delay());
	set_state(TileState::STOP);
}

void JumperTile::reset (  )
{
	vel.zero();
	set_state(TileState::STOP);
}

void JumperTile::input ( SDL_Event & event )
{
	if (isVisible() == false)
		return;
}

void JumperTile::draw ( SDL_Renderer * renderer, Camera * camera )
{
	if (currAnim && isVisible())
		currAnim->draw(renderer, camera, pos.x, pos.y);
		
	//raw_texture(renderer, camera, Texturer::get("tiles"), pos.x,pos.y);
	//printf("pos.x = %d, pos.y = %d\n", int(pos.x), int(pos.y));
}

int JumperTile::update (  )
{
	switch (get_state())
	{
		case TileState::STOP:
			if (jump)
			{
				if (bgTile > -1)
					level->set_tile(start.x, start.y, bgTile);
				jump = false;
				vel.zero();
				vel.y = config.velStartJump;
				set_state(TileState::JUMP);
				currAnim = &anim["tile"];
				currAnim->reset();
				show(true);
				set_state(TileState::JUMP);
				break;
			}
			break;
		
		case TileState::JUMP:
			vel.y += config.gravity;
			
			if (vel.y < -config.velMax.y)
				vel.y = -config.velMax.y;
			else if (vel.y > config.velMax.y)
				vel.y = config.velMax.y;
			
			pos.y += vel.y;
			if (pos.y > start.y)
			{
				if (newTile > -1)
					level->set_tile(start.x, start.y, newTile);
				set_state(TileState::READY);
				show(false);
				break;
			}
			if (currAnim)
				currAnim->update();
			break;
		
		case TileState::READY:
			break;
		
		default:
			set_state(TileState::STOP);
			show(false);
			break;
	}
	
	return get_state();
}

Jumper * Jumper::singleton = nullptr;

Jumper * Jumper::instance()
{
	if (singleton == nullptr)
		singleton = new Jumper();
	return singleton;
}

void Jumper::setup ( TileMapView * level, std::string tiles_name )
{
	this->levelMap = level;
	texture = level->texture;
}
/*
faz o tile na posição (x,y) pular
*/
void Jumper::doJump ( int x, int y, int newTile, int bgTile )
{
	unsigned int i = 0;
	for (auto & tile: jumpers)
	{
		if (tile.get_state() == JumperTile::TileState::READY)
		{
			jumpers.erase(jumpers.begin() + i);
			i--;
			continue;
		}
		i++;
	}
	
	if (jumpers.size() < 5 && levelMap->get_tile(x,y) > -1)
	{
		std::cout<<"level.x.y.tile = "<<char(levelMap->get_tile(x,y))<<std::endl;
		std::cout<<"x = "<<x<<", y = "<<y<<std::endl;
		jumpers.push_back(JumperTile());
		jumpers.back().setTile(levelMap, x, y, newTile, bgTile);
		jumpers.back().setJump(true);
		jumpers.back().reset();
		return;
	}
	
	//se chegou aqui é porque todos os tiles estão em uso
	std::cout<<"Falta adicionar mais tiles puladores, só tem "<<jumpers.size()<<std::endl; 
}

const std::vector<JumperTile> & Jumper::getJumpers (  )
{
	return jumpers;
}

void Jumper::input ( SDL_Event & event )
{
}

void Jumper::draw ( SDL_Renderer * renderer, Camera * camera )
{
	for (auto & tile: jumpers)
		tile.draw(renderer, camera);
}

int Jumper::update (  )
{
	for (auto & tile: jumpers)
	{
		tile.update();
	}
	return get_state();
}





