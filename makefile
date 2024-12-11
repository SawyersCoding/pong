CC=g++
CFLAGS=-g -Wall -lm
INCLUDE=-Iinclude

EXE=pong
LIBS=-lglfw

# All source files
SRC=src/main.cpp

# All object files
OBJ=$(SRC:src/%.cpp=bin/obj/%.o)
OBJ:=$(OBJ:src/%.c=bin/obj/%.o)

# Compile pong
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