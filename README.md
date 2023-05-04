# UNO-game
A Uno game with built in AI to be played on an ARM Soc connected to a VGA display

"bello" we working hard i need sleep
 
### Background 
This program is an attempt at imitating a digital version of the popular card game UNO. The
rules of the game are almost entirely based on official UNO rules except for the fact players are
dealt 5 cards instead of 7 to start and will automatically lose if their card number exceeds 10.

### Theory of Operations 
The main game logic is implemented using a massive finite state machine that updates boolean
condition flags, states, and the main data structures. The graphics display read data from main
data structures and display its corresponding sprites from a pre-built graphics library. The bot
algorithm uses a mix of play-anything and random-search.
