#include "bitmap.h"

Bitmap::Bitmap(const std::string& f)
:bitmap(al_load_bitmap(f.c_str()))
,filename(f)
{
}

Bitmap::~Bitmap()
{
	al_destroy_bitmap(bitmap);
}

void Bitmap::Draw(float x, float y)
{
	if(bitmap)
		al_draw_bitmap(bitmap, x, y, 0);
}

const std::string& Bitmap::Get_filename()
{
	return filename;
}

int Bitmap::Get_width()
{
	if(bitmap)
		return al_get_bitmap_width(bitmap);
	else
		return 0;
}

int Bitmap::Get_height()
{
	if(bitmap)
		return al_get_bitmap_height(bitmap);
	else
		return 0;
}

ALLEGRO_BITMAP* Bitmap::Get_allegro_bitmap()
{
	return bitmap;
}
