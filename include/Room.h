#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <map>
#include <vector>
#include <memory>
#include "Item.h"

class Room {
private:
    int id;
    std::string name;
    std::string description;
    std::string longDescription;
    std::map<std::string, int> exits; // direction -> room_id
    std::vector<std::unique_ptr<Item>> items;
    bool visited;
    bool locked;
    std::string unlockKey; // Item name required to unlock

public:
    Room(int roomId, const std::string& roomName, const std::string& desc);
    Room(int roomId, const std::string& roomName, const std::string& desc, const std::string& longDesc);
    ~Room();
    
    // Getters
    int getId() const { return id; }
    std::string getName() const { return name; }
    std::string getDescription() const;
    bool isVisited() const { return visited; }
    bool isLocked() const { return locked; }
    std::string getUnlockKey() const { return unlockKey; }
    
    // Setters
    void setVisited(bool vis) { visited = vis; }
    void setLocked(bool lock) { locked = lock; }
    void setUnlockKey(const std::string& key) { unlockKey = key; }
    void setLongDescription(const std::string& longDesc) { longDescription = longDesc; }
    
    // Exit management
    void addExit(const std::string& direction, int roomId);
    int getExit(const std::string& direction) const;
    std::vector<std::string> getAvailableExits() const;
    
    // Item management
    void addItem(std::unique_ptr<Item> item);
    std::unique_ptr<Item> removeItem(const std::string& itemName);
    Item* findItem(const std::string& itemName) const;
    void displayItems() const;
    
    // Display methods
    void displayRoom() const;
    void displayExits() const;
};

#endif // ROOM_H