#OBJS All c or cpp files
OBJS =  main.cpp ../blue-tile-engine-lite/glad.c

#CC Which Compiler to use.
CC = g++

#COMPILER_FLAGS Other include files
# -w suppresses all warnings
COMPILER_FLAGS = -I../libraries/includes -I../blue-tile-engine-lite/ -L../libraries/libs

#LINKER_FLAGS Specifies the libraries to link against
LINKER_FLAGS = -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl

#OBJ_NAME The name of the output file
OBJ_NAME = sigils-of-outri

#The Make commands
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) blue-tiles-engine-lite.a $(LINKER_FLAGS) -o $(OBJ_NAME)

clean:	
	rm sigils-of-outri