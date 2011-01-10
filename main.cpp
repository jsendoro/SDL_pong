/************************************************************************** 
	This source code contain some codes taken from Lazy Foo' SDL 
	tutorial lesson 17 http://lazyfoo.net/SDL_tutorials/lesson17/index.php
**************************************************************************/

//The headers
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
#include "Timer.h"
#include "PongBall.h"
#include "PongBat.h"

//Screen attributes
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

//The frame rate
const int FRAMES_PER_SECOND = 30;

//The attributes of the square
const int SQUARE_WIDTH = 10;
const int SQUARE_HEIGHT = 10;

//The surfaces
SDL_Surface *ball = NULL;
SDL_Surface *screen = NULL;
SDL_Surface *left_bat = NULL;
SDL_Surface *right_bat = NULL;
SDL_Surface *pong_board = NULL;

//The event structure
SDL_Event event;

SDL_Surface *load_image( std::string filename )
{
	//The image that's loaded
	SDL_Surface* loadedImage = NULL;

	//The optimized surface that will be used
	SDL_Surface* optimizedImage = NULL;

	//Load the image
	loadedImage = IMG_Load( filename.c_str() );

	//If the image loaded
	if( loadedImage != NULL )
	{
		//Create an optimized surface
		optimizedImage = SDL_DisplayFormat( loadedImage );

		//Free the old surface
		SDL_FreeSurface( loadedImage );

		//If the surface was optimized
		if( optimizedImage != NULL )
		{
			//Color key surface
			SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF ) );
		}
	}

	//Return the optimized surface
	return optimizedImage;
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
	//Holds offsets
	SDL_Rect offset;

	//Get offsets
	offset.x = x;
	offset.y = y;

	//Blit"images/pong_ball24_small.bmp"
	SDL_BlitSurface( source, clip, destination, &offset );
}

int check_sidecollision( SDL_Rect A, SDL_Rect B )
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = A.x;
	rightA = A.x + A.w;
	topA = A.y;
	bottomA = A.y + A.h;

	//Calculate the sides of rect B
	leftB = B.x;
	rightB = B.x + B.w;
	topB = B.y;
	bottomB = B.y + B.h;
	
	//If any of the sides from A are outside of B
	if( rightA <= leftB )
	{
		return false;
	}

	if( leftA >= rightB )
	{
		return false;
	}

	if( bottomA <= topB )
	{
		return false;
	}

	if( topA >= bottomB )
	{
		return false;
	}

	//If none of the sides from A are outside B
	return true;
}

bool init()
{
	//Initialize all SDL subsystems
	if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
	{
		return false;
	}

	//Set up the screen
	screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

	//If there was an error in setting up the screen
	if( screen == NULL )
	{
		return false;
	}
	
	//Set the window caption
	SDL_WM_SetCaption( "My pong", NULL );

	//If everything initialized fine
	return true;
}

bool load_files()
{
	//Load the ball image
	ball = load_image( "images/pong_ball24_small.bmp" );
	
	//Load the bat images
	left_bat = load_image( "images/left_bat24.bmp" );	
	right_bat = load_image( "images/right_bat24.bmp" );

	//If there was a problem in loading the ball
	if( ball == NULL || left_bat == NULL || right_bat == NULL )
	{
		return false;
	}

	//If everything loaded fine
	return true;
}

void clean_up()
{
	//Free the surface
	SDL_FreeSurface( ball );
	SDL_FreeSurface( left_bat );
	SDL_FreeSurface( right_bat );
	//SDL_FreeSurface( pong_board );
	
	//Quit SDL
	SDL_Quit();
}

int main( int argc, char* args[] )
{
	//Quit flag
	bool quit = false;
	
	//Game flag
	bool pause = true; //Pause flag
	bool lbat_moveup = false; //Left bat movement flag
	bool lbat_movedown = false; //Left bat movement flag  
	bool rbat_moveup = false; //Right bat movement flag 
	bool rbat_movedown = false; //Right bat movement flag 
	//bool side_collision = false //Side collision flag
	//bool topdown_collision = false //Side collision flag

	//The ball
	PongBall pball;

	//The bats
	PongBat lbat( 20, 200, 15, 90, 90.0 );
	PongBat rbat( 605, 200, 15, 90, 90.0 );

	//The frame rate regulator
	Timer fps;

	//Initialize
	if( init() == false ){ return 1; }

	//Load the files
	if( load_files() == false ){ return 1; }

	//While the user hasn't quit
	while( quit == false )
	{
		//Start the frame timer
		fps.start();

		//While there's events to handle
		while( SDL_PollEvent( &event ) )
		{
			//If a key was pressed
			if( event.type == SDL_KEYDOWN )
			{
				//Pause the ball
				if( event.key.keysym.sym == SDLK_SPACE )
				{
					if( pause )
					{
						pball.unsuspend();
						pause = false;
					}
					else
					{
						pball.suspend();
						pause = true;
					}
				}

				//Set the flag for bat movement
				if( event.key.keysym.sym == SDLK_s )
					lbat_movedown = true;
				else if( event.key.keysym.sym == SDLK_w )
					lbat_moveup = true;
				if( event.key.keysym.sym == SDLK_UP ) 
					rbat_moveup = true;
				else if( event.key.keysym.sym == SDLK_DOWN )
					rbat_movedown = true;
			}

			//If a key was pressed
			if( event.type == SDL_KEYUP )
			{
				//Set the flag for bat movement
				if( event.key.keysym.sym == SDLK_s )
					lbat_movedown = false;
				else if( event.key.keysym.sym == SDLK_w )
					lbat_moveup = false;
				if( event.key.keysym.sym == SDLK_UP ) 
					rbat_moveup = false;
				else if( event.key.keysym.sym == SDLK_DOWN )
					rbat_movedown = false;
			}

			//If the user has Xed out the window
			if( event.type == SDL_QUIT )
			{
				//Quit the program
				quit = true;
			}
		}
				
		//Move the bat
		if( lbat_moveup )
			lbat.moveUp();
		else if( lbat_movedown )
			lbat.moveDown();
		if( rbat_moveup )
			rbat.moveUp();
		else if( rbat_movedown )
			rbat.moveDown();			
		
		//Move the ball
		pball.move();

		//Check if the ball hit the bats 
		if( check_sidecollision( pball.getCollisionBox(), lbat.getCollisionBox() ) or 
				check_sidecollision( pball.getCollisionBox(), rbat.getCollisionBox() ) )
		{
			pball.sidecollision();
		}		

    //Fill the screen white
    SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );

		//Show the ball on the screen
		apply_surface( pball.getCoordX(), pball.getCoordY(), ball, screen );
		
		//Show the bats on the screen
		apply_surface( lbat.getCoordX(), lbat.getCoordY(), left_bat, screen );
		apply_surface( rbat.getCoordX(), rbat.getCoordY(), right_bat, screen );

		//Update the screen
		if( SDL_Flip( screen ) == -1 ){ return 1; }

		//Cap the frame rate
		if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
		{
			SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
		}
	}

	//Clean up
	clean_up();

	return 0;
}
