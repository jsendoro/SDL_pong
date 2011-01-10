#include "PongBat.h"
#include <iostream>
#include <math.h>

/* Constructor */
PongBat::PongBat()
{
	//Initialize the offsets
	box.x = 0;
	box.y = 0;
	//Set the square's dimentions
	box.w = 0;
	box.h = 0;
	myAngle = 0.0;
}

PongBat::PongBat( int startX, int startY, int width, int length, double angle )
{
	//Initialize the offsets
	box.x = startX;
	box.y = startY;
	//Set the square's dimentions
	box.w = width;
	box.h = length;
	myAngle = angle;
}

/* Get - Set functions */ 
int PongBat::getCoordX()
{
	return box.x;
}

void PongBat::setCoordX( int x )
{
	box.x = x;
}

int PongBat::getCoordY()
{
	return box.y;
}

void PongBat::setCoordY( int y )
{
	box.y = y;
}

int PongBat::getWidth()
{
	return box.w;
}

void PongBat::setWidth( int width )
{
	box.w = width;
}

int PongBat::getHeight()
{
	return box.w;
}

void PongBat::setHeight( int height )
{
	box.h = height;
}

double PongBat::getAngle()
{
	return myAngle;
}

void PongBat::setAngle( double angle )
{
	myAngle = angle;
}

//Public functions
double PongBat::getDestX()
{
	return box.x + box.h * cos( myAngle * PI / 180.0 );
}

double PongBat::getDestY()
{
	return box.y - box.h * sin( myAngle * PI / 180.0 );
}

void PongBat::moveUp()
{
	if( box.y > 0)
		box.y -= 5;
}

void PongBat::moveDown()
{
	if( box.y + box.h < 480 )
		box.y += 5;
}

SDL_Rect PongBat::getCollisionBox()
{
	return box;
}
