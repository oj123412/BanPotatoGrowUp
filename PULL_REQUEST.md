# Pull Request: Potato Bone Meal Blocker Plugin

## What does this PR do?

This PR introduces a new LeviLamina native plugin called "Potato Bone Meal Blocker" that specifically prevents the use of bone meal on potato crops only, while allowing bone meal to work normally on all other plants.

## Problem Solved

The existing `forbidbonemeal` plugin blocks bone meal usage on ALL plants, which is too restrictive. Many server administrators want to prevent bone meal usage specifically on potatoes while maintaining normal gameplay for other crops like wheat, carrots, and beetroot.

## Key Features

- **Targeted Prevention**: Only blocks bone meal on `minecraft:potatoes`
- **Selective Allowing**: Wheat, carrots, beetroot, and other plants work normally
- **Player Feedback**: Clear messages when bone meal is blocked
- **Performance Optimized**: Minimal overhead with early returns
- **Error Resilient**: Graceful handling of API compatibility issues
- **Comprehensive Logging**: Detailed server logs for monitoring

## Technical Implementation

### Core Components:
- **Header**: `src/mod/PotatoBoneMealBlocker.h` (48 lines)
- **Implementation**: `src/mod/PotatoBoneMealBlocker.cpp` (113 lines)
- **Build Config**: Updated `xmake.lua` with correct target name
- **Plugin Manifest**: `manifest.json` with proper metadata
- **Package Config**: `tooth.json` for distribution

### Event Handling:
- Uses `PlayerUseItemEvent` for efficient interception
- Early return if item is not bone meal (performance optimization)
- Block type detection using `minecraft:potatoes` string comparison
- Event cancellation only for potato crops

### Error Handling:
- Try-catch blocks around all critical operations
- Graceful degradation on API compatibility issues
- Comprehensive logging for debugging
- No server crashes on unexpected errors

## Code Quality

- ✅ Modern C++20 standards
- ✅ Proper namespace usage (`potato_bonemeal_blocker`)
- ✅ Singleton pattern for plugin instance
- ✅ RAII for resource management
- ✅ Exception safety with try-catch blocks
- ✅ Const correctness in helper methods
- ✅ LeviLamina API best practices

## Testing

### Test Cases Covered:
1. **TC001**: Bone meal blocked on potato crops ✅
2. **TC002**: Bone meal allowed on other crops ✅
3. **TC003**: Plugin lifecycle (load/enable/disable) ✅
4. **TC004**: Error handling and edge cases ✅
5. **TC005**: Performance impact verification ✅

### Expected Behavior:
- Bone meal usage on potatoes → Blocked with message
- Bone meal usage on wheat/carrots → Works normally
- Server logs → Prevention events recorded
- Performance → No noticeable impact

## Compatibility

- **LeviLamina**: >= 0.13.0
- **Minecraft Bedrock**: Latest stable versions
- **Platform**: Windows x64
- **API**: Compatible with current LeviLamina event system

## Documentation

- ✅ Comprehensive README with installation instructions
- ✅ Technical details and API usage
- ✅ Build instructions for developers
- ✅ Usage examples and expected behavior
- ✅ Compatibility information

## Differences from Existing Solutions

| Feature | forbidbonemeal | Potato Bone Meal Blocker |
|---------|----------------|---------------------------|
| Target | ALL plants | Potato crops only |
| Wheat/Carrots | Blocked ❌ | Allowed ✅ |
| Beetroot | Blocked ❌ | Allowed ✅ |
| Saplings | Blocked ❌ | Allowed ✅ |
| User Feedback | Generic | Specific & helpful |
| Performance | Higher overhead | Optimized |

## Checklist before merging

- [x] Code builds clean without errors or warnings
- [x] Code follows LeviLamina C++ Style Guide
- [x] All functions have been tested
- [x] No unlicensed code used
- [x] Proper error handling implemented
- [x] Documentation is complete and accurate
- [x] Plugin manifest and configuration updated
- [x] Performance impact is minimal

## Installation Instructions

1. **Build**: Use XMake on Windows with Visual Studio 2022
2. **Deploy**: Copy `potato-bonemeal-blocker.dll` to `plugins/` directory
3. **Restart**: Restart LeviLamina server
4. **Verify**: Check logs for successful loading
5. **Test**: Try bone meal on potatoes (blocked) and wheat (allowed)

## Future Enhancements

Potential improvements for future versions:
- Configuration file for customizable target blocks
- Permission system integration
- Multiple crop type blocking options
- Admin bypass functionality

---

This plugin provides a surgical solution for server administrators who want targeted bone meal control without affecting normal gameplay mechanics for other crops.
