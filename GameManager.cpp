#include "GameManager.h"
#include "Utils.h"
#include "AI.h"

GameManager::GameManager(int seed, int numPlayers) {

    std::string playerName1, playerName2;

    std::cout << "Enter a name for player 1" << std::endl;
    std::cout << "> ";
    std::cin >> playerName1;

    plyr1 = new Player(1, playerName1);

    // instantiate bag and factory
    bag = new Bag(seed);
    factory = new Factory();
    // load factory for the first time
    factory->loadFactory(bag);

    if(numPlayers == 1) {
        plyr2 = new AI(2, factory);
        singlePlayer = true;
    } else {
        std::cout << "Enter a name for player 2" << std::endl;
        std::cout << "> ";
        std::cin >> playerName2;

        plyr2 = new Player(2, playerName2);
        singlePlayer = false;
    }



    // variable to check if game is over
    gameOver = false;
    std::cout << "Let’s Play!" << std::endl;

    currPlayerID = 1;

}

GameManager::GameManager(Player *p1, Player *p2, int r, Factory *f, Bag *b,
                         int active, bool sp) :
    round(r),
    plyr1(p1),
    plyr2(p2),
    bag(b),
    factory(f),
    singlePlayer(sp)
{

    currPlayerID = active;
    gameOver = false;

    std::cout << "Azul game successfully loaded" << std::endl;

}

GameManager::~GameManager() {
    //Destructor for game manager
    delete plyr1;
    delete plyr2;
    delete factory;
    delete currTile;
    delete bag;
}

void GameManager::playRound() {
    std::cout << std::endl;
    std::cout<<"=== Start Round ==="<<std::endl;
    // Plays the game
    // Play turns until factory is empty
    while(!factory->isEmpty() && !gameOver){
        //Display factories and board to user

        displayTurn();
        if(singlePlayer && currPlayerID == 2) {
            dynamic_cast<AI*>(plyr2)->setFactory(factory);
            dynamic_cast<AI*>(plyr2)->playTurn();
            currPlayerID = 1;
        } else {
            runCommand();
        }

        // End of Turn

    }

    // if factory is empty then the round is over 
    // score players and set variables
    if (factory->isEmpty()){
        // score the players
        plyr1->getMosaic()->score();
        plyr2->getMosaic()->score();

        // Display scores for this round
        // Shows Players both their score   
        std::cout<<"Score for Player "<<plyr1->getName()<<": "<<plyr1->getMosaic()->getPoints();
        std::cout << std::endl;
        std::cout<<"Score for Player "<<plyr2->getName()<<": "<<plyr2->getMosaic()->getPoints();
        std::cout << std::endl;

        // add excess tiles to boxlid
        bag->putBox(plyr1->getMosaic()->getToBox());
        plyr1->getMosaic()->clearToBox();
        bag->putBox(plyr2->getMosaic()->getToBox());
        plyr2->getMosaic()->clearToBox();

        // check if game is over
        if (plyr1->getMosaic()->isGameover() || plyr2->getMosaic()->isGameover()){
            gameOver = true;
            std::cout << "=== GAME OVER ===" << std::endl << std::endl;
            plyr1->getMosaic()->endScore();
            plyr2->getMosaic()->endScore();

            std::cout<<"Final score for Player "<<plyr1->getName()<<": "<<plyr1->getMosaic()->getPoints();
            std::cout << std::endl;
            std::cout<<"Final score for Player "<<plyr2->getName()<<": "<<plyr2->getMosaic()->getPoints();
            std::cout << std::endl;
            std::cout << std::endl;

            if (plyr1->getMosaic()->getPoints() > plyr2->getMosaic()->getPoints()){
                std::cout << "Player 1 wins with " << plyr1->getMosaic()->getPoints() << " points!" << std::endl;
            } else {
                std::cout << "Player 2 wins with " << plyr2->getMosaic()->getPoints() << " points!" << std::endl;
            }
        } else {
            // reload the bag if it is empty
            if (bag->size() == 0){
                bag->reload();
            }
            factory->loadFactory(bag);
            ++round;
            std::cout<<"=== END OF ROUND ==="<<std::endl;

            // check who to start round and
            // adjust variables accordingly
            if (plyr1->toStart()){
                currPlayerID = plyr1->getId();
                plyr1->getMosaic()->startReset();
            }
            if (plyr2->toStart()){
                currPlayerID = plyr2->getId();
                plyr2->getMosaic()->startReset();
            }

            playRound();
        }
    }
    
}

