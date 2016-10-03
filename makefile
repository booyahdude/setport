all: portsetter

portsetter:
	g++ -std=c++11 -o setport portsetter.cpp
	
clean:
	rm setport