#pragma once

/**
 * @brief Mock implementations for LeviLamina API for testing purposes
 * 
 * This file provides minimal mock implementations of LeviLamina classes
 * to allow unit testing and benchmarking without requiring the full
 * LeviLamina framework.
 */

#ifdef MOCK_LEVILAMINA

#include <string>
#include <memory>
#include <functional>
#include <optional>

// Mock LeviLamina namespace structure
namespace ll {
    namespace mod {
        class NativeMod {
        public:
            static NativeMod* current() {
                static NativeMod instance;
                return &instance;
            }
            
            struct Logger {
                void info(const std::string& msg) const {}
                void error(const std::string& msg) const {}
                void debug(const std::string& msg) const {}
                
                template<typename... Args>
                void info(const std::string& format, Args&&... args) const {}
                
                template<typename... Args>
                void error(const std::string& format, Args&&... args) const {}
                
                template<typename... Args>
                void debug(const std::string& format, Args&&... args) const {}
            };
            
            Logger getLogger() const { return Logger{}; }
        };
    }
    
    namespace event {
        using ListenerPtr = std::shared_ptr<void>;
        
        class EventBus {
        public:
            static EventBus& getInstance() {
                static EventBus instance;
                return instance;
            }
            
            template<typename EventType>
            ListenerPtr emplaceListener(std::function<void(EventType&)> callback) {
                return std::make_shared<int>(42); // Dummy listener
            }
            
            void removeListener(ListenerPtr listener) {}
        };
        
        class PlayerUseItemEvent {
        public:
            struct MockItemStack {
                std::string getTypeName() const { return "minecraft:bone_meal"; }
            };
            
            struct MockPlayer {
                std::string getName() const { return "TestPlayer"; }
                void sendMessage(const std::string& msg) const {}
                
                struct MockDimension {
                    struct MockBlock {
                        std::string getTypeName() const { return "minecraft:potatoes"; }
                    };
                    
                    MockBlock getBlock(const struct BlockPos& pos) const { return MockBlock{}; }
                };
                
                MockDimension getDimension() const { return MockDimension{}; }
            };
            
            MockItemStack getItemStack() const { return MockItemStack{}; }
            MockPlayer getPlayer() const { return MockPlayer{}; }
            
            std::optional<struct BlockPos> getBlockPos() const {
                return BlockPos{0, 64, 0};
            }
            
            void cancel() {}
        };
    }
}

// Mock Minecraft namespace
struct BlockPos {
    int x, y, z;
    BlockPos(int x = 0, int y = 0, int z = 0) : x(x), y(y), z(z) {}
};

class Block {
public:
    std::string getTypeName() const { return "minecraft:potatoes"; }
};

class ItemStack {
public:
    std::string getTypeName() const { return "minecraft:bone_meal"; }
};

class Player {
public:
    std::string getName() const { return "TestPlayer"; }
    void sendMessage(const std::string& msg) const {}
    
    struct Dimension {
        Block getBlock(const BlockPos& pos) const { return Block{}; }
    };
    
    Dimension getDimension() const { return Dimension{}; }
};

// Mock registration macro
#define LL_REGISTER_MOD(className, instance) \
    static className* g_mock_instance = &instance;

#endif // MOCK_LEVILAMINA
