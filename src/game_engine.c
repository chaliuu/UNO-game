#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "definition.h"


//this bot only knows how to play number cards
//it will not use any skip cards, colour changing cards, or plus cards
//will always take in cards for plus cards
//will always take an extra card if there is no fit for colour changing cards
//will not stack any special cards
void bot(){
    for (int i = 0; i < sizeof(ai_deck)/sizeof(ai_deck[i]); i++){
        //if its a regular number card
        if((curr_card.colour == ai_deck[i].colour || curr_card.number == ai_deck[i].number) 
        && (((0 <= curr_card.colour)&&(curr_card.colour <= 3) && (0 <= curr_card.number)&&(curr_card.number <= 9)))){
            //play the card
            curr_card.colour = ai_deck[i].colour;
            curr_card.number = ai_deck[i].number;
            shift_card(i);
            break;   
        }
        //if its a black card
        if(prev_card.colour == 4){
            //if its change colour
            if(prev_card.number == 0){
                //bot must put down the right colour otherwise plus 1
                if(ai_deck[i].colour == curr_card.colour ){
                    curr_card.colour = ai_deck[i].colour;
                    curr_card.number = ai_deck[i].number;
                    shift_card(i);
                    break;
                }
                //or else it plays a colour change/+4 card as well
                else if(ai_deck[i].colour == 4){
                    int index2= rand() % (sizeof(colours) / sizeof(int));
                    random_card.colour = colours[index2];
                    colour_changed = random_card.colour;
                    if(ai_deck[i].number == 1){
                        curr_card.colour = ai_deck[i].colour;
                        curr_card.number = ai_deck[i].number;
                    }
                    break;

                }
                else{
                    plusone_easy(ai_deck);
                    break;
                }
            }
            //if its plus four (includes change colour)
            if(curr_card.number == 1){
                //adds four to ai deck
                plusfour_easy();
                //must also find the right colour to put
                break;
            }
        }
        // if its skip or plus two
        if(curr_card.number >= 10 && curr_card.number <= 11){
            // if its skip
            if(curr_card.number == 10){
                //skips the bots turn
                break;
            }
            //if its plus 2
            if(curr_card.number == 11){
                    plustwo_easy();
                    break;
            }
        }
        
    }
    bot_turn = false;
}



//this bot only knows how to play number all cards
//will always take in cards for plus cards
//will always take an extra card if there is no fit for colour changing cards
//will not stack any special cards
//void medium_bot(){}


//if it passes rule check, the current card will be changed.
//if its a change colour card, the previous card will be set to be the curret colour



//helper functions

//shift the list down from the jth posistion

