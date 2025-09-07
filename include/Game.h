#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>
#include <map>
#include <memory>
#include "Player.h"
#include "Room.h"
#include "Item.h"

class Game {
private:
    std::unique_ptr<Player> player;
    std::map<int, std::unique_ptr<Room>> rooms;
    int currentRoomId;
    bool gameRunning;
    
    // Game state tracking
    std::map<std::string, bool> gameFlags;
    int gameScore;
    
    // Private helper methods
    void initializeRooms();
    void initializeItems();
    void processCommand(const std::string& command);
    void displayHelp();
    void displayInventory();
    void displayRoom();
    void handleMovement(const std::string& direction);
    void handleExamine(const std::string& target);
    void handleTake(const std::string& itemName);
    void handleUse(const std::string& itemName);
    void handleDrop(const std::string& itemName);
    
    // Game logic methods
    void checkWinCondition();
    void updateGameState();
    std::string toLowerCase(const std::string& str);
    std::vector<std::string> splitCommand(const std::string& command);

public:
    Game();
    ~Game();
    
    void startGame();
    void gameLoop();
    void endGame();
    
    // Getters
    Player* getPlayer() const { return player.get(); }
    Room* getCurrentRoom() const;
    int getScore() const { return gameScore; }
    
    // Game flag management
    void setFlag(const std::string& flag, bool value) { gameFlags[flag] = value; }
    bool getFlag(const std::string& flag) const;
};

#endif // GAME_H