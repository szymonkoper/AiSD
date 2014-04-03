 
make: MST

MST: MST.o
	g++ -Wall -W -O2 -static -lm MST.o -o MST
	

MST.o: MST.cpp
	g++ -Wall -W -O2 -static -lm MST.cpp -c

clean:
	rm -f *.o MST