void shift_card(int j){
    for (int k = j; k < 11; k++){
        ai_deck[k].colour = ai_deck[k+1].colour;
        ai_deck[k].number = ai_deck[k+1].number;
        ai_deck[11].colour = 4;
        ai_deck[11].number = 2;  
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

void plusfour_easy(){
    played = false;
    plusone_easy(ai_deck);
    plusone_easy(ai_deck);
    plusone_easy(ai_deck);
    plusone_easy(ai_deck);
}

void plustwo_easy(){
    played = false;
    plusone_easy(ai_deck);
    plusone_easy(ai_deck);

}

//picks up a card and decides to put it down or add it to the end of the deck
int plusone_easy(struct Card deck[11]){
    //adds a card onto the deck
    card_generator();
    printf("%d",random_card.colour);
    printf("%d",random_card.number);
    if (!played){
    //if the card can be played
        if((curr_card.colour == random_card.colour || curr_card.number == random_card.number) 
        && (((0 <= random_card.colour)&&(random_card.colour <= 3) && (0 <= random_card.number)&&(random_card.number <= 9)))){
            //play the card
            curr_card.colour = random_card.colour;
            curr_card.number = random_card.number;
            played = true;
        }
        else if(random_card.colour == 4){
                if(random_card.number == 0){
                    int index2= rand() % (sizeof(colours) / sizeof(int));
                    random_card.colour = colours[index2];
                    colour_changed = random_card.colour;
                    curr_card.colour = random_card.colour;
                    curr_card.number = random_card.number;
                    played = true;

                }
                else if(random_card.colour == 1){
                    int index2= rand() % (sizeof(colours) / sizeof(int));
                    random_card.colour = colours[index2];
                    colour_changed = random_card.colour;
                    curr_card.colour = random_card.colour;
                    curr_card.number = random_card.number;
                    played = true;
                    //and the user ceck adds 4
                    
                }
            
        }
        else if (random_card.number == 10){ //skip users turn
            bot_turn = true;
            curr_card.colour = random_card.colour;
            curr_card.number = random_card.number;
        }
        else if(random_card.number == 11){
            // user adds two cards
            curr_card.colour = random_card.colour;
            curr_card.number = random_card.number;
            
        }
        else{
            //add the card to the deck
            for(int i = 0; i < 11; i++){
            //find a black spot and add it on
                if(i == 10){
                    printf("game over");
                    return 0;
                }
                else if(deck[i].colour == 4 && deck[i].number == 2){
                    deck[i].number = random_card.number;
                    deck[i].colour = random_card.colour;
                    break;
                }
                else{ //search until we find an empty spot
                    continue;
                }
            }
        }
    }
    else{
        for(int i = 0; i < 12;i++){
            //find a black spot and add it on
            if(i == 11){
                printf("game over");
                return 0;
            }
            else if(deck[i].colour == 4 && deck[i].number == 2){
                deck[i].number = random_card.number;
                deck[i].colour = random_card.colour;
                break;
            }
            else{ //search until we find an empty spot
                continue;
            }

        }
    }
}


//initializes the ai_deck  
void initializer(){
    //ai deck
    for(int i = 0; i < (sizeof(ai_deck)/sizeof(ai_deck[i]));i++){
        card_generator();
        ai_deck[i] = random_card;

        if (i > 4){
            ai_deck[i].colour = 4;
            ai_deck[i].number = 2;
        }
            
    }
    //user deck
    for(int i = 0; i < (sizeof(user_deck)/sizeof(user_deck[i]));i++){
        card_generator();
        user_deck[i] = random_card;

        if (i > 4){
            user_deck[i].colour = 4;
            user_deck[i].number = 2;
        }
            
    }  
    //currentcard
    curr_card.colour = rand()%4;
    curr_card.number =  rand()%12;

    //ai card number, user card nunmber
    ai_card_num = 5;
    user_card_num = 5;

}


//prints the ai deck
void print_ai_deck(){
    for(int i = 0; i < sizeof(ai_deck)/sizeof(ai_deck[i]);i++){
        printf("Colour: ");
        printf("%d",ai_deck[i].colour);
        printf("\tNumber: ");
        printf("%d\n",ai_deck[i].number);  
    }
}

int main(){
    /*printf("original deck: \n");
    ai_deck[11].colour = 4;
    ai_deck[11].number = 2;
    ai_deck[10].colour = 4;
    ai_deck[10].number = 2;
    ai_deck[9].colour = 4;
    ai_deck[9].number = 2;
    ai_deck[8].colour = 4;
    ai_deck[8].number = 2;
    ai_deck[7].colour = 4;
    ai_deck[7].number = 2;
    ai_deck[6].colour = 4;
    ai_deck[6].number = 2;
    ai_deck[5].colour = 4;
    ai_deck[5].number = 2;
    ai_deck[4].colour = 2;
    ai_deck[4].number = 4;
    ai_deck[3].colour = 2;
    ai_deck[3].number = 3;
    ai_deck[2].colour = 2;
    ai_deck[2].number = 2;
    ai_deck[1].colour = 2;
    ai_deck[1].number = 1;
    ai_deck[0].colour = 2;
    ai_deck[0].number = 5;
    print_ai_deck();
    printf("\n");
    curr_card.colour = 2; //green
    curr_card.number = 0; // zero
    easy_bot();
    printf("new deck: \n");
    print_ai_deck();
    printf("\n");
    curr_card.colour = 3; //blue
    curr_card.number = 4; // four
    easy_bot();
    printf("new deck: \n");
    print_ai_deck();
    curr_card.colour = 0; //red
    curr_card.number = 10; //skip
    easy_bot();
    printf("new deck: \n");
    print_ai_deck();
    curr_card.colour = 4; //black
    curr_card.number = 1; //plus four and change colour
    easy_bot();
    printf("new deck: \n");
    print_ai_deck();
    curr_card.colour = 1; //yellow
    curr_card.number = 11; //plus two
    easy_bot();
    printf("new deck: \n");
    print_ai_deck();  */

    card_generator();
    card_generator();
    card_generator();
    card_generator();
    card_generator();
    card_generator();
    card_generator();
    card_generator();
    card_generator();
    card_generator();
    card_generator();
    card_generator();
    card_generator();
    card_generator();
    card_generator();
    card_generator();
    card_generator();
    card_generator();
    card_generator();
    card_generator();
    card_generator();
    card_generator();
    card_generator();
    card_generator();
    card_generator();
    card_generator();
    card_generator();
    card_generator();
    card_generator();
    card_generator();
    card_generator();
    card_generator();
    card_generator();
    card_generator();
    card_generator();
    card_generator();
    card_generator();
    card_generator();
    card_generator();
    card_generator();
    card_generator();
    card_generator();
    card_generator();
    card_generator();
    card_generator();
    card_generator();
    card_generator();
    card_generator();
    card_generator();
    card_generator();
    card_generator();
    card_generator();
    card_generator();
    card_generator();
    card_generator();
    card_generator();
    card_generator();
    card_generator();
    card_generator();
    card_generator();
    card_generator();
    card_generator();
    card_generator();
    card_generator();
    card_generator();
    card_generator();


}


