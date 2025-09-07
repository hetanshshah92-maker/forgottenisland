#include "Player.h"
#include <iostream>
#include <algorithm>

Player::Player(const std::string& playerName) 
    : name(playerName), health(100), maxHealth(100), maxInventorySize(10) {
}

Player::~Player() = default;

void Player::heal(int amount) {
    if (amount > 0) {
        health = std::min(health + amount, maxHealth);
        std::cout << "You feel better! Health restored by " << amount << " points.\n";
        std::cout << "Current health: " << health << "/" << maxHealth << "\n";
    }
}

void Player::takeDamage(int amount) {
    if (amount > 0) {
        health = std::max(0, health - amount);
        std::cout << "You take " << amount << " damage!\n";
        std::cout << "Current health: " << health << "/" << maxHealth << "\n";
        
        if (health <= 0) {
            std::cout << "You have been defeated!\n";
        } else if (health <= 20) {
            std::cout << "You are badly injured!\n";
        } else if (health <= 50) {
            std::cout << "You are hurt.\n";
        }
    }
}

bool Player::addItem(std::unique_ptr<Item> item) {
    if (!item) return false;
    
    if (inventory.size() >= static_cast<size_t>(maxInventorySize)) {
        return false;
    }
    
    inventory.push_back(std::move(item));
    return true;
}

std::unique_ptr<Item> Player::removeItem(const std::string& itemName) {
    auto it = std::find_if(inventory.begin(), inventory.end(),
        [&itemName](const std::unique_ptr<Item>& item) {
            return item && item->getName() == itemName;
        });
    
    if (it != inventory.end()) {
        std::unique_ptr<Item> removedItem = std::move(*it);
        inventory.erase(it);
        return removedItem;
    }
    
    return nullptr;
}

Item* Player::findItem(const std::string& itemName) const {
    auto it = std::find_if(inventory.begin(), inventory.end(),
        [&itemName](const std::unique_ptr<Item>& item) {
            return item && item->getName() == itemName;
        });
    
    return (it != inventory.end()) ? it->get() : nullptr;
}

bool Player::hasItem(const std::string& itemName) const {
    return findItem(itemName) != nullptr;
}

void Player::displayInventory() const {
    if (inventory.empty()) {
        std::cout << "Your inventory is empty.\n";
        return;
    }
    
    std::cout << "\n=== INVENTORY ===\n";
    std::cout << "Carrying " << inventory.size() << "/" << maxInventorySize << " items:\n";
    
    for (const auto& item : inventory) {
        if (item) {
            std::cout << "  " << item->getName();
            if (item->getValue() > 0) {
                std::cout << " (Value: " << item->getValue() << " gold)";
            }
            std::cout << "\n";
        }
    }
    std::cout << "================\n";
}

void Player::displayStatus() const {
    std::cout << "\n=== CHARACTER STATUS ===\n";
    std::cout << "Name: " << name << "\n";
    std::cout << "Health: " << health << "/" << maxHealth;
    
    if (health == maxHealth) {
        std::cout << " (Perfect health)";
    } else if (health >= maxHealth * 0.8) {
        std::cout << " (Slightly injured)";
    } else if (health >= maxHealth * 0.6) {
        std::cout << " (Moderately injured)";
    } else if (health >= maxHealth * 0.4) {
        std::cout << " (Badly injured)";
    } else if (health >= maxHealth * 0.2) {
        std::cout << " (Severely injured)";
    } else if (health > 0) {
        std::cout << " (Critically injured)";
    } else {
        std::cout << " (Unconscious)";
    }
    
    std::cout << "\n";
    std::cout << "Inventory: " << inventory.size() << "/" << maxInventorySize << " items\n";
    std::cout << "=======================\n";
}