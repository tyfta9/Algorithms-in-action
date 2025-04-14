CC=gcc
CFLAGS=

FILES=main ReadProductFile
_CFILES=$(addsuffix .c,$(FILES))
_OBJECTS=$(addsuffix .o,$(FILES))

CFILES_DIR=./src
OBJECTS_DIR=./build
BINARY=./bin/out

# e.g.
# ./build/main.o
OBJECTS=$(patsubst %,$(OBJECTS_DIR)/%,$(_OBJECTS))

all: $(BINARY)
	@echo bin: $(BINARY)

$(BINARY): $(OBJECTS)
	@echo objects: $^
	$(CC) $^ -o $@

$(OBJECTS_DIR)/%.o: $(CFILES_DIR)/%.c
	@echo cfiles: $<
	$(CC) -c $< -o $@

$(CFILES_DIR)/%.c:
	@echo Error, couldn't find file: $@
	exit 1

clean:
	rm -f $(OBJECTS_DIR)/*.o
# rm does not work for me for some reason