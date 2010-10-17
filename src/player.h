#ifndef player_h
#define player_h
#include <allegro5/allegro5.h>
#include <Box2D/Box2D.h>

class Player
{
public:
	Player();
	void Set_image(ALLEGRO_BITMAP* i);
	void Create_body(b2World* world);
	void Set_position(float x, float y);
	b2Vec2 Get_position();
	void Event(ALLEGRO_EVENT& event);
	void Update(float dt);
	void Draw(b2Vec2 camera);
private:
	bool jetpack;
	bool move_left;
	bool move_right;
	bool jump;
	b2Body* body;

	ALLEGRO_BITMAP* image;
};

#endif
