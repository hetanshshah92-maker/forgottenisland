#include "Game.h"

void Game::initializeRooms() {
    // Room 1: Beach (Starting location)
    auto beach = std::make_unique<Room>(1, "Sandy Beach", 
        "You are on a pristine sandy beach. The ocean stretches endlessly to the east.",
        "The warm sand feels good beneath your feet. Waves gently lap at the shore, "
        "and you can hear seabirds calling in the distance. To the west, a dense jungle "
        "beckons with mysterious shadows. Palm trees sway in the tropical breeze.");
    beach->addExit("west", 2);
    beach->addExit("north", 3);
    
    // Room 2: Jungle Path
    auto junglePath = std::make_unique<Room>(2, "Jungle Path",
        "A narrow path winds through dense tropical vegetation.",
        "Thick vines hang from towering trees, creating a green canopy overhead. "
        "The air is humid and filled with the sounds of exotic birds and insects. "
        "Strange flowers bloom in vibrant colors along the path.");
    junglePath->addExit("east", 1);
    junglePath->addExit("north", 4);
    junglePath->addExit("west", 5);
    
    // Room 3: Rocky Outcrop
    auto rockyOutcrop = std::make_unique<Room>(3, "Rocky Outcrop",
        "You stand on a high rocky formation overlooking the island.",
        "From this vantage point, you can see the entire island laid out before you. "
        "The beach stretches to the south, jungle covers most of the interior, and "
        "you can make out what looks like ancient ruins to the northwest. A cave "
        "entrance is visible in the rocks below.");
    rockyOutcrop->addExit("south", 1);
    rockyOutcrop->addExit("down", 6);
    
    // Room 4: Dense Jungle
    auto denseJungle = std::make_unique<Room>(4, "Dense Jungle",
        "The jungle grows thicker here, making progress difficult.",
        "Massive trees tower overhead, their branches intertwined to form an almost "
        "impenetrable canopy. Shafts of sunlight pierce through occasionally, "
        "illuminating patches of colorful orchids and strange fungi.");
    denseJungle->addExit("south", 2);
    denseJungle->addExit("west", 7);
    
    // Room 5: Ancient Ruins Entrance
    auto ruinsEntrance = std::make_unique<Room>(5, "Ancient Ruins Entrance",
        "You stand before the crumbling entrance to ancient stone ruins.",
        "Weathered stone blocks covered in mysterious carvings form an archway. "
        "Vines and moss have claimed much of the structure, but you can still make "
        "out intricate patterns etched into the stone. The entrance leads north "
        "into darkness.");
    ruinsEntrance->addExit("east", 2);
    ruinsEntrance->addExit("north", 8);
    
    // Room 6: Hidden Cave
    auto hiddenCave = std::make_unique<Room>(6, "Hidden Cave",
        "You are in a damp cave hidden within the rocky outcrop.",
        "The cave is cool and damp, with water dripping steadily from stalactites "
        "above. Strange phosphorescent moss provides a faint, eerie glow. Deep "
        "shadows conceal the far reaches of the cave.");
    hiddenCave->addExit("up", 3);
    
    // Room 7: Mysterious Grove
    auto mysteriousGrove = std::make_unique<Room>(7, "Mysterious Grove",
        "You enter a circular clearing surrounded by ancient trees.",
        "This grove feels different from the rest of the jungle. The trees here "
        "are older and more gnarled, their branches forming almost perfect circle "
        "overhead. In the center stands a weathered stone altar covered in strange "
        "symbols.");
    mysteriousGrove->addExit("east", 4);
    mysteriousGrove->addExit("north", 9);
    
    // Room 8: Temple Antechamber
    auto templeAntechamber = std::make_unique<Room>(8, "Temple Antechamber",
        "You are in a stone chamber filled with ancient artifacts.",
        "This rectangular chamber is lined with stone shelves holding mysterious "
        "objects. Faded murals on the walls depict scenes of ancient ceremonies. "
        "A heavy stone door to the north is sealed with an intricate lock mechanism.");
    templeAntechamber->addExit("south", 5);
    templeAntechamber->addExit("north", 9);
    
    // Room 9: Inner Temple (requires key)
    auto innerTemple = std::make_unique<Room>(9, "Inner Temple",
        "You stand in the heart of the ancient temple.",
        "This grand chamber rises high above you, supported by carved stone pillars. "
        "Shafts of light filter down from openings in the ceiling, illuminating "
        "intricate carvings that tell the story of the island's ancient civilization. "
        "A passage to the east leads deeper into the temple complex.");
    innerTemple->addExit("south", 8);
    innerTemple->addExit("east", 10);
    innerTemple->addExit("west", 7);
    innerTemple->setLocked(true);
    innerTemple->setUnlockKey("temple key");
    
    // Room 10: Treasure Chamber (final room)
    auto treasureChamber = std::make_unique<Room>(10, "Treasure Chamber",
        "You have discovered the legendary treasure chamber!",
        "This magnificent chamber is filled with golden artifacts and precious gems. "
        "Ancient chests line the walls, overflowing with treasure accumulated over "
        "centuries. At the far end, a hidden passage leads to a dock where a small "
        "boat waits - your escape route off the island!");
    treasureChamber->addExit("west", 9);
    
    // Add all rooms to the game
    rooms[1] = std::move(beach);
    rooms[2] = std::move(junglePath);
    rooms[3] = std::move(rockyOutcrop);
    rooms[4] = std::move(denseJungle);
    rooms[5] = std::move(ruinsEntrance);
    rooms[6] = std::move(hiddenCave);
    rooms[7] = std::move(mysteriousGrove);
    rooms[8] = std::move(templeAntechamber);
    rooms[9] = std::move(innerTemple);
    rooms[10] = std::move(treasureChamber);
}

void Game::initializeItems() {
    // Beach items
    auto seashell = std::make_unique<Item>("seashell", 
        "A beautiful conch shell washed up by the waves. It still echoes with the sound of the ocean.");
    seashell->setCanTake(true);
    seashell->setValue(5);
    rooms[1]->addItem(std::move(seashell));
    
    auto driftwood = std::make_unique<Item>("driftwood",
        "A piece of weathered wood from your shipwreck. It might be useful for something.");
    driftwood->setCanTake(true);
    driftwood->setValue(10);
    rooms[1]->addItem(std::move(driftwood));
    
    // Jungle Path items
    auto vine = std::make_unique<Item>("vine",
        "A strong, flexible vine that could be useful for climbing or binding things together.");
    vine->setCanTake(true);
    vine->setCanUse(true);
    vine->setValue(15);
    rooms[2]->addItem(std::move(vine));
    
    // Rocky Outcrop items
    auto binoculars = std::make_unique<Item>("binoculars",
        "An old pair of binoculars, probably from another shipwreck survivor. Still functional.");
    binoculars->setCanTake(true);
    binoculars->setCanUse(true);
    binoculars->setValue(25);
    rooms[3]->addItem(std::move(binoculars));
    
    // Hidden Cave items
    auto torch = std::make_unique<Item>("torch",
        "A makeshift torch that provides light in dark places. The flame flickers but burns steadily.");
    torch->setCanTake(true);
    torch->setCanUse(true);
    torch->setValue(30);
    rooms[6]->addItem(std::move(torch));
    
    auto crystals = std::make_unique<Treasure>("crystals",
        "Beautiful luminescent crystals that glow with an inner light.", 50);
    crystals->setCanTake(true);
    rooms[6]->addItem(std::move(crystals));
    
    // Dense Jungle items
    auto machete = std::make_unique<Weapon>("machete",
        "A sharp machete perfect for cutting through jungle vegetation and defending yourself.", 15);
    machete->setCanTake(true);
    machete->setValue(40);
    rooms[4]->addItem(std::move(machete));
    
    // Mysterious Grove items
    auto herbs = std::make_unique<Consumable>("herbs",
        "Medicinal herbs that can restore health when consumed.", 25);
    herbs->setCanTake(true);
    rooms[7]->addItem(std::move(herbs));
    
    auto stone_tablet = std::make_unique<Item>("tablet",
        "An ancient stone tablet covered in mysterious hieroglyphs. It might contain important information.");
    stone_tablet->setCanTake(true);
    stone_tablet->setValue(35);
    rooms[7]->addItem(std::move(stone_tablet));
    
    // Ancient Ruins Entrance items
    auto old_key = std::make_unique<Key>("rusty key",
        "An old, rusty key found among the ruins. It looks like it might open something important.", "chest");
    old_key->setCanTake(true);
    old_key->setValue(20);
    rooms[5]->addItem(std::move(old_key));
    
    // Temple Antechamber items
    auto temple_key = std::make_unique<Key>("temple key",
        "An ornate golden key with intricate engravings. It bears the same symbols as the temple walls.", "inner temple");
    temple_key->setCanTake(true);
    temple_key->setValue(75);
    rooms[8]->addItem(std::move(temple_key));
    
    auto ancient_scroll = std::make_unique<Item>("scroll",
        "An ancient scroll with faded text. You can barely make out warnings about temple guardians.");
    ancient_scroll->setCanTake(true);
    ancient_scroll->setValue(30);
    rooms[8]->addItem(std::move(ancient_scroll));
    
    auto healing_potion = std::make_unique<Consumable>("potion",
        "A mysterious healing potion in a crystal vial. The liquid glows with a soft blue light.", 50);
    healing_potion->setCanTake(true);
    rooms[8]->addItem(std::move(healing_potion));
    
    // Inner Temple items
    auto golden_idol = std::make_unique<Treasure>("idol",
        "A beautiful golden idol depicting an ancient island deity. It's incredibly valuable.", 100);
    golden_idol->setCanTake(true);
    rooms[9]->addItem(std::move(golden_idol));
    
    // Treasure Chamber items (final prize)
    auto ancient_treasure = std::make_unique<Treasure>("ancient treasure",
        "The legendary treasure of the forgotten island! A chest filled with gold, gems, and ancient artifacts.", 500);
    ancient_treasure->setCanTake(true);
    rooms[10]->addItem(std::move(ancient_treasure));
    
    auto map = std::make_unique<Item>("map",
        "A detailed map showing the location of the hidden dock and the route back to civilization.");
    map->setCanTake(true);
    map->setCanUse(true);
    map->setValue(100);
    rooms[10]->addItem(std::move(map));
    
    auto emergency_supplies = std::make_unique<Consumable>("supplies",
        "Emergency supplies including food and fresh water for the journey home.", 75);
    emergency_supplies->setCanTake(true);
    rooms[10]->addItem(std::move(emergency_supplies));
}