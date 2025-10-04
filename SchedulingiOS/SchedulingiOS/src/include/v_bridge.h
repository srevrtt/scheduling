//
//  v_bridge.h
//  SchedulingiOS
//
//  Created by Srevrtt on 10/4/25.
//

#ifndef V_BRIDGE_H
#define V_BRIDGE_H

void draw_rect(int x, int y, int w, int h, int r, int g, int b);
int create_font(const char *font_path, int font_size);
void draw_text_runtime(int font_idx, const char *text, int x, int y, int r, int g, int b);

#endif
