module ui

pub enum StackLayoutAlignment {
	left
	center
	right
}

pub struct StackLayout {
mut:
	text_widgets []Text
	horizontal_orientation bool
	horizontal_direction bool
	margin int
	padding int
	x_ptr int
	y_ptr int
	alignment StackLayoutAlignment
}

pub fn create_stack_layout(margin int, padding int) StackLayout {
	return StackLayout{
		text_widgets: []Text{}
		horizontal_orientation: false
		horizontal_direction: false
		margin: margin
		padding: padding
		x_ptr: 0
		y_ptr: margin
		alignment: .left
	}
}

pub fn (mut layout StackLayout) add_text(text_string string, font_size int, color Color) {
	mut x_pos := 0
	mut y_pos := 0

	mut text := create_text(0, 0, text_string, font_size, color)
	measure_ptr := C.measure_static_text(text.idx)
	mut measured_text := [2]int{}

	// Convert the C pointer into a V array
	unsafe {
		measured_text[0] = measure_ptr[0]
		measured_text[1] = measure_ptr[1]
	}

	if !layout.horizontal_direction {
		match layout.alignment {
			.left {
				x_pos = layout.margin
			}
			.center {
			}
			.right {
			}
		}

		y_pos = layout.y_ptr
		layout.y_ptr += layout.margin + measured_text[1]
	}

	text.x = x_pos
	text.y = y_pos

	layout.text_widgets << text
}

pub fn (layout StackLayout) draw() {
	for text in layout.text_widgets {
		text.draw()
	}
}
