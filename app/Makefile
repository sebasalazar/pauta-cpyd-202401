CXX = g++
CXXFLAGS = -g3 -Wall -std=c++14 -fopenmp
MKDIR = mkdir -p
RM = rm -fr

LIBS = -lm ./xlsxio/lib/libxlsxio_read.a -lminizip -lexpat

directorios:
	$(RM) build dist tmp cpi
	$(MKDIR) build dist

utem.o: directorios utem.cpp
	$(CXX) $(CXXFLAGS) -c utem.cpp -o build/utem.o

cpi.o: directorios cpi.cpp
	$(CXX) $(CXXFLAGS) -c cpi.cpp -o build/cpi.o

year_month.o: directorios year_month.cpp
	$(CXX) $(CXXFLAGS) -c year_month.cpp -o build/year_month.o

product.o: directorios product.cpp
	$(CXX) $(CXXFLAGS) -c product.cpp -o build/product.o

summary.o: directorios summary.cpp
	$(CXX) $(CXXFLAGS) -c summary.cpp -o build/summary.o

main.o: directorios main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o build/main.o

all: clean main.o product.o year_month.o utem.o cpi.o summary.o
	$(CXX) $(CXXFLAGS) -o dist/programa \
	build/main.o build/product.o \
	build/year_month.o build/utem.o \
	build/cpi.o build/summary.o \
	$(LIBS)
	$(RM) build

clean:
	rm -fr *.o a.out core programa dist build tmp cpi

.DEFAULT_GOAL := all
