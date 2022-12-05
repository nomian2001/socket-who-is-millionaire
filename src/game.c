/**
 * This game logic is based on the popular game show who wants to be a Millionaire
 *
 * we will be implementing a Quiz game where n players can play simultaneously (Each
 * player playing their own game).
 *
 * Each game contains 10 questions with the four options and it is divided into 3 segments.
 *
 * First segment has 4 questions and the next two segments have three questions each.
 *
 * @author: Abdul Hakim Shanavas
 * @author: Maha Krishnan Krishnan
 */

#include <iostream>
#include <sstream>
#include "game.h"
#include <cstring>

using std::cin;
using std::cout;
using std::endl;
using std::string;

std::vector<std::string> Game::questions_;
std::vector<std::string> Game::options_;
std::vector<std::string> Game::correct_answers_;
std::vector<std::string> Game::prize_money_;


/**
 * Game constructor will create the new game for each client
 * @param player
 * @param server
 */
Game::Game(std::string player, int server) : attempts_(3), prize_won_("0"), player_(player), server_(server),
                                             buffer_() {

}

/**
 * Static initialize game method will it be called only once by the server as soon the server establishes the connection
 *
 * This method set of default questions and 4 options for each questions and the answer for the questions which all are
 * stored in the vector.
 *
 * This method also contains the prize money for each questions which is also stored in the vector
 */

void Game::initialize_game() {

    /* Set of questions which is tored in the vector*/
    questions_.emplace_back("1. Declaring a pointer more than once may cause __");
    questions_.emplace_back("2. An expression A.B in C++ means __");
    questions_.emplace_back("3. __ function is used to allocate space for array in memory.");
    questions_.emplace_back("4. A pointer pointing to a variable that is not initialized is called __");
    questions_.emplace_back("5. A class who's objects can not be created is known as ___");
    questions_.emplace_back("6. Which class allows only one object to be created.");
    questions_.emplace_back("7. Reusability of code in C++ is achieved through __");
    questions_.emplace_back("8. In C++ Program, inline functions are expanded during __");
    questions_.emplace_back("9. To perform file input / output operation in C++, we must include which header file ?");
    questions_.emplace_back("10. An exception in C++ can be generated using which keywords.");


    /*Four Options to each questions which is stored into the vector */
    options_.emplace_back("1.Error ,2.Abort ,3.Trap ,4.Null ");
    options_.emplace_back(
            "1.A is member of object B ,2.B is member of Object A ,3.Product of A and B ,4.None of these ");
    options_.emplace_back("1.malloc() ,2.realloc() ,3.alloc() ,4.calloc() ");
    options_.emplace_back("1.Void Pointer ,2.Null Pointer ,3.Empty Pointer ,4.Wild Pointer ");
    options_.emplace_back("1.Absurd Class ,2.Dead Class ,3.Super Class ,4.Abstract Class ");
    options_.emplace_back("1.Nuclear Family Class ,2.Abstract Class ,3.Singleton Class ,4.Numero Uno Class ");
    options_.emplace_back("1.Polymorphism ,2.Inheritance ,3.Encapsulation ,4.Both A and B ");
    options_.emplace_back("1.Run Time ,2.Compile Time ,3.Debug Time ,4.Coding Time ");
    options_.emplace_back("1.<fiostream> ,2.<ifstream> ,3.<ofstream> ,4.<fstream> ");
    options_.emplace_back("1.thrown ,2.threw ,3.throw ,4.throws ");


    /* Correct answer for each question whichh is stored into the vector*/
    correct_answers_.emplace_back("3.Trap ");
    correct_answers_.emplace_back("2.B is member of Object A ");
    correct_answers_.emplace_back("4.calloc() ");
    correct_answers_.emplace_back("2.Null Pointer ");
    correct_answers_.emplace_back("4.Abstract Class ");
    correct_answers_.emplace_back("3.Singleton Class ");
    correct_answers_.emplace_back("2.Inheritance ");
    correct_answers_.emplace_back("1.Run Time ");
    correct_answers_.emplace_back("4.<fstream> ");
    correct_answers_.emplace_back("3.throw ");


    /* Prize money for each question which is stored into the vector*/
    prize_money_.emplace_back("$2,000");
    prize_money_.emplace_back("$4,000");
    prize_money_.emplace_back("$8,000");
    prize_money_.emplace_back("$16,000");
    prize_money_.emplace_back("$32,000");
    prize_money_.emplace_back("$64,000");
    prize_money_.emplace_back("$128,000");
    prize_money_.emplace_back("$250,000");
    prize_money_.emplace_back("$500,000");
    prize_money_.emplace_back("$1,000,000");

}


