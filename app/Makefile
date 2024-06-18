CXX = g++
CXXFLAGS = -g3 -Wall -std=c++14 -fopenmp
MKDIR = mkdir -p
RM = rm -fr

LIBS = -lm

directorios:
	$(RM) build dist tmp ipc
	$(MKDIR) build dist

utem.o: directorios utem.cpp
	$(CXX) $(CXXFLAGS) -c utem.cpp -o build/utem.o

ipc.o: directorios ipc.cpp
	$(CXX) $(CXXFLAGS) -c ipc.cpp -o build/ipc.o

year_month.o: directorios year_month.cpp
	$(CXX) $(CXXFLAGS) -c year_month.cpp -o build/year_month.o

product.o: directorios product.cpp
	$(CXX) $(CXXFLAGS) -c product.cpp -o build/product.o

main.o: directorios main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o build/main.o

all: clean main.o product.o year_month.o utem.o ipc.o
	$(CXX) $(CXXFLAGS) -o dist/programa \
	build/main.o build/product.o \
	build/year_month.o build/utem.o \
	build/ipc.o \
	$(LIBS)
	$(RM) build

clean:
	rm -fr *.o a.out core programa dist build tmp ipc

.DEFAULT_GOAL := all
