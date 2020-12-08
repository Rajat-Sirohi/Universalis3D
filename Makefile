CC = g++
CFLAGS = -g -Wall -lOpenGL -lGLU -lglfw -lglad -lSOIL -lfreeimage
OBJ = main.o game.o resource_manager.o game_object.o terrain.o mesh.o shader.o texture.o camera.o

universalis: $(OBJ)
	$(CC) $(CFLAGS) -o universalis $(OBJ)

main.o: main.cpp
	$(CC) -g -c main.cpp
game.o: game.cpp game.h
	$(CC) -g -c game.cpp
resource_manager.o: resource_manager.cpp resource_manager.h
	$(CC) -g -c resource_manager.cpp
game_object.o: game_object.cpp game_object.h
	$(CC) -g -c game_object.cpp
terrain.o: terrain.cpp terrain.h
	$(CC) -g -c terrain.cpp
mesh.o: mesh.cpp mesh.h
	$(CC) -g -c mesh.cpp
shader.o: shader.cpp shader.h
	$(CC) -g -c shader.cpp
texture.o: texture.cpp texture.h
	$(CC) -g -c texture.cpp
camera.o: camera.cpp camera.h
	$(CC) -g -c camera.cpp

clean:
	rm -f *.o universalis