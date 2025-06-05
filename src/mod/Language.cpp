#include "Language.h"
#include <sstream>

namespace potato_bonemeal_blocker {

Language& Language::getInstance() noexcept {
    static Language instance;
    return instance;
}

Language::Language() noexcept : mCurrentLanguage(LanguageCode::CHINESE_SIMPLIFIED) {
    initializeMessages();
}

void Language::setLanguage(LanguageCode language) noexcept {
    mCurrentLanguage = language;
}

Language::LanguageCode Language::getCurrentLanguage() const noexcept {
    return mCurrentLanguage;
}

void Language::initializeMessages() noexcept {
    // Blocked message - shown to players when bone meal is blocked
    mMessages["blocked_message"] = {
        {LanguageCode::CHINESE_SIMPLIFIED, "§c骨粉不能用于土豆作物！"},
        {LanguageCode::ENGLISH, "§cBone meal cannot be used on potato crops!"}
    };

    // Info message - additional information for players
    mMessages["info_message"] = {
        {LanguageCode::CHINESE_SIMPLIFIED, "§e你仍然可以在其他作物上使用骨粉。"},
        {LanguageCode::ENGLISH, "§eYou can still use bone meal on other crops."}
    };

    // Plugin loading message
    mMessages["loading"] = {
        {LanguageCode::CHINESE_SIMPLIFIED, "正在加载土豆骨粉阻止器 v1.1.0..."},
        {LanguageCode::ENGLISH, "Loading Potato Bone Meal Blocker v1.1.0..."}
    };

    // Plugin enabled message
    mMessages["enabled"] = {
        {LanguageCode::CHINESE_SIMPLIFIED, "土豆骨粉阻止器已成功启用！"},
        {LanguageCode::ENGLISH, "Potato Bone Meal Blocker enabled successfully!"}
    };

    // Compatibility message
    mMessages["compatibility"] = {
        {LanguageCode::CHINESE_SIMPLIFIED, "兼容 LeviLamina 3 v1.2.0"},
        {LanguageCode::ENGLISH, "Compatible with LeviLamina 3 v1.2.0"}
    };

    // Performance optimization message
    mMessages["optimization"] = {
        {LanguageCode::CHINESE_SIMPLIFIED, "插件已初始化，具有优化的性能特性"},
        {LanguageCode::ENGLISH, "Plugin initialized with optimized performance features"}
    };

    // Event listener registration message
    mMessages["listener_registered"] = {
        {LanguageCode::CHINESE_SIMPLIFIED, "已为 PlayerInteractBlockEvent 注册事件监听器"},
        {LanguageCode::ENGLISH, "Event listener registered for PlayerInteractBlockEvent"}
    };

    // Statistics message
    mMessages["blocked_attempt_log"] = {
        {LanguageCode::CHINESE_SIMPLIFIED, "阻止了 {} 在位置 ({}, {}, {}) 对土豆作物使用骨粉"},
        {LanguageCode::ENGLISH, "Prevented {} from using bone meal on potato crop at ({}, {}, {})"}
    };

    // Plugin disable message
    mMessages["disabled"] = {
        {LanguageCode::CHINESE_SIMPLIFIED, "土豆骨粉阻止器已禁用"},
        {LanguageCode::ENGLISH, "Potato Bone Meal Blocker disabled"}
    };

    // Error messages
    mMessages["error_generic"] = {
        {LanguageCode::CHINESE_SIMPLIFIED, "插件运行时发生错误"},
        {LanguageCode::ENGLISH, "An error occurred while running the plugin"}
    };
}

std::string_view Language::getMessage(std::string_view key) const noexcept {
    const auto keyStr = std::string(key);
    const auto messageIt = mMessages.find(keyStr);
    
    if (messageIt != mMessages.end()) {
        const auto& languageMap = messageIt->second;
        const auto langIt = languageMap.find(mCurrentLanguage);
        
        if (langIt != languageMap.end()) {
            return langIt->second;
        }
        
        // Fallback to English if current language not found
        const auto englishIt = languageMap.find(LanguageCode::ENGLISH);
        if (englishIt != languageMap.end()) {
            return englishIt->second;
        }
    }
    
    // Ultimate fallback
    return "Message not found";
}

std::string Language::getBlockedMessage() const noexcept {
    return std::string(getMessage("blocked_message"));
}

std::string Language::getInfoMessage() const noexcept {
    return std::string(getMessage("info_message"));
}

std::string Language::getLoadingMessage() const noexcept {
    return std::string(getMessage("loading"));
}

std::string Language::getEnabledMessage() const noexcept {
    return std::string(getMessage("enabled"));
}

std::string Language::getCompatibilityMessage() const noexcept {
    return std::string(getMessage("compatibility"));
}

} // namespace potato_bonemeal_blocker
