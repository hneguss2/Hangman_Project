/*Greet the user and Display Menu
INIT MENU_OPTION
INPUT MENU_OPTION
INIT SET_WORDS: an array that has 10 elements in 2D */
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<stdbool.h>
#include<string.h>

//Sets a struct with a user name and score
typedef struct {
    char pname[4];
    int score;
} Players_Data;

//Declaring functions
int PLAY_GAME();
void TRACK_GAME(Players_Data game_user[], char user_name[], int score);
void DISPLAY_STATISTICS(Players_Data game_user[]);
void clean_stdin(void);


int main(void){

    Players_Data game_user[50]; // Sets an array of structs that can contain 3 letter player name, and their score.

    //Sets all player names and scores to NUl and -850, this is for my code to guarantee what is in each struct of the array.
    for(int i = 0; i < 50; i++){
        strcpy(game_user[i].pname, "NUL");
        game_user[i].score = -850;
    }

    //Main Menu, continues to run until i doesn't equal 0, which is when they select 3.
    for(int i = 0; i == 0;){

        int menu_input;
        printf("\nHowdy fellow Player!!\n               . . .Main Menu. . . \nPlease select a number\n(1) Play Hangman\n(2) Display Statistics\n(3) Quit\n\nPlease select a number ");
        scanf("%d", &menu_input);

        if(menu_input == 1){
            
            char user_name[4];
            printf("Let's play Hangman ;) \n Please enter your initials: \n");
            scanf("%3s", user_name);
            int score = PLAY_GAME();
            printf("\nPlayer: %s\nScore: %d\n", user_name, score);
            TRACK_GAME(game_user, user_name, score);

        }else if(menu_input == 2){
            DISPLAY_STATISTICS(game_user);
            printf("\n");
        }else if(menu_input == 3){
            printf("Exiting Program\n");
            i = 1;
        }else{
            printf("Invalid response... try again.\n");
        }
    }

    return 0;

}

