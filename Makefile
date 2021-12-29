OBJS = template.cpp
OBJ_NAME = template

CC = g++

INCLUDE_PATHS = -IC:\CodingLibs\CPP\SDL\include\SDL2 -IC:\CodingLibs\CPP\JSON
LIBRARY_PATHS = -LC:\CodingLibs\CPP\SDL\lib

COMPILER_FLAGS = -w -Wl,-subsystem,windows
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2

all : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o Build/$(OBJ_NAME) \
	&& cd Build && .\$(OBJ_NAME).exe