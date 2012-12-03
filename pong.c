// MACROS AND HEADERS {{{
#include <math.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

#define MINY 1
#define MAXY ( LINES - 1 )
// }}}

// STRUCTS {{{
typedef struct _paddle_part_struct
{
	int x; // X axis location.
	int y; // Y axis location.
} PART;

typedef struct _paddle_struct
{
	PART part_a;
	PART part_b;
	PART part_c;
} PADDLE;
// }}}

// FUNCTION PROTOTYPES {{{
void init_paddles( PADDLE *left, PADDLE *right );
void init_screen(); 
void c_printer( char * );
void paddle_builder( PADDLE *left, PADDLE *right );
void screen_bottom(int COLS );
// }}}

// FUNCTIONS {{{
void init_paddles ( PADDLE *left, PADDLE *right )
{
	// Left paddle
	left->part_a.x = 1;
	left->part_a.y = ( LINES - 4 ) / 2;

	left->part_b.x = 1;
	left->part_b.y = ( LINES - 4 ) / 2 + 1;

	left->part_c.x = 1;
	left->part_c.y = ( LINES - 4 ) / 2 + 2;

	// Right paddle
	right->part_a.x = COLS - 1;
	right->part_a.y = ( LINES - 4 ) / 2;

	right->part_b.x = COLS - 1,
	right->part_b.y = ( LINES - 4 ) / 2 + 1;

	right->part_c.x = COLS - 1,
	right->part_c.y = ( LINES - 4 ) / 2 + 2;
}

void init_screen()
{
	initscr();
	start_color();
	cbreak();
	keypad( stdscr, TRUE );
	noecho();
	clear(); 
}

void c_printer( char *s )
{
	int length;

	for ( length = 0; *( s + length ) != '\0'; ++length )
		;

	mvprintw( getcury( stdscr ), ( COLS - length ) / 2, "%s\n\n", s );
}

void paddle_builder ( PADDLE *left, PADDLE *right )
{
	mvprintw( right->part_a.y, right->part_a.x, "|" );
	mvprintw( right->part_b.y, right->part_b.x, "|" );
	mvprintw( right->part_c.y, right->part_c.x, "|" );

	mvprintw( left->part_a.y, left->part_a.x,"|" );
	mvprintw( left->part_b.y, left->part_b.x,"|" );
	mvprintw( left->part_c.y, left->part_c.x,"|" );
}

void screen_bottom (int COLS )
{
	int x;

	for( x = 0; x <= COLS; ++x ) // <= or just <?
		mvprintw( MAXY - 1, x, "_" );
	mvprintw( MAXY, ( COLS - sizeof( "Press F1 to end." ) ) / 2, "Press F1 to end." );
}
// }}}

////////////////////////////////////////////////////////////////////////////////
int main( void )
{
	// Variable declaration
	int ch;
	init_screen();
	curs_set( 0 );
	init_pair( 1, COLOR_CYAN, COLOR_BLACK );
	PADDLE left, right;
	init_paddles( &left, &right );

	//|NTRODUCT|ON
	mvprintw( LINES / 2, ( COLS - sizeof( "WELCOME TO PONG" ) ) / 2, "WELCOME TO PONG" );
	getch(); clear();

	c_printer( "This is a two person game." );
	c_printer( "The object is to gain points by having your opponent miss hitting the ball with the paddle." );
	c_printer( "The game ends when a player reaches 20 points." );
	c_printer( "You can stop the game early anytime by pressing either the Enter or Escape key." );
	c_printer( "The paddle on the left can be controlled with the arrow up and down keys." );
	c_printer( "The paddle on the right can be controlled using the page up and down keys." );
	getch(); clear();

	wmove( stdscr, LINES / 2, ( COLS - sizeof( "Press any key to begin" ) ) / 2 ); c_printer( "Press any key to begin" );

	attron( COLOR_PAIR( 1 ) );
	screen_bottom( COLS );
	attroff( COLOR_PAIR( 1 ) );

	//CREATE PADDLES
	while( ( ch = getch() ) != KEY_F( 1 ) )
	{
		switch( ch )
		{
			case KEY_LEFT:
				if( left.part_a.y > MINY )
				{
					--left.part_a.y;
					--left.part_b.y;
					--left.part_c.y;
				}
				break;
			case KEY_RIGHT:
				if( left.part_c.y < MAXY - 2 )
				{
					++left.part_a.y;
					++left.part_b.y;
					++left.part_c.y;
				}
				break;
			case KEY_UP:
				if( right.part_a.y > MINY )
				{
					--right.part_a.y;
					--right.part_b.y;
					--right.part_c.y;
				}
				break;
			case KEY_DOWN:
				if( right.part_c.y < MAXY - 2 )
				{
					++right.part_a.y;
					++right.part_b.y;
					++right.part_c.y;
				}
				break;
		}
		clear();
		paddle_builder( &left, &right );
		refresh();
	}
	endwin();

	return 0;
}
