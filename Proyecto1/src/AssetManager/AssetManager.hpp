/**
 * @file AssetManager.hpp
 * @brief Asset management system for SDL2-based applications
 */

#ifndef ASSETMANAGER_HPP
#define ASSETMANAGER_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <map>
#include <string>

/**
 * @struct SoundStruct
 * @brief Structure containing audio data and playback state information
 * 
 * This structure encapsulates all necessary components for audio playback
 * including the audio buffer, device information, and current playback state.
 */
struct SoundStruct {
    std::string filePath;        ///< Path to the audio file
    SDL_AudioSpec soundSpec;     ///< Audio specification (format, frequency, channels, etc.)
    SDL_AudioDeviceID soundDevice; ///< SDL audio device identifier
    Uint8* soundBuffer;          ///< Raw audio data buffer
    Uint32 soundLength;          ///< Total length of audio data in bytes
    Uint32 soundPosition;        ///< Current playback position in bytes
    bool isPlayingSound;         ///< Flag indicating if sound is currently playing
};

/**
 * @class AssetManager
 * @brief Centralized asset management system for textures, fonts, and sounds
 * 
 * The AssetManager class provides a unified interface for loading, storing, and
 * accessing game assets including SDL2 textures, TTF fonts, and audio files.
 * Assets are stored in memory and accessed via string identifiers for efficient
 * resource management throughout the application lifecycle.
 * 
 * @note This class manages the lifetime of all loaded assets and handles
 *       proper cleanup when destroyed.
 */
class AssetManager {
private:
    std::map<std::string, SDL_Texture*> textures; ///< Map of texture ID to SDL_Texture pointer
    std::map<std::string, TTF_Font*> fonts;       ///< Map of font ID to TTF_Font pointer
    std::map<std::string, SoundStruct*> sounds;   ///< Map of sound ID to SoundStruct pointer

public:
    /**
     * @brief Default constructor
     * 
     * Initializes an empty AssetManager with no loaded assets.
     */
    AssetManager();

    /**
     * @brief Destructor
     * 
     * Automatically cleans up all loaded assets and frees associated memory.
     * Calls ClearAssets() to ensure proper resource deallocation.
     */
    ~AssetManager();

    /**
     * @brief Clears all loaded assets and frees associated memory
     * 
     * Destroys all textures, fonts, and sounds currently managed by this
     * AssetManager instance. This method is called automatically by the
     * destructor but can be called manually if needed.
     * 
     * @warning After calling this method, all previously obtained asset
     *          pointers become invalid and should not be used.
     */
    void ClearAssets();

    /**
     * @brief Loads and stores a texture from file
     * 
     * Creates an SDL_Texture from the specified image file and associates it
     * with the given identifier for future retrieval.
     * 
     * @param renderer SDL renderer used to create the texture
     * @param textureId Unique string identifier for the texture
     * @param filePath Path to the image file to load
     * 
     * @note If a texture with the same ID already exists, it will be replaced.
     * @warning The renderer must be valid and initialized before calling this method.
     */
    void AddTexture(SDL_Renderer* renderer, const std::string& textureId,
                    const std::string& filePath);

    /**
     * @brief Retrieves a previously loaded texture
     * 
     * Returns a pointer to the SDL_Texture associated with the given identifier.
     * 
     * @param textureId String identifier of the texture to retrieve
     * @return SDL_Texture* Pointer to the texture, or nullptr if not found
     * 
     * @note The returned pointer is owned by the AssetManager and should not be
     *       freed by the caller.
     */
    SDL_Texture* GetTexture(const std::string& textureId);

    /**
     * @brief Loads and stores a font from file
     * 
     * Creates a TTF_Font from the specified font file with the given size
     * and associates it with the provided identifier.
     * 
     * @param fontId Unique string identifier for the font
     * @param filePath Path to the font file to load
     * @param fontSize Size of the font in points
     * 
     * @note If a font with the same ID already exists, it will be replaced.
     * @warning TTF must be initialized before calling this method.
     */
    void AddFont(const std::string& fontId, const std::string& filePath,
                 int fontSize);

    /**
     * @brief Retrieves a previously loaded font
     * 
     * Returns a pointer to the TTF_Font associated with the given identifier.
     * 
     * @param fontId String identifier of the font to retrieve
     * @return TTF_Font* Pointer to the font, or nullptr if not found
     * 
     * @note The returned pointer is owned by the AssetManager and should not be
     *       freed by the caller.
     */
    TTF_Font* GetFont(const std::string& fontId);

    /**
     * @brief Loads and stores an audio file
     * 
     * Creates a SoundStruct containing all necessary audio data and playback
     * information from the specified audio file and associates it with the
     * given identifier.
     * 
     * @param soundId Unique string identifier for the sound
     * @param filePath Path to the audio file to load
     * 
     * @note If a sound with the same ID already exists, it will be replaced.
     * @warning SDL Audio must be initialized before calling this method.
     */
    void AddSound(const std::string& soundId, const std::string& filePath);

    /**
     * @brief Retrieves a previously loaded sound
     * 
     * Returns a pointer to the SoundStruct associated with the given identifier.
     * The returned structure contains all audio data and playback state information.
     * 
     * @param soundId String identifier of the sound to retrieve
     * @return SoundStruct* Pointer to the sound structure, or nullptr if not found
     * 
     * @note The returned pointer is owned by the AssetManager and should not be
     *       freed by the caller. The SoundStruct can be used to control audio
     *       playback and query playback state.
     */
    SoundStruct* GetSound(const std::string& soundId);
};

#endif // ASSETMANAGER_HPP