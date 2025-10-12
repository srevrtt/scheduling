module ui

pub struct Text {
pub:
	idx int
pub mut:
	x int
	y int
}

pub fn create_text(x int, y int, text string, font_size int, color Color) Text {
	return ui.Text{
		idx: C.create_static_text(text.str, font_size, color.r, color.g, color.b)
		x: x
		y: y
	}
}

pub fn (text Text) draw() {
	C.draw_static_text(text.idx, text.x, text.y)
}
