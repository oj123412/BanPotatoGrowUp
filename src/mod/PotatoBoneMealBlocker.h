#pragma once

#include "ll/api/mod/NativeMod.h"
#include "ll/api/event/EventBus.h"
#include "ll/api/event/player/PlayerUseItemEvent.h"
#include "ll/api/event/ListenerBase.h"
#include "mc/world/level/block/Block.h"
#include "mc/world/item/ItemStack.h"
#include "mc/world/actor/player/Player.h"
#include "mc/world/level/BlockPos.h"

#include <string_view>
#include <atomic>
#include <memory>

namespace potato_bonemeal_blocker {

/**
 * @brief Main plugin class that prevents bone meal usage on potato crops
 *
 * This plugin implements a singleton pattern and uses event-driven architecture
 * to intercept PlayerUseItemEvent and selectively block bone meal usage on potatoes.
 *
 * Compatibility:
 * - LeviLamina 3 v1.2.0 and later
 * - Minecraft Bedrock Edition latest versions
 * - Windows x64 platform
 *
 * Performance optimizations:
 * - Cached string comparisons using string_view
 * - Early returns to minimize processing
 * - Atomic counters for statistics
 * - Efficient memory management
 */
class PotatoBoneMealBlocker {
public:
    // Compile-time constants for better performance
    static constexpr std::string_view POTATO_BLOCK_NAME = "minecraft:potatoes";
    static constexpr std::string_view BONE_MEAL_ITEM_NAME = "minecraft:bone_meal";
    static constexpr std::string_view BLOCKED_MESSAGE = "§cBone meal cannot be used on potato crops!";
    static constexpr std::string_view INFO_MESSAGE = "§7You can still use bone meal on other crops.";

    /**
     * @brief Get the singleton instance of the plugin
     * @return Reference to the singleton instance
     */
    static PotatoBoneMealBlocker& getInstance();

    /**
     * @brief Constructor - initializes the plugin with current mod reference
     */
    PotatoBoneMealBlocker() : mSelf(*ll::mod::NativeMod::current()), mBlockedCount(0) {}

    // Disable copy constructor and assignment operator for singleton
    PotatoBoneMealBlocker(const PotatoBoneMealBlocker&) = delete;
    PotatoBoneMealBlocker& operator=(const PotatoBoneMealBlocker&) = delete;

    /**
     * @brief Get reference to the native mod instance
     * @return Reference to the native mod
     */
    [[nodiscard]] ll::mod::NativeMod& getSelf() const noexcept { return mSelf; }

    /**
     * @brief Load the plugin (initialization phase)
     * @return true if loaded successfully, false otherwise
     */
    bool load() noexcept;

    /**
     * @brief Enable the plugin (register event listeners)
     * @return true if enabled successfully, false otherwise
     */
    bool enable() noexcept;

    /**
     * @brief Disable the plugin (unregister event listeners)
     * @return true if disabled successfully, false otherwise
     */
    bool disable() noexcept;

    /**
     * @brief Get the number of blocked bone meal attempts
     * @return Number of times bone meal was blocked on potatoes
     */
    [[nodiscard]] std::uint64_t getBlockedCount() const noexcept { return mBlockedCount.load(); }

private:
    ll::mod::NativeMod& mSelf;
    ll::event::ListenerPtr mPlayerUseItemListener;
    std::atomic<std::uint64_t> mBlockedCount; ///< Thread-safe counter for blocked attempts

    /**
     * @brief Event handler for player item usage
     * @param event The PlayerUseItemEvent to process
     */
    void onPlayerUseItem(ll::event::PlayerUseItemEvent& event) noexcept;

    /**
     * @brief Check if a block is a potato crop
     * @param block The block to check
     * @return true if the block is a potato crop, false otherwise
     */
    [[nodiscard]] bool isPotatoCrop(const Block& block) const noexcept;

    /**
     * @brief Check if an item is bone meal
     * @param item The item to check
     * @return true if the item is bone meal, false otherwise
     */
    [[nodiscard]] bool isBoneMeal(const ItemStack& item) const noexcept;

    /**
     * @brief Send feedback messages to player efficiently
     * @param player The player to send messages to
     */
    void sendBlockedMessage(Player& player) const noexcept;

    /**
     * @brief Log blocked attempt with optimized formatting
     * @param playerName The name of the player
     * @param blockPos The position where bone meal was blocked
     */
    void logBlockedAttempt(std::string_view playerName, const BlockPos& blockPos) const noexcept;
};

} // namespace potato_bonemeal_blocker
