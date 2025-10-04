//
//  shared.h
//  SchedulingiOS
//
//  Created by Srevrtt on 10/4/25.
//

#ifndef SHARED_H
#define SHARED_H

typedef struct SDL_Window SDL_Window;
typedef struct SDL_Renderer SDL_Renderer;

void initialize_sdl(void);
void destroy_sdl(void);

SDL_Window *get_sdl_window(void);
SDL_Renderer *get_sdl_renderer(void);

#endif
