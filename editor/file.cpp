#include "file.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <iostream>
#include <sinxml/sinxml.h>
#include <map>

File::File(ALLEGRO_FONT* ifont)
:platforms(NULL),
bitmaps(NULL),
sprites(NULL),
font(ifont),
open(false)
{
	w = al_get_text_width(font, "File") + 4;
	h = al_get_font_line_height(font) + 4;
	inputbox.Set_font(font);
	inputbox.Set_text("filename");
	savebutton.Set_font(font);
	savebutton.Set_text("Save");
	loadbutton.Set_font(font);
	loadbutton.Set_text("Load");
}

File::~File()
{
}

void File::Draw()
{
	ALLEGRO_COLOR color = al_map_rgb_f(1, 1, 1);
	ALLEGRO_COLOR back_color = al_map_rgb_f(1, .9, .9);
	al_draw_rectangle(x, y, x+w, y+h, back_color, 0);
	al_draw_text(font, color, x+w/2, y+2, ALLEGRO_ALIGN_CENTRE, "File");
	if(open)
	{
		inputbox.Draw();
		savebutton.Draw();
		loadbutton.Draw();
	}
}

void File::Event(ALLEGRO_EVENT& event)
{
	if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
	{
		if(event.mouse.button == 1)
		{
		}
	}
	inputbox.Event(event);
	savebutton.Event(event);
	loadbutton.Event(event);
	if(savebutton.Get_active())
	{
		savebutton.Set_active(false);

		if(!al_ustr_equal(inputbox.Get_text(), al_ustr_empty_string()))
		{
			std::cout<<"Save"<<std::endl;
			sinxml::Document doc("1.0");
			sinxml::Element* map = new sinxml::Element("map");
			doc.Set_root(map);
			
			//Platforms
			for(Platforms::iterator i = platforms->begin(); i != platforms->end(); ++i)
			{
				sinxml::Element* platform = new sinxml::Element("platform");
				map->Add_child(platform);
				Vertices& vertices = (*i)->Get_vertices();
				for(Vertices::iterator i = vertices.begin(); i != vertices.end(); ++i)
				{
					sinxml::Element* vertex = new sinxml::Element("vertex");
					platform->Add_child(vertex);
					vertex->Add_child(new sinxml::Element("x", sinxml::tostring(i->x)));
					vertex->Add_child(new sinxml::Element("y", sinxml::tostring(i->y)));
				}
			}
			
			//Bitmaps
			typedef std::map<Bitmap*, int> Bmpmap;
			Bmpmap bmpmap;
			int id = 0;
			for(Bitmaps::iterator i = bitmaps->begin(); i!= bitmaps->end(); ++i)
			{
				sinxml::Element* bitmap = new sinxml::Element("bitmap");
				map->Add_child(bitmap);
				sinxml::Element* filename = new sinxml::Element("filename", (*i)->Get_filename());
				bitmap->Add_child(filename);
				sinxml::Element* eid = new sinxml::Element("id", sinxml::tostring(id));
				bitmap->Add_child(eid);
				bmpmap[*i] = id;
				++id;
			}

			for(Sprites::iterator i = sprites->begin(); i != sprites->end(); ++i)
			{
				sinxml::Element* sprite = new sinxml::Element("sprite");
				map->Add_child(sprite);
				sinxml::Element* id = new sinxml::Element("id", sinxml::tostring(bmpmap[(*i)->Get_bitmap()]));
				sprite->Add_child(id);
				Vector2 p = (*i)->Get_position();
				sinxml::Element* x = new sinxml::Element("x", sinxml::tostring(p.x));
				sprite->Add_child(x);
				sinxml::Element* y = new sinxml::Element("y", sinxml::tostring(p.y));
				sprite->Add_child(y);
			}

			doc.Save_file(al_cstr(inputbox.Get_text()));
		}
	}
	if(loadbutton.Get_active())
	{
		loadbutton.Set_active(false);

		if(!al_ustr_equal(inputbox.Get_text(), al_ustr_empty_string()))
		{
			std::cout<<"Load"<<std::endl;
			Load(al_cstr(inputbox.Get_text()));
		}
	}
}

void File::Load(const char* filename)
{
	inputbox.Set_text(filename);
	for(Platforms::iterator i = platforms->begin(); i!=platforms->end(); ++i)
	{
		delete *i;
	}
	platforms->clear();
	bitmaps->clear();
	sprites->clear();

	typedef std::map<int, Bitmap*> Idbmpmap;
	Idbmpmap idbmpmap;

	sinxml::Document doc("1.0");
	if(!doc.Load_file(filename))
		return;
	sinxml::Children& mapchildren = doc.Get_root()->Get_children();
	for(sinxml::Children::iterator i = mapchildren.begin(); i != mapchildren.end(); ++i)
	{
		if((*i)->Get_name() == "platform")
		{
			Platform* platform = new Platform;
			sinxml::Children& platformchildren = (*i)->Get_children();
			for(sinxml::Children::iterator j = platformchildren.begin(); j != platformchildren.end(); ++j)
			{
				float x = sinxml::fromstring<float>((*j)->Get_child("x")->Get_value());
				float y = sinxml::fromstring<float>((*j)->Get_child("y")->Get_value());
				platform->Add_collision_vertex(Vector2(x, y));
			}
			platforms->push_back(platform);
		}
		if((*i)->Get_name() == "bitmap")
		{
			std::string filename = (*i)->Get_child("filename")->Get_value();
			int id = sinxml::fromstring<int>((*i)->Get_child("id")->Get_value());
			
			Bitmap* bitmap = new Bitmap(filename);
			bitmaps->push_back(bitmap);
			idbmpmap[id] = bitmap;
		}
	}
	for(sinxml::Children::iterator i = mapchildren.begin(); i != mapchildren.end(); ++i)
	{
		if((*i)->Get_name() == "sprite")
		{
			int id = sinxml::fromstring<int>((*i)->Get_child("id")->Get_value());
			float x = sinxml::fromstring<float>((*i)->Get_child("x")->Get_value());
			float y = sinxml::fromstring<float>((*i)->Get_child("y")->Get_value());
			Sprite* sprite = new Sprite(idbmpmap[id]);
			sprite->Set_position(Vector2(x, y));
			sprites->push_back(sprite);
		}
	}
}

void File::Open()
{
/*	ALLEGRO_DISPLAY *display;
	al_set_new_display_flags(ALLEGRO_WINDOWED);
	display = al_create_display(800, 600);

	ALLEGRO_FILECHOOSER* filechooser = al_create_native_file_dialog(NULL, "Save", "*.*", 0);
	al_show_native_file_dialog(display, filechooser);
	al_destroy_native_file_dialog(filechooser);
*/
	inputbox.Set_position(x, y+h);
	inputbox.Set_size(100, h);
	savebutton.Set_position(x, y+h*2);
	savebutton.Set_size(50, h);
	loadbutton.Set_position(x+50, y+h*2);
	loadbutton.Set_size(50, h);
	h = h*3;
	w = 100;
	resized = true;
	open = true;
}

void File::Close()
{
	h/=3;
	resized = true;
	open = false;
}
