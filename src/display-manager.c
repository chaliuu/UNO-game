#include <stdlib.h>
#include <stdio.h>
#include "address_map_arm.h"
#include "definitions.h"
#include "cards_library.c"

void clear_screen(void);
void plot_pixel(int x, int y, short int line_color);
void draw_card(int orgX, int orgY, int color, int number);
void draw_back(int orgX, int orgY);
void display_curr_card();
void display_ai_deck();
void display_user_deck();
void display_deck();

volatile int pixel_buffer_start; // global variable

int main(void)
{
    volatile int * pixel_ctrl_ptr = (int *)0xFF203020;
    /* Read location of the pixel buffer from the pixel buffer controller */
    pixel_buffer_start = *pixel_ctrl_ptr;

    clear_screen();

	display_curr_card();
	display_ai_deck();
	display_user_deck();
	display_deck();
   
}

void display_curr_card(){
	draw_card(147, 100, curr_card.colour, curr_card.number);
  printf(" %d  %d", curr_card.colour, curr_card.number);
  //draw_card(147, 100, 2, 3);
}

void display_ai_deck(){
	int i;
	for(i = 0; i < 10; i++){
    if(!(ai_deck[i].colour == 4 && ai_deck[i].number == 2)){
      draw_back(319 - (CARD_WIDTH + 5)*(i+1), 10);
    }
	}
	
}

void display_user_deck(){
	int i;
	for(i = 0; i < 10; i++){
		draw_card(319 - (CARD_WIDTH + 10)*(i+1), 219 - CARD_HEIGHT - 10 - user_deck[i].ifSelected * 10, user_deck[i].colour, user_deck[i].number);
	}

}

void display_deck(){
	draw_back(80, 100);
	draw_back(70, 100);
}

void draw_back(int orgX, int orgY)
{
	int i, j;
	int data ;	
	
	for (i = 0; i < CARD_HEIGHT ; i++)
	{		
		for(j=0 ; j < CARD_WIDTH; j++)	
		{ 	
			data = card_back[(i*CARD_WIDTH+j)*2+1] ;
			data = data << 8;
			data += card_back[(i*CARD_WIDTH+j)*2];	
			plot_pixel(orgX+j, orgY+i, data);
			//printf(" x, y  = %d, %d,   data = %x, \n ", j, i,data );
		}		
	}
}


void draw_card(int orgX, int orgY, int color, int number)
{
	// 
	int i, j;
	int Pos, data ;
	
	Pos = color * COLOUR_SIZE + number * CARD_SIZE ;
	for (i = 0; i < CARD_HEIGHT ; i++)
	{		
		for(j=0 ; j < CARD_WIDTH; j++)	
		{ 	
			data = card_lib[Pos+(i*CARD_WIDTH+j)*2+1] ;
			data = data << 8;
			data += card_lib[Pos+(i*CARD_WIDTH+j)*2];	
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