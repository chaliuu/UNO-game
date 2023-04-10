#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
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
void update_display();
void print_char(int x, int y,  char char_print);
void clear_character_all();
void clear_character(int x_start, int y_start, int x_end,int y_end);
void print_message(int x, int y, char * char_data);
void update_message();



volatile int pixel_buffer_start; // global variable
volatile int char_buffer_start; // global variable

void update_display()
{
    volatile int * pixel_ctrl_ptr = (int *)0xFF203020;
    /* Read location of the pixel buffer from the pixel buffer controller */
    pixel_buffer_start = *pixel_ctrl_ptr;
	
	volatile int * char_ctrl_ptr =  (int *)0xFF203030;
	// Read location of the character buffer from the character buffer controller /
	char_buffer_start = *char_ctrl_ptr; // address is  0xC9000000

    clear_screen();

	update_message();
	display_curr_card();
	display_ai_deck();
	display_user_deck();
	display_deck();
   
}

void display_curr_card(){
	draw_card(147, 80, curr_card.colour, curr_card.number);
}

void display_ai_deck(){
	int i;
	for(i = 0; i < 10; i++){
		if(!(ai_deck[i].colour == 4 && ai_deck[i].number == 2)){
		draw_back(319 - (CARD_WIDTH + 5)*(i+1), 5);
		}
	}
	
}

void display_user_deck(){
	int i;
	for(i = 0; i < 10; i++){
		draw_card(319 - (CARD_WIDTH + 5)*(i+1), 219 - CARD_HEIGHT - 20 - user_deck[i].ifSelected * 10, user_deck[i].colour, user_deck[i].number);
	}
}

void display_deck(){
	draw_back(84, 80);
	draw_back(82, 80);
	draw_back(80, 80);
	draw_back(78, 80);
	draw_back(76, 80);
	draw_back(74, 80);
	draw_back(72, 80);
	draw_back(70, 80);
	draw_back(68, 80);
	draw_back(66, 80);
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

void update_message(){
	int x_start, y_start, x_end, y_end;
	
	x_start = 46;
	y_start = 23;
	
	x_end = CHAR_RESOLUTION_X -1;
	y_end = y_start + 6 ;// assume the message won't be longer than 7 lines
	
	clear_character(x_start, y_start, x_end, y_end); // clear previous meesage before update new message
	print_message(x_start, y_start, message_string);
}

void clear_character_all()
{
	int x, y;
	for (x = 0; x < CHAR_RESOLUTION_X; x++)
	{
		for( y = 0; y < CHAR_RESOLUTION_Y; y++)
			print_char( x,  y, 0x20); //wirte 0x20 to fill blank space
	}
}

void clear_character(int x_start, int y_start, int x_end,int y_end)
{
	int x, y;
	for (x = 0; x < (x_end - x_start+ 1); x++)
	{
		for( y = 0; (y < y_end - y_start + 1 ) ; y++)
			print_char( x_start + x,  x_start + y, 0x20); //wirte 0x20 to fill blank space
	}
}

void print_message(int x, int y, char * char_data)
{
	 char *data_ptr;
	int i;
	
	data_ptr = char_data;
	i = x;
	while (*data_ptr)
	{
	 print_char( i,  y, *data_ptr);	
	 i++;
	 data_ptr++;
	}

}

//char_print need to be in format of ASCII
void print_char(int x, int y,  char char_print)
{
    *( char *)(char_buffer_start + (y << 7) + x ) = char_print;
}