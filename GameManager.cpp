#include "GameManager.h"
#include "Utils.h"

GameManager::GameManager() {

    // std::string playerName1, playerName2;

    // std::cout << "Enter a name for player 1" << std::endl;
    // std::cout << "> ";
    // std::cin >> playerName1;

    // //  Create player 1
    // player1 = new Player(1,playerName1);

    // std::cout << "Enter a name for player 2" << std::endl;
    // std::cout << "> ";
    // std::cin >> playerName2;

    // //  Create player 2
    // player2 = new Player(2,playerName2);
    // //  Create tiles and factories
    // factory = new Factory();
    // currTile = new Tile();
    // setFirstPlayer(player1->getId());
    // //  Create Bag
    // //bag = new Bag(20);
    // std::cout << "Let’s Play!" <<std::endl;

}

GameManager::GameManager(int seed) {

    std::string playerName1, playerName2;

    std::cout << "Enter a name for player 1" << std::endl;
    std::cout << "> ";
    std::cin >> playerName1;

    plyr1 = new Player(1, playerName1);

    std::cout << "Enter a name for player 2" << std::endl;
    std::cout << "> ";
    std::cin >> playerName2;

    plyr2 = new Player(2, playerName2);

    // instantiate bag and factory
    bag = new Bag(seed);
    factory = new Factory();
    // load factory for the first time
    factory->loadFactory(bag);

    std::cout << "Let’s Play!" ;
    // variable to check if game is over
    gameOver = false;

}

GameManager::GameManager(Player* p1, Player* p2, int r, Factory* f):
    round(r),
    plyr1(p1),
    plyr2(p2),
    factory(f)
{
    if(plyr1->getMosaic()->toStart()) {
        setFirstPlayer(1);
    } else {
        setFirstPlayer(2);
    }
}

GameManager::~GameManager() {
    //Destructor for game manager
    delete plyr1;
    delete plyr2;
    delete factory;
    delete currTile;
    delete bag;
}

void GameManager::getRound() {

}

void GameManager::startGame(){
    // make player 1 the first starter
    std::cout << "Factories" << std::endl;
    factory->listFactory();
    std::cout << " Mosaic for " << plyr1->getName() << std::endl;
    plyr1->getMosaic()->displayMosaic();
    std::cout << "TURN FOR PLAYER: " << plyr1->getName() << std::endl;
    std::cout << "> ";
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
        std::cout<<command<<std::endl;
        stringcommand.push_back(command);
    }

    if(stringcommand.front()=="turn"){
                
        int fRow = std::stoi(stringcommand.at(1));
        char color = stringcommand.at(2)[0];
        int pRow = std::stoi(stringcommand.at(3));
        std::cout << fRow << color << pRow;
        //Convert color to enum
        Colour colour = makeColour(color);

        // Player Turn: Adds selected tiles to mosaic
        // Records history of turns to vector turns
        std::string turn =" ";
        plyr1->playTurn(factory,fRow,colour,pRow);
        turn = "("+plyr1->getName()+")"+" > turn "+std::to_string(fRow)
            +" "+color+" "+std::to_string(pRow);
        
        // Add turn to vector to record
        turns.push_back(turn);

        // Switch to player 2
        currPlayerID = 2;

        std::cout << "Turn successful." <<std::endl;
        std::cout << std::endl;
        std::cout<<"< the following turns happen >" << std::endl;
        for(std::vector<std::string>::iterator i = turns.begin(); i != turns.end(); ++i){
            std::cout<< *i << std::endl;
        }  
    } else {
        throw std::logic_error("The game just started");
    }

    while (!gameOver){
        playRound();
    }
}

