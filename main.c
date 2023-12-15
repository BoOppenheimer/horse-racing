#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#ifdef _WIN32
#endif

// dynamic arrays? or just intialize to like 99 like old photoshop?

typedef struct {
    int win_order[4]; //{4,2,3,1} // this is the order won?
    int bet_order[4]; // this is the bet order placed and type of bet
    bool win_lose;
    int money_before; //$200
    int money_after; //$250
    int game_round; //1 
} history ;

// util fn's
// input fn's

void pauseScreen() {
    #ifdef _WIN32
    system("pause");
    #else
    printf("Press Enter to continue...");
    while (getchar() != '\n');  // Wait for Enter key
    #endif
}


bool getIntInput(unsigned int *value) {
    if (scanf("%u", value) != 1) {
        // Clear the input buffer
        while(getchar() != '\n');
        return false;
    }
    // Clear the input buffer
    while(getchar() != '\n');
    return true;
}

void getUserInput_UInt(unsigned int *uInt , unsigned int max_number_to_check) {

    printf("Enter your choice: ");
    while (true) {  // Infinite loop until valid input is received
        if(getIntInput(uInt) && *uInt >= 1 && *uInt <= max_number_to_check) {
            break;  // Exit the loop if input is valid and within range5
        }
        printf("Invalid input. Please enter a number 1-%u: ", max_number_to_check); 
    }
}


/** 
  * @brief printBettingHistory takes the array of type stuct history and iterates each el printing the the log of bets
  * @param history array[] of history stuct's
  * @param unsigned int *gameRound 
*/
void printBettingHistory (history user_history[], int *gameRound) {

  if (*gameRound == 0) {
    printf("You have no history. So Sad :( \n");
    return;
  }
  printf("you played: %d\n", *gameRound);

  for (int i = 1; i <= *gameRound; i++) {
    
    if (user_history[i].win_lose == true) {
        printf("Round %d: WIN, Money before: $%d, Money after: $%d\n",
        user_history[i].game_round,
        user_history[i].money_before,
        user_history[i].money_after);
        } else { 
        printf("Round %d: LOSE, Money before: $%d, Money after: $%d\n",
        user_history[i].game_round,
        user_history[i].money_before,
        user_history[i].money_after);
      }

      printf("\twin order { %d, %d, %d, %d }\n", 
        user_history[i].win_order[0],
        user_history[i].win_order[1],
        user_history[i].win_order[2],
        user_history[i].win_order[3]);

      printf("\tbet order { %d, %d, %d, %d }\n", 
        user_history[i].bet_order[0],
        user_history[i].bet_order[1],
        user_history[i].bet_order[2],
        user_history[i].bet_order[3]);
  }

}




// Start - Betting fn's here --------------------------------------------
void checkWin_Exacta (int* gameRound, unsigned int user_bet[], unsigned int horse_race_order[], int* money, char horse_names[][15], history* user_history) {
  *gameRound = *gameRound + 1; // we start off with 0, this means no games have started.
  bool temp_win_lose; // to set in the history struct
  int tempBeforeMoney = *money; // to set the history struct value - money befor
 
  printf("|---------------    RESULTS     ---------------|\n");
  printf("|--------------- YOU BET EXACTA ---------------|\n");
  printf("|--------- BET -------- |---- RACE RESULTS ----|\n");
  printf("| 1st: %d %-15s| %d %-15s    |\n", user_bet[0], horse_names[user_bet[0]-1], horse_race_order[0], horse_names[horse_race_order[0]-1] );
  printf("| 2nd: %d %-15s| %d %-15s    |\n", user_bet[1], horse_names[user_bet[1]-1], horse_race_order[1], horse_names[horse_race_order[1]-1] );
  printf("| 3rd:                  | %d %-15s    | \n", horse_race_order[2], horse_names[horse_race_order[2]-1] );
  printf("| 4th:                  | %d %-15s    | \n", horse_race_order[3], horse_names[horse_race_order[3]-1] );

  if (user_bet[0] == horse_race_order[0] &&
      user_bet[1] == horse_race_order[1]) {
    *money = *money + 150;
    temp_win_lose = true;
    printf("|   YOU WIN!  Your total winnings are: $%-5d   |\n", *money);
  } else {
    *money = *money - 15;
    temp_win_lose = false;
    printf("|  YOU LOST!     Your account is now: $%-5d   |\n", *money);
  }
  // setting the hisotry log -----------------------------------------------
    user_history[*gameRound] = (history) {
    .win_lose = temp_win_lose, 
    .money_before = tempBeforeMoney,
    .money_after = *money,
    .game_round = *gameRound
    };
    // need this in each fn to copy array vales to user_history
    memcpy(user_history[*gameRound].win_order, horse_race_order, sizeof(horse_race_order[0])*4);
    memcpy(user_history[*gameRound].bet_order, user_bet, sizeof(user_bet[0])*4);
  
  printf("|----------------------------------------------|\n\n");

  pauseScreen();
  
}

