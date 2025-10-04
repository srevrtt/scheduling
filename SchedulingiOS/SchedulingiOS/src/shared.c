//
//  shared.c
//  SchedulingiOS
//
//  Created by Srevrtt on 10/4/25.
//

#include <stdlib.h>

#include "include/shared.h"
#include "include/objc_bridge.h"

#include <SDL2/SDL.h>

// TODO: Globals are evil.
SDL_Window *wnd;
SDL_Renderer *ren;

// Helper function
static void err(const char *str) {
    printf("%s: %s\n", str, SDL_GetError());
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, str, SDL_GetError(), NULL);
    exit(1);
}

void initialize_sdl(void) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        err("Could not initialize SDL2!");
    }
    
    SDL_SetHint(SDL_HINT_ORIENTATIONS, "Portrait");
    
    wnd = SDL_CreateWindow("Scheduling App - iOS", SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED, 640, 480,
                                          SDL_WINDOW_ALLOW_HIGHDPI);
    
    ren = SDL_CreateRenderer(wnd, -1, 0);
    
    // Set the window size
    int windowW, windowH = 0;
    SDL_GetWindowSize(wnd, &windowW, &windowH);
    SDL_RenderSetLogicalSize(ren, windowW, windowH);
    
    // Show the status bar (in objc_bridge.m)
    showStatusBar();
}

void destroy_sdl(void) {
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(wnd);
    SDL_Quit();
}

SDL_Window *get_sdl_window(void) {
    return wnd;
}

SDL_Renderer *get_sdl_renderer(void) {
    return ren;
}
