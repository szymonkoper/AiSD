 
make: LENLCS

LENLCS: LENLCS.o
	g++ -Wall -W -O2 -static -lm LENLCS.o -o LENLCS
	

LENLCS.o: LENLCS.cpp
	g++ -Wall -W -O2 -static -lm LENLCS.cpp -c

clean:
	rm -f *.o LENLCS
