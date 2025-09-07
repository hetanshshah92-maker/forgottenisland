#ifndef ITEM_H
#define ITEM_H

#include <string>

enum class ItemType {
    GENERIC,
    WEAPON,
    KEY,
    CONSUMABLE,
    TREASURE,
    TOOL
};

class Item {
protected:
    std::string name;
    std::string description;
    ItemType type;
    bool canTake;
    bool canUse;
    int value;

public:
    Item(const std::string& itemName, const std::string& desc, ItemType itemType = ItemType::GENERIC);
    virtual ~Item() = default;
    
    // Getters
    std::string getName() const { return name; }
    std::string getDescription() const { return description; }
    ItemType getType() const { return type; }
    bool getCanTake() const { return canTake; }
    bool getCanUse() const { return canUse; }
    int getValue() const { return value; }
    
    // Setters
    void setCanTake(bool take) { canTake = take; }
    void setCanUse(bool use) { canUse = use; }
    void setValue(int val) { value = val; }
    void setDescription(const std::string& desc) { description = desc; }
    
    // Virtual methods for different item behaviors
    virtual std::string use();
    virtual void examine() const;
    
    // Utility methods
    std::string getTypeString() const;
};

// Specialized item classes
class Key : public Item {
private:
    std::string unlocks; // What this key unlocks
    
public:
    Key(const std::string& keyName, const std::string& desc, const std::string& unlocksWhat);
    std::string getUnlocks() const { return unlocks; }
    std::string use() override;
};

class Weapon : public Item {
private:
    int damage;
    
public:
    Weapon(const std::string& weaponName, const std::string& desc, int dmg);
    int getDamage() const { return damage; }
    std::string use() override;
};

class Consumable : public Item {
private:
    int healAmount;
    
public:
    Consumable(const std::string& consumableName, const std::string& desc, int heal);
    int getHealAmount() const { return healAmount; }
    std::string use() override;
};

class Treasure : public Item {
public:
    Treasure(const std::string& treasureName, const std::string& desc, int worth);
    void examine() const override;
};

#endif // ITEM_H