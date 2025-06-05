#include "mod/PotatoBoneMealBlocker.h"
#include "mod/Language.h"
#include "ll/api/mod/RegisterHelper.h"
#include "ll/api/event/EventBus.h"
#include "mc/world/level/block/Block.h"
#include "mc/world/item/ItemStack.h"
#include "mc/world/actor/player/Player.h"
#include "mc/world/level/BlockPos.h"
#include "mc/world/level/Level.h"
#include "mc/world/level/dimension/Dimension.h"
#include "mc/world/level/BlockSource.h"

#include <string_view>
#include <sstream>
#include <iomanip>

namespace potato_bonemeal_blocker {

PotatoBoneMealBlocker& PotatoBoneMealBlocker::getInstance() {
    static PotatoBoneMealBlocker instance;
    return instance;
}

bool PotatoBoneMealBlocker::load() noexcept {
    try {
        // Initialize language system for Chinese servers
        auto& language = Language::getInstance();
        language.setLanguage(Language::LanguageCode::CHINESE_SIMPLIFIED);

        getSelf().getLogger().info(language.getLoadingMessage());
        getSelf().getLogger().info(language.getCompatibilityMessage());
        getSelf().getLogger().info(language.getMessage("optimization"));
        return true;
    } catch (...) {
        // Fallback logging in case of logger issues
        return false;
    }
}

bool PotatoBoneMealBlocker::enable() noexcept {
    try {
        getSelf().getLogger().info("Enabling Potato Bone Meal Blocker...");

        auto& eventBus = ll::event::EventBus::getInstance();

        // Use optimized lambda capture for better performance
        mPlayerUseItemListener = eventBus.emplaceListener<ll::event::PlayerInteractBlockEvent>(
            [this](ll::event::PlayerInteractBlockEvent& event) noexcept {
                onPlayerInteractBlock(event);
            }
        );

        if (!mPlayerUseItemListener) {
            getSelf().getLogger().error("Failed to register event listener");
            return false;
        }

        auto& language = Language::getInstance();
        getSelf().getLogger().info(language.getEnabledMessage());
        getSelf().getLogger().info(language.getMessage("listener_registered"));
        return true;

    } catch (const std::exception& e) {
        getSelf().getLogger().error("Failed to enable plugin: {}", e.what());
        return false;
    } catch (...) {
        getSelf().getLogger().error("Failed to enable plugin: Unknown error");
        return false;
    }
}

bool PotatoBoneMealBlocker::disable() noexcept {
    try {
        getSelf().getLogger().info("Disabling Potato Bone Meal Blocker...");

        if (mPlayerUseItemListener) {
            ll::event::EventBus::getInstance().removeListener(mPlayerUseItemListener);
            mPlayerUseItemListener.reset();
            getSelf().getLogger().info("Event listener unregistered successfully");
        }

        // Log final statistics
        const auto blockedCount = getBlockedCount();
        if (blockedCount > 0) {
            getSelf().getLogger().info("Total bone meal attempts blocked on potatoes: {}", blockedCount);
        }

        auto& language = Language::getInstance();
        getSelf().getLogger().info(language.getMessage("disabled"));
        return true;

    } catch (const std::exception& e) {
        getSelf().getLogger().error("Error during disable: {}", e.what());
        return false;
    } catch (...) {
        // Ensure we always return gracefully
        return false;
    }
}

void PotatoBoneMealBlocker::onPlayerInteractBlock(ll::event::PlayerInteractBlockEvent& event) noexcept {
    try {
        const auto& itemStack = event.item();

        // Critical performance optimization: Early return if not bone meal
        // This check happens first to minimize processing for non-bone-meal items
        if (!isBoneMeal(itemStack)) [[likely]] {
            return;
        }

        auto& player = event.self();

        // Get block position and block directly from the event
        try {
            const auto& blockPos = event.blockPos();

            // Check if we have a valid block reference
            auto blockRef = event.block();
            if (!blockRef.has_value()) [[unlikely]] {
                // Fallback: get block from dimension if direct reference not available
                auto& dimension = player.getDimension();
                auto& blockSource = dimension.getBlockSourceFromMainChunkSource();
                const auto& block = blockSource.getBlock(blockPos);

                // Check if this is a potato crop that should be blocked
                if (isPotatoCrop(block)) [[unlikely]] {
                    // Cancel the event to prevent bone meal usage
                    event.cancel();

                    // Send optimized feedback messages
                    sendBlockedMessage(player);

                    // Log the blocked attempt with optimized formatting
                    logBlockedAttempt(player.getRealName(), blockPos);

                    // Increment atomic counter for statistics
                    mBlockedCount.fetch_add(1, std::memory_order_relaxed);
                }
            } else {
                // Use the direct block reference for better performance
                const auto& block = blockRef.value();

                // Check if this is a potato crop that should be blocked
                if (isPotatoCrop(block)) [[unlikely]] {
                    // Cancel the event to prevent bone meal usage
                    event.cancel();

                    // Send optimized feedback messages
                    sendBlockedMessage(player);

                    // Log the blocked attempt with optimized formatting
                    logBlockedAttempt(player.getRealName(), blockPos);

                    // Increment atomic counter for statistics
                    mBlockedCount.fetch_add(1, std::memory_order_relaxed);
                }
            }

        } catch (const std::exception& blockException) {
            // Log block position errors at debug level to avoid spam
            getSelf().getLogger().debug("Could not process block interaction: {}", blockException.what());
        }

    } catch (const std::exception& e) {
        getSelf().getLogger().error("Error in onPlayerInteractBlock: {}", e.what());
    } catch (...) {
        // Catch-all to prevent any crashes
        getSelf().getLogger().error("Unknown error in onPlayerInteractBlock");
    }
}

bool PotatoBoneMealBlocker::isPotatoCrop(const Block& block) const noexcept {
    try {
        // Use string_view for efficient comparison without allocations
        const auto blockName = block.getTypeName();
        const std::string_view blockNameView{blockName};

        // Direct comparison with compile-time constant
        return blockNameView == POTATO_BLOCK_NAME;

    } catch (const std::exception& e) {
        getSelf().getLogger().debug("Error checking block type: {}", e.what());
        return false;
    } catch (...) {
        // Catch-all for safety
        return false;
    }
}

bool PotatoBoneMealBlocker::isBoneMeal(const ItemStack& item) const noexcept {
    try {
        // Use string_view for efficient comparison without allocations
        const auto itemName = item.getTypeName();
        const std::string_view itemNameView{itemName};

        // Direct comparison with compile-time constant
        return itemNameView == BONE_MEAL_ITEM_NAME;

    } catch (const std::exception& e) {
        getSelf().getLogger().debug("Error checking item type: {}", e.what());
        return false;
    } catch (...) {
        // Catch-all for safety
        return false;
    }
}

void PotatoBoneMealBlocker::sendBlockedMessage(Player& player) const noexcept {
    try {
        // Send localized messages using the language system
        auto& language = Language::getInstance();
        player.sendMessage(language.getBlockedMessage());
        player.sendMessage(language.getInfoMessage());
    } catch (const std::exception& e) {
        getSelf().getLogger().debug("Error sending message to player: {}", e.what());
    } catch (...) {
        // Silently fail to avoid cascading errors
    }
}

void PotatoBoneMealBlocker::logBlockedAttempt(std::string_view playerName, const BlockPos& blockPos) const noexcept {
    try {
        // Use stringstream for efficient string formatting (compatible with older C++ standards)
        std::ostringstream logStream;
        logStream << "Prevented " << playerName
                  << " from using bone meal on potato crop at ("
                  << blockPos.x << ", " << blockPos.y << ", " << blockPos.z << ")";

        getSelf().getLogger().info(logStream.str());

    } catch (const std::exception& e) {
        // Fallback to basic logging if formatting fails
        getSelf().getLogger().info("Prevented player from using bone meal on potato crop");
        getSelf().getLogger().debug("Logging error: {}", e.what());
    } catch (...) {
        // Last resort logging
        getSelf().getLogger().info("Prevented bone meal usage on potato crop");
    }
}

} // namespace potato_bonemeal_blocker

LL_REGISTER_MOD(potato_bonemeal_blocker::PotatoBoneMealBlocker, potato_bonemeal_blocker::PotatoBoneMealBlocker::getInstance());

// Explicit plugin export functions for better compatibility
extern "C" {
    __declspec(dllexport) bool ll_plugin_load() {
        try {
            auto& plugin = potato_bonemeal_blocker::PotatoBoneMealBlocker::getInstance();
            return plugin.load();
        } catch (...) {
            return false;
        }
    }

    __declspec(dllexport) bool ll_plugin_unload() {
        try {
            auto& plugin = potato_bonemeal_blocker::PotatoBoneMealBlocker::getInstance();
            return plugin.disable();
        } catch (...) {
            return false;
        }
    }
}
