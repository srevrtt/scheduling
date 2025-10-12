//
//  v_bridge.h
//  SchedulingiOS
//
//  Created by Srevrtt on 10/4/25.
//

#ifndef V_BRIDGE_H
#define V_BRIDGE_H

void init_sdl(void);
void destroy_sdl(void);

void draw_rect(int x, int y, int w, int h, int r, int g, int b);
int create_font(const char *font_path, int font_size);
void draw_text_runtime(int font_idx, const char *text, int x, int y, int r, int g, int b);
void draw_text_runtime_default(const char *text, int font_size, int x, int y, int r, int g,
                               int b);
int create_static_text(const char *text, int font_size, int r, int g, int b);
int *measure_static_text(int text_idx);
void draw_static_text(int text_idx, int x, int y);
void clear_text_arr(void);

int handle_app_events(int isCloseRequested);
void render_clear(void);
void render_present(void);

#endif