void GameManager::playRound() {
    // Plays the game

    // Play turns until factory is empty
    while(!factory->isEmpty()){
        std::cout<<"=== Start Turn ==="<<std::endl;
        //Display factories and board to user
        displayTurn();

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
            std::cout<<command<<std::endl;
            stringcommand.push_back(command);
        }

        // Check for the user input command.
        // If command is turn . Continue with player's turn
        if(stringcommand.front() == "turn"){
            
            int fRow = std::stoi(stringcommand.at(1));
            char color = stringcommand.at(2)[0];
            int pRow = std::stoi(stringcommand.at(3));
            std::cout << fRow << color << pRow;
            //Convert color to enum
            Colour colour = makeColour(color);

            // Player Turn: Adds selected tiles to mosaic
            // Records history of turns to vector turns
            std::string turn =" ";
            if(currPlayerID == 1){
                plyr1->playTurn(factory,fRow,colour,pRow);
                turn = "("+plyr1->getName()+")"+" > turn "+std::to_string(fRow)+" "+color+" "+std::to_string(pRow);
            
            }
            else if(currPlayerID == 2){
                plyr2->playTurn(factory,fRow,colour,pRow);
                turn = "("+plyr2->getName()+")"+" > turn "+std::to_string(fRow)+" "+color+" "+std::to_string(pRow);
            }

            // // Add string (gets first player token) to player who picks from center first
            // if(count == 0){
            //     if(player1->getMosaic()->getBrokenTile().at(0)->getColour() == F || player2->getMosaic()->getBrokenTile().at(0)->getColour() == F){
            //         turn += "( gets first player token )";
            //         count = count + 1;
            //     }
            // }
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
            std::cout<<"< the following turns happen >" << std::endl;
            for(std::vector<std::string>::iterator i = turns.begin(); i != turns.end(); ++i){
                std::cout<< *i << std::endl;
            } 
            std::cout<<"=== END OF TURN ==="<<std::endl;  

        } else if(stringcommand.front() == "save"){

            // Save current state of the game
            saveGame();
            std::cout << "Game successfully saved to '" << stringcommand.at(1) << "'" << std::endl;

        } else {
            // No recognizable commands throw error
            throw std::out_of_range(" You entered an invalid command");
            // loadGame();
            // std::cout << "Please enter a valid command" <<std::endl;
        }
        // End of Turn
        // Shows Players both their score   
        std::cout<<"Score for Player "<<plyr1->getName()<<": "<<plyr1->getMosaic()->getPoints();
        std::cout<<"Score for Player "<<plyr2->getName()<<": "<<plyr2->getMosaic()->getPoints();
    }

    // if factory is empty then the round is over 
    // score players and set variables
    if (factory->isEmpty()){
        // score the players
        plyr1->getMosaic()->score();
        plyr2->getMosaic()->score();

        // add excess tiles to boxlid
        bag->putBox(plyr1->getMosaic()->getToBox());
        plyr1->getMosaic()->clearToBox();
        bag->putBox(plyr2->getMosaic()->getToBox());
        plyr2->getMosaic()->clearToBox();

        // check if game is over
        if (plyr1->getMosaic()->isGameover() || plyr2->getMosaic()->isGameover()){
            gameOver = true;
            std::cout << "The game is over" << std::endl;
            if (plyr1->getMosaic()->getPoints() > plyr2->getMosaic()->getPoints()){
                std::cout << "Player 1 wins with " << plyr1->getMosaic()->getPoints() << std::endl;
            } else {
                std::cout << "Player 2 wins with " << plyr2->getMosaic()->getPoints() << std::endl;
            }
        }

        // reload the bag if it is empty
        if (bag->size() == 0){
            bag->reload();
        }
        factory->loadFactory(bag);
        ++round;
    }
    
}

void GameManager::displayTurn() {
    std::cout<< "Factories" << std::endl;
    factory->listFactory();
    if(currPlayerID == 1){
        std::cout<< "Mosaic for" << plyr1->getName()<<std::endl;
        plyr1->getMosaic()->displayMosaic();
        std::cout << "TURN FOR PLAYER: " << plyr1->getName();

    }
    else if(currPlayerID == 2){
        std::cout<< "Mosaic for" << plyr2->getName()<<std::endl;
        plyr2->getMosaic()->displayMosaic();
        std::cout << "TURN FOR PLAYER: " << plyr2->getName();
    }
    std::cout<<std::endl;
            std::cout<< "> ";
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

Tile *GameManager::getFactory(int pile, char colour) {
    return nullptr;
}

void GameManager::generatePiles() {

}

void GameManager::setFirstPlayer(int playerID) {
    currPlayerID = playerID;
}
