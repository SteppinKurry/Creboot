#OBJS specifies which files to compile as part of the project
OBJS = qmenu.c creboot.c

#CC specifies which compiler we're using
CC = gcc

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -Wall

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = 

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = creboot

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
	#./$(OBJ_NAME)
