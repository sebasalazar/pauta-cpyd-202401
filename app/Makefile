CXX = g++
CXXFLAGS = -g3 -Wall -std=c++14 -fopenmp
MKDIR = mkdir -p

LIBS = -lm

directorios:
	$(MKDIR) build dist

utem.o: directorios utem.cpp
	$(CXX) $(CXXFLAGS) -c utem.cpp -o build/utem.o

year_month.o: directorios year_month.cpp
	$(CXX) $(CXXFLAGS) -c year_month.cpp -o build/year_month.o

producto.o: directorios producto.cpp
	$(CXX) $(CXXFLAGS) -c producto.cpp -o build/producto.o

main.o: directorios main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o build/main.o

all: clean main.o producto.o year_month.o utem.o
	$(CXX) $(CXXFLAGS) -o dist/programa \
	build/main.o build/producto.o \
	build/year_month.o build/utem.o \
	$(LIBS)
	rm -fr build

clean:
	rm -fr *.o a.out core programa dist build

.DEFAULT_GOAL := all