void GameManager::displayTurn() {
    if(currPlayerID == 1){
        std::cout << "TURN FOR PLAYER: " << plyr1->getName();
    }
    else if(currPlayerID == 2){
        std::cout << "TURN FOR PLAYER: " << plyr2->getName();
    }
    std::cout<<std::endl;

    std::cout<< "Factories:" << std::endl;
    factory->listFactory();
    std::cout<<std::endl;

    if(currPlayerID == 1) {
        std::cout<< "Mosaic for " << plyr1->getName()<<std::endl;
        plyr1->getMosaic()->displayMosaic();
    } else if(currPlayerID == 2) {
        std::cout<< "Mosaic for " << plyr2->getName()<<std::endl;
        plyr2->getMosaic()->displayMosaic();
    }
}

void GameManager::playTurn(int fRow, char color, int pRow, Colour colour) {
    // Player Turn: Adds selected tiles to the pile
    // Records history of turns to vector turns

    try {
        std::string turn =" ";
        if(currPlayerID == 1){
            plyr1->playTurn(factory,fRow,colour,pRow);
            turn = "("+plyr1->getName()+")"+" > turn "+std::to_string(fRow)+" "+color+" "+std::to_string(pRow);

        }
        else if(currPlayerID == 2){
            plyr2->playTurn(factory,fRow,colour,pRow);
            turn = "("+plyr2->getName()+")"+" > turn "+std::to_string(fRow)+" "+color+" "+std::to_string(pRow);
        }

        // Add turn to vector to record
        turns.push_back(turn);

        // Switch players turn
        if(currPlayerID == 1){
            currPlayerID = plyr2->getId();
        }
        else if(currPlayerID == 2){
            currPlayerID = plyr1->getId();
        }

        std::cout << "Turn successful." <<std::endl;
        std::cout << std::endl;
    } catch (std::exception& e) {
        std::cerr << "Exception Caught: " << e.what() << std::endl;
        runCommand();
    }
}

Colour GameManager::makeColour(char c){
    Colour toReturn = E;

    if (c == 'R'){
        toReturn = R;
    } else if (c == 'Y'){
        toReturn = Y;
    } else if (c == 'B'){
        toReturn = B;
    } else if (c == 'L'){
        toReturn = L;
    } else if (c == 'U'){
        toReturn = U;
    }

    return toReturn;
}

void GameManager::setFirstPlayer(int playerID) {
    currPlayerID = playerID;
}

void GameManager::runCommand() {
    std::cout<< "> ";
    // Fix for line space leak
    // Skips all leading whitespace.
    std::cin >> std::ws;

    // Detects user input line
    std::string line;
    std::string command;
    std::getline(std::cin,line);
    std::stringstream ss(line);
    std::cout << command << std::endl;

    // Clear command vector for new commands
    stringcommand.clear();
    while(getline(ss,command, ' ')) // delimiter as space
    {
        std::stringstream stream(command);
        stringcommand.push_back(command);
    }

    // Check for the user input command.
    // If command is turn. Continue with player's turn
    if(stringcommand.front() == "turn" && stringcommand.size() == 4){
        int fRow = std::stoi(stringcommand.at(1));
        char color = stringcommand.at(2)[0];
        int pRow = std::stoi(stringcommand.at(3));
        //Convert color to enum
        Colour colour = makeColour(color);

        playTurn(fRow, color, pRow, colour);
    } else if(stringcommand.front() == "save"){
        // Save current state of the game
        saveGame(stringcommand.at(1), plyr1, plyr2, factory, round,
                 currPlayerID, bag, singlePlayer);
        std::cout << "Game successfully saved to '" << stringcommand.at(1) << "'" << std::endl;
    } else if(stringcommand.front() == "^D"){
        std::cout << "Bye Bye" << std::endl;
        exit(0);
    } else {
        // No recognizable commands throw error
        std::cout << "Invalid Input. Usage:" << std::endl;
        std::cout << "turn <factory no> <colour> <pile no>" << std::endl;
        std::cout << "save <filename>" << std::endl;
        runCommand();
    }

}
