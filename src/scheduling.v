module scheduling

#include "../SchedulingiOS/SchedulingiOS/src/include/v_bridge.h"

fn C.draw_rect(x int, y int, w int, h int, r int, g int, b int)
fn C.create_font(font_name &char, font_size int) int
fn C.draw_text_runtime(font_idx int, text &char, x int, y int, r int, g int, b int)
fn C.draw_text_runtime_default(text &char, font_size int, x int, y int, r int, g int, b int)

@[export: 'app_init']
fn app_init() {
}

@[export: 'app_loop']
fn app_loop() {
  C.draw_text_runtime_default(c"Hello iOS! This is so annoying :(", 20, 10, 10, 255, 255, 255)
}
