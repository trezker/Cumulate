
solution ("Cumulate")
	configurations { "Debug", "Release" }

	project ("Cumulate")
		kind "ConsoleApp"
		language "C++"
		location "build"
		files { "src/*.cpp" }
		links ( {"allegro", "allegro_image"} )

		configuration "Debug"
			defines { "DEBUG" }
			flags { "Symbols" }
 
		configuration "Release"
			defines { "NDEBUG" }
			flags { "Optimize" }
