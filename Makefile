CC := clang
SOURCES := src/main.c src/game.c src/sdl_interface.c
OBJECTS := $(SOURCES:src/%.c=build/%.o)
CFLAGS := -Isrc -Iinclude `sdl2-config --cflags`
WARN :=  -Wall -Werror -Wextra
LDFLAGS := `sdl2-config --libs` -lSDL2_image
TARGET := build/flappybird

.PHONY: all clean

all: clean $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $^ -o $@ $(LDFLAGS) $(WARN)

build/%.o: src/%.c build
	$(CC) -c $< -o $@ $(CFLAGS) $(WARN)

build:
	@mkdir -p build

clean:
	@rm -rf build
