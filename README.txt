This is a simple SDL impelementation of pong game.

Some code are taken from from Lazy Foo' SDL tutorial lesson 17 ( http://lazyfoo.net/SDL_tutorials/lesson17/index.php ).
It has great tutorial about SDL library. Please visit the site if you want to know more about SDL.

This pong game is created as SDL learning purpose & created by hemogoblin( ex_hemogoblin (at) yahoo.com ).


to build the exe file:
- in UNIX: 
  1) install SDL & SDL_image library
	2) put all files (all *.cpp, *.h, makefile, and images folder) on the same folder 
	3) use makefile to build the .exe file (pong.exe)
- in WINDOWS: 
  1) download SDL & SDL_image library
	2) put all files (all *.cpp, *.h, makefile, and images folder) on the same folder  
	3) copy the *.dll file from those library to the same folder with above 
	4) change the include statement from 'SDL/SDL.h' & 'SDL/SDL_image.h' to 'SDL.h' & 'SDL_image.h'
	5) use nmake to build the .exe file (pong.exe)
  6) If you use IDE (Visual C++, Eclipse, Dev C++, etc) see Lazy Foo' SDL tutorial to set it up (http://lazyfoo.net/SDL_tutorials/lesson01/index.php)

		
GAME CONTROL:
'W' / 'S'     -- move the left bat up & down
'Up' / 'Down' -- move the right bat up & down
'Space'       -- suspend the ball

