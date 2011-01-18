#include "PongBall.h"
#include <iostream>
#include <math.h>

/* Constructor */
PongBall::PongBall()
{
	myAngle = 30.0;
	mySpeed = 0;
	myRadius = 5;
	//Initialize the velocity
	xVel = 0;
	yVel = 0;
	motion = false;
	//Initialize the offsets
	box.x = 400;
	box.y = 250;
	//Set the square's dimentions
	box.w = 2 * myRadius;
	box.h = 2 * myRadius;
}

/* Get - Set functions */ 
int PongBall::getCoordX()
{
	return box.x;
}

void PongBall::setCoordX( int x )
{
	box.x = x;
}

int PongBall::getCoordY()
{
	return box.y;
}

void PongBall::setCoordY( int y )
{
	box.y = y;
}

double PongBall::getAngle()
{
	return myAngle;
}

void PongBall::setAngle( double angle )
{
	myAngle = angle;
}

double PongBall::getSpeed()
{
	return mySpeed;
}

void PongBall::setSpeed( double speed )
{
	mySpeed = speed;
}

int PongBall::getRadius()
{
	return myRadius;
}

void PongBall::setRadius( int radius )
{
	myRadius = radius;
}
	
/* Public functions */
double PongBall::getDirX()
{
	/*if( motion )
	{
		std::cout << "getDirX() = cos( myAngle * 3.14 / 180 ) = " << cos( myAngle * 3.1415926535897932384626433832795 / 180 ) << std::endl;
		std::cout << "getDirX() = cos( myAngle * PI / 180 ) = " << cos( myAngle * PI / 180 ) << std::endl; 
	}*/
	return cos( myAngle * PI / 180 );
}

double PongBall::getDirY()
{
	return sin( myAngle * PI / 180 );
}

double PongBall::getSpeedX()
{
	return( getDirX() * mySpeed / 10 );
}

double PongBall::getSpeedY()
{
	return( getDirY() * mySpeed / 10 );
}

bool PongBall::outOfYBound( int minY, int maxY )
{
	return( box.y + box.h > maxY || box.y < minY );
}

bool PongBall::outOfXBound( int minX, int maxX )
{
	return( box.x + box.w > maxX || box.x < minX );
}

void PongBall::move()
{
	/* Logic for deflection */
	if( outOfYBound( 0,480 ) ) 
	{
		myAngle = -1 * myAngle;
	}
	box.y -= getSpeedY();

	if( outOfXBound( 5,640 ) )
	{
		myAngle = ( 180.0 - myAngle );
		if( myAngle > 360.0 )
			myAngle -= 360.0;
	}
	box.x += getSpeedX();
	/* End of logic */
}

void PongBall::suspend()
{
	mySpeed = 0;
}

void PongBall::unsuspend()
{
	mySpeed = 50;
}

void PongBall::sidecollision()
{
	myAngle = ( 180.0 - myAngle );
	if( myAngle > 360.0 )
		myAngle -= 360.0;
	box.x += getSpeedX();
}

void PongBall::topdowncollision()
{
	myAngle = -1 * myAngle;
	box.y -= getSpeedY();
}

SDL_Rect PongBall::getCollisionBox()
{
	return box;
}
