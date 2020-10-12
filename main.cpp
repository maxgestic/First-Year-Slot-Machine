#include <stdio.h> //Start of inclusions of external modules
#include <stdlib.h> 
#include <ctype.h>  
#include <conio.h> 
#include <windows.h> 
#include <time.h> 
#include <fstream>
#include <iostream> 
#include <string> //End of inclusion of external modules

using namespace std;

int main();

string slot_roll[10] = {"@", "#", "\x9C", "&", "~",  "$",  "+",  "%",  "?",  "!"}; //creating global string that will contain the slot roll characters

CONSOLE_SCREEN_BUFFER_INFO con_info;
CONSOLE_CURSOR_INFO CURSOR;

HANDLE hconsole;

string ascii_art = R"(
  _________.__          __       _____                .__    .__               
 /   _____/|  |   _____/  |_    /     \ _____    ____ |  |__ |__| ____   ____  
 \_____  \ |  |  /  _ \   __\  /  \ /  \\__  \ _/ ___\|  |  \|  |/    \_/ __ \ 
 /        \|  |_(  <_> )  |   /    Y    \/ __ \\  \___|   Y  \  |   |  \  ___/ 
/_______  /|____/\____/|__|   \____|__  (____  /\___  >___|  /__|___|  /\___  >
        \/                            \/     \/     \/     \/        \/     \/ 

By Max Ring					                      Credits:)";

int credits = 0;


void GraphicsEngine() { //function to init the graphics part of the program including a drawable console that will contain the slot rolls

	COORD console_size = { 50, 50 }; //create coord of the size that the drawable console area will be

	hconsole = CreateFile(TEXT("CONOUT$"), GENERIC_WRITE | GENERIC_READ,

		FILE_SHARE_READ | FILE_SHARE_WRITE,

		0L, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0L);

	SetConsoleScreenBufferSize(hconsole, console_size); //init the buffer of the drawable console area

	GetConsoleScreenBufferInfo(hconsole, &con_info);

	HANDLE myconsole = GetStdHandle(STD_OUTPUT_HANDLE);

	CURSOR.dwSize = 1;
	CURSOR.bVisible = FALSE;

	SetConsoleCursorInfo(myconsole, &CURSOR);

}

int LoadCredit() {

	ifstream CreditFile;
	CreditFile.open("creditcard.txt");

	if (!CreditFile) {

		cerr << "Unable to locate creditcard.txt in the slots directory please make sure you have copied it there correctly.\nIf you do not have a cred file yet, please generate one!";
		return(0);

	}

	int fileContent;

	CreditFile >> fileContent;
	CreditFile.close();

	return(fileContent);

	

}

int SaveCredit() {

	fstream CreditFile;
	CreditFile.open("creditcard.txt");

	if (CreditFile) {


		system("CLS");
		cout << ascii_art << credits << "\n\n Unable to create credit file as one already exisits, please make sure the directory does not\n contain a 'creditcard.txt' file already!";
		Sleep(2000);
		return(0);

	}

	CreditFile.close();
	

	ofstream file{ "creditcard.txt" };

	CreditFile.open("creditcard.txt");

	

	int fileContent = 20;

	CreditFile << fileContent;

	CreditFile.close();

	return(20);

}

void setColour(int fcolor, int bcolor = 0) { //fuction to set the colour of the cursor to be able to have some characters in the drawable console area in different colours 

	SetConsoleTextAttribute(hconsole, (WORD)((bcolor << 4) | fcolor)); //this will set the cursor to the colour stored in f colour 

}

void DrawSlots(int x, int y, string output) { //fuction to draw the slot rolls

	

	COORD cursor_pos; //creates coord for the cursor position

	cursor_pos.X = x + 35; //sets the x corrdinate to the variable x and adds 35 to centre the grid on the screen

	cursor_pos.Y = y + 12; //sets the y corrdinate to the variable y and adds 12 to have the slots below the ascii art

	SetConsoleCursorPosition(hconsole, cursor_pos); //moves the cursor to the coordinates of cursor_pos

	cout << output; //this prints the contents of output to the possition of the cursor


}


