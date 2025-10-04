//
//  main.c
//  SchedulingiOS
//
//  Created by Srevrtt on 10/4/25.
//

#include <stdbool.h>

#include <SDL2/SDL.h>

#include "include/shared.h"
#include "objc_bridge.h"

// V functions
extern void app_init(void);
extern void app_loop(void);

int main(int argc, char *argv[]) {
    initialize_sdl();
    
    app_init();
    
    // App loop
    SDL_Event event;
    bool running = true;
    
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }
        
        SDL_Renderer *renderer = get_sdl_renderer();
        
        SDL_SetRenderDrawColor(renderer, 10, 10, 10, 255);
        SDL_RenderClear(renderer);
        app_loop(); // Called in V
        SDL_RenderPresent(renderer);

        SDL_Delay(1);
    }

    destroy_sdl();
    
    return 0;
}
