# default compiler
CC=gcc

# name of the files to be included in the program ______ ADD THE NAME OF YOUR FILES YOU WISH TO INCLUDE IN THE PROGRAM
FILES=main ReadProductFile
# Binary file name, program name
_BINARY=out
# make a list of C files
_CFILES=$(addsuffix .c,$(FILES))
# make a list of Object (assembly) files
_OBJECTS=$(addsuffix .o,$(FILES))

# path from makefile to C files
CFILES_DIR=./src
# path from makefile to Object (assembly) files
OBJECTS_DIR=./build
# path from makefile to Binary (executable) files
BINARY_DIR=./bin

# make a list of objects and add path to them
# e.g.
# ./build/main.o
OBJECTS=$(patsubst %,$(OBJECTS_DIR)/%,$(_OBJECTS))
# add path to the binary file
# ./bin/out
BINARY=$(addprefix $(BINARY_DIR)/,$(_BINARY))

# PHONY helps to specify that "all" is NOT a file
# therefore it will work even if there is a file named "all" and it is up to date
.PHONY: all
# all depends on binary file
all: $(BINARY)

# if objects are up to date, and binary dir exists - compile the binary file
# else go to objects or binary_dir
$(BINARY): $(OBJECTS) | $(BINARY_DIR)
# compile all object files in the binary
	$(CC) $^ -o $@

# if c files are NOT up to date and object dir exists - compile c files to object files
# else go to c files or object_dir
$(OBJECTS_DIR)/%.o: $(CFILES_DIR)/%.c | $(OBJECTS_DIR)
	$(CC) -c $< -o $@

# if directories do NOT exist - create them
$(BINARY_DIR) $(OBJECTS_DIR):
	mkdir $@

# if a c file does NOT exist - display the error and exit script
$(CFILES_DIR)/%.c:
	@echo Error, couldn't find the file: $@
	exit 1

# PHONY helps to specify that "clean" is NOT a file
# therefore it will work even if there is a file named "clean" and it is up to date
.PHONY: clean
clean:
# remove directories of object and binary files
	rmdir /s /q $(subst ./,,$(OBJECTS_DIR)) $(subst ./,,$(BINARY_DIR))