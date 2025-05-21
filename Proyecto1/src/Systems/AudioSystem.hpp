#ifndef AUDIOSYSTEM_HPP
#define AUDIOSYSTEM_HPP

#include <string>
#include <iostream>

#include "../ECS/ECS.hpp"
#include "../AssetManager/AssetManager.hpp"
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

        void playSound(SoundStruct* sound) {
            if(sound->isPlayingSound) stopSound(sound);
            
            std::cout << "[AUDIOSYSTEM] Se reproduce el sonido: " << sound->filePath.c_str() << std::endl;
            SDL_PauseAudioDevice(sound->soundDevice, 0);

            sound->isPlayingSound = true;
        }

        void stopSound(SoundStruct* sound) {
            if (sound->isPlayingSound) {
                SDL_PauseAudioDevice(sound->soundDevice, 1);
                sound->soundPosition = 0;
                sound->isPlayingSound = false;
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

        
};



#endif // AUDIOSYSTEM_HPP
