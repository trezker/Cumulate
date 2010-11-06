#ifndef bitmap_h
#define bitmap_h

#include <string>
#include <allegro5/allegro.h>
#include <vector>

class Bitmap
{
public:
	Bitmap(const std::string& filename);
	~Bitmap();
	void Draw(float x, float y);
	const std::string& Get_filename();
	int Get_width();
	int Get_height();
	ALLEGRO_BITMAP* Get_allegro_bitmap();
private:
	ALLEGRO_BITMAP* bitmap;
	std::string filename;
};

typedef std::vector<Bitmap*> Bitmaps;

#endif
