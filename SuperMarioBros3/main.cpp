#include <iostream>
#include <string>
#include "Chora.hpp"
#include "Player.hpp"
#include "JumperTile.hpp"

#include <iostream>

#define TILEIMAGE  16 //tamanho do tile na imagens de tiles
#define TILESIZE   16 //tamanho do tile no jogo
//no padrão widescreen 16:9
#define WIDTH      16*2*TILESIZE//
#define HEIGHT      9*2*TILESIZE//

#define SCREEN_WIDTH    WIDTH*2
#define SCREEN_HEIGHT  HEIGHT*2

using namespace std;

int main ( int argc, char** argv )
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cerr << "SDL_Init Erro: "<<SDL_GetError()<<endl;
		return 1;
	}

	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		cerr<<"IMG_Init Erro: "<<SDL_GetError()<<endl;
		SDL_Quit();
		return 1;
	}

	SDL_Window * window = SDL_CreateWindow("Super Mario Bros 3", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (window == nullptr)
	{
		cerr<<"SDL_CreateWindow Erro: "<<SDL_GetError()<<endl;
		IMG_Quit();
		SDL_Quit();
		return 1;
	}

	SDL_RendererInfo drinfo;
	SDL_GetRenderDriverInfo (0, &drinfo);
	Uint32 renderFlags = 0;

	if (drinfo.flags & SDL_RENDERER_ACCELERATED)
		renderFlags = renderFlags | SDL_RENDERER_ACCELERATED;
	else if (drinfo.flags & SDL_RENDERER_SOFTWARE)
		renderFlags = renderFlags | SDL_RENDERER_SOFTWARE;
	/*
	if (drinfo.flags & SDL_RENDERER_PRESENTVSYNC)
		renderFlags = renderFlags | SDL_RENDERER_PRESENTVSYNC;
	*/
	if (drinfo.flags & SDL_RENDERER_TARGETTEXTURE)
		renderFlags = renderFlags | SDL_RENDERER_TARGETTEXTURE;

	SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, renderFlags);
	if (renderer == nullptr)
	{
		cerr<<"SDL_CreateRenderer Erro: "<<SDL_GetError()<<endl;
		IMG_Quit();
		SDL_Quit();
		return 1;
	}

	SDL_Texture * targetTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, WIDTH, HEIGHT);

	if (targetTexture == nullptr)
	{
		cerr<<"Erro: "<<SDL_GetError()<<endl;
		IMG_Quit();
		SDL_Quit();
		return 1;
	}

	SDL_Event event;
	printf("Chora começa aqui\n");
	// a exceção de ponto flutuante ocorre por aqui
	TileMapView *level;
	try
	{
		level = new TileMapView(TILESIZE);
	}catch (Exception & e)
	{
		std::cout<<"Level Error: "<<e.what()<<std::endl;
		return 1;
	}



	level->texture = IMG_LoadTexture(renderer, "images/level/81122.png");
	if (level->texture == nullptr)
	{
		std::cout<<"Error: "<<IMG_GetError()<<std::endl;
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
	Texturer::add(level->texture, "tiles");

	level->set_source('.', (SDL_Rect){647,18,TILEIMAGE,TILEIMAGE});// céu
	level->set_source('s', (SDL_Rect){596,18,TILEIMAGE,TILEIMAGE});// chão
	level->set_source('a', (SDL_Rect){613,18,TILEIMAGE,TILEIMAGE});// chão
	level->set_source('d', (SDL_Rect){630,18,TILEIMAGE,TILEIMAGE});// chão
	level->set_source('t', (SDL_Rect){936,205,TILEIMAGE,TILEIMAGE});// arvore

	if (level->read("levels/demo.txt") == 0)
	{
		std::cout<<"Main::Erro ao ler mapa de tiles\n";
		return 1;
	}

	std::vector<int> solid;
	//solid.push_back('a');
	solid.push_back('s');
	solid.push_back('d');


	Camera camera(renderer, 0,0,SCREEN_WIDTH,SCREEN_HEIGHT,WIDTH,HEIGHT, level->get_dimension());
	camera.set_focus(Vect(WIDTH/2, HEIGHT/2));

	Player * mario;
	try
	{
		mario = new Player(renderer, level, "player1");
	} catch (Exception & e )
	{
		std::cout<<"Error: "<< e.what()<<std::endl;
		return 1;
	}

	for (auto s: solid)
		mario->addSolid(s);
	Elements::add(mario);
	//adicionando uma roupa diferente ao mário
	//mario->addPowerUp(new TanookiSuit(mario));
	mario->addPowerUp(new PowerUp("mushroom",mario));
	mario->changeAnim("idle");

	Key fullscreen(SDLK_f);

	FPSManager::instance()->set_framerate(60); // 60 fps

	Jumper::instance()->setup(level, "tiles");

	Uint32 fullscreenFlags = 0;
	bool done = false;
	while (done == false)
	{
		bool mouseDown = false;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				done = true;
			if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.sym == SDLK_r)
				{
					mario->reset();
				}
			}

			if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				if (mouseDown == false)
				{
					mouseDown = true;
					Vect p = Vect(event.button.x + camera.get_position().x, event.button.y + camera.get_position().y);
					std::cout<<"p.x = "<<p.x<<", p.y = "<<p.y<<std::endl;
					Vect q = p;

					std::cout<<"p.x.y = "<<p.x<<", "<<p.y<<" Q.x.y = "<<q.x<<", "<<q.y<<std::endl;

					Jumper::instance()->doJump(p.x, p.y, 'a', '.');
				}
			}

			fullscreen.input(event);
			// atualiza entradas dos elementos do jogo
			Elements::input(event);
		}

		fullscreen.update();

		if (fullscreen.get_state() == Key::PRESS)
		{
			fullscreenFlags = (fullscreenFlags ^ SDL_WINDOW_FULLSCREEN);
			SDL_SetWindowFullscreen(window, fullscreenFlags);
		}

		if (FPSManager::instance()->get_delta() > 0)
		{

			//atualiza elementos do jogo
			try{
			Elements::update();
			}catch (Exception & e){
				e.what();
				return 1;
			}

			Vect p1 = mario->get_pos();
			camera.lookat(p1);

			SDL_SetRenderTarget(renderer, targetTexture);
			SDL_SetRenderDrawColor(renderer, 0,0,0,255);
			SDL_RenderClear(renderer);

			camera.updateViewport(renderer);
			level->draw(renderer, &camera);
			mario->update();
			Elements::draw(renderer, &camera);

			Jumper::instance()->update();
			Jumper::instance()->draw(renderer, &camera);

			SDL_SetRenderTarget(renderer, nullptr);
			SDL_RenderCopyEx(renderer, targetTexture, nullptr, nullptr, 0, nullptr, SDL_FLIP_NONE);
			SDL_RenderPresent(renderer);
		}

		FPSManager::instance()->update();
	}

	delete level;
	delete mario;
	Elements::clear();
	Texturer::destroy();

	SDL_DestroyTexture(level->texture);
	SDL_DestroyTexture(targetTexture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();

	return 0;
}
