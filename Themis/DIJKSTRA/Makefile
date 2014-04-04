 
make: DIJKSTRA

DIJKSTRA: DIJKSTRA.o
	g++ -Wall -W -O2 -static -lm DIJKSTRA.o -o DIJKSTRA
	

DIJKSTRA.o: DIJKSTRA.cpp
	g++ -Wall -W -O2 -static -lm DIJKSTRA.cpp -c

clean:
	rm -f *.o DIJKSTRA
