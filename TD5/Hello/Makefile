CC := g++
CFLAGS := -std=c++11

all : Hello

Hello : Hello.o
	$(CC) $(CFLAGS) -fopenmp -o $@  $< 

%.o : %.cpp
	$(CC) $(CFLAGS) -fopenmp -o $@ -c $<

clean:
	rm -f *.o *~ Hello



