#include "GameManager.h"
#include "Utils.h"

GameManager::GameManager() {

    std::string playerName1, playerName2;

    std::cout << "Enter a name for player 1" << std::endl;
    std::cout << "> ";
    std::cin >> playerName1;

    //  Create player 1
    player1 = new Player(1,playerName1);

    std::cout << "Enter a name for player 2" << std::endl;
    std::cout << "> ";
    std::cin >> playerName2;

    //  Create player 2
    player2 = new Player(2,playerName2);
    //  Create tiles and factories
    factory = new Factory();
    currTile = new Tile();
    setFirstPlayer(player1->getId());
    //  Create Bag
    //bag = new Bag(20);
    std::cout << "Let’s Play!" <<std::endl;


}

GameManager::GameManager(Player* p1, Player* p2, int r, Factory* f):
    round(r),
    player1(p1),
    player2(p2),
    factory(f)
{
    if(player1->getMosaic()->toStart()) {
        setFirstPlayer(1);
    } else {
        setFirstPlayer(2);
    }
}

GameManager::~GameManager() {
    //Destructor for game manager
    delete player1;
    delete player2;
    delete factory;
    delete currTile;
    //delete bag;
}

void GameManager::getRound() {

}

void GameManager::playRound(Bag* gameBag) {
    // Plays the game

    // Check for adding ( First token ) string once Line:136
    int count = 0;
    // Fill factories from bag
    factory->loadFactory(gameBag);  
    // Game continues until a player fills out their mosaic or the bag runs out of tiles
    while(player1->getMosaic()->isGameover()||player2->getMosaic()->isGameover()||gameBag->size()>0){
        // Round begins until factory is out of tiles and center is out of tiles
        while(!factory->isEmpty()){
            std::cout<<"=== Start Round ==="<<std::endl;
            //Display factories and board to user
            displayRound();
            // User turn command
            if(currPlayerID == 1){
                std::cout << "TURN FOR PLAYER: " << player1->getName();
            }
            else if(currPlayerID == 2){
                std::cout << "TURN FOR PLAYER: " << player2->getName();
            }
            std::cout<<std::endl;
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
                std::cout<<command<<std::endl;
                stringcommand.push_back(command);
            }

            // Check for the user input command.
            // If command is turn . Continue with player's turn
            if(stringcommand.front()=="turn"){
                
                int fRow = std::stoi(stringcommand.at(1));
                char color = stringcommand.at(2)[0];
                int pRow = std::stoi(stringcommand.at(3));
                std::cout << fRow << color << pRow;
                //Convert color to enum
                Colour colour;
                if(color == 'F'){
                    colour = Colour::F;
                }
                else if(color == 'R'){
                    colour = Colour::R;
                }
                else if(color == 'Y'){
                    colour = Colour::Y;
                }
                else if(color == 'B'){
                    colour = Colour::B;
                }
                else if(color == 'L'){
                    colour = Colour::L;
                }
                else if(color == 'U'){
                    colour = Colour::U;
                }
                else if(color == 'E'){
                    colour = Colour::E;
                }
                else{
                    colour = Colour::F;
                }

                // Player Turn: Adds selected tiles to mosaic
                // Records history of turns to vector turns
                std::string turn =" ";
                if(currPlayerID == 1){
                    player1->playTurn(factory,fRow,colour,pRow);
                    turn = "("+player1->getName()+")"+" > turn "+std::to_string(fRow)+" "+color+" "+std::to_string(pRow);
                
                }
                else if(currPlayerID == 2){
                    player2->playTurn(factory,fRow,colour,pRow);
                    turn = "("+player2->getName()+")"+" > turn "+std::to_string(fRow)+" "+color+" "+std::to_string(pRow);
                }

                // Add string (gets first player token) to player who picks from center first
                if(count == 0){
                    if(player1->getMosaic()->getBrokenTile().at(0)->getColour() == F || player2->getMosaic()->getBrokenTile().at(0)->getColour() == F){
                        turn += "( gets first player token )";
                        count = count + 1;
                    }
                }
                // Add turn to vector to record
                turns.push_back(turn);

                // Switch players turn
                if(currPlayerID == 1){
                    currPlayerID = player2->getId();
                }
                else if(currPlayerID == 2){
                    currPlayerID = player1->getId();
                }

                std::cout << "Turn successful." <<std::endl;
                std::cout << std::endl;
                std::cout<<"< the following turns happen >" << std::endl;
                for(std::vector<std::string>::iterator i = turns.begin(); i != turns.end(); ++i){
                    std::cout<< *i << std::endl;
                } 
                std::cout<<"=== END OF ROUND ==="<<std::endl;     
            }
            else if(stringcommand.front()=="save"){
                // Save current state of the game
                saveGame(stringcommand.at(1), player1, player2, factory, round, currPlayerID);
                std::cout << "Game successfully saved to '" << stringcommand.at(1) << "'" << std::endl;
            }
            else{
                // No recognizable commands throw error
                std::cout << "Please enter a valid command" <<std::endl;
            }
        // End of Round:
        // Shows Players both their score   
        std::cout<<"Score for Player "<<player1->getName()<<": "<<player1->getMosaic()->getPoints();
        std::cout<<"Score for Player "<<player2->getName()<<": "<<player2->getMosaic()->getPoints();
        }
        // Score for both players when the round ends
        player1->getMosaic()->score();
        player2->getMosaic()->score();

        round++;

        
    }
    std::cout << "=== GAME OVER ===" << std::endl;
    // Check for the winner or a draw
    if(player1->getMosaic()->isGameover()&&player2->getMosaic()->isGameover()){
        // Game is a draw 
        std::cout<<"Its a draw !" << std::endl;
    }
    else if(player1->getMosaic()->isGameover()){
        // Player 1 wins
        std::cout<<"Player " <<player1->getName()<<" WINS !"<< std::endl;
    }
    else if(player2->getMosaic()->isGameover()){
        // Player 2 wins
        std::cout<<"Player " <<player2->getName()<<" WINS !"<< std::endl;
    }
    
}

void GameManager::displayRound() {
    std::cout<< "Factories" << std::endl;
    factory->listFactory();
    if(currPlayerID == 1){
        std::cout<< "Mosaic for" << player1->getName()<<std::endl;
        player1->getMosaic()->displayMosaic();

    }
    else if(currPlayerID == 2){
        std::cout<< "Mosaic for" << player2->getName()<<std::endl;
        player2->getMosaic()->displayMosaic();
    }
    else{
        std::cout<<"Mosaic currently empty"<<std::endl;
    }

}

Tile *GameManager::getFactory(int pile, char colour) {
    return nullptr;
}

void GameManager::generatePiles() {

}

void GameManager::setFirstPlayer(int playerID) {
    currPlayerID = playerID;
}
