#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <limits>

#define MAX 20

//               I don't want to write this every time so using BodyPartVector
//                                      |   |   |
//                                      v   v   v
using BodyPartVector = std::vector<std::pair<std::pair<int, int>, std::string>>;

class Hangman
{
private:
    std::vector<std::vector<std::string>> hangman;

    //See? Would've been a lot
    BodyPartVector bodyParts;

    //decides which body part to add to hangman
    int bodyPartIndex;
public:
    //constructor
    Hangman(int rows, int cols)
    {
        hangman.resize(rows, std::vector<std::string>(cols));
        createHangman();       //Function definition is a ways down

        // Body parts and their locations in the vector of vector of strings
        bodyParts = { {{9, 12}, "O"} ,
                      {{10,11}, "/"} ,
                      {{11,10}, "/" },
                      {{10,13}, "\\"},
                      {{11,14}, "\\"},
                      {{10,12}, "|" },
                      {{11,12}, "|" },
                      {{12,11}, "/" },
                      {{13,10}, "/" },
                      {{12,13}, "\\"},
                      {{13,14}, "\\"} };
    }

    //getter functions
    BodyPartVector getBodyParts()
    {
        return bodyParts;
    }

    int getBodyPartIndex() const
    {
        return bodyPartIndex;
    }

    //simple nested for loop to create the hangman. (MAX = 20, it's in #define)
    void drawHangman()
    {
        for (int i = 0; i < MAX; i++)
        {
            for (int j = 0; j < MAX; j++)
            {
                std::cout << hangman[i][j];
            }
            std::cout << std::endl;
        }
    }

    void addHangmanPart()
    {
        //So I don't have to write all that.
        int xIndex = bodyParts[bodyPartIndex].first.first;                  
        int yIndex = bodyParts[bodyPartIndex].first.second;
        std::string bodyPartToAdd = bodyParts[bodyPartIndex].second;

        hangman[xIndex][yIndex] = bodyPartToAdd;

        //So the index will increase every time the function is called, meaning the
        //body part added will be different up until a game over. Kind of like
        //a for loop whose iterations are spread out through the game
        if (bodyPartIndex < 11)
            bodyPartIndex++;
    }

