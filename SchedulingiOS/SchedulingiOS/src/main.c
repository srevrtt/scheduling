//
//  main.c
//  SchedulingiOS
//
//  Created by Srevrtt on 10/4/25.
//

#include <stdbool.h>

#include <SDL2/SDL.h>
#include "objc_bridge.h"

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    
    SDL_SetHint(SDL_HINT_ORIENTATIONS, "Portrait");
    
    SDL_Window *window = SDL_CreateWindow("Scheduling App - iOS", SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED, 640, 480,
                                          SDL_WINDOW_ALLOW_HIGHDPI);
    
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    
    // Set the window size
    int windowW, windowH = 0;
    SDL_GetWindowSize(window, &windowW, &windowH);
    SDL_RenderSetLogicalSize(renderer, windowW, windowH);
    
    showStatusBar();
    
    // App loop
    SDL_Event event;
    bool running = true;
    
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }
        
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 10, 10, 10, 255);
        SDL_RenderPresent(renderer);
        SDL_Delay(1);
    }

    // When the app is quit
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}
