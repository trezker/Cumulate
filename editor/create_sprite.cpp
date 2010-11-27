#include "create_sprite.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <iostream>

Create_sprite::Create_sprite(Bitmaps& ibitmaps, Sprites& isprites, Vector2& icamera, ALLEGRO_FONT* ifont)
:bitmaps(&ibitmaps)
,sprites(&isprites)
,camera(&icamera)
,sprite(NULL)
,font(ifont)
,selected(0)
,open(false)
{
	w = al_get_text_width(font, "Create sprite") + 4;
	h = al_get_font_line_height(font) + 4;
	inputbox.Set_font(font);
	inputbox.Set_text("filename");
	loadbutton.Set_font(font);
	loadbutton.Set_text("Load");
	choosebutton.Set_font(font);
	choosebutton.Set_text("Choose file");
	if(!bitmaps->empty())
	{
		sprite = new Sprite((*bitmaps)[0]);
	}
	for(Bitmaps::iterator i = bitmaps->begin(); i!=bitmaps->end(); ++i)
	{
		thumbnail_list.Add_thumbnail(*i);
	}
	datapath = al_create_path("data/");
}

Create_sprite::~Create_sprite()
{
}

void Create_sprite::Draw()
{
	ALLEGRO_COLOR color = al_map_rgb_f(1, 1, 1);
	ALLEGRO_COLOR back_color = al_map_rgb_f(1, .9, .9);
	al_draw_rectangle(x, y, x+w, y+h, back_color, 0);
	al_draw_text(font, color, x+w/2, y+2, ALLEGRO_ALIGN_CENTRE, "Create sprite");

	if(open)
	{
		inputbox.Draw();
		loadbutton.Draw();
		choosebutton.Draw();
		thumbnail_list.Draw();
		if(sprite)
		{
			sprite->Draw(*camera);
		}
	}
}

void Create_sprite::Event(ALLEGRO_EVENT& event)
{
	if(event.type == ALLEGRO_EVENT_MOUSE_AXES)
	{
		mouse.Set(event.mouse.x, event.mouse.y);
		ALLEGRO_KEYBOARD_STATE keystate;
		al_get_keyboard_state(&keystate);
		if(al_key_down(&keystate, ALLEGRO_KEY_RSHIFT)
		|| al_key_down(&keystate, ALLEGRO_KEY_LSHIFT))
		{
			mouse.x -= int(mouse.x)%10;
			mouse.y -= int(mouse.y)%10;
		}
		mouse += *camera;
		if(sprite)
			sprite->Set_position(mouse);
	}

	if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
	{
		if(event.mouse.button == 1)
		{
			if(sprite)
			{
				sprites->push_back(sprite);
				sprite = new Sprite((*bitmaps)[selected]);
				sprite->Set_position(mouse);
			}
		}
	}
	
	inputbox.Event(event);
	loadbutton.Event(event);
	choosebutton.Event(event);
	thumbnail_list.Event(event);

	if(loadbutton.Get_active())
	{
		loadbutton.Set_active(false);

		if(!al_ustr_equal(inputbox.Get_text(), al_ustr_empty_string()))
		{
//			std::cout<<"Load"<<std::endl;
			Bitmap* bitmap = new Bitmap(al_cstr(inputbox.Get_text()));
			if(!bitmap->Get_allegro_bitmap())
				delete bitmap;
			else
			{
				bitmaps->push_back(bitmap);
				thumbnail_list.Add_thumbnail(bitmap);
				if(!sprite)
					sprite = new Sprite(bitmap);
			}
		}
	}

	if(choosebutton.Get_active())
	{
		choosebutton.Set_active(false);

		ALLEGRO_FILECHOOSER *filechooser = al_create_native_file_dialog(datapath, "Load", "*.*", ALLEGRO_FILECHOOSER_MULTIPLE|ALLEGRO_FILECHOOSER_FILE_MUST_EXIST);
		al_show_native_file_dialog(NULL, filechooser);
		int nf = al_get_native_file_dialog_count(filechooser);
		for(int i = 0; i<nf; ++i)
		{
			const ALLEGRO_PATH *path = al_get_native_file_dialog_path(filechooser, i);

			ALLEGRO_PATH *relpath = Get_relative_path(path);
			if(!relpath)
				continue;

			const char *p = al_path_cstr(relpath, '/');
			Bitmap* bitmap = new Bitmap(p);
			if(!bitmap->Get_allegro_bitmap())
				delete bitmap;
			else
			{
				std::cout<<p<<std::endl;
				char *cwd = al_get_current_directory();
				bitmaps->push_back(bitmap);
				thumbnail_list.Add_thumbnail(bitmap);
				if(!sprite)
					sprite = new Sprite(bitmap);
			}
			al_destroy_path(relpath);
		}
		al_destroy_native_file_dialog(filechooser);
		std::cout<<"Woop"<<std::endl;
	}

	if(thumbnail_list.Get_changed())
	{
		thumbnail_list.Set_changed(false);
		selected = thumbnail_list.Get_selected();
		if(sprite)
			delete sprite;
		sprite = new Sprite((*bitmaps)[selected]);
	}
}

void Create_sprite::Open()
{
	inputbox.Set_position(x, y+h);
	inputbox.Set_size(100, h);
	loadbutton.Set_position(x, y+h*2);
	loadbutton.Set_size(50, h);
	choosebutton.Set_position(x+50, y+h*2);
	choosebutton.Set_size(100, h);
	thumbnail_list.Set_position(x, y+h*3);
	thumbnail_list.Set_size(150, 200);
	h = h*2+200;
	w = 150;
	resized = true;
	open = true;

	thumbnail_list.Clear();
	for(Bitmaps::iterator i = bitmaps->begin(); i!=bitmaps->end(); ++i)
	{
		thumbnail_list.Add_thumbnail(*i);
	}
	selected = 0;
	if(sprite)
		delete sprite;
	if(!bitmaps->empty())
		sprite = new Sprite((*bitmaps)[selected]);
	else
		sprite = NULL;
}

void Create_sprite::Close()
{
	h = (h-200)/2;
	resized = true;
	open = false;
/*	if(sprite)
	{
		delete sprite;
		sprite = NULL;
	}
*/
}
