module scheduling

#include "../SchedulingiOS/SchedulingiOS/src/include/v_bridge.h"

fn C.draw_rect(x int, y int, w int, h int, r int, g int, b int)
fn C.create_font(font_path &char, font_size int) int
fn C.draw_text_runtime(font_idx int, text &char, x int, y int, r int, g int, b int)

@[export: 'app_init']
fn app_init() {
  println('hello world!')
}

@[export: 'app_loop']
fn app_loop() {
	C.draw_rect(10, 10, 100, 100, 150, 150, 150)
}