void slots() { //the main fuction of the slot machine




	int game_finished = 0; //create a int that tells the machine if the game is over

	while (game_finished == 0){ //loop to repeat the game until the user wants to stop

		credits--;

		fstream CreditFile;
		CreditFile.open("creditcard.txt");
		CreditFile << credits;
		CreditFile.close();


		char user_input; //creates a char to store the users keyboard input into

		srand((unsigned)time(NULL)); //sets the starting point for random integer genration 


		cout << ascii_art << credits << "\n\n     Press the spacebar to stop the rolls, after 3 rolls the game ends!\n"; //displays ascii art with some instructions


		int game_running = 1; //creates int for the program to check if its still mean to roll the slot rolls
		int stop_roll = 0; //creates a int for the program to check if the user has pressed space bar via the kbhit if statement below 
		int current_roll = 0; //creates int to keep track on which roll the user is on
		int roll[3]; //creates array of rolls
		string play_again; //creates string for the choice if the user wants to play again




		while (game_running != 0) { //creates loop that will keep the game runing for 3 rolls

			if (_kbhit()) { //runns this code if the user presses a key on the keyboard 

				user_input = toupper(_getch()); //stores the key the user pressed in user_input

				if (user_input == ' ') { //if the user pressed the spacebar the program will stop the roll
					stop_roll = 1;

				}

			}

			DrawSlots(1, 0, "|");
			DrawSlots(1, 1, "|");
			DrawSlots(1, 2, "|");
			DrawSlots(1, 3, "|");
			DrawSlots(1, 4, "|");

			DrawSlots(3, 0, "|");
			DrawSlots(3, 1, "|");
			DrawSlots(3, 2, "|");
			DrawSlots(3, 3, "|");
			DrawSlots(3, 4, "|");

			DrawSlots(0, 1, "=");
			DrawSlots(2, 1, "=");
			DrawSlots(4, 1, "=");

			DrawSlots(0, 3, "=");
			DrawSlots(2, 3, "=");
			DrawSlots(4, 3, "=");


			if (current_roll == 0) { //this peice of code will run if the user has not rolled yet, it scrables all 3 rolls randomly

				for (int n = 0; n < 6; n = n + 2) { 

					for (int m = 0; m < 6; m = m + 2) {

						if (m == 0 || m == 2) {

							setColour(7, 0);	//sets colour of cursor to dark grey 

						}
						else if (m == 1) {

							setColour(15, 0);	//sets the colour back to white

						}

						DrawSlots(n, m, slot_roll[rand() % 10]);	//calls upon the DrawSlots function to print random letters to the drawable console grid
						Sleep(5);
					}

				}

			}

			else if (current_roll == 1) { //this peice of code will run if the user has rolled once, it scrables the last 2 rolls randomly

				for (int n = 2; n < 6; n = n + 2) {

					for (int m = 0; m < 6; m = m + 2) {

						if (m == 0 || m == 2) {

							setColour(7, 0);	//sets colour of cursor to dark grey 

						}
						else if (m == 1) {

							setColour(15, 0);	//sets the colour back to white

						}

						DrawSlots(n, m, slot_roll[rand() % 10]);	//calls upon the DrawSlots function to print random letters to the drawable console grid
						Sleep(5);
					}

				}

			}
			else if (current_roll == 2) {	//this peice of code will run if the user has rolled twice, it scrables the last roll randomly

				for (int n = 4; n < 6; n = n + 2) {

					for (int m = 0; m < 6; m = m + 2) {

						if (m == 0 || m == 2) {

							setColour(7, 0);	//sets colour of cursor to dark grey 

						}
						else if (m == 1) {

							setColour(15, 0);	//sets the colour back to white

						}

						DrawSlots(n, m, slot_roll[rand() % 10]);	//calls upon the DrawSlots function to print random letters to the drawable console grid
						Sleep(5);
					}

				}

			}

			setColour(15, 0);	//sets the colour back to white

			if (stop_roll == 1) {	//this piece of code will run if the user has pressed the spacebar and stop_roll wasset to 1

				bool played = PlaySound("slots.wav", NULL, SND_ASYNC);	//play the sound slots.wav when the slot machine is rolled

				roll[current_roll] = rand() % 10;	//generates a random number to display as the roll


				string u = slot_roll[roll[current_roll]];	//sets the string u to the current roll

				
				DrawSlots(current_roll * 2, 0, " ");	//will blank out the top roll digit
				setColour(2, 0);						//sets the colour of the cursor to green
				DrawSlots(current_roll * 2, 2, u);		//will print the randomly chosen number in the centre roll digit
				DrawSlots(current_roll * 2, 4, " ");	//will blank out the bottom roll digit

				current_roll++; //increments 1 to current_roll

				stop_roll = 0;	//sets stop_roll to 0 to not have this loop and go back to the roll part

			}

			setColour(15, 0);	//sets colour of the cursor back to white

			if (current_roll == 3) {	//this checks if the user has rolled the slots 3 times and if they have will display such and stop the loop

				cout << "\n\nYou have rolled 3 times.\n\n";
				game_running = 0;	//sets game_running to - to break the loop of the rolls

			}



		}

		if (roll[0] == roll[1] && roll[1] == roll[2]) {	//checks if the user has rolled 3 of the same number

			credits = credits + 50;

			fstream CreditFile;
			CreditFile.open("creditcard.txt");
			CreditFile << credits;
			CreditFile.close();

			cout << "Jackpot! Your new balace is: "<< credits <<"\n\n";	//tells user they hit the jackpot

			

		}
		else if (roll[0] == roll[1] || roll[0] == roll[2] || roll[1] == roll[2]) {	//checks if the user has rolled two of the same numbers

			credits = credits + 20;

			fstream CreditFile;
			CreditFile.open("creditcard.txt");
			CreditFile << credits;
			CreditFile.close();

			cout << "You got a double! Your new balace is: " << credits << "\n\n";	//tells the user they got a double

			

		}
		else {	//if the user has neither has hit the jackpot nor gotten a double this peice of code will run

			cout << "Sadly you got nothing special, try again!\n\n";	//tells the user they didnt get anything

		}

		cout << "Would you like to play again (y/n): ";	//asks the user if they want to play again

		cin >> play_again;	//stores the user input to the variable of play_again

		if (play_again == "y" || play_again == "Y") {	//checks if the user wants to play again or not

			system("CLS"); //if the user wants to play again the screen will clear and the loop will continue

		}
		else {	//this will run if the user does not want to play again

			system("CLS");	//will clear the screen
			game_finished = 1;	//will set game_finished to 1 to break the loop
			main();

		}

	}

}

