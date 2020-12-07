CC = g++
CFLAGS = -g -Wall -lOpenGL -lGLU -lglfw -lglad -lSOIL -lfreeimage
OBJ = main.o game.o resource_manager.o terrain_renderer.o terrain.o shader.o texture.o camera.o

universalis: $(OBJ)
	$(CC) $(CFLAGS) -o universalis $(OBJ)

main.o: main.cpp
	$(CC) -g -c main.cpp
game.o: game.cpp game.h
	$(CC) -g -c game.cpp
resource_manager.o: resource_manager.cpp resource_manager.h
	$(CC) -g -c resource_manager.cpp
terrain_renderer.o: terrain_renderer.cpp terrain_renderer.h
	$(CC) -g -c terrain_renderer.cpp
terrain.o: terrain.cpp terrain.h
	$(CC) -g -c terrain.cpp
shader.o: shader.cpp shader.h
	$(CC) -g -c shader.cpp
texture.o: texture.cpp texture.h
	$(CC) -g -c texture.cpp
camera.o: camera.cpp camera.h
	$(CC) -g -c camera.cpp

clean:
	rm -f *.o universalis