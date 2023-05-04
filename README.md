# UNO-game
An Uno game with built in AI to be played on an ARM Soc connected to a VGA display

### Background 
This program is an attempt at imitating a digital version of the popular card game UNO. The
rules of the game are almost entirely based on official UNO rules except for the fact players are
dealt 5 cards instead of 7 to start and will automatically lose if their card number exceeds 10.

### Theory of Operations 
The main game logic is implemented using a massive finite state machine that updates boolean
condition flags, states, and the main data structures. The graphics display read data from main
data structures and display its corresponding sprites from a pre-built graphics library. The bot
algorithm uses a mix of play-anything and random-search.

### Procedure
![image](https://user-images.githubusercontent.com/47972556/236096759-a5071aed-b02c-44ce-bb8b-cb60f5abedab.png)
1. Press any key to start

![image](https://user-images.githubusercontent.com/47972556/236098337-579e6358-e8c0-4eea-8b95-170358d8ce9c.png) <br>
2. Press any key to skip the instructions page

![image](https://user-images.githubusercontent.com/47972556/236296636-db5f71ad-fd88-4590-b4b4-3b1566f2529f.png) <br>
3. Each of the switches corresponds to a card on the screen, only one card can be played
at once<br>
4. Once the switch is on, the card will pop up<br>
5. Press KEY0 to submit the card <br>
6. The AI should play a card according to the current card<br>
 &nbsp; a. Our AI is having trouble operating with the VGA but works in C <br>
 &nbsp; b. So instead the game is more like solitaire, where the user will play based on the
 current deck<br>
7. Playing a plus four card or change colour card will prompt the change colour screen<br>

![image](https://user-images.githubusercontent.com/47972556/236296737-55b4c89d-40c6-4542-9ec3-e6fa8eff68fa.png)<br>
8. Each of the keys corresponds to one of the colours<br>
9. Skip cards will skip the turn of the ai and go back to the player<br>
10. Plus two cards should add two cards to the ai deck<br>
11. Once the deck is full the user loses<br>
12. The user wins by using all their cards
