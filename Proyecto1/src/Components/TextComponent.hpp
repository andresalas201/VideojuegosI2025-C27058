#ifndef TEXTCOMPONENT_HPP
#define TEXTCOMPONENT_HPP
#include <SDL2/SDL.h>
#include <string>

/**
 * @brief A component for storing text rendering properties and metadata.
 * 
 * TextComponent encapsulates all the necessary information for rendering text,
 * including the text content, font identification, color settings, and dimensions.
 * This struct is typically used in entity-component systems for text rendering.
 */
struct TextComponent {
    /** @brief The text content to be rendered */
    std::string text;
    
    /** @brief Identifier for the font to be used for rendering */
    std::string fontId;
    
    /** @brief SDL color structure defining the text color (RGBA) */
    SDL_Color color;
    
    /** @brief Width of the rendered text in pixels */
    int width;
    
    /** @brief Height of the rendered text in pixels */
    int height;
    
    /**
     * @brief Constructs a TextComponent with specified parameters.
     * 
     * Creates a TextComponent with the given text content, font identifier,
     * and color values. The width and height are initialized to 0 and should
     * be set after text rendering calculations.
     * 
     * @param text The text string to be rendered (default: empty string)
     * @param fontId The identifier for the font to use (default: empty string)
     * @param r Red component of the text color (0-255, default: 0)
     * @param g Green component of the text color (0-255, default: 0)
     * @param b Blue component of the text color (0-255, default: 0)
     * @param a Alpha (transparency) component of the text color (0-255, default: 0)
     */
    TextComponent(const std::string& text = "", const std::string& fontId = "",
                  u_char r = 0, u_char g = 0, u_char b = 0,
                  u_char a = 0) {
        this->text = text;
        this->fontId = fontId;
        this->color.r = r;
        this->color.g = g;
        this->color.b = b;
        this->color.a = a;
        this->width = 0;
        this->height = 0;
    }
};

#endif // TEXTCOMPONENT_HPP