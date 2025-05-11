#ifndef AUDIOSYSTEM_HPP
#define AUDIOSYSTEM_HPP

#include <string>
#include <iostream>

#include "../ECS/ECS.hpp"
#include "../Components/SoundComponent.hpp"

class AudioSystem : public System {
    
    private:
    
        SDL_AudioSpec audioSpec;
        SDL_AudioDeviceID audioDevice;

        SDL_AudioSpec soundSpec;
        SDL_AudioDeviceID soundDevice;

    public:

        Uint8* audioBuffer;
        Uint32 audioLength;
        Uint32 audioPosition;

        Uint8* soundBuffer;
        Uint32 soundLength;
        Uint32 soundPosition;

        bool isPlaying = false;
        bool isPlayingSound = false;
        
        AudioSystem() {
            RequireComponent<SoundComponent>();
        }

        void Setup() {
            audioBuffer = NULL;
            audioLength = 0;
            audioPosition = 0;
            soundBuffer = NULL;
            soundLength = 0;
            soundPosition = 0;
        }

        void playSound(std::string filePath) {
            if(this->isPlayingSound) stopSound();

            soundLength = 0;
            if (SDL_LoadWAV(filePath.c_str(), &soundSpec, &soundBuffer, &soundLength) == NULL) {
                std::cerr << "[AUDIOSYSTEM] Error al cargar sonido: " << SDL_GetError() << std::endl;
                return;
            }
            soundSpec.callback = soundCallback;
            soundSpec.userdata = this;
            
            soundDevice = SDL_OpenAudioDevice(NULL, 0, &this->soundSpec, NULL, 0);
            std::cout << "[AUDIOSYSTEM] Se reproduce el sonido: " << filePath.c_str() << std::endl;
            SDL_PauseAudioDevice(soundDevice, 0);

            this->isPlayingSound = true;
        }

        void stopSound() {
            if (this->isPlayingSound) {
                SDL_CloseAudioDevice(soundDevice);
                SDL_FreeWAV(soundBuffer);
                soundBuffer = NULL;
                soundLength = 0;
                soundPosition = 0;
                this->isPlayingSound = false;
            }
        }

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

        static void soundCallback(void* voidSystem, Uint8* stream, int len) {
            AudioSystem* audioSystem = static_cast<AudioSystem*>(voidSystem);
            if (audioSystem->soundBuffer == nullptr || audioSystem->soundLength == 0) {
                SDL_memset(stream, 0, len);
                return;
            }
        
            Uint32 remaining = audioSystem->soundLength - audioSystem->soundPosition;
            if (remaining > (Uint32)len) {
                remaining = len;
            }
        
            SDL_memcpy(stream, audioSystem->soundBuffer + audioSystem->soundPosition, remaining);
            audioSystem->soundPosition += remaining;
        }
};



#endif // AUDIOSYSTEM_HPP