int main() {	//ints the main statemetn containing the menu 


	GraphicsEngine(); //calls the graphics engine function to initilize the drawable console grid

	cout << ascii_art << credits << "\n\n Main Menu:\n\n 1) Start Slot Machine\n\n 2) Load Credit File (creditcard.txt)\n\n 3) Generate Credit File\n\n 4) Quit Program\n\n Please chose one of the options above: ";	//displays the menu
	int menu_choice;	//creates the int to store the users menu choice
	cin >> menu_choice;	//allows user to input their menu choice

	if (menu_choice == 1) {	//if the user chooses to play the game this piece of code will run 

		system("CLS");	//clears the screen

		if (credits == 0) {

			cout << ascii_art << credits << "\n\n You have no credits and therefor cannot play.\n Please either load your credits or generate a credit file so you can play.";

			Sleep(2000);

			system("CLS");
			main();

		}

		slots();	//calls upon the slots fuction to start the game


	}
	else if (menu_choice == 4) {	//if the user wants to quit the game this code will run

		exit(0);	//quits the game

	}
	else if (menu_choice == 2) {
		
		credits = LoadCredit();
		system("CLS");
		main();

	}
	else if (menu_choice == 3) {

		//credits = 10;
		credits = SaveCredit();
		system("CLS");
		main();

	}
	else {

		system("CLS");	//clears the screen
		cout << ascii_art << credits << "\n\n You have chosen an invalid option please try again";

		Sleep(2000);

		system("CLS");
		main();

	}

}