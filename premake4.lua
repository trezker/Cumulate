
solution ("Cumulate")
	configurations { "Debug", "Release" }

	project ("common")
		kind "StaticLib"
		language "C++"
		location "build"
		files { "common/*.cpp" }
		targetdir "build/lib"

		configuration "Debug"
			defines { "DEBUG" }
			flags { "Symbols" }
 
		configuration "Release"
			defines { "NDEBUG" }
			flags { "Optimize" }

	project ("Cumulate")
		kind "ConsoleApp"
		language "C++"
		location "build"
		files { "game/*.cpp" }
		links ( {"allegro", "allegro_image", "allegro_primitives", "allegro_font", "allegro_ttf", "Box2D", "sinxml", "common", "lua5.1" } )
		includedirs { "common" }

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
		links ( {"allegro", "allegro_image", "allegro_primitives", "allegro_font", "allegro_ttf", "allegro_dialog", "sinxml", "common"} )
		includedirs { "common" }

		configuration "Debug"
			defines { "DEBUG" }
			flags { "Symbols" }
 
		configuration "Release"
			defines { "NDEBUG" }
			flags { "Optimize" }
