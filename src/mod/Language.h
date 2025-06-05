#pragma once

#include <string>
#include <unordered_map>
#include <string_view>

namespace potato_bonemeal_blocker {

/**
 * @brief Language support for the Potato Bonemeal Blocker plugin
 * 
 * Provides localized messages for Chinese and English languages.
 * Default language is Chinese (Simplified) for Chinese Minecraft servers.
 */
class Language {
public:
    enum class LanguageCode {
        CHINESE_SIMPLIFIED,  // zh_CN - Default for Chinese servers
        ENGLISH             // en_US - Fallback language
    };

    /**
     * @brief Get the singleton instance of Language
     * @return Reference to the Language instance
     */
    static Language& getInstance() noexcept;

    /**
     * @brief Set the current language
     * @param language The language code to use
     */
    void setLanguage(LanguageCode language) noexcept;

    /**
     * @brief Get the current language
     * @return Current language code
     */
    LanguageCode getCurrentLanguage() const noexcept;

    /**
     * @brief Get a localized message by key
     * @param key The message key
     * @return Localized message string
     */
    std::string_view getMessage(std::string_view key) const noexcept;

    /**
     * @brief Get the blocked message for display to players
     * @return Localized blocked message with formatting
     */
    std::string getBlockedMessage() const noexcept;

    /**
     * @brief Get the info message for display to players
     * @return Localized info message with formatting
     */
    std::string getInfoMessage() const noexcept;

    /**
     * @brief Get the plugin loading message
     * @return Localized loading message
     */
    std::string getLoadingMessage() const noexcept;

    /**
     * @brief Get the plugin enabled message
     * @return Localized enabled message
     */
    std::string getEnabledMessage() const noexcept;

    /**
     * @brief Get the compatibility message
     * @return Localized compatibility message
     */
    std::string getCompatibilityMessage() const noexcept;

private:
    Language() noexcept;
    ~Language() = default;
    Language(const Language&) = delete;
    Language& operator=(const Language&) = delete;

    void initializeMessages() noexcept;

    LanguageCode mCurrentLanguage;
    std::unordered_map<std::string, std::unordered_map<LanguageCode, std::string>> mMessages;
};

} // namespace potato_bonemeal_blocker
