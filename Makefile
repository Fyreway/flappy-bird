CC := clang
SOURCES := src/main.c
OBJECTS := $(SOURCES:src/%.c=build/%.o)
CFLAGS := -Isrc -Iinclude $(sdl2-config --cflags)
WARN :=  -Wall -Werror -Wextra
LDFLAGS := $(sdl2-config --libs)
TARGET := build/flappybird

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $^ -o $@ $(LDFLAGS) $(WARN)

build/%.o: src/%.c
	$(CC) -c $< -o $@ $(CFLAGS) $(WARN)
