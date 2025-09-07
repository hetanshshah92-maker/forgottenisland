#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include <memory>
#include "Item.h"

class Player {
private:
    std::string name;
    int health;
    int maxHealth;
    std::vector<std::unique_ptr<Item>> inventory;
    int maxInventorySize;

public:
    Player(const std::string& playerName);
    ~Player();
    
    // Getters
    std::string getName() const { return name; }
    int getHealth() const { return health; }
    int getMaxHealth() const { return maxHealth; }
    int getInventorySize() const { return inventory.size(); }
    int getMaxInventorySize() const { return maxInventorySize; }
    
    // Health management
    void heal(int amount);
    void takeDamage(int amount);
    bool isAlive() const { return health > 0; }
    
    // Inventory management
    bool addItem(std::unique_ptr<Item> item);
    std::unique_ptr<Item> removeItem(const std::string& itemName);
    Item* findItem(const std::string& itemName) const;
    bool hasItem(const std::string& itemName) const;
    void displayInventory() const;
    
    // Utility methods
    void displayStatus() const;
};

#endif // PLAYER_H