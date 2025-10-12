module ui

pub struct Color {
pub mut:
	r int
	g int
	b int
}

pub fn create_color_from_rgb(r int, g int, b int) Color {
	return Color{
		r, g, b
	}
}

pub fn color_white() Color {
	return Color{
		255, 255, 255
	}
}
