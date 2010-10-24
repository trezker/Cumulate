#include "file.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <iostream>
#include <sinxml/sinxml.h>

File::File(Platforms& iplatforms, ALLEGRO_FONT* ifont)
:platforms(&iplatforms),
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
	
	sinxml::Document doc("1.0");
	if(!doc.Load_file(filename))
		return;
	sinxml::Children& mapchildren = doc.Get_root()->Get_children();
	for(sinxml::Children::iterator i = mapchildren.begin(); i != mapchildren.end(); ++i)
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
