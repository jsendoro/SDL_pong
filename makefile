all: pong

Timer.o: Timer.cpp Timer.h
	g++ -c Timer.cpp Timer.h

PongBat.o: PongBat.cpp PongBat.h
	g++ -c PongBat.cpp PongBat.h

PongBall.o: PongBall.cpp PongBall.h
	g++ -c PongBall.cpp PongBall.h

main.o: main.cpp
	g++ -c main.cpp

pong: main.o Timer.o PongBat.o PongBall.o
	g++ main.o Timer.o PongBat.o PongBall.o -o pong -lSDL -lSDL_image -lSDL_ttf

clean:
	rm -rf *o pong
