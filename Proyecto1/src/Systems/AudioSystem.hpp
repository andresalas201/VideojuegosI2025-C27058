/**
 * @file AudioSystem.hpp
 * @brief Audio system for managing music and sound effects using SDL2
 */

#ifndef AUDIOSYSTEM_HPP
#define AUDIOSYSTEM_HPP

#include <string>
#include <iostream>
#include "../ECS/ECS.hpp"
#include "../AssetManager/AssetManager.hpp"
#include "../Components/SoundComponent.hpp"

/**
 * @brief System responsible for audio playback including music and sound effects
 * 
 * The AudioSystem manages audio playback using SDL2's audio subsystem.
 * It supports both background music (single track) and multiple sound effects
 * that can be played simultaneously. The system handles loading, playing,
 * stopping, and looping of audio files in WAV format.
 */
class AudioSystem : public System {
private:
    SDL_AudioSpec audioSpec;     ///< Audio specification for music playback
    SDL_AudioDeviceID audioDevice; ///< Audio device ID for music
    SDL_AudioSpec soundSpec;     ///< Audio specification for sound effects
    SDL_AudioDeviceID soundDevice; ///< Audio device ID for sound effects

public:
    Uint8* audioBuffer;    ///< Buffer containing music audio data
    Uint32 audioLength;    ///< Length of the music audio buffer
    Uint32 audioPosition;  ///< Current playback position in music buffer
    Uint8* soundBuffer;    ///< Buffer containing sound effect audio data
    Uint32 soundLength;    ///< Length of the sound effect audio buffer
    Uint32 soundPosition;  ///< Current playback position in sound buffer
    bool isPlaying = false;      ///< Flag indicating if music is currently playing
    bool isPlayingSound = false; ///< Flag indicating if sound effects are playing

    /**
     * @brief Constructs the audio system and sets component requirements
     * 
     * Initializes the system to require SoundComponent for entities
     * that need audio functionality.
     */
    AudioSystem() {
        RequireComponent<SoundComponent>();
    }

    /**
     * @brief Initializes audio system buffers and state
     * 
     * Sets up initial state for all audio buffers and playback positions.
     * Should be called once during system initialization.
     */
    void Setup() {
        audioBuffer = NULL;
        audioLength = 0;
        audioPosition = 0;
        soundBuffer = NULL;
        soundLength = 0;
        soundPosition = 0;
    }

    /**
     * @brief Plays a sound effect
     * @param sound Pointer to the SoundStruct containing sound data and state
     * 
     * Plays the specified sound effect. If the sound is already playing,
     * it will be stopped first before restarting. Sound effects can play
     * concurrently with background music.
     */
    void playSound(SoundStruct* sound) {
        if(sound->isPlayingSound) stopSound(sound);
        std::cout << "[AUDIOSYSTEM] Se reproduce el sonido: " << sound->filePath.c_str() << std::endl;
        SDL_PauseAudioDevice(sound->soundDevice, 0);
        sound->isPlayingSound = true;
    }

    /**
     * @brief Stops a currently playing sound effect
     * @param sound Pointer to the SoundStruct to stop
     * 
     * Pauses the audio device and resets the playback position
     * for the specified sound effect.
     */
    void stopSound(SoundStruct* sound) {
        if (sound->isPlayingSound) {
            SDL_PauseAudioDevice(sound->soundDevice, 1);
            sound->soundPosition = 0;
            sound->isPlayingSound = false;
        }
    }

    /**
     * @brief Plays background music from a file
     * @param filePath Path to the WAV audio file to play
     * 
     * Loads and plays a music file. If music is already playing,
     * it will be stopped first. The music will loop automatically
     * when it reaches the end. Only supports WAV format files.
     */
    void playMusic(std::string filePath) {
        if(this->isPlaying) stopMusic();
        audioLength = 0;
        if (SDL_LoadWAV(filePath.c_str(), &audioSpec, &audioBuffer, &audioLength) == NULL) {
            std::cerr << "[AUDIOSYSTEM] Error al cargar musica: " << SDL_GetError() << std::endl;
            return;
        }
        audioSpec.callback = audioCallback;
        audioSpec.userdata = this;
        audioDevice = SDL_OpenAudioDevice(NULL, 0, &this->audioSpec, NULL, 0);
        std::cout << "[AUDIOSYSTEM] Se reproduce la cancion: " << filePath.c_str() << std::endl;
        SDL_PauseAudioDevice(audioDevice, 0);
        this->isPlaying = true;
    }

    /**
     * @brief Stops the currently playing background music
     * 
     * Closes the audio device, frees the audio buffer, and resets
     * all music-related state variables.
     */
    void stopMusic() {
        if(this->isPlaying) {
            SDL_CloseAudioDevice(audioDevice);
            SDL_FreeWAV(audioBuffer);
            audioBuffer = NULL;
            audioLength = 0;
            audioPosition = 0;
            this->isPlaying = false;
        }
    }

    /**
     * @brief Static callback function for SDL audio processing
     * @param voidSystem Pointer to the AudioSystem instance
     * @param stream Output audio stream to fill with audio data
     * @param len Length of the stream buffer to fill
     * 
     * This callback is called by SDL when more audio data is needed.
     * It copies audio data from the current buffer position to the
     * output stream and handles looping when the end is reached.
     */
    static void audioCallback(void* voidSystem, Uint8* stream, int len) {
        AudioSystem* audioSystem = static_cast<AudioSystem*>(voidSystem);
        if (audioSystem->audioBuffer == nullptr || audioSystem->audioLength == 0) {
            SDL_memset(stream, 0, len);
            return;
        }
        Uint32 remaining = audioSystem->audioLength - audioSystem->audioPosition;
        if (remaining > (Uint32)len) {
            remaining = len;
        }
        SDL_memcpy(stream, audioSystem->audioBuffer + audioSystem->audioPosition, remaining);
        audioSystem->audioPosition += remaining;
        if (audioSystem->audioPosition >= audioSystem->audioLength) {
            audioSystem->audioPosition = 0; // Loop audio
        }
    }
};

#endif // AUDIOSYSTEM_HPP