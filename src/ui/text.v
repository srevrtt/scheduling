module ui

pub struct Text {
	idx int
}

pub fn create_text(text string, font_size int, color Color) Text {
	return ui.Text{
		idx: C.create_static_text(text.str, font_size, color.r, color.g, color.b)
	}
}

pub fn (text Text) draw(x int, y int) {
	C.draw_static_text(text.idx, x, y)
}
