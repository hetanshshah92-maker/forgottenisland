#include "Room.h"
#include <iostream>
#include <algorithm>

Room::Room(int roomId, const std::string& roomName, const std::string& desc)
    : id(roomId), name(roomName), description(desc), longDescription(desc), 
      visited(false), locked(false) {
}

Room::Room(int roomId, const std::string& roomName, const std::string& desc, const std::string& longDesc)
    : id(roomId), name(roomName), description(desc), longDescription(longDesc), 
      visited(false), locked(false) {
}

Room::~Room() = default;

std::string Room::getDescription() const {
    // Return long description if this is the first visit, short description otherwise
    if (!visited && !longDescription.empty()) {
        return longDescription;
    }
    return description;
}

void Room::addExit(const std::string& direction, int roomId) {
    exits[direction] = roomId;
}

int Room::getExit(const std::string& direction) const {
    auto it = exits.find(direction);
    return (it != exits.end()) ? it->second : -1;
}

std::vector<std::string> Room::getAvailableExits() const {
    std::vector<std::string> availableExits;
    for (const auto& exit : exits) {
        availableExits.push_back(exit.first);
    }
    return availableExits;
}

void Room::addItem(std::unique_ptr<Item> item) {
    if (item) {
        items.push_back(std::move(item));
    }
}

std::unique_ptr<Item> Room::removeItem(const std::string& itemName) {
    auto it = std::find_if(items.begin(), items.end(),
        [&itemName](const std::unique_ptr<Item>& item) {
            return item && item->getName() == itemName;
        });
    
    if (it != items.end()) {
        std::unique_ptr<Item> removedItem = std::move(*it);
        items.erase(it);
        return removedItem;
    }
    
    return nullptr;
}

Item* Room::findItem(const std::string& itemName) const {
    auto it = std::find_if(items.begin(), items.end(),
        [&itemName](const std::unique_ptr<Item>& item) {
            return item && item->getName() == itemName;
        });
    
    return (it != items.end()) ? it->get() : nullptr;
}

void Room::displayItems() const {
    if (items.empty()) {
        return;
    }
    
    std::cout << "\nYou can see:\n";
    for (const auto& item : items) {
        if (item) {
            std::cout << "  " << item->getName();
            if (item->getCanTake()) {
                std::cout << " (you can take this)";
            }
            std::cout << "\n";
        }
    }
}

void Room::displayRoom() const {
    std::cout << "=== " << name << " ===\n";
    std::cout << getDescription() << "\n";
    
    // Display items in the room
    displayItems();
    
    // Display available exits
    displayExits();
}

void Room::displayExits() const {
    if (exits.empty()) {
        std::cout << "\nThere are no obvious exits.\n";
        return;
    }
    
    std::cout << "\nExits: ";
    bool first = true;
    for (const auto& exit : exits) {
        if (!first) {
            std::cout << ", ";
        }
        std::cout << exit.first;
        first = false;
    }
    std::cout << "\n";
}