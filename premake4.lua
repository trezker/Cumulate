
solution ("Cumulate")
	configurations { "Debug", "Release" }

	project ("Cumulate")
		kind "ConsoleApp"
		language "C++"
		location "build"
		files { "src/*.cpp" }
		links ( {"allegro", "allegro_image", "allegro_primitives", "Box2D", "sinxml"} )

		configuration "Debug"
			defines { "DEBUG" }
			flags { "Symbols" }
 
		configuration "Release"
			defines { "NDEBUG" }
			flags { "Optimize" }

	project ("Edit_cumulate")
		kind "ConsoleApp"
		language "C++"
		location "build/editor"
		files { "editor/*.cpp" }
		links ( {"allegro", "allegro_image", "allegro_primitives", "allegro_font", "allegro_ttf", "allegro_dialog", "sinxml"} )

		configuration "Debug"
			defines { "DEBUG" }
			flags { "Symbols" }
 
		configuration "Release"
			defines { "NDEBUG" }
			flags { "Optimize" }
