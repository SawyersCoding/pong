CC=g++
CFLAGS=-g -Wall -lm
INCLUDE=-Iinclude

EXE=pong
LIBS=-lglfw -lsfml-audio

# All source files
SRC=src/main.cpp src/model/pong.cpp src/view/pong3dview.cpp src/view/glad.c src/view/staticquadtextureview.cpp src/view/rectangularprismview.cpp src/view/shader/shader.cpp src/view/digitview.cpp src/view/stb_image/stb_image.cpp src/view/audio/audioplayer.cpp src/controller/pongcontroller.cpp src/controller/playerpaddlecontroller.cpp src/controller/basicpaddlecontroller.cpp

# All object files
OBJ=$(SRC:src/%.cpp=bin/obj/%.o)
OBJ:=$(OBJ:src/%.c=bin/obj/%.o)

$(EXE): bin/$(EXE)

bin/$(EXE): $(OBJ) | bin
	$(CC) -o $@ $^ $(INCLUDE) $(LIBS) $(CFLAGS)

# Compile all object files
bin/obj/%.o: src/%.cpp | bin/obj
	mkdir -p $(dir $@)
	$(CC) -c $< -o $@ $(INCLUDE) $(CFLAGS)

bin/obj/%.o: src/%.c | bin/obj
	mkdir -p $(dir $@)
	$(CC) -c $< -o $@ $(INCLUDE) $(CFLAGS)

bin:
	mkdir -p $@

bin/obj:
	mkdir -p $@

clean:
	rm -rf bin