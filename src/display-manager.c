#include <stdlib.h>
#include <stdio.h>
#include "address_map_arm.h"
#include "definitions.h"
#include "cards_library.c"

// Begin part1.s for Lab 5
const unsigned char Uno_front_small_map[2464];

void clear_screen(void);
void draw_line ( int x0, int y0, int x1, int y1, short int line_color);
void plot_pixel(int x, int y, short int line_color);
void draw_card(int orgX, int orgY, int w, int h);
void draw_back(int orgX, int orgY);

volatile int pixel_buffer_start; // global variable

int main(void)
{
    volatile int * pixel_ctrl_ptr = (int *)0xFF203020;
    /* Read location of the pixel buffer from the pixel buffer controller */
    pixel_buffer_start = *pixel_ctrl_ptr;

    clear_screen();

	draw_card(0, 1, 50, 50);
   
}

void draw_back(int orgX, int orgY)
{
	int i, j;
	int data ;	
	
	for (i = 0; i < H ; i++)
	{		
		for(j=0 ; j < W; j++)	
		{ 	
			data = card_back[(i*W+j)*2+1] ;
			data = data << 8;
			data += card_back[(i*W+j)*2];	
			plot_pixel(orgX+j, orgY+i, data);
			//printf(" x, y  = %d, %d,   data = %x, \n ", j, i,data );
		}		
	}
}


void draw_card(int orgX, int orgY, int color, int number)
{
	int i, j;
	int Pos, data ;
	
	Pos = color * CARD_SIZE * 12 + number * CARD_SIZE ;
	for (i = 0; i < H ; i++)
	{		
		for(j=0 ; j < W; j++)	
		{ 	
			data = card_lib[Pos+(i*W+j)*2+1] ;
			data = data << 8;
			data += card_lib[Pos+(i*W+j)*2];	
			plot_pixel(orgX+j, orgY+i, data);
			//printf(" x, y  = %d, %d,   data = %x, \n ", j, i,data );
		}		
	}
}

void plot_pixel(int x, int y, short int line_color)
{
    *(short int *)(pixel_buffer_start + (y << 10) + (x << 1)) = line_color;
}

void clear_screen(void)
{
	int x, y;
	for (x=0; x < RESOLUTION_X; x++)
	{
		for( y=0; y< RESOLUTION_Y; y++)
			plot_pixel( x,  y, 0x0000); //0x001F);// test blue 0x0000);
	}
}

