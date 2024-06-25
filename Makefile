main: main.cpp
	g++ -Wall -Werror main.cpp -o main

clean:
	rm -f main *~ *.o