void checkWin_ExactaBox ( int* gameRound, unsigned int user_bet[], unsigned int horse_race_order[], int* money, char horse_names[][15], history* user_history) {
  *gameRound = *gameRound + 1;
  bool temp_win_lose; // to set in the history struct
  int tempBeforeMoney = *money; // to set the history struct value - money befor
  printf("|---------------    RESULTS     ---------------|\n");
  printf("|------------- YOU BET EXACTA BOX -------------|\n");
  printf("|--------- BET -------- |---- RACE RESULTS ----|\n");
  printf("| 1st: %d %-15s| %d %-15s    |\n", user_bet[0], horse_names[user_bet[0]-1], horse_race_order[0], horse_names[horse_race_order[0]-1] );
  printf("| 2nd: %d %-15s| %d %-15s    |\n", user_bet[1], horse_names[user_bet[1]-1], horse_race_order[1], horse_names[horse_race_order[1]-1] );
  printf("| 3rd:                  | %d %-15s    | \n", horse_race_order[2], horse_names[horse_race_order[2]-1] );
  printf("| 4th:                  | %d %-15s    | \n", horse_race_order[3], horse_names[horse_race_order[3]-1] ); 

  if ((user_bet[0] == horse_race_order[0] || 
       user_bet[0] == horse_race_order[1]) &&
      (user_bet[1] == horse_race_order[0] || 
       user_bet[1] == horse_race_order[1])) {
    *money = *money + 100;
    temp_win_lose = true;
    printf("|   YOU WIN!  Your total winnings are: $%-5d   |\n", *money);
  } else {
    *money = *money - 10;
    temp_win_lose = false;
    printf("|  YOU LOST!     Your account is now: $%-5d   |\n", *money);

  }
  // setting the hisotry log -----------------------------------------------
    user_history[*gameRound] = (history) {
    .win_lose = temp_win_lose, 
    .money_before = tempBeforeMoney,
    .money_after = *money,
    .game_round = *gameRound
    };
    // need this in each fn to copy array vales to user_history
    memcpy(user_history[*gameRound].win_order, horse_race_order, sizeof(horse_race_order[0])*4);
    memcpy(user_history[*gameRound].bet_order, user_bet, sizeof(user_bet[0])*4);
  
  printf("|----------------------------------------------|\n\n");

  pauseScreen();
}

void checkWin_Trifecta ( int* gameRound, unsigned int user_bet[], unsigned int horse_race_order[], int* money, char horse_names[][15], history* user_history) {
  bool temp_win_lose; // to set in the history struct
  *gameRound = *gameRound + 1;
  int tempBeforeMoney = *money; // to set the history struct value - money befor
  printf("|---------------    RESULTS     ---------------|\n");
  printf("|------------- YOU BET TRIFECTA  --------------|\n");
  printf("|--------- BET -------- |---- RACE RESULTS ----|\n");
  printf("| 1st: %d %-15s| %d %-15s    |\n", user_bet[0], horse_names[user_bet[0]-1], horse_race_order[0], horse_names[horse_race_order[0]-1] );
  printf("| 2nd: %d %-15s| %d %-15s    |\n", user_bet[1], horse_names[user_bet[1]-1], horse_race_order[1], horse_names[horse_race_order[1]-1] );
  printf("| 3nd: %d %-15s| %d %-15s    |\n", user_bet[1], horse_names[user_bet[1]-1], horse_race_order[2], horse_names[horse_race_order[2]-1] );
  printf("| 4th:                  | %d %-15s    | \n", horse_race_order[3], horse_names[horse_race_order[3]-1] ); 

  if (user_bet[0] == horse_race_order[0] &&
      user_bet[1] == horse_race_order[1] && 
      user_bet[2] == horse_race_order[2]) {
    *money = *money + 250;
    temp_win_lose = true;
    printf("|   YOU WIN!  Your total winnings are: $%-5d   |\n", *money);
  } else {
    *money = *money - 20;
    temp_win_lose = false;
    printf("|  YOU LOST!     Your account is now: $%-5d   |\n", *money);
  }
    // setting the hisotry log -----------------------------------------------
    user_history[*gameRound] = (history) {
    .win_lose = temp_win_lose, 
    .money_before = tempBeforeMoney,
    .money_after = *money,
    .game_round = *gameRound
    };
    // need this in each fn to copy array vales to user_history
    memcpy(user_history[*gameRound].win_order, horse_race_order, sizeof(horse_race_order[0])*4);
    memcpy(user_history[*gameRound].bet_order, user_bet, sizeof(user_bet[0])*4);
  
  printf("|----------------------------------------------|\n\n");

  pauseScreen();
}

