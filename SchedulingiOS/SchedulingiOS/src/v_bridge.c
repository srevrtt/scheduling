//
//  v_bridge.c
//  SchedulingiOS
//
//  Created by Srevrtt on 10/4/25.
//

#include <stdlib.h>

#include "include/v_bridge.h"
#include "include/shared.h"

#include <SDL2/SDL.h>

void draw_rect(int x, int y, int w, int h, int r, int g, int b) {
    SDL_Renderer *renderer = get_sdl_renderer();
    SDL_Rect rect = { x, y + 44, w, h }; // Offset the y by 44px for the system bar
    
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderFillRect(renderer, &rect);
}
