CC = g++
OPT = -O3
#OPT = -g
WARN = -Wall
CFLAGS = $(OPT) $(WARN) $(INC) $(LIB)

# List all .cpp files here
SIM_SRC = src/main.cpp src/predictors/BimodalPredictor.cpp src/predictors/GsharePredictor.cpp src/predictors/SmithPredictor.cpp

# now generate the object file names
SIM_OBJ  = src/main.o src/predictors/BimodalPredictor.o src/predictors/GsharePredictor.o src/predictors/SmithPredictor.o

all: sim
	@echo "my work is done here..."


# rule for making sim_cache

sim: $(SIM_OBJ)
	$(CC) -o sim $(CFLAGS) $(SIM_OBJ) -lm
	@echo "-----------DONE WITH SIM_CACHE-----------"


# generic rule for converting any .cc file to any .o file

.cc.o:
	$(CC) $(CFLAGS)  -c $*.cpp


# type "make clean" to remove all .o files plus the sim_cache binary

clean:
	rm -f *.o sim


# type "make clobber" to remove all .o files (leaves sim_cache binary)

clobber:
	rm -f *.o
