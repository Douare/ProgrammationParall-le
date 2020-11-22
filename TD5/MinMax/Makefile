CC := g++
CFLAGS := -std=c++11

all : MinMax

MinMax : MinMax.o
	$(CC) $(CFLAGS) -fopenmp -o $@  $< 

%.o : %.cpp
	$(CC) $(CFLAGS) -fopenmp -o $@ -c $<

clean:
	rm -f *.o *~ MinMax



