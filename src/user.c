#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "definition.h"
#include "address_map_arm.h"
#include "user_utilities.c"
#include "display-manager.c"

/*=======MAIN USER FUCNTION=======*/
void update_user(); //use this to update any deaded user actions

void apply_card_action();
int get_user_input(); //return index of user_deck of chosen user card, return -1 if no card selected;
bool if_valid(int card_index);
void make_move(int card_index);
void check_ifWin();
void choose_colour();

bool has_drawn; //determines if user has drawn card. Used to check if not playing card is legal
bool has_changed_colour; //check if a wild card has been played. User for checking correct card play


void apply_card_action(){
    //check if Skip card
    if(curr_card.number = 10){
        bot_turn = true; //automatically bot's turn if true
    }//check if +2 card
    else if(curr_card.number = 11){
        plustwo(user_deck); //draw 2 cards
    }else if(curr_card.colour == 4){
        has_changed_colour = true; //update colour has been changed -> different rulse check

        //check if its +4 Wild card
        if(curr_card.numer == 1){
            plusfour(user_deck); //draw 4 cards if true
            has_drawn = true;
        }
    }//check if there is a playable card in a user's deck
    else if(!has_playable_card(user_deck)){
        plusone(user_deck);
        has_drawn = true;
    }else{
        has_drawn = false;
    }
    
}

int get_user_input(){
    //not sure how yet lol
    
    while(!key0){

    }
}


//check if user input is valid
bool if_valid(int card_index){
    if(card_index == -1){//if no user input
        if(has_drawn){
            return true; //valid move if user has drawn card
        }else{
            return false;
        }
    }else if(has_changed_colour){// if colour changed
        if(user_deck[card_index].colour == colour_changed){
            return true;
        }else{ 
            return false;
        }
    }else{//check if cards: are of same colour, are of same number, is special card
        if(user_deck[card_index].colour == curr_card.colour || user_deck[card_index].number == curr_card.number || user_deck[card_index].colour == 4){
            return true;
        }else{
            return false;
        }
    }
}
 

void make_move(int card_index){
    int card_col = user_deck[card_index].colour;
    int card_num = user_deck[card_index].number;
    if(card_col== 4){
       choose_colour();
    }else if (card_index == -1){
        return;
    }
    curr_card.colour = card_col;
    curr_card.number = card_num;
    shift_card(card_index);
    user_card_num --;
}

choose_colour(){
    //dk how to write yet lol
}

void check_ifWin(){
    if(user_card_num <= 0 || ai_card_num > 10){
        message_string = "You Won!";
        game_over = true;
    }else if (user_card_num > 10 || ai_card_num <= 0){
        message_string = "You Lost";
        game_over = true;
    }else{
        game_over = false;
    }
}

void update_user(){
    int card_i;
    apply_card_action()
    if(bot_turn){
        return;
    }
    while(!if_valid(get_user_input())){
        card_i = get_user_input();
    }
    void make_move(card_i);
    void check_ifWin();
}
