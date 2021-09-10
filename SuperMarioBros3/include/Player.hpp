//iniciado em 11/08/2017 às 17:12
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "PowerUp.hpp"
#include <string>
#include <vector>
#include <map>

class PowerUp;

struct PlayerConfig
{
	std::map<std::string, Vect> shootPos;//nomeEstado/PosiçãoNoSprite
	Vect maxVel;//velocidade máxima no chão sem água
	Vect minVel;
	Vect accLadder;//aceleração ao subir escadas
	Vect acc; //aceleração ao caminhar
	Vect accJump; //aceleração ao mover no ar
	Vect damp;//o quanto tirar da velocidade a cada loop
	Vect velAdj;//velocidade quando encostar no canto do tile

	float slide;//taxa de velocidade MÍNIMA para deslizar, aqui é uma taxa de maxVel.x
	float gravity; //gravidade
	Vect  velOnWall;
	float velStartJump;//velocidade ao iniciar um pulo normal
	float velStartRunJump;//velocidade inicial ao correr e pular
	float velStartJumpWall;
	int velAnim;
	float velMult;

	Vect accTree;
	std::vector<int> treeTiles;
	//<nomeDaAnimação, delay>
	std::map<std::string,int> velAnimDefault;
	PlayerConfig (  );
	void setEnviroment ( std::string env );
};

class Player: public Entity
{
	public:
	/*
		-Tentar diminuir o numero de estados para evitar repetir código à torto.
		-[Adicionado]SLIDE pode ser inserido no WALK, e SLIDE_DOWN pode ser SLIDE somente
		-[Adicionado]RUN pode ser um case no mesmo ponto do WALK
		-[Adicionado]FALL pode ser um case no mesmo ponto do JUMP, pois muda só a imagem se for o caso
		-SHOOT pode ser somente uma troca de sprites/animação, já que acontece muito rápido
		-WATER_JUMP pode ser somente um JUMP
		-UP/DOWN_LADDER pode ser só MOVE_LADDER e, conforme aperta o botão, sobe ou desce
		-Os estados da escada poderiam ser somente ON_LADDER
		-WALK no chão da água apenas diminui a velocidade no config (maxVel e minVel)
	*/
		enum PlayerState: int
		{
			IDLE,//parado sob o chão
			WALK,//caminhando
			LOWER,//abaixado
			FALL,//caindo quando não há chão e não pulou
			SLIDE,//deslizando no chão quando muda de direção numa velocidade alta
			SLIDE_DOWN, //desliza de bunda no chão
			JUMP,//pulo não abaixado, aqui por enquanto não permito
			DIE,//more
			RUN,//corre pelo chao
			RUN_JUMP,//pula rápido do chão
			RUN_FALL,//cai de modo rápido
			IDLE_SWIM,//parou de nadar
			SWIM,//nadar pra cima ou lados
			SHOOT,//apenas quando grande
			IDLE_LADDER,
			MOVE_LADDER,//sobe desce na escada
			UP_LADDER,
			DOWN_LADDER,
			WATER_JUMP,//pulo por cima da água
			TALL_TO_SMALL,//estado de quando perde o powerup e fica pequeno
			MOVE_OUT_TILE,//move para fora do tile, quando entra por baixo deles

			IDLE_TREE,
			MOVE_TREE,
		};

		enum PlayerSize: int
		{
			SMALL,
			TALL
		};

	public:
		Player ( SDL_Renderer * renderer, TileMap * level, std::string playerName );

		bool receive ( Entity * sender, std::string mesg ) override;

		//atualiza retanmgulos de colisão
		void updateCollRect (  );
		bool isTopSolid (  );
		bool isMiddleTopSolid (  );

		bool isTree (  );
		void catchTree (  );

		void reset (  );

		void changeSize();
		void addPowerUp(PowerUp * p);//adiciona o powerup
		bool touchPowerUp (  );
		// se foi atingido por algum inimigo do grupo objGroup
		bool wasHitBy ( std::string objGroup );
		bool inLadder (  );
		void catchLadder (  );

		Key getControlKey ( std::string keyName );

		// controles - interface
		void doShoot (  ); // usada para atirar
		void doJump (  );

		void changeDir ( Direction d );
		void updateAnim (  );
		void updateControls (  );

		virtual bool collisionHor (  );

		std::string getAnimName ( std::string animName );
		void changeAnim ( std::string animName, bool reset=false );

		void input ( SDL_Event & event ) override;
		void draw ( SDL_Renderer * renderer, Camera * camera ) override;
		int update (  ) override;

	protected:
		PlayerConfig config;
		PlayerSize size;
		float gravity;
		bool right, left, up, down, jump, shoot;
		bool holdJump;
		std::map<std::string, Key> controls;
		PowerUp * powerup;//powerup principal
		PowerUp * subpower;//powerup secundário
		int animUpdates;
		bool invencible;
		STimer invencibleTime;
		std::map<std::string, bool> hitObj;

};

#endif
