 
make: BELLMAN

BELLMAN: BELLMAN.o
	g++ -Wall -W -O2 -static -lm BELLMAN.o -o BELLMAN
	

BELLMAN.o: BELLMAN.cpp
	g++ -Wall -W -O2 -static -lm BELLMAN.cpp -c

clean:
	rm -f *.o BELLMAN
