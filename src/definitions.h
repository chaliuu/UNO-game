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

/* Constants for animation */
#define CARD_WIDTH 27
#define CARD_HEIGHT 40
#define CARD_SIZE 2160

#define FALSE 0
#define TRUE 1

struct Card {
    int colour;
    int number;
};

struct Card user_deck[10];
struct Card ai_deck[10];
struct Card curr_card;