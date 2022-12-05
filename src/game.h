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



struct Game {

/**
     * Game constructor will create the new game for each client
     * @param player
     * @param server
 */


    /*To get and store the player name when new unique game object has been created*/
    char player[10];


    /* Server reads the values from the socket connection to the dynamic variable*/
    char buffer_[1024];

    /*Vector Collection to store the questions*/
    static vector<std::string> questions_;

    /*Vector Collection to sstore the options to the questions*/
    static vector<std::string> options_;

    /*Vector Collection to store the correct answers to the questions*/
    static vector<std::string> correct_answers_;

    /*Vector Collection to store the prize money to the questions*/
    static vector<std::string> prize_money_;


};


Game(char* player,int server);

void play_game();

static void initialize_game();


#endif //MILLIONAIREGAME_GAME_H