void checkWin_TrifectaBox ( int* gameRound, unsigned int user_bet[], unsigned int horse_race_order[], int* money, char horse_names[][15], history* user_history) {
  bool temp_win_lose; // to set in the history struct
  *gameRound = *gameRound + 1;
  int tempBeforeMoney = *money; // to set the history struct value - money befor
  printf("|---------------    RESULTS     ---------------|\n");
  printf("|------------ YOU BET TRIFECTA BOX ------------|\n");
  printf("|--------- BET -------- |---- RACE RESULTS ----|\n");
  printf("| 1st: %d %-15s| %d %-15s    |\n", user_bet[0], horse_names[user_bet[0]-1], horse_race_order[0], horse_names[horse_race_order[0]-1] );
  printf("| 2nd: %d %-15s| %d %-15s    |\n", user_bet[1], horse_names[user_bet[1]-1], horse_race_order[1], horse_names[horse_race_order[1]-1] );
  printf("| 3nd: %d %-15s| %d %-15s    |\n", user_bet[1], horse_names[user_bet[1]-1], horse_race_order[2], horse_names[horse_race_order[2]-1] );
  printf("| 4th:                  | %d %-15s    | \n", horse_race_order[3], horse_names[horse_race_order[3]-1] ); 

  if ((user_bet[0] == horse_race_order[0] || 
       user_bet[0] == horse_race_order[1] || 
       user_bet[0] == horse_race_order[2]) && 
      (user_bet[1] == horse_race_order[0] || 
       user_bet[1] == horse_race_order[1] ||
       user_bet[1] == horse_race_order[2]) &&
      (user_bet[2] == horse_race_order[0] || 
       user_bet[2] == horse_race_order[1] ||
       user_bet[2] == horse_race_order[2])) {
    *money = *money + 250;
    temp_win_lose = true;
    printf("|   YOU WIN!  Your total winnings are: $%-5d   |\n", *money);
  } else {
    *money = *money - 20;
    temp_win_lose = false;
    printf("|  YOU LOST!     Your account is now: $%-5d   |\n", *money);
  }
    // setting the hisotry log -----------------------------------------------
    user_history[*gameRound] = (history) {
    .win_lose = temp_win_lose, 
    .money_before = tempBeforeMoney,
    .money_after = *money,
    .game_round = *gameRound
    };
    // need this in each fn to copy array vales to user_history
    memcpy(user_history[*gameRound].win_order, horse_race_order, sizeof(horse_race_order[0])*4);
    memcpy(user_history[*gameRound].bet_order, user_bet, sizeof(user_bet[0])*4);
  
  printf("|----------------------------------------------|\n\n");

  pauseScreen();
}