int PLAY_GAME(){

    //declaring all variables needed
    int word = (rand() % 10) + 1;
    int score = 0;
    int check[26] = {0};
    char Listed_Word[10][31] = {
        {'e', 'a', 't', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'},

        {'g', 'h', 'o', 's', 't', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'},

        {'d', 'e', 'e', 'p', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'},

        {'l', 'a', 'c', 'y', 'e', 'r', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'},

        {'s', 'e', 'a', 't', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'},

        {'s', 'p', 'a', 'g', 'h', 'e', 't', 't', 'i', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'},

        {'e', 'x', 't', 'r', 'l', 'a', 'r', 'g', 'e', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'},

        {'m', 'i', 'n', 'e', 'c', 'r', 'a', 'f', 't', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'},

        {'c', 'a', 't', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'},

        {'f', 'i', 't', 'n', 'e', 's', 's', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'},
    };
    char word_attempt[31] = {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'};
    char player_char;
    char guess[31];
    int word_length = 0; 

    //setting up board, checks if a character in a word is character and adds a _ to the board
    for(int i = 0; i < 31; i++){
        if(Listed_Word[word - 1][i] >= 'a' && Listed_Word[word - 1][i] <= 'z'){
            word_attempt[i] = '_';
            word_length += 1;
        }
    }

    //Game plays, asks for inputs and gives outputs depending on their input.
    for(int counter = 1; counter < 11; counter++){

        clean_stdin();

        printf("\nRound %d: Current Board: %s\n", counter, word_attempt);

        //This portion of the code tells the user what letters are available and have been used.
        printf("\nYou can guess:");
        for(int attempt_left = 0; attempt_left < 26; attempt_left++){
            char change_to_char = (char) (attempt_left + 'a');
            if(check[attempt_left] == 0){
                printf(" %c", change_to_char);
            }
        }
        printf("\nYou have used:");
        for(int used = 0; used < 26; used++){
            char change_to_char = (char) (used + 'a');
            if(check[used] == 1){
                printf(" %c", change_to_char);
            }
        }

        char try_word;
        printf("\n\n Can you think of a word this length? (y/n): ");
        try_word = getchar();

        int Completion_Check = 0; //This variable is used to check if the user has completed the word at any point in the loop
        if(try_word == 'y'){ //Game asks for string input, checks to see if its correct.

            clean_stdin();

            printf("What is it?  ");
            scanf("%30s", guess);

            int valid_letters_check = 0; //This for loop checks to see if all the characters that the user inputed are lowercase, uppercase, or not a valid option. Since continue would only break the for loop, I used this line as a getaround.
            for(int lower_counter = 0; lower_counter < 31; lower_counter++){
                if ('a' <= guess[lower_counter] && guess[lower_counter] <= 'z'){
                    guess[lower_counter] = guess[lower_counter];
                }else if('A' <= guess[lower_counter] && guess[lower_counter] <= 'Z'){
                    guess[lower_counter] = tolower(guess[lower_counter]);
                }else if('\0' == guess[lower_counter]){
                    break;
                }else{
                    printf("One or more of your characters are invalid! Try again.\n");
                    counter = counter - 1;
                    valid_letters_check = 1;
                    break;
                }
            }
            if(valid_letters_check == 1){
                continue;
            }

            int user_correct = 0; //This loop checks if the user input is the same as the word selected
            int user_correct_check = 0;
            for(int same_check = 0; same_check < word_length; same_check++){
                if(Listed_Word[word - 1][same_check] == guess[same_check]){
                    user_correct_check = user_correct_check + 1;
                }
                if(user_correct_check == word_length){
                    user_correct = 1;
                }
            }

            //If the user is correct I want the word to be displayed. So if user is correct it updates the board to the word of the PLAY_GAME.
            if(user_correct == 1){
                score = score + 200;
                Completion_Check = word_length;
                for(int updating_board = 0; updating_board < 31; updating_board++){
                    word_attempt[updating_board] = Listed_Word[word - 1][updating_board];
                }
            }else{
                printf("Your guess was incorrect!\n");
                score = score - 80;
            }

        }else if(try_word == 'n'){ //Game asks for user character input, plays hangman like normal.

            clean_stdin();

            printf("Enter a character: ");
            player_char = getchar();


            //Checks if the user's character is valid
            if ('a' <= player_char && player_char <= 'z'){
                player_char = player_char;
            }else if('A' <= player_char && player_char <= 'Z'){
                player_char = tolower(player_char);
            }else{
                printf("That character is invalid!\n");
                counter = counter - 1;
                continue;
            }
        
            int char_index = (int) (player_char - 'a');

            //Checks if the letter has been used before, than checks if it is in the word and rewards/deducts points accordingly.
            if(check[char_index] == 0){
                int found = 0;
                for(int counting = 0; counting < word_length; counting++){
                if(player_char == Listed_Word[word - 1][counting]){
                    printf("You found a letter!\n");
                    score += 10;
                    word_attempt[counting] = player_char;
                    check[char_index] = 1;
                    found = 1;
                }
            }
            if(found == 0){
                printf("This character is not in the word!\n");
                score -= 2;
                check[char_index] = 1;
            }else{
                counter = counter - 1;
            }


            //Loop to check if the PLAY_GAME is finished
            for(int finished = 0; finished < word_length; finished++){
                if(word_attempt[finished] == Listed_Word[word - 1][finished]){
                    Completion_Check += 1;
                }
            }

            }else{
            printf("You have already used this character before.\n");
            counter = counter - 1;
            }

        }else{ //If the user didn't enter y or n, then it restarts the loop and tells the player to type y or n.
            printf("That isn't any of the options, type y or n!");
            counter = counter - 1;
            continue;
        }


        //If the user was correct at any point in the loop this ends the PLAY_GAME
        if(Completion_Check == word_length){
            printf("Good work! You found the word!\n");
            printf("\nThe word was: %s\n", word_attempt);
            score += 100;
            counter = 11;
        }

        //If user has used all ten rounds displays game over and tells the user what the word was.
        if(counter == 10){
            printf("YOU lOST :( \n GAME OVER!\n");
            for(int updating_board = 0; updating_board < 31; updating_board++){
                word_attempt[updating_board] = Listed_Word[word - 1][updating_board];
            }
            printf("The word was: %s", word_attempt);
            score -= 40;
        }

    }

    return score;

}

void TRACK_GAME(Players_Data players[], char user_name[], int score){
    

    //Creates temp player names and scores to do operations on, ensures no data is lost.
    char temp_user[4];
    int temp_score_one;
    char new_user[4];
    int new_score;

    strcpy(new_user, user_name);
    new_score = score;

    //Sorts new score and all previous scores by greatest to least (displays max 50)
    for(int i = 0; i < 50; i++){

        strcpy(temp_user, players[i].pname);
        temp_score_one = players[i].score;

        if(new_score > temp_score_one){
            players[i].score = new_score;
            strcpy(players[i].pname, new_user);
            new_score = temp_score_one;
            strcpy(new_user, temp_user);
        }
    }

}

void DISPLAY_STATISTICS(Players_Data players[]){
    
    printf("\nPlayer  Score");

    //Loops to print all scores, stops if player name is NUL as no score can be lower than NUL's score.
    for(int i = 0; i < 50; i++){
        if(players[i].score == -850){
            break;
        }else{
            printf("\n%s    %d", players[i].pname, players[i].score);
        }
    }

}

void clean_stdin(void){
    int c;
    do{
        c = getchar();
    } while (c != '\n' && c != EOF);
}