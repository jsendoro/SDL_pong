/************************************************************************** 
	This source code contain some codes taken from Lazy Foo' SDL 
	tutorial lesson 17 http://lazyfoo.net/SDL_tutorials/lesson17/index.php
**************************************************************************/

//The headers
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
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
SDL_Surface *left_score = NULL;
SDL_Surface *right_score = NULL;
SDL_Surface *pong_board = NULL;

//The event structure
SDL_Event event;

//The font
TTF_Font *font = NULL;

//The color of the font
SDL_Color textColor = { 0x0, 0x0, 0x0 };

//SDL_Color textColor = { 0xFF, 0xFF, 0xFF }; //Debug
int temp_posX = 200;

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

	SDL_BlitSurface( source, clip, destination, &offset );
}

bool check_sidecollision( SDL_Rect A, SDL_Rect B )
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
	
	if( ( topA < topB && bottomA < bottomB ) || ( topA > topB && bottomA > bottomB ) )
		return false;
	else
	{
		//If any of the sides from A are outside of B
		if( rightA <= leftB )
		{
			return false;
		}

		if( leftA >= rightB )
		{
			return false;
		}

		//If none of the sides from A are outside B
		return true;
	}
}

bool check_topdowncollision( SDL_Rect A, SDL_Rect B )
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
	
	if( ( leftA < leftB && rightA < rightB ) || ( leftA > leftB && rightA > rightB ) )
		return false;
	else
	{
		//If any of the sides from A are outside of B
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
	if( screen == NULL ){ return false;	}
	
	//Initialize SDL_ttf 
	if( TTF_Init() == -1 ){ return false; } 
	
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
	
	//Open the font 
	font = TTF_OpenFont( "font/Arena_Black.ttf", 28 ); 

	//If there was a problem in loading the ball
	if( ball == NULL || left_bat == NULL || right_bat == NULL || font == NULL )
	{
		return false;
	}
	
	//If everything loaded fine
	return true;
}

void clean_up()
{
	//Free the surfaceleft_score
	SDL_FreeSurface( ball );
	SDL_FreeSurface( left_bat );
	SDL_FreeSurface( right_bat );
	SDL_FreeSurface( left_score );
	SDL_FreeSurface( right_score );
	SDL_FreeSurface( pong_board );
	
	//Quit SDL
	SDL_Quit();
}

int main( int argc, char* argv[] )
{
	//Debug flag
	bool debug;
	if( argv[1] == "-d" )
		debug = true;
	else
		debug = false;

	//Quit flag
	bool quit = false;
	
	//Game flag
	bool lbat_moveup = false; //Left bat movement flag
	bool lbat_movedown = false; //Left bat movement flag  
	bool rbat_moveup = false; //Right bat movement flag 
	bool rbat_movedown = false; //Right bat movement flag 
	
	//The ball
	PongBall pball;

	//The bats
	PongBat lbat( 20, 200, 15, 90, 90.0 );
	PongBat rbat( 605, 200, 15, 90, 90.0 );
	
	//The score
	int lscore = 0;
	int rscore = 0;
	std::string scorestring[] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };	

	//The frame rate regulator
	Timer fps;

	//Initialize
	if( init() == false ){ return 1; }

	//Load the files
	if( load_files() == false ){ return 1; }
	
	if( debug )
	{
		textColor.r = 0xFF;
		textColor.g = 0xFF;
		textColor.b = 0xFF;
	}
	left_score = TTF_RenderText_Solid( font, scorestring[lscore].c_str(), textColor );
	right_score = TTF_RenderText_Solid( font, scorestring[rscore].c_str(), textColor );

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
					if( pball.getMotion() )
					{
						pball.suspend();
						pball.setMotion( false );
					}
					else
					{
						pball.unsuspend();
						pball.setMotion( true );
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

			//If a key was released
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
				
		//Movement of the ball
		pball.move();
		//Adjust the score
		if( pball.getOutRight() )
		{
			if( rscore <= 9 )
				lscore += 1;
			if( lscore > 9 )
			{
				left_score = TTF_RenderText_Solid( font, "You Win", textColor );
				right_score = TTF_RenderText_Solid( font, "You Lose", textColor );						
				//break;
				//Show the winning message to the screen
				temp_posX = 150;
			}
			else if( rscore <= 9 )
			{
				left_score = TTF_RenderText_Solid( font, scorestring[lscore].c_str(), textColor );
			}
			pball.setAngle( 135.0 );
		}
		if( pball.getOutLeft() )
		{
			if( lscore <= 9 )
				rscore += 1;
			if( rscore > 9 )
			{
				right_score = TTF_RenderText_Solid( font, "You Win", textColor );
				left_score = TTF_RenderText_Solid( font, "You Lose", textColor );
				//break;
				//Show the winning message to the screen
				temp_posX = 120;
			}
			else if( lscore <= 9 )
				right_score = TTF_RenderText_Solid( font, scorestring[rscore].c_str(), textColor );
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
	
		//Check if the ball hit the bats from the sides
		if( check_sidecollision( pball.getCollisionBox(), lbat.getCollisionBox() ) || check_sidecollision( pball.getCollisionBox(), rbat.getCollisionBox() ) )
		{
			pball.sidecollision();
		}		

		//Check if the ball hit the bats from top or bottom
		if( check_topdowncollision( pball.getCollisionBox(), lbat.getCollisionBox() ) || check_topdowncollision( pball.getCollisionBox(), rbat.getCollisionBox() ) )
		{
			//Undo movement the bat
			if( lbat_moveup )
				lbat.moveDown();
			else if( lbat_movedown )
				lbat.moveUp();

			if( rbat_moveup )
				rbat.moveDown();
			else if( rbat_movedown )
				rbat.moveUp();			

			pball.topdowncollision();
		}

    //Fill the screen white
		//if( debug )
    	SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0x0, 0x0, 0x0 ) ); //Debug
		//else
	    //SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) ); //White

		//Show the ball on the screen
		apply_surface( pball.getCoordX(), pball.getCoordY(), ball, screen );
		
		//Show the bats on the screen
		apply_surface( lbat.getCoordX(), lbat.getCoordY(), left_bat, screen );
		apply_surface( rbat.getCoordX(), rbat.getCoordY(), right_bat, screen );

		//Show the score on the screen
		apply_surface( temp_posX, 50, left_score, screen );	
		apply_surface( 420, 50, right_score, screen );

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
