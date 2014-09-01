all: life life_gui 

life_gui:
	qmake-qt4 -makefile -o gui-makefile life_gui.pro; make -f gui-makefile;
clean:
	rm -f *.o life temp.txt  gui-makefile life_gui

life: chars.o board.o cell.o initial.o colors.o fileinfo.o flags.o life.o name.o terrain.o window.o parse.o rule.o
	g++ -o life chars.o board.o cell.o initial.o colors.o fileinfo.o flags.o life.o name.o terrain.o window.o parse.o rule.o

chars.o: chars.cpp
	g++ -c chars.cpp

board.o: board.cpp
	g++ -c board.cpp

cell.o: cell.cpp
	g++ -c cell.cpp

initial.o: initial.cpp
	g++ -c initial.cpp

colors.o: colors.cpp
	g++ -c colors.cpp

fileinfo.o: fileinfo.cpp
	g++ -c fileinfo.cpp

flags.o: flags.cpp
	g++ -c flags.cpp

life.o: life.cpp
	g++ -c life.cpp

name.o: name.cpp
	g++ -c name.cpp

window.o: window.cpp
	g++ -c window.cpp

parse.o: parse.cpp
	g++ -c parse.cpp

terrain.o: terrain.cpp
	g++ -c terrain.cpp

rule.o: rule.cpp
	g++ -c rule.cpp
