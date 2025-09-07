#include "Item.h"
#include <iostream>

// Base Item class implementation
Item::Item(const std::string& itemName, const std::string& desc, ItemType itemType)
    : name(itemName), description(desc), type(itemType), canTake(true), canUse(false), value(0) {
}

std::string Item::use() {
    if (!canUse) {
        return "You can't use that.";
    }
    return "You use the " + name + ".";
}

void Item::examine() const {
    std::cout << "Looking at the " << name << ":\n";
    std::cout << description << "\n";
    
    if (value > 0) {
        std::cout << "This item appears to be worth " << value << " gold.\n";
    }
    
    if (canTake) {
        std::cout << "You can take this item.\n";
    }
    
    if (canUse) {
        std::cout << "This item can be used.\n";
    }
}

std::string Item::getTypeString() const {
    switch (type) {
        case ItemType::WEAPON: return "Weapon";
        case ItemType::KEY: return "Key";
        case ItemType::CONSUMABLE: return "Consumable";
        case ItemType::TREASURE: return "Treasure";
        case ItemType::TOOL: return "Tool";
        default: return "Item";
    }
}

// Key class implementation
Key::Key(const std::string& keyName, const std::string& desc, const std::string& unlocksWhat)
    : Item(keyName, desc, ItemType::KEY), unlocks(unlocksWhat) {
    canUse = true;
    value = 25;
}

std::string Key::use() {
    return "You hold up the " + name + ". It might unlock " + unlocks + ".";
}

// Weapon class implementation
Weapon::Weapon(const std::string& weaponName, const std::string& desc, int dmg)
    : Item(weaponName, desc, ItemType::WEAPON), damage(dmg) {
    canUse = true;
    value = damage * 2;
}

std::string Weapon::use() {
    return "You brandish the " + name + " menacingly. It deals " + std::to_string(damage) + " damage.";
}

// Consumable class implementation
Consumable::Consumable(const std::string& consumableName, const std::string& desc, int heal)
    : Item(consumableName, desc, ItemType::CONSUMABLE), healAmount(heal) {
    canUse = true;
    value = healAmount;
}

std::string Consumable::use() {
    return "You consume the " + name + " and feel refreshed!";
}

// Treasure class implementation
Treasure::Treasure(const std::string& treasureName, const std::string& desc, int worth)
    : Item(treasureName, desc, ItemType::TREASURE) {
    value = worth;
    canUse = false;
}

void Treasure::examine() const {
    std::cout << "Looking at the " << name << ":\n";
    std::cout << description << "\n";
    std::cout << "This treasure is worth " << value << " gold! ";
    std::cout << "It would fetch a handsome price from any collector.\n";
    
    if (canTake) {
        std::cout << "You can take this valuable item.\n";
    }
}