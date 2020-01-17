# Copyright 2019 SMS
# License(Apache-2.0)
# Makefile

.PHONY:clean

SRC = $(wildcard ./*.cpp)
OBJ = $(patsubst %.cpp, %.o, $(SRC))


himconsole : $(OBJ)
	g++ $(OBJ) -o himconsole

console.o : console.cpp console.h print.h
	g++ -c $< -o $@

command.o : command.cpp command.h
	g++ -c $< -o $@

himconsole.o : himconsole.h console.h
	g++ -c $< -o $@

print.o : print.h attribute.h
	g++ -c $< -o $@

attribute.o : attribute.h
	g++ -c $< -o $@

localization.o : localization.h
	g++ -c $< -o $@


clean:
	rm -rf *.o himconsole
