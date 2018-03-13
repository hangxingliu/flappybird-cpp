del dist\game.o
del dist\game.exe
mingw32-g++ -O -I%cd%\SDL2\include\SDL2 -c src\main.c -o dist\game.o 
mingw32-g++ -L%cd%\SDL2\lib -o dist\game.exe dist\game.o -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf
