# 🌊 Journey of the Forgotten Island 🌊

A text-based adventure game written in C++ where you explore a mysterious island, solve puzzles, collect treasures, and find your way home.

## 📖 Story

You wake up on a sandy beach after your ship was caught in a terrible storm. You find yourself alone on an unknown island with no sign of your crew. As the sun sets, you must explore the island, find shelter, collect useful items, and ultimately discover the ancient treasure that will help you escape back to civilization.

## 🎮 Features

- **Rich Interactive World**: Explore 10+ unique locations including beaches, jungles, caves, and ancient temples
- **Inventory Management**: Collect and use various items including weapons, keys, treasures, and consumables
- **Puzzle Solving**: Unlock secrets and solve challenges to progress through the game
- **Character Progression**: Track your health, score, and discoveries
- **Multiple Item Types**: 
  - 🗝️ Keys to unlock new areas
  - ⚔️ Weapons for protection
  - 💊 Consumables for healing
  - 💎 Treasures for points
  - 🛠️ Tools for solving puzzles

## 🚀 Quick Start

### Prerequisites

- C++ compiler with C++17 support (GCC, Clang, or MSVC)
- Make (optional, for using the Makefile)

### Building the Game

#### Using Make (Recommended)

```bash
# Clone the repository
git clone https://github.com/yourusername/forgotten-island.git
cd forgotten-island

# Build the game
make

# Run the game
make run
```

#### Manual Compilation

```bash
# Compile all source files
g++ -std=c++17 -Wall -Wextra -O2 -o forgotten_island main.cpp Game.cpp GameInitialization.cpp Player.cpp Room.cpp Item.cpp

# Run the game
./forgotten_island
```

## 🎯 How to Play

### Basic Commands

**Movement:**
- `north`, `south`, `east`, `west`, `up`, `down` (or `n`, `s`, `e`, `w`, `u`, `d`)
- `go <direction>` - Move in a specified direction

**Interaction:**
- `look` - Examine your surroundings
- `examine <item>` - Look at something closely
- `take <item>` - Pick up an item
- `drop <item>` - Drop an item from inventory
- `use <item>` - Use an item

**Information:**
- `inventory` (or `i`) - Check your items
- `status` - Check your health and condition
- `score` - View your current score
- `help` - Show all available commands

**Game Control:**
- `quit` (or `q`) - Exit the game

### Game Tips

1. **Explore thoroughly** - Check every room and examine everything you find
2. **Collect items** - Many items are useful for solving puzzles or surviving
3. **Pay attention to descriptions** - They often contain important clues
4. **Use your inventory wisely** - You have limited carrying capacity
5. **Save healing items** - You might need them in dangerous situations
6. **Look for keys** - Some areas require specific keys to access

## 🗺️ Game World

The island contains various interconnected locations:

- 🏖️ **Sandy Beach** - Your starting location
- 🌿 **Jungle Paths** - Dense tropical vegetation with hidden secrets
- 🪨 **Rocky Outcrop** - High ground with great views of the island
- 🕳️ **Hidden Cave** - Dark caves containing mysterious items
- 🏛️ **Ancient Ruins** - Weathered stone structures with ancient mysteries
- ⛩️ **Temple Complex** - Sacred chambers holding the island's greatest treasures

## 🏗️ Project Structure

```
forgotten-island/
├── main.cpp                 # Main entry point
├── Game.h                   # Game class header
├── Game.cpp                 # Game class implementation
├── GameInitialization.cpp   # World setup and item placement
├── Player.h                 # Player class header
├── Player.cpp               # Player class implementation
├── Room.h                   # Room class header
├── Room.cpp                 # Room class implementation
├── Item.h                   # Item classes header
├── Item.cpp                 # Item classes implementation
├── Makefile                 # Build configuration
├── README.md               # This file
└── bin/                    # Compiled executable (created during build)
```

## 🛠️ Development

### Building for Development

```bash
# Debug build with symbols
make debug

# Run with debug build
make run-debug

# Clean build files
make clean
```

### Adding New Content

**Adding New Rooms:**
1. Edit `GameInitialization.cpp`
2. Create new Room objects in `initializeRooms()`
3. Connect them with exits to existing rooms

