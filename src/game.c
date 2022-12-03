#include "game.h"
#include <stddef.h>


Game* new_game(char player,int server){
  Game* g = malloc(sizeof(Game));
  g->attempts_ = 1;
  strcpy(g->prize_won_, "0");
  strcpy(g->player_, player);
  g->server_ = server;
  return g;
}

void play_game(Game* game){
 /* Sending the welcome message to the client from the game server*/
    strcpy(game->buffer_, "\n\nWelcome new player\n ");
    send(game->server_, game->buffer_, 1024, 0);

    /*Counter to track the questions*/
    int question_counter = 0;

    /* Iterating the total number of questions in the vector*/
    for (int iter = 0; iter < 4; ++iter) {
        question_counter++;
        char* option;
        int answer;

        /* Get the separate */
        char** options = (char**)malloc(sizeof(char*)*4);;
        option = strtok(game->options_[question_counter - 1],",");
        int optIter = 0;
        while (option != NULL) {
            options[optIter] = malloc(sizeof(char)*50);
	    strcpy(options[optIter], option);
	    optIter++;
	    option = strtok(NULL, ",");
        }

        /* Send the questions and its options to the client user*/
        char* it = strcat(game->questions_[iter],game->options_[question_counter - 1]);
        strcpy(game->buffer_, it);
        send(game->server_, game->buffer_, 1024, 0);

        /*Get the option number from the client*/
        recv(game->server_, game->buffer_, 1024, 0);
        char* strValue;
        strValue = game->buffer_;
        answer = atoi(*strValue);

        /* Checking if the client provides the input or not*/
        if (game->buffer_ != NULL) {

            /* Checking the answer for the question with the input provided by the user
             * If correct then else*/
            if (game->correct_answers_[question_counter - 1] == options[answer - 1]) {

                /* Notify the user that given input is correct*/
                strcpy(game->buffer_, "\nCorrect!");
                send(game->server_, game->buffer_, 1024, 0);

                /* Get the prize money for the questions*/
                strcpy(game->prize_won_,game->prize_money_[question_counter - 1]);

                /* If the user answered all the questions correctly then notify the user that he/she won the game*/
                if (question_counter == 10) {
                    strcpy(game->buffer_, "Congratulations! You are a Millionaire!");
                    send(game->server_, game->buffer_, 1024, 0);
                    break;
                } else {

                    /*Else Print the total prize that user won and the total life that the user has to the user*/
                    char message[] = "You Won";
                    //"Prize Won " + game->prize_won_ + "\n" + "Life line remaining : " + itoa(game->attempts_,10) +"\n";
                    strcpy(game->buffer_, message);
                    send(game->server_, game->buffer_, 1024, 0);
                }
            } else {

                /* Notify the user that given input is wrong*/
                strcpy(game->buffer_, "\nWrong!");
                send(game->server_, game->buffer_, 1024, 0);
                --game->attempts_;

                /* If the user used all the given lifes then the game will end*/
                if (game->attempts_ < 1) {

                    /*If the user answered questions between 5 and 7 then the user will receive $16,000 prize money*/
                    if (question_counter > 4 && question_counter <= 7) {
                        strcpy(game->prize_won_,game->prize_money_[3]);

                        /*If the user answered questions 8 and 10 then the user will receive $128,000 prize money*/
                    } else if (question_counter > 7) {
                        strcpy(game->prize_won_,game->prize_money_[6]);

                        /*If the user answered questions between 1 and 4 then the user will receive nothing*/
                    } else {
                        strcpy(game->prize_won_,"0");
                    }

                    char message[] = "Game Over!";
                    strcpy(game->buffer_, message);
                    send(game->server_, game->buffer_, 1024, 0);
                    break;
                } 
            }
        }
    }
}

static void initialize_game(Game* game){

	game->questions_ = (char**)malloc(sizeof(char*)*4);
	game->questions_[0] = malloc(sizeof(char)*50);
	strcpy(game->questions_[0], "1. Declaring a pointer more than once may cause __");
	game->questions_[1] = malloc(sizeof(char)*50);
	strcpy(game->questions_[1], "1. Declaring a pointer more than once may cause __");
	game->questions_[2] = malloc(sizeof(char)*50);
	strcpy(game->questions_[2], "1. Declaring a pointer more than once may cause __");
	game->questions_[3] = malloc(sizeof(char)*50);
	strcpy(game->questions_[3], "1. Declaring a pointer more than once may cause __");
    

    /*Four Options to each questions which is stored into the vector */
    	game->options_ = (char**)malloc(sizeof(char*)*4);
	game->options_[0] = malloc(sizeof(char)*33);
	strcpy(game->options_[0], "1.Error ,2.Abort ,3.Trap ,4.Null ");
	game->options_[1] = malloc(sizeof(char)*33);
	strcpy(game->options_[1], "1.Error ,2.Abort ,3.Trap ,4.Null ");
	game->options_[2] = malloc(sizeof(char)*33);
	strcpy(game->options_[2], "1.Error ,2.Abort ,3.Trap ,4.Null ");
	game->options_[3] = malloc(sizeof(char)*33);
	strcpy(game->options_[3], "1.Error ,2.Abort ,3.Trap ,4.Null ");

    
    /* Correct answer for each question whichh is stored into the vector*/
        game->correct_answers_ = (char**)malloc(sizeof(char*)*4);
	game->correct_answers_[0] = malloc(sizeof(char)*8);
	strcpy(game->correct_answers_[0], "1.Error ");
	game->correct_answers_[1] = malloc(sizeof(char)*8);
	strcpy(game->correct_answers_[1], "2.Abort ");
	game->correct_answers_[2] = malloc(sizeof(char)*8);
	strcpy(game->correct_answers_[2], "3.Trap ");
	game->correct_answers_[3] = malloc(sizeof(char)*8);
	strcpy(game->correct_answers_[3], "4.Null ");
    
    /* Prize money for each question which is stored into the vector*/
    	game->prize_money_ = (char**)malloc(sizeof(char*)*10);
    	game->prize_money_[0] = malloc(sizeof(char)*6);
	strcpy(game->prize_money_[0], "$2,000");
	game->prize_money_[1] = malloc(sizeof(char)*6);
	strcpy(game->prize_money_[1], "$4,000");
	game->prize_money_[2] = malloc(sizeof(char)*6);
	strcpy(game->prize_money_[2], "$8,000");
	game->prize_money_[3] = malloc(sizeof(char)*7);
	strcpy(game->prize_money_[3], "$16,000");
	game->prize_money_[4] = malloc(sizeof(char)*7);
	strcpy(game->prize_money_[4], "$32,000");
	game->prize_money_[5] = malloc(sizeof(char)*7);
	strcpy(game->prize_money_[5], "$64,000");
	game->prize_money_[6] = malloc(sizeof(char)*8);
	strcpy(game->prize_money_[6], "$128,000");
	game->prize_money_[7] = malloc(sizeof(char)*8);
	strcpy(game->prize_money_[7], "$250,000");
	game->prize_money_[8] = malloc(sizeof(char)*8);
	strcpy(game->prize_money_[8], "$500,000");
	game->prize_money_[9] = malloc(sizeof(char)*10);
	strcpy(game->prize_money_[9], "$1,000,000");

}