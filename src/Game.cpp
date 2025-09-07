#include "Game.h"
#include <iostream>
#include <algorithm>
#include <sstream>
#include <cctype>

Game::Game() : currentRoomId(1), gameRunning(false), gameScore(0) {
    player = std::make_unique<Player>("Adventurer");
    initializeRooms();
    initializeItems();
}

Game::~Game() = default;

void Game::startGame() {
    gameRunning = true;
    
    // Set initial game state
    setFlag("has_torch", false);
    setFlag("cave_explored", false);
    setFlag("temple_door_open", false);
    setFlag("treasure_found", false);
    
    std::cout << "Enter your name, brave adventurer: ";
    std::string playerName;
    std::getline(std::cin, playerName);
    
    if (!playerName.empty()) {
        player = std::make_unique<Player>(playerName);
    }
    
    std::cout << "\nWelcome, " << player->getName() << "!\n\n";
    
    // Display starting room
    displayRoom();
    
    // Start main game loop
    gameLoop();
}

void Game::gameLoop() {
    std::string input;
    
    while (gameRunning) {
        std::cout << "\n> ";
        std::getline(std::cin, input);
        
        if (input.empty()) {
            continue;
        }
        
        processCommand(toLowerCase(input));
        updateGameState();
        checkWinCondition();
        
        if (!player->isAlive()) {
            std::cout << "\nYou have died! Your adventure ends here.\n";
            std::cout << "Final Score: " << gameScore << "\n";
            gameRunning = false;
        }
    }
}

void Game::processCommand(const std::string& command) {
    std::vector<std::string> words = splitCommand(command);
    
    if (words.empty()) return;
    
    std::string action = words[0];
    std::string target = words.size() > 1 ? words[1] : "";
    
    // Movement commands
    if (action == "go" || action == "move") {
        if (!target.empty()) {
            handleMovement(target);
        } else {
            std::cout << "Go where? Try: go north, go south, go east, go west\n";
        }
    }
    else if (action == "north" || action == "n") handleMovement("north");
    else if (action == "south" || action == "s") handleMovement("south");
    else if (action == "east" || action == "e") handleMovement("east");
    else if (action == "west" || action == "w") handleMovement("west");
    else if (action == "up" || action == "u") handleMovement("up");
    else if (action == "down" || action == "d") handleMovement("down");
    
    // Interaction commands
    else if (action == "look" || action == "l") {
        if (target.empty()) {
            displayRoom();
        } else {
            handleExamine(target);
        }
    }
    else if (action == "examine" || action == "inspect") {
        handleExamine(target);
    }
    else if (action == "take" || action == "get" || action == "pick") {
        handleTake(target);
    }
    else if (action == "drop" || action == "leave") {
        handleDrop(target);
    }
    else if (action == "use") {
        handleUse(target);
    }
    
    // Information commands
    else if (action == "inventory" || action == "i") {
        displayInventory();
    }
    else if (action == "status" || action == "health") {
        player->displayStatus();
    }
    else if (action == "help" || action == "h") {
        displayHelp();
    }
    else if (action == "score") {
        std::cout << "Current Score: " << gameScore << "\n";
    }
    
    // Game control
    else if (action == "quit" || action == "exit" || action == "q") {
        std::cout << "Are you sure you want to quit? (y/n): ";
        std::string confirm;
        std::getline(std::cin, confirm);
        if (toLowerCase(confirm) == "y" || toLowerCase(confirm) == "yes") {
            gameRunning = false;
            std::cout << "Thanks for playing!\n";
        }
    }
    else {
        std::cout << "I don't understand that command. Type 'help' for available commands.\n";
    }
}

void Game::handleMovement(const std::string& direction) {
    Room* currentRoom = getCurrentRoom();
    if (!currentRoom) return;
    
    int nextRoomId = currentRoom->getExit(direction);
    
    if (nextRoomId == -1) {
        std::cout << "You can't go that way.\n";
        return;
    }
    
    // Check if the destination room exists
    auto it = rooms.find(nextRoomId);
    if (it == rooms.end()) {
        std::cout << "That path leads nowhere.\n";
        return;
    }
    
    Room* nextRoom = it->second.get();
    
    // Check if room is locked
    if (nextRoom->isLocked()) {
        std::string keyName = nextRoom->getUnlockKey();
        if (!keyName.empty() && !player->hasItem(keyName)) {
            std::cout << "The way is locked. You need a " << keyName << " to proceed.\n";
            return;
        } else if (!keyName.empty() && player->hasItem(keyName)) {
            std::cout << "You use the " << keyName << " to unlock the way.\n";
            nextRoom->setLocked(false);
        }
    }
    
    currentRoomId = nextRoomId;
    nextRoom->setVisited(true);
    
    std::cout << "You move " << direction << ".\n\n";
    displayRoom();
}

void Game::handleExamine(const std::string& target) {
    if (target.empty()) {
        std::cout << "Examine what?\n";
        return;
    }
    
    // Check inventory first
    Item* item = player->findItem(target);
    if (item) {
        item->examine();
        return;
    }
    
    // Check current room
    Room* room = getCurrentRoom();
    if (room) {
        item = room->findItem(target);
        if (item) {
            item->examine();
            return;
        }
    }
    
    std::cout << "You don't see a " << target << " here.\n";
}

void Game::handleTake(const std::string& itemName) {
    if (itemName.empty()) {
        std::cout << "Take what?\n";
        return;
    }
    
    Room* room = getCurrentRoom();
    if (!room) return;
    
    Item* item = room->findItem(itemName);
    if (!item) {
        std::cout << "There's no " << itemName << " here.\n";
        return;
    }
    
    if (!item->getCanTake()) {
        std::cout << "You can't take that.\n";
        return;
    }
    
    std::unique_ptr<Item> takenItem = room->removeItem(itemName);
    if (takenItem && player->addItem(std::move(takenItem))) {
        std::cout << "You take the " << itemName << ".\n";
        gameScore += 10;
    } else {
        std::cout << "Your inventory is full!\n";
        room->addItem(std::move(takenItem)); // Put it back
    }
}

void Game::handleDrop(const std::string& itemName) {
    if (itemName.empty()) {
        std::cout << "Drop what?\n";
        return;
    }
    
    std::unique_ptr<Item> item = player->removeItem(itemName);
    if (item) {
        Room* room = getCurrentRoom();
        if (room) {
            room->addItem(std::move(item));
            std::cout << "You drop the " << itemName << ".\n";
        }
    } else {
        std::cout << "You don't have a " << itemName << ".\n";
    }
}

void Game::handleUse(const std::string& itemName) {
    if (itemName.empty()) {
        std::cout << "Use what?\n";
        return;
    }
    
    Item* item = player->findItem(itemName);
    if (!item) {
        std::cout << "You don't have a " << itemName << ".\n";
        return;
    }
    
    if (!item->getCanUse()) {
        std::cout << "You can't use that.\n";
        return;
    }
    
    std::string result = item->use();
    std::cout << result << "\n";
    
    // Handle special item effects
    if (item->getType() == ItemType::CONSUMABLE) {
        Consumable* consumable = dynamic_cast<Consumable*>(item);
        if (consumable) {
            player->heal(consumable->getHealAmount());
            player->removeItem(itemName); // Consumable items are removed after use
            gameScore += 5;
        }
    }
}

void Game::displayHelp() {
    std::cout << "\n=== AVAILABLE COMMANDS ===\n";
    std::cout << "Movement:\n";
    std::cout << "  go <direction>, north, south, east, west, up, down\n";
    std::cout << "  (or use shortcuts: n, s, e, w, u, d)\n";
    std::cout << "\nInteraction:\n";
    std::cout << "  look - examine your surroundings\n";
    std::cout << "  examine <item> - look at something closely\n";
    std::cout << "  take <item> - pick up an item\n";
    std::cout << "  drop <item> - drop an item\n";
    std::cout << "  use <item> - use an item\n";
    std::cout << "\nInformation:\n";
    std::cout << "  inventory (i) - check your items\n";
    std::cout << "  status - check your health\n";
    std::cout << "  score - check your current score\n";
    std::cout << "  help (h) - show this help\n";
    std::cout << "\nGame Control:\n";
    std::cout << "  quit (q) - exit the game\n";
    std::cout << "===========================\n";
}

void Game::displayInventory() {
    player->displayInventory();
}

void Game::displayRoom() {
    Room* room = getCurrentRoom();
    if (room) {
        room->displayRoom();
    }
}

Room* Game::getCurrentRoom() const {
    auto it = rooms.find(currentRoomId);
    return (it != rooms.end()) ? it->second.get() : nullptr;
}

bool Game::getFlag(const std::string& flag) const {
    auto it = gameFlags.find(flag);
    return (it != gameFlags.end()) ? it->second : false;
}

void Game::updateGameState() {
    // Update game state based on player actions and flags
    if (player->hasItem("torch") && !getFlag("has_torch")) {
        setFlag("has_torch", true);
    }
}

void Game::checkWinCondition() {
    if (currentRoomId == 10 && player->hasItem("ancient treasure")) {
        std::cout << "\n========================================\n";
        std::cout << "🎉 CONGRATULATIONS! 🎉\n";
        std::cout << "You have found the ancient treasure and\n";
        std::cout << "discovered a way off the forgotten island!\n";
        std::cout << "Your adventure is complete!\n";
        std::cout << "========================================\n";
        std::cout << "Final Score: " << gameScore + 100 << "\n";
        gameRunning = false;
    }
}

std::string Game::toLowerCase(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

std::vector<std::string> Game::splitCommand(const std::string& command) {
    std::vector<std::string> words;
    std::istringstream iss(command);
    std::string word;
    
    while (iss >> word) {
        words.push_back(word);
    }
    
    return words;
}

void Game::endGame() {
    gameRunning = false;
}