CC := g++
CFLAGS := -std=c++11

all : Mandelbrot

Mandelbrot : Mandelbrot.o Fonctions.o 
	$(CC) $(CFLAGS) -fopenmp -o $@  $^

%.o : %.cpp
	$(CC) $(CFLAGS) -fopenmp -o $@ -c $< 

clean:
	rm -f *.o *~ Mandelbrot



