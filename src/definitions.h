/* VGA colors */
#define WHITE 0xFFFF
#define YELLOW 0xFFE0
#define RED 0xF800
#define GREEN 0x07E0
#define BLUE 0x001F
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define GREY 0xC618
#define PINK 0xFC18
#define ORANGE 0xFC00
#define TEST 0xF5D7

#define ABS(x) (((x) > 0) ? (x) : -(x))

/* Screen size. */
#define RESOLUTION_X 320
#define RESOLUTION_Y 240

//character size
#define CHAR_RESOLUTION_X 80
#define CHAR_RESOLUTION_Y 60

/* Constants for animation */
#define CARD_WIDTH 27
#define CARD_HEIGHT 40
#define CARD_SIZE 2160
#define COLOUR_SIZE 25920

#define FALSE 0
#define TRUE 1


//colours are represented as: 0:red, 1:yellow, 2:green, 3:blue, 4:black (special card)
//numbers are defined as: 0-9 represent corresponding number, 10:skip, 11:plus 2
//for back (special) cards: 0: change colour, 1: plus 4,2: black card (to clear)
// e.g. a yellow skip would be defined as {int colour = 1; int number = 10};
//colours{0-3}numbers{0-11}
//colour{4}numbers{0-1}
struct Card {
    int colour;
    int number;
    int ifSelected;
};

struct Card user_deck[11];
struct Card ai_deck[11]; 
struct Card curr_card; 
struct Card random_card;
struct Card prev_card;

int ai_card_num;
int user_card_num; 


char *message_string; // global variable

bool bot_turn; // true -> 1 -> bots turn // false -> 0 -> player turn
bool played;
int colour_changed;
bool game_over;

int numbers[] = {0,1,2,3,4,5,6,7,8,9,10,11};
int colours[] = {4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,
1,1,1,1,1,1,1,1,1,1,1,1,
2,2,2,2,2,2,2,2,2,2,2,2,
3,3,3,3,3,3,3,3,3,3,3,3,
};

int special_numbers[] = {0,1};

