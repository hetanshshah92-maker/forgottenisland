#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Game.h"

void displayTitle() {
    std::cout << "\n";
    std::cout << "========================================================\n";
    std::cout << "🌊        JOURNEY OF THE FORGOTTEN ISLAND        🌊\n";
    std::cout << "========================================================\n";
    std::cout << "\n";
    std::cout << "   A mysterious island awaits your exploration...\n";
    std::cout << "   Uncover ancient secrets and find your way home!\n";
    std::cout << "\n";
    std::cout << "========================================================\n";
    std::cout << "\n";
}

void displayIntro() {
    std::cout << "You wake up on a sandy beach, waves gently lapping at your feet.\n";
    std::cout << "The last thing you remember is your ship being caught in a terrible storm.\n";
    std::cout << "Now you find yourself on an unknown island, with no sign of your crew.\n";
    std::cout << "The sun is setting, and you need to find shelter and a way off this island.\n";
    std::cout << "\n";
    std::cout << "Type 'help' at any time to see available commands.\n";
    std::cout << "Type 'quit' to exit the game.\n";
    std::cout << "\n";
}

int main() {
    // Seed random number generator
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    
    try {
        displayTitle();
        displayIntro();
        
        // Create and start the game
        Game game;
        game.startGame();
        
        std::cout << "\nThank you for playing Journey of the Forgotten Island!\n";
        std::cout << "Press Enter to exit...";
        std::cin.get();
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}