CC = g++
OPT = -O3
#OPT = -g
WARN = -Wall
CFLAGS = $(OPT) $(WARN) $(INC) $(LIB)

# List all .cpp files here
SIM_SRC = $(shell find src/ -type f -name '*.cpp' 2>/dev/null)

# now generate the object file names
SIM_OBJ  = $(SIM_SRC:%.cpp=%.o)

all: sim

sim: $(SIM_OBJ)
	$(CC) -o sim $(CFLAGS) $(SIM_OBJ) -lm

.cpp.o:
	$(CC) $(CLFAGS) -c $.cpp

clean:
	rm -f *.o sim

clobber:
	rm -f *.o
