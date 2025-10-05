//
//  v_bridge.c
//  SchedulingiOS
//
//  Created by Srevrtt on 10/4/25.
//

#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "include/v_bridge.h"
#include "include/objc_bridge.h"
#include "include/shared.h"

#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>

#define FONT_ARR_SIZE 20

typedef struct {
    TTF_Font *fonts[FONT_ARR_SIZE];
    int fonts_count;
} font_arr;

static font_arr ttf_fonts;

void draw_rect(int x, int y, int w, int h, int r, int g, int b) {
    SDL_Renderer *renderer = get_sdl_renderer();
    
    int *offsets = computeSafeAreaOffset();
    SDL_Rect rect = { x + offsets[0], y + offsets[1], w, h };
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderFillRect(renderer, &rect);
}

int create_font(const char *font_name, int font_size) {
    // Make sure we have enough room in the array
    assert(ttf_fonts.fonts_count < FONT_ARR_SIZE);

    TTF_Font *font = loadSystemFont(font_name, font_size);
    
    if (font == NULL) {
        fprintf(stderr, "Failed to open font at path %s.\n", font_name);
        exit(EXIT_FAILURE);
    }
    
    ttf_fonts.fonts[ttf_fonts.fonts_count++] = font;
    return ttf_fonts.fonts_count;
}

// TODO: Static text rendering (not runtime)
void draw_text_runtime(int font_idx, const char *text, int x, int y, int r, int g, int b) {
    assert((font_idx >= 0) && (font_idx < ttf_fonts.fonts_count));
    
    SDL_Renderer *renderer = get_sdl_renderer();

    // Render the text
    SDL_Color color = { r, g, b };
    SDL_Surface *surface = TTF_RenderText_Blended(ttf_fonts.fonts[font_idx], text, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    
    // Get the rendered text size in pixels
    int width, height = 0;
    SDL_QueryTexture(texture, NULL, NULL, &width, &height);
    
    int *offsets = computeSafeAreaOffset();
    SDL_Rect dstrect = { x + offsets[0], y + offsets[1], width, height };
    
    // Render the text
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);
    
    // Free the memory we don't need
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

// Renders text to the screen using the iOS default system font, rather than a custom
// specified font (SF Pro).
void draw_text_runtime_default(const char *text, int font_size, int x, int y, int r, int g,
                              int b) {
    SDL_Color color = { r, g, b, 255 };
    SDL_Renderer *renderer = get_sdl_renderer();

    SDL_Texture *texture = renderDefaultText(renderer, NULL, text,
                                             (float)font_size, color);

    // Draw the text
    int width, height = 0;
    SDL_QueryTexture(texture, NULL, NULL, &width, &height);
    
    int *offsets = computeSafeAreaOffset();
    SDL_Rect dst = { x + offsets[0], y + offsets[1], width, height };
    SDL_RenderCopy(renderer, texture, NULL, &dst);
    
    // Free memory
    SDL_DestroyTexture(texture);
}
