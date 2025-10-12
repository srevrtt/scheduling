//
//  main.c
//  SchedulingiOS
//
//  Created by Srevrtt on 10/4/25.
//

#include <stdbool.h>

#include <SDL2/SDL.h>

#include "include/api.h"

// V functions
extern void app_main(void);

int main(int argc, char *argv[]) {
    init_sdl();
    app_main();
    destroy_sdl();
    return 0;
}
