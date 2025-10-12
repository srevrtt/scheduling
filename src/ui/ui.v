module ui

pub fn C.create_static_text(text &char, font_size int, r int, g int, b int) int
pub fn C.measure_static_text(text_idx int) &int
pub fn C.draw_static_text(text_idx int, x int, y int)
