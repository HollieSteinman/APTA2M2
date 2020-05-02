#include "Utils.h"

void showMenu(){
    std::cout << "Welcome To Azul! " << std::endl;
    std::cout << "------------------" << std::endl;
    std::cout << std::endl;
    std::cout << "Menu " << std::endl;
    std::cout << "1. New Game " << std::endl;
    std::cout << "2. Load Game " << std::endl;
    std::cout << "3. Credits " << std::endl;
    std::cout << "4. Quit" << std::endl;
    std::cout << std::endl;
    std::cout << "> ";

    int menu = 0;
    std::cin >> menu;

    if (menu == 1) {
        // playGame();
    } else if (menu == 2) {
        // loadGame();
    } else if (menu == 3) {
        showCredits();
        showMenu();
    } else if (menu == 4) {
        exit;
    } else {
        throw std::range_error("Please select an item from the list");
    }

}

void showCredits(){
    std::cout << std::endl;
    std::cout << "-------------------------------------------" << std::endl;
    std::cout << "Name: Emmanuel Chukwudi Nwordu " << std::endl;
    std::cout << "Student ID: s3667339 " << std::endl;
    std::cout << "Email: s3667339@student.rmit.edu.au " << std::endl;
    std::cout << std::endl;
    std::cout << "Name: Joel Liang Shien Tan " << std::endl;
    std::cout << "Student ID: s3758729 " << std::endl;
    std::cout << "Email: s758729@student.rmit.edu.au " << std::endl;
    std::cout << std::endl;
    std::cout << "Name: Hollie Steinman " << std::endl;
    std::cout << "Student ID: s3784783 " << std::endl;
    std::cout << "Email: s784783@student.rmit.edu.au " << std::endl;
    std::cout << "-------------------------------------------" << std::endl;
}