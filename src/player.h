#ifndef player_h
#define player_h
#include <allegro5/allegro5.h>

class Player
{
public:
	Player();
	void Set_position(float x, float y);
	void Event(ALLEGRO_EVENT& event);
	void Update(float dt);
	void Draw();
private:
	float x;
	float y;
	float xs;
	float ys;
	bool move_left;
	bool move_right;
	bool jump;
	
	ALLEGRO_BITMAP* image;
};

#endif
