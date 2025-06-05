# Potato Bone Meal Blocker

A LeviLamina native plugin for Minecraft Bedrock Edition servers that specifically prevents the use of bone meal on potato crops only, while allowing bone meal to work normally on all other plants.

## Features

- **Targeted Prevention**: Only blocks bone meal usage on potato crops (`minecraft:potatoes`)
- **Selective Blocking**: Allows bone meal to work normally on wheat, carrots, beetroot, and all other plants
- **Player Feedback**: Sends clear localized messages to players when bone meal usage is blocked
- **Chinese Language Support**: Full Chinese (Simplified) language support for Chinese servers
- **Efficient**: Minimal performance impact with targeted event handling
- **Logging**: Comprehensive logging for debugging and monitoring

## Differences from Existing Solutions

Unlike the existing `forbidbonemeal` plugin that bans bone meal usage on ALL plants, this plugin:
- ✅ **Only blocks potato crops** - wheat, carrots, beetroot work normally
- ✅ **Surgical precision** - no interference with other gameplay mechanics
- ✅ **Better user experience** - clear feedback about what's blocked and what isn't

## Language Support

### **Default: Chinese (Simplified)**
The plugin defaults to Chinese language for Chinese Minecraft servers:

**Blocked Message:** `§c骨粉不能用于土豆作物！`
**Info Message:** `§e你仍然可以在其他作物上使用骨粉。`

### **Supported Languages**
- **Chinese Simplified (zh_CN)** - Default for Chinese servers
- **English (en_US)** - Fallback language

### **Language Configuration**
Edit `config/potato-bonemeal-blocker.json` to change language:
```json
{
    "language": {
        "code": "zh_CN"
    }
}
```

**📖 Chinese Documentation:** See [README_CN.md](README_CN.md) for complete Chinese documentation.

## Requirements

- LeviLamina 3 >= 1.2.0
- Minecraft Bedrock Dedicated Server
- Windows x64 platform

## Installation

### Method 1: Manual Installation

1. Download `potato-bonemeal-blocker.dll` from releases
2. Place in your server's `plugins/` directory
3. Restart your server

### Method 2: Build from Source

```bash
# Prerequisites: XMake + Visual Studio 2022
git clone <repository-url>
cd potato-bonemeal-blocker
xmake f -a x64 -m release -p windows -y
xmake
# Find compiled DLL in bin/ directory
```

## Usage

Once installed, the plugin works automatically:

- ✅ **Allowed**: Bone meal on wheat, carrots, beetroot, saplings, flowers, etc.
- ❌ **Blocked**: Bone meal on potato crops only
- 📢 **Feedback**: Players receive clear messages when blocked
- 📝 **Logging**: Server logs all prevention events

## Technical Implementation

- **Event System**: Uses `PlayerUseItemEvent` for efficient interception
- **Block Detection**: Identifies `minecraft:potatoes` specifically
- **Item Detection**: Identifies `minecraft:bone_meal` specifically
- **Error Handling**: Graceful degradation on API compatibility issues
- **Performance**: Early returns and minimal processing overhead

## Compatibility

- **LeviLamina**: 3 >= 1.2.0
- **Minecraft Bedrock**: Latest stable versions
- **Platform**: Windows x64

## License

CC0-1.0 - Public Domain Dedication
