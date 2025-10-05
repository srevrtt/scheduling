//
//  objc_bridge.h
//  SchedulingiOS
//
//  Created by Srevrtt on 10/4/25.
//

#ifndef OBJC_BRIDGE_H
#define OBJC_BRIDGE_H

typedef struct TTF_Font TTF_Font;
typedef struct SDL_Renderer SDL_Renderer;
typedef struct SDL_Texture SDL_Texture;
typedef struct SDL_Color SDL_Color;

void showStatusBar(void);
TTF_Font *loadSystemFont(const char *name, int fontSize);
SDL_Texture *renderDefaultText(SDL_Renderer *renderer, const char *name, const char *text,
                               float size, SDL_Color color);
int *computeSafeAreaOffset(void);

#endif
