#ifndef JUMPERTILE_HPP
#define JUMPERTILE_HPP

#include "Chora.hpp"



struct JumperTileConfig
{
	Vect dump;//o quanto tirar da velocidade
	Vect acc;//aceleração
	Vect velMax;//velocidade máxima
	float gravity;//gravidade
	float velStartJump;//velocidade inicial ao pular
	
	JumperTileConfig (  );
};

/*
	está classe poderia ser só um sólido que o mario pega, e daí apenas muda o movimento, se é para segurar e jogar ou se é para apenas pular
	alçgo como um DragableObject
*/
class JumperTile: public Entity
{
	public:
		enum TileState: int
		{
			STOP,
			JUMP,
			READY,
		};
	public:
		JumperTile (  );
		void setJump ( bool jump );
		//x e y são posições no mundo em pixels
		void setTile ( TileMapView *level, int x, int y, int newTile, int bgTile=-1 );

		void reset (  );

		void input ( SDL_Event & event ) override;
		void draw ( SDL_Renderer * renderer, Camera * camera ) override;
		int update (  ) override;
		
	protected:
		int bgTile;
		int newTile;
		bool jump;
		Vect start;//posição inicial em coordenadas do level
		
		JumperTileConfig config;
	private:
		
};

/*
*/

class Jumper: public Entity
{
	static Jumper * singleton;
	Jumper (  )	{ 	}
	public:
		static Jumper * instance (  );
		void setup ( TileMapView * level, std::string tiles_name );
		/*
		faz o tile na posição (x,y) pular
		newTile = novo tile quando alcansar READY ele troca por esse, se for negativo não faz nada
		bgTile = tile que fica no lugar vazio quando o tile pular
		*/
		void doJump ( int x, int y, int newTile, int bgTile );
		const std::vector<JumperTile> & getJumpers (  );
		
		virtual void input ( SDL_Event & event );
		virtual void draw ( SDL_Renderer * renderer, Camera * camera );
		virtual int update (  );
		
	protected:
		TileMapView * levelMap;
		SDL_Renderer * renderer;
		std::vector <JumperTile> jumpers;//tiles que pulam
	private:
		
};


#endif