    void createHangman()
    {
        bodyPartIndex = 0;
        //The gallows
        hangman = { {  " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},  //0
                    {  " ", " ", " ", " ", " ", "|", "-", "-", "-", "-", "-", "-", "-", " ", " ", " ", " ", " ", " ", " "},  //1
                    {  " ", " ", " ", " ", " ", "|", " ", " ", " ", " ", " ", " ", "|", " ", " ", " ", " ", " ", " ", " "},  //2
                    {  " ", " ", " ", " ", " ", "|", " ", " ", " ", " ", " ", " ", "|", " ", " ", " ", " ", " ", " ", " "},  //3
                    {  " ", " ", " ", " ", " ", "|", " ", " ", " ", " ", " ", " ", "|", " ", " ", " ", " ", " ", " ", " "},  //4
                    {  " ", " ", " ", " ", " ", "|", " ", " ", " ", " ", " ", " ", "|", " ", " ", " ", " ", " ", " ", " "},  //5
                    {  " ", " ", " ", " ", " ", "|", " ", " ", " ", " ", " ", " ", "|", " ", " ", " ", " ", " ", " ", " "},  //6
                    {  " ", " ", " ", " ", " ", "|", " ", " ", " ", " ", " ", " ", "|", " ", " ", " ", " ", " ", " ", " "},  //7
                    {  " ", " ", " ", " ", " ", "|", " ", " ", " ", " ", " ", " ", "|", " ", " ", " ", " ", " ", " ", " "},  //8
                    {  " ", " ", " ", " ", " ", "|", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},  //9
                    {  " ", " ", " ", " ", " ", "|", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},  //10
                    {  " ", " ", " ", " ", " ", "|", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},  //11
                    {  " ", " ", " ", " ", " ", "|", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},  //12
                    {  " ", " ", " ", " ", " ", "|", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},  //13
                    {  " ", " ", " ", " ", " ", "|", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},  //14
                    {  " ", " ", " ", " ", " ", "|", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},  //15
                    {  " ", " ", " ", " ", " ", "|", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},  //16
                    {  " ", " ", " ", " ", " ", "|", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},  //17
                    {  " ", " ", " ", " ", " ", "|", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},  //18
                    {  "_", "_", "_", "_", "_", "_", "_", "_", "_", "_", "_", "_", "_", "_", "_", "_", "_", "_", "_", "_"} };//19
                     // 0    1    2    3    4    5    6    7    8    9    10   11   12   13   14   15   16   17   18   19
    }
};

//Checks if the chosen word(s) is (are) completeley filled in
bool checkIfFull(std::string word)
{
    for (int i = 0; i < word.size(); i++)
    {
        if (word[i] != '_')
            continue;
        else
            return true;
    }
    return false;
}

//"Clearing the screen" (didn't use the OS-specific methods for better portability)
void clearScreen()
{
    std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}

int main()
{
    //initialization of game
    Hangman hangman(MAX, MAX);          // Creates object of hangman
    char entryChar;                     // Your guessed letter/number
    std::string entry;                  // The word/phrase you're supposed to guess
    bool p1Turn = true;                 // Player 1 goes first if true, not if false
    bool gameOver = false;              // When true, the following loop is exited and the game ends
    bool letterAlreadyThere = false;    // Checking to see if the letter has already been guessed AND it is a correct letter
    bool win = true;                    // Stays true until the game is lost, then it is changed to false
    bool dontUnderstand = false;        // Another boolean for the flow of the game, at the end

    std::string quitter;                // Just used at the end so that the window doesn't close before you can read it

    int p1Score = 0, p2Score = 0;       // Scores

    std::cout << "Welcome to hangman! Press enter to play!\n\n";

    while (gameOver == false)
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "Player 1: " << p1Score << " points\nPlayer 2: " << p2Score << " points\n\n";
        
        p1Turn ? std::cout << "PLAYER 1'S TURN\nPlayer (1), type the word for Player (2) to guess (50 characters max) (Don't peek you!)\n" : std::cout << "PLAYER 2'S TURN\nPlayer (2), type the word for Player (1) to guess (50 characters max) (Don't peek you!)\n";

        do
        {
            getline(std::cin, entry);
        } while (entry == "");

        clearScreen();

        //If this isn't true, then the first turn hasn't happened yet
        bool matchJustStarted = true;
           
        //Entry is copied into blankWord, but every character except space is turned to a '_', 
        //and it is shown at the bottom of the screen every turn
        std::string blankWord;
        blankWord.resize(entry.size());

        for (int i = 0; i < entry.size(); i++)
        {
            if (entry[i] == ' ')
                blankWord[i] = ' ';
            else
                blankWord[i] = '_';
        }

        std::cout << "\n\n";
        while
        (
            checkIfFull(blankWord) &&                                   
            hangman.getBodyPartIndex() <= 11                            
        )                                                               
        {                                                               
            entryChar = '\0';                                           
            if (matchJustStarted)                                       
            {                                                           
                hangman.drawHangman();                                  
                matchJustStarted = false;                               
            }                                                           
                                                                        
            std::cout << "\nGuess a letter or number: ";                
            std::cin >> entryChar;                                      
                                                                        
            int numOfLettersFound = 0;                                  
            for (int i = 0; i < entry.size(); i++)                      
            {                                                           
                if (entryChar == entry[i])                              
                {                                                       
                    if (blankWord[i] == '_')                            
                    {                                                   
                        blankWord[i] = entryChar;                       
                        numOfLettersFound++;                            
                    }                                                   
                    else
                        letterAlreadyThere = true;
                }
                else if (entryChar != entry[i])
                    continue;
            }
            
            
            if (numOfLettersFound > 0)
            {
                clearScreen();
                hangman.drawHangman();
                std::cout << "\n\nFound " << numOfLettersFound << " " << entryChar << "'s in the word\n\n";
                std::cout << blankWord << "\n\n\n";
            }
            if (numOfLettersFound == 0)
            {
                if (letterAlreadyThere)
                {
                    clearScreen();
                    hangman.drawHangman();
                    std::cout << "\n\nThat letter has already been found.\n\n";
                    letterAlreadyThere = false;
                    std::cout << blankWord << "\n\n\n";
                }
                else
                {
                    clearScreen();
                    if (hangman.getBodyPartIndex() <= 11)
                        hangman.addHangmanPart();
                    hangman.drawHangman();
                    std::cout << "\nNo " << entryChar << "'s found. Hangman part added.\n\n";
                    std::cout << blankWord << "\n\n\n";
                    if (hangman.getBodyPartIndex() >= 11)
                        break;
                }
            }
            
            
        }
        if (hangman.getBodyPartIndex() >= 11)
        {
            std::cout << "\n\nYou lose...";
            win = false;
        }
        else
        {
            std::cout << "\n\nYou win!!";
            win = true;
        }

        if (win)
            p1Turn ? p1Score++ : p2Score++;
        else
            p1Turn ? p2Score++ : p1Score++;
        p1Turn = !p1Turn;

        std::cout << " Play again? ( Y / N )\n\n";
        std::cin >> entryChar;
        do
        {
            if (entryChar == 'y' || entryChar == 'Y')
            {
                dontUnderstand = false;
                hangman.createHangman();
                clearScreen();
            }
            else if (entryChar == 'n' || entryChar == 'N')
            {
                gameOver = true;
                break;
            }
            else
                dontUnderstand = true;
        } while (dontUnderstand);

    }

    std::cout << "Game ended with score:\nPLAYER 1: " << p1Score << "\nPLAYER 2: " << p2Score << "\n\n";

    std::cout << "Goodbye! (Type something, then press enter to quit)\n";
    std::cin >> quitter;

    return 0;
}