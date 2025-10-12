//
//  v_bridge.c
//  SchedulingiOS
//
//  Created by Srevrtt on 10/4/25.
//

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

#include "include/api.h"
#include "include/objc_bridge.h"

#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>

#define FONT_ARR_SIZE 20
#define STATIC_TEXT_ARR_SIZE 100

typedef struct {
    TTF_Font *fonts[FONT_ARR_SIZE];
    int fonts_count;
} font_arr;

typedef struct {
    SDL_Texture *text_objs[STATIC_TEXT_ARR_SIZE];
    int *text_sizes[STATIC_TEXT_ARR_SIZE];
    int text_count;
} text_arr;

static font_arr ttf_fonts;
static text_arr static_text;

static SDL_Window *window;
static SDL_Renderer *renderer;
static SDL_Event event;

// Helper functions
static void err(const char *str) {
    printf("%s: %s\n", str, SDL_GetError());
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, str, SDL_GetError(), NULL);
    exit(1);
}

void init_sdl(void) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        err("Could not initialize SDL2!");
    }
    
    if (TTF_Init() < 0) {
        err("Could not initialize SDL2_ttf!");
    }
    
    SDL_SetHint(SDL_HINT_ORIENTATIONS, "Portrait");    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    
    window = SDL_CreateWindow("Scheduling App - iOS", SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED, 2556, 1179,
                                          SDL_WINDOW_ALLOW_HIGHDPI);
    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                  SDL_RENDERER_PRESENTVSYNC);

    // Show the status bar (in objc_bridge.m)
    showStatusBar();
    
    // Initialize the arrays
    ttf_fonts.fonts_count = 0;
    static_text.text_count = 0;
}

void destroy_sdl(void) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void draw_rect(int x, int y, int w, int h, int r, int g, int b) {
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
    return ttf_fonts.fonts_count - 1;
}

// TODO: Static text rendering (not runtime)
void draw_text_runtime(int font_idx, const char *text, int x, int y, int r, int g, int b) {
    assert((font_idx >= 0) && (font_idx < ttf_fonts.fonts_count));

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

int create_static_text(const char *text, int font_size, int r, int g, int b) {
    // Make sure we have enough room in the array
    assert(static_text.text_count < STATIC_TEXT_ARR_SIZE);

    SDL_Color color = { r, g, b, 255 };

    SDL_Texture *texture = renderDefaultText(renderer, NULL, text, (float)font_size, color);

    // Append the text
    static_text.text_objs[static_text.text_count] = texture;
    
    // Get the text size
    int *size = malloc(2 * sizeof(int));
    int width, height = 0;
    SDL_QueryTexture(texture, NULL, NULL, &width, &height);

    size[0] = width;
    size[1] = height;

    static_text.text_sizes[static_text.text_count++] = size;
    return static_text.text_count - 1;
}

int *measure_static_text(int text_idx) {
    assert((text_idx >= 0) && (text_idx < static_text.text_count));
    return static_text.text_sizes[text_idx];
}

void draw_static_text(int text_idx, int x, int y) {
    assert((text_idx >= 0) && (text_idx < static_text.text_count));
    
    int *size = static_text.text_sizes[text_idx];
    SDL_Texture *texture = static_text.text_objs[text_idx];

    // Compute the offsets
    int *offsets = computeSafeAreaOffset();
    SDL_Rect dst = { x + offsets[0], y + offsets[1], size[0], size[1] };

    SDL_RenderCopy(renderer, texture, NULL, &dst);
}

void clear_text_arr(void) {
    static_text.text_count = 0;
}

int handle_app_events(int isCloseRequested) {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return false;
        }
    }
    
    return true;
}

void render_clear(void) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void render_present(void) {
    SDL_RenderPresent(renderer);
}
