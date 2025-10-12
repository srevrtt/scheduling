module scheduling

import ui

#include "../SchedulingiOS/SchedulingiOS/src/include/api.h"

fn C.draw_rect(x int, y int, w int, h int, r int, g int, b int)
fn C.create_font(font_name &char, font_size int) int
fn C.draw_text_runtime(font_idx int, text &char, x int, y int, r int, g int, b int)
fn C.draw_text_runtime_default(text &char, font_size int, x int, y int, r int, g int, b int)
fn C.handle_app_events(is_close_requested int) int
fn C.render_clear()
fn C.render_present()

pub struct SchedulingApp {
mut:
    layout ui.StackLayout
}

@[export: 'app_main']
fn app_main() {
    mut app := SchedulingApp{}
    app.layout = ui.create_stack_layout(10, 10)
    app.layout.add_text('Hello', 14, ui.color_white())

    mut run_app := true

    for run_app {
        run_app_int := C.handle_app_events(run_app)

        if run_app_int == 0 {
            run_app = false
        }

        // Rendering
        C.render_clear()
        C.render_present()
    }
}
