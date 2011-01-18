/*	PongBall Class */

#include "SDL/SDL.h"

#ifndef PONGBALL_H
#define PI 3.1415926535897932384626433832795
#define PONGBALL

class PongBall
{
private:
	SDL_Rect box; //Collision box
	double myAngle;
	double mySpeed;
	int myRadius;
	int xVel;
	int yVel;
	bool motion;

public:
	//Constructor - Initialize variables
	PongBall();

	//Get - Set functions
	int getCoordX();
	void setCoordX( int x );
	int getCoordY();
	void setCoordY( int y );
	double getAngle();
	void setAngle( double angle );
	double getSpeed();
	void setSpeed( double speed );
	int getRadius();
	void setRadius( int radius );

	//Public functions
	double getDirX();
	double getDirY();
	double getSpeedX();
	double getSpeedY();
	bool outOfYBound( int minY, int maxY );	
	bool outOfXBound( int minX, int maxX );
	void move();
	void suspend();
	void unsuspend();
	void sidecollision();
	void topdowncollision();
	SDL_Rect getCollisionBox();
};

#endif