**Adding New Items:**
1. Create items in `initializeItems()` in `GameInitialization.cpp`
2. Use appropriate item types: `Item`, `Key`, `Weapon`, `Consumable`, or `Treasure`
3. Place items in rooms using `room->addItem()`

**Adding New Game Logic:**
1. Modify `processCommand()` in `Game.cpp` for new commands
2. Update `updateGameState()` for new game flags and conditions
3. Modify `checkWinCondition()` for new victory conditions

### Code Style Guidelines

- Use meaningful variable and function names
- Follow RAII principles for memory management
- Use `std::unique_ptr` for ownership semantics
- Keep functions focused and single-purpose
- Add comments for complex game logic

## 🎮 Game Mechanics

### Health System
- Start with 100 health points
- Take damage from hazards and combat
- Use consumable items to heal
- Game ends if health reaches 0

### Inventory System
- Limited carrying capacity (10 items by default)
- Different item types with unique behaviors
- Items can be examined for detailed descriptions
- Some items are required to progress

### Scoring System
- Gain points for discovering items (+10)
- Bonus points for using consumables (+5)
- Major bonuses for reaching new areas
- Final bonus for completing the game (+100)

### Puzzle Elements
- Locked doors requiring specific keys
- Environmental challenges requiring tools
- Hidden items in secret locations
- Sequential puzzle solving

## 🏆 Walkthrough (Spoilers!)

<details>
<summary>Click to reveal complete walkthrough</summary>

1. **Beach (Start)**: Take seashell and driftwood
2. **Rocky Outcrop** (north): Get binoculars, go down to cave
3. **Hidden Cave**: Take torch and crystals
4. **Jungle Path** (west from beach): Get vine
5. **Dense Jungle** (north): Take machete
6. **Ancient Ruins**: Get rusty key
7. **Temple Antechamber** (north): Get temple key, scroll, and healing potion
8. **Inner Temple** (use temple key): Get golden idol
9. **Mysterious Grove** (west from temple): Get herbs and stone tablet
10. **Treasure Chamber** (east from temple): Get ancient treasure, map, and supplies
11. **Victory!** - You've found the treasure and escape route

</details>

## 🐛 Troubleshooting

### Common Issues

**Game won't compile:**
- Ensure you have a C++17 compatible compiler
- Check that all source files are in the same directory
- Verify Make is installed if using the Makefile

**"Command not found" errors:**
- Make sure you're typing commands exactly as shown
- Use `help` command to see all available commands
- Check spelling and try shorter versions (e.g., `n` instead of `north`)

**Can't pick up items:**
- Check if your inventory is full (`inventory` command)
- Some items can't be taken (examine them for clues)
- Drop unnecessary items to make space

**Can't enter certain areas:**
- Look for required keys or items
- Some areas require specific items to unlock
- Examine doors and barriers for clues

## 📚 Technical Details

### Memory Management
- Uses RAII and smart pointers (`std::unique_ptr`)
- No manual memory allocation/deallocation
- Exception-safe resource management

### Design Patterns Used
- **Command Pattern**: For processing user input
- **Factory Pattern**: For creating different item types
- **State Pattern**: For game state management
- **Observer Pattern**: For game event handling

### Performance Considerations
- Efficient string operations using references
- Minimal dynamic allocations during gameplay
- Fast lookup using `std::map` for rooms and game flags

## 🤝 Contributing

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add some amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

### Contribution Ideas
- Add new locations and items
- Implement save/load functionality
- Add more interactive NPCs
- Create additional puzzle types
- Improve the user interface
- Add sound effects (ASCII art sounds!)
- Create difficulty levels

## 📄 License

This project is licensed under the MIT License - see the LICENSE file for details.

## 🙏 Acknowledgments

- Inspired by classic text adventure games like Zork and Adventure
- Thanks to the C++ community for excellent documentation
- Special thanks to all contributors and players

## 📞 Support

If you encounter any issues or have questions:

1. Check this README for common solutions
2. Look at the source code comments for implementation details
3. Create an issue on GitHub with detailed information
4. Include your compiler version and operating system

---

**Have fun exploring the Forgotten Island! 🏝️**

*May your adventure be filled with discovery and wonder!*