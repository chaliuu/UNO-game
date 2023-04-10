#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "definition.h"

//helper functions

//shift the list down from the jth posistion

void shift_card(struct Card deck[11],int j){
    int k;
    for (k = j; k < 11; k++){
        deck[k].colour = deck[k+1].colour;
        deck[k].number = deck[k+1].number;
        deck[11].colour = 4;
        deck[11].number = 2;  
    } 
}

//generates a random card
void card_generator(){
    srand(time(NULL));
    int index1 = rand() % (sizeof(numbers) / sizeof(int));
    int index2= rand() % (sizeof(colours) / sizeof(int));
    int index3 = rand() % (sizeof(special_numbers) / sizeof(int));
    random_card.colour = colours[index2];
    if (random_card.colour == 4){
        random_card.number = special_numbers[index3];
    }
    else{
        random_card.number = numbers[index1];
    }
}

void plusfour(struct Card deck[11]){
    played = false;
    plusone(deck);
    plusone(deck);
    plusone(deck);
    plusone(deck);
}

void plustwo(struct Card deck[11]){
    played = false;
    plusone(deck);
    plusone(deck);

}

//picks up a card and decides to put it down or add it to the end of the deck
void plusone(struct Card deck[11]){
    //adds a card onto the deck
    card_generator();
    //printf("%d",random_card.colour);
    //printf("%d",random_card.number);
            //add the card to the deck
    for(int i = 0; i < 11; i++){
    //find a black spot and add it on
        if(deck[i].colour == 4 && deck[i].number == 2){
            deck[i].number = random_card.number;
            deck[i].colour = random_card.colour;
            user_card_num ++; 
            break;
        }
        else{ //search until we find an empty spot
            continue;
        }
    }
}

//loops through the deck and deck if there are playable cards in the deck
bool has_playable_card(struct Card deck[11]){
    int i;
    for(i = 0; i < 10; i++){
        if(deck[i].colour == curr_card.colour || deck[i].number == curr_card.number)){
            return true;
        }
    }else{
        return false;
    }
}

/*
//checks if the input card is equal to the current card. Returns bool true if true returns false if not true
bool card_equal_curr(int card_colour, int card_number){
    if(card_colour == curr_card.colour && card_number == curr_card.number){
        return true;
    }else{
        return false;
    }
}*/

//prints the ai deck
void print_ai_deck(){
    for(int i = 0; i < sizeof(ai_deck)/sizeof(ai_deck[i]);i++){
        printf("Colour: ");
        printf("%d",ai_deck[i].colour);
        printf("\tNumber: ");
        printf("%d\n",ai_deck[i].number);  
    }
}

