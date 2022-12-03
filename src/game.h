/**
 * This game logic is based on the popular game show who wants to be a Millionaire
 *
 * we will be implementing a Quiz game where n players can play simultaneously (Each
 * player playing their own game).
 *
 *
 * Each game contains 10 questions with the four options and it is divided into 3 segments.
 *
 * First segment has 4 questions and the next two segments have three questions each.
 *
 */

#ifndef MILLIONAIREGAME_GAME_H
#define MILLIONAIREGAME_GAME_H


typedef struct {

/**
     * Game constructor will create the new game for each client
     * @param player
     * @param server
 */
/*To track the total number of attempts that the user has*/
    int attempts_;
/*To get the prize money for the particular question*/
    char prize_won_[1000];

    /*To get and store the player name when new unique game object has been created*/
    char player_[1000];

    /*Unique Server connection number to connect between client and server*/
    int server_;

    /* Server reads the values from the socket connection to the dynamic variable*/
    char buffer_[1024];

    /*Collection to store the questions*/
     char** questions_;

    /*Collection to sstore the options to the questions*/
     char** options_;
     
    /*Collection to store the correct answers to the questions*/
     char** correct_answers_;

    /*Collection to store the prize money to the questions*/
     char** prize_money_;


}Game;

Game* new_game(char player,int server);

void play_game(Game* game);

static void initialize_game(Game* game);


#endif //MILLIONAIREGAME_GAME_H