 
make: MACIERZE

MACIERZE: MACIERZE.o
	g++ -Wall -W -O2 -static -lm MACIERZE.o -o MACIERZE
	

MACIERZE.o: MACIERZE.cpp
	g++ -Wall -W -O2 -static -lm MACIERZE.cpp -c

clean:
	rm -f *.o MACIERZE