//------------------------------------ MAIN --------------------------------------
int main () {

  int money = 200;
  int gameRound = 0; // itialized at zero, for no game yet.
  unsigned int user_input, max_number_to_check;  //max number is a number for input checking for a maximum number, ex you need to check the number between 1-4 only. 
  unsigned int horse_race_order[] = {1, 2, 3, 4};  // intial horse numbers to start game.
  unsigned int user_bet[4] = {0, 0, 0, 100}; //Positions 1 -  3 are user horse choices. While 4th pos is type of race, ex 101 = exacta, 102 exacta box etc.  
  
  int array_length = sizeof horse_race_order / sizeof horse_race_order[0];
  bool toggle_cheat = true;
  bool exit_game = false;
  history user_history[100]; // could be dynamic.. 

  srand(time(NULL));  //using rand()

  char horse_names[][15] = {
  "Black Lighting",
  "Fools Gold", 
  "Leslie's Folly",
  "TripleX"
  };
  
  // check if cheat is on?
  // ---------------------------- GAME LOOP -------------------------------------
  do {

  // Fisher yates scamble array
  // TODO move to own fn!
  //array_randomize_elements (horse_race_order, array_length);
  for (int i = array_length-1; i >= 1; i--) {  
    int temp_random_array_pos = rand() %(i+1); // random range will be 0 to %number, decrements as decreases 
    int temp;
      if (temp_random_array_pos != (i)) {  
        temp = horse_race_order[i];
        horse_race_order[i] = horse_race_order[temp_random_array_pos];
        horse_race_order[temp_random_array_pos] = temp;
      }
    }

  // take user input and display
  //system("clear");  // 1st clear the terminal to only show this screen.
  printf("|--------------------------------- HORSE RACING! ---------------------------------|\n");
  printf("|------------------------------------------------------------------ RACE #:  %4d |\n", gameRound);
  printf("|------------------------------------------------------------------ USD  $:  %4.2d |\n", money);
  printf("|---------------------------------------------------------------------------------|\n");
  printf("|  1) Place an Exacta bet - 1st and 2nd correctly       *** cost $15 - win $150   |\n");
  printf("|  2) Place an Exactabox bet - 1st or 2nd any order     *** cost $10 - win $100   |\n");
  printf("|  3) Place an Trifecta bet - 1st, 2nd and 3rd correct  *** cost $20 - win $250   |\n");
  printf("|  4) Place an TrifectBox bet - 1st, 2nd, 3rd any order *** cost $18 - win $180   |\n");
  printf("|  5) See your USD Balance                                                        |\n");
  printf("|  6) Exit                                                                        |\n");
  printf("|------------------------------------- MENU --------------------------------------|\n");
  if (toggle_cheat) {
    // TODO current cheat is set via bool variable - can make an arg for running? 
    printf("| Secret Cheat Mode\n| 1st: %d \n| 2nd: %d\n| 3rd: %d \n", horse_race_order[0], horse_race_order[1], horse_race_order[2]);
    printf("|---------------------------------------------------------------------------------|\n");
  }
  // get menu choices from user
  // TODO need to check if user has enough money for the current bet... 
  printf("| ");
  getUserInput_UInt(&user_input, 6);

  switch (user_input) {
    case 1:
       user_bet[2] = 0; //clear 3rd pos - this type does not have this
       user_bet[3] = 101; // 101 = exacta 
       printf("|---------------------------------------------------------------------------------|\n");
       printf("|--------------------------------- EXACTA BET ------------------------------------|\n");
       printf("|---------------------------------------------------------------------------------|\n");

       printf("| Enter horse for 1st Place\n ");
       printf("| ");
       getUserInput_UInt(&user_bet[0], 4);

       printf("| Enter horse for 2nd Place\n ");
       printf("| ");
//TODO check if not value of 1st pos.
       getUserInput_UInt(&user_bet[1], 4);

       system("clear"); 
       checkWin_Exacta(&gameRound, user_bet, horse_race_order, &money, horse_names, user_history); 
       system("clear"); 
       break;

    case 2: 
       user_bet[2] = 0; //clear 3rd pos - this type does not have this
       user_bet[3] = 102; // 102 = exacta box
       printf("|---------------------------------------------------------------------------------|\n");
       printf("|------------------------------- EXACTA BOX BET ----------------------------------|\n");
       printf("|---------------------------------------------------------------------------------|\n");

       printf("| Enter your choice for 1st or 2nd Place\n ");
       printf("| ");
       getUserInput_UInt(&user_bet[0], 4);

       printf("| Enter your choice for 1st or 2nd Place\n ");
       printf("| ");
       getUserInput_UInt(&user_bet[1], 4);
 
       system("clear"); 
       checkWin_ExactaBox(&gameRound, user_bet, horse_race_order, &money, horse_names, user_history);
       break;

    case 3:
       user_bet[3] = 103; // 103 = Trifecta

       printf("|---------------------------------------------------------------------------------|\n");
       printf("|------------------------------ TRIFECTA  BET ------------------------------------|\n");
       printf("|---------------------------------------------------------------------------------|\n");

       printf("Enter your choice for 1st place\n ");
       printf("| ");
       getUserInput_UInt(&user_bet[0], 4);

       printf("Enter your choice for 2nd place\n ");
       printf("| ");
       getUserInput_UInt(&user_bet[1], 4);

       printf("Enter your choice for 3rd place\n ");
       printf("| ");
       getUserInput_UInt(&user_bet[2], 4);

       system("clear"); 
       checkWin_Trifecta(&gameRound, user_bet, horse_race_order, &money, horse_names, user_history);
       break;

    case 4: 
       user_bet[3] = 103; // 104 = Trifecta box

       printf("|---------------------------------------------------------------------------------|\n");
       printf("|---------------------------- TRIFECTA  BOX BET ----------------------------------|\n");
       printf("|---------------------------------------------------------------------------------|\n");

       printf("Enter your choice for 1st, 2nd or 3rd place\n ");
       getUserInput_UInt(&user_bet[0], 4);

       printf("Enter your choice for 1st, 2nd or 3rd place\n ");
       getUserInput_UInt(&user_bet[1], 4);

       printf("Enter your choice for 1st, 2nd or 3rd place\n ");
       getUserInput_UInt(&user_bet[2], 4);

       printf("You have chosen: %u 1st and %u second\n", user_bet[0], user_bet[1]);
       system("clear"); 
       checkWin_TrifectaBox(&gameRound, user_bet, horse_race_order, &money, horse_names, user_history);
       break;

    case 5:
       system("clear"); 
       printBettingHistory(user_history, &gameRound);
       pauseScreen();
       system("clear"); 
       break;

    case 6:
       system("clear");
       printf("---- Goodbye you gambling fool! ----\n\n");
       exit_game = true;
       break;

    default:
       printf("Invalid Choice! \n");
       break;
       
  }

  } while (exit_game != true);
// end of do while loop

  return 0;
}