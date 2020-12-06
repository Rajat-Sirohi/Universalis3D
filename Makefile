CC = g++
CFLAGS = -g -Wall -lOpenGL -lGLU -lglfw -lglad -lSOIL -lfreeimage
OBJ = camera.o game.o game_object.o main.o resource_manager.o shader.o sprite_renderer.o texture.o

universalis: $(OBJ)
	$(CC) $(CFLAGS) -o universalis $(OBJ)

camera.o: camera.cpp camera.h
	$(CC) -g -c camera.cpp
game.o: game.cpp game.h
	$(CC) -g -c game.cpp
game_object.o: game_object.cpp game_object.h
	$(CC) -g -c game_object.cpp
main.o: main.cpp
	$(CC) -g -c main.cpp
resource_manager.o: resource_manager.cpp resource_manager.h
	$(CC) -g -c resource_manager.cpp
shader.o: shader.cpp shader.h
	$(CC) -g -c shader.cpp
sprite_renderer.o: sprite_renderer.cpp sprite_renderer.h
	$(CC) -g -c sprite_renderer.cpp
texture.o: texture.cpp texture.h
	$(CC) -g -c texture.cpp

clean:
	rm -f *.o universalis