/**
 * This method is to implement the game logic.
 *
 * Once the thread has been succesfully started the play game will implement
 *
 */
void Game::play_game() {

    /* Sending the welcome message to the client from the game server*/
    string welcome = "\n\nWelcome " + player_ + "\n";
    strcpy(buffer_, welcome.c_str());
    send(server_, buffer_, 1024, 0);

    /*Counter to track the questions*/
    int question_counter = 0;

    /* Iterating the total number of questions in the vector*/
    for (auto iter = questions_.begin(); iter != questions_.end(); ++iter) {
        question_counter++;
        string option;
        int answer;

        /* Get the separate */
        std::vector<string> options;
        std::istringstream optionStream(options_[question_counter - 1]);
        while (std::getline(optionStream, option, ',')) {
            options.emplace_back(option);
        }


        /* Send the questions and its options to the client user*/
        string it = *iter;
        it += "\n" + options_[question_counter - 1];
        strcpy(buffer_, it.c_str());
        send(server_, buffer_, 1024, 0);

        /*Get the option number from the client*/
        recv(server_, buffer_, 1024, 0);
        std::stringstream strValue;
        strValue << buffer_;
        strValue >> answer;

        /* Checking if the client provides the input or not*/
        if (buffer_ != NULL) {

            /* Checking the answer for the question with the input provided by the user
             * If correct then else*/
            if (correct_answers_[question_counter - 1] == options[answer - 1]) {

                /* Notify the user that given input is correct*/
                strcpy(buffer_, "\nCorrect!");
                send(server_, buffer_, 1024, 0);

                /* Get the prize money for the questions*/
                prize_won_ = prize_money_[question_counter - 1];

                /* If the user answered all the questions correctly then notify the user that he/she won the game*/
                if (question_counter == 10) {
                    strcpy(buffer_, "Congratulations! You are a Millionaire!");
                    send(server_, buffer_, 1024, 0);
                    break;
                } else {

                    /*Else Print the total prize that user won and the total life that the user has to the user*/
                    string message =
                            "Prize Won " + prize_won_ + "\n" + "Life line remaining : " + std::to_string(attempts_) +
                            "\n";
                    strcpy(buffer_, message.c_str());
                    send(server_, buffer_, 1024, 0);
                }
            } else {

                /* Notify the user that given input is wrong*/
                strcpy(buffer_, "\nWrong!");
                send(server_, buffer_, 1024, 0);
                --attempts_;

                /* If the user used all the given lifes then the game will end*/
                if (attempts_ < 1) {

                    /*If the user answered questions between 5 and 7 then the user will receive $16,000 prize money*/
                    if (question_counter > 4 && question_counter <= 7) {
                        prize_won_ = prize_money_[3];

                        /*If the user answered questions 8 and 10 then the user will receive $128,000 prize money*/
                    } else if (question_counter > 7) {
                        prize_won_ = prize_money_[6];

                        /*If the user answered questions between 1 and 4 then the user will receive nothing*/
                    } else {
                        prize_won_ = "0";
                    }

                    string message = "Game Over! \nTotal prize money won : " + prize_won_;
                    strcpy(buffer_, message.c_str());
                    send(server_, buffer_, 1024, 0);
                    break;
                } else {
                    /*If the user still has life. Display the life to the user and display the same question again to answer*/
                    string message = "Life line remaining : " + std::to_string(attempts_) + "\n";
                    strcpy(buffer_, message.c_str());
                    send(server_, buffer_, 1024, 0);
                    iter--;
                    question_counter--;
                }
            }
        }
    }

}