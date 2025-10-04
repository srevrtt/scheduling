module scheduling

// square calculates the second power of `x`
@[export: 'sch_square']
pub fn square(x int) int {
	return x * x
}

@[export: 'sch_add']
pub fn add(x int, y int) int {
	return x + y
}
