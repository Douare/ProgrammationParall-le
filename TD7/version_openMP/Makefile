CXX = g++
SRC= $(wildcard *.cpp)
OBJ= $(SRC:.cpp=.o)
EXEC= main

%.o :%.cpp
	$(CXX) -fopenmp -o $@ -c $< 

main : $(OBJ) 
	$(CXX) -fopenmp -o $@ $^

.PHONY: clean mrproper

clean:
	@rm -rf *.o

mrproper: clean
	@rm -rf $(EXEC)
