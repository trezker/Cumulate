#ifndef sprite_h
#define sprite_h

#include "vector2.h"
#include "bitmap.h"
#include <vector>

class Sprite
{
public:
	Sprite(Bitmap* i);
	void Set_position(const Vector2& p);
	const Vector2& Get_position();
	const Vector2& Get_size();
	Bitmap* Get_bitmap();
	void Draw(Vector2 camera);
private:
	Bitmap* bitmap;
	Vector2 position;
	Vector2 size;
};

typedef std::vector<Sprite*> Sprites;

#endif
