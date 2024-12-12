CC=g++
CFLAGS=-g -Wall -lm
INCLUDE=-Iinclude

EXE=pong
LIBS=-lglfw

# All source files
SRC=src/main.cpp src/model/pong.cpp src/view/pongview.cpp src/view/glad.c src/view/paddleview.cpp src/view/ballview.cpp src/view/shader/shader.cpp src/controller/pongcontroller.cpp

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