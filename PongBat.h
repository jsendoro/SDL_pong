/*	PongBat Class */

#include "SDL/SDL.h"

#ifndef PONGBAT_H
#define PI 3.1415926535897932384626433832795
#define PONGBAT

class PongBat
{
private:
	SDL_Rect box; //Collision box
	double myAngle;

public:
	//Constructor - Initialize variables
	PongBat();
	PongBat( int startX, int startY, int width, int length, double angle );

	//Get - Set functions
	int getCoordX();
	void setCoordX( int x );
	int getCoordY();
	void setCoordY( int y );
	int getWidth();
	void setWidth( int width );
	int getHeight();
	void setHeight( int height );
	double getAngle();
	void setAngle( double angle );

	//Public functions
	double getDestX();
	double getDestY();
	void moveUp();
	void moveDown();
	//void handleInput( SDL_Event event );
	SDL_Rect getCollisionBox();
};

#endif
