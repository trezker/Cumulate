#include "sprite.h"

Sprite::Sprite(Bitmap* i)
:bitmap(i)
,size(Vector2(i->Get_width(), i->Get_height()))
{
}

const Vector2& Sprite::Get_position()
{
	return position;
}

void Sprite::Set_position(const Vector2& p)
{
	position = p;
}

const Vector2& Sprite::Get_size()
{
	return size;
}

Bitmap* Sprite::Get_bitmap()
{
	return bitmap;
}

void Sprite::Draw(Vector2 camera)
{
	bitmap->Draw(position.x-camera.x, position.y-camera.y);
}
