# Copyright 2019 SMS
# License(Apache-2.0)
# Makefile

SRC = $(wildcard ./*.cpp)
OBJ = $(patsubst %.cpp, %.o, $(SRC))

himconsole : $(OBJ)
	g++ $(OBJ) -o himconsole

$(OBJ) : $(SRC)
	g++ -c $(SRC) -o $(OBJ